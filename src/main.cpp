
#include "file.hpp"

#include <zstd.h>
#include <xxhash32.h>
#include <json.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <format>

using json = nlohmann::json;

#define PACKAGE_COMPRESSION_LEVEL 1

auto compress(const char* input, const size_t size, int level)
{
	const size_t bound_size = ZSTD_compressBound(size);
	std::basic_string<char> block(bound_size, 0x0);

	const size_t compressed_size = ZSTD_compress(block.data(), block.size(), input, size, level);
	block.erase(block.begin() + compressed_size, block.end());

	return block;
}

auto decompress(const char* input, const size_t size)
{
	const size_t fsize = ZSTD_getFrameContentSize(input, size);
	std::basic_string<char> block(fsize, 0x0);
	const size_t block_size = ZSTD_decompress(block.data(), block.size(), input, size);

	return block;
}

std::string hash(std::string text)
{
	uint32_t seed = 0;
	uint32_t num = XXHash32::hash(text.c_str(), text.size(), seed);

	char hex_string[20];
	sprintf(hex_string, "%X", num);
	return hex_string;
}

static std::vector<char> ReadAllBytes(std::string fp)
{
	std::ifstream ifs(fp, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
}

std::vector<char> buf;

auto containerType = File::ContainerType::UNKNOWN_CONTAINER;

std::string chunkName;
std::string chunkNamePlain;
size_t chunkNameLength;

std::string data;
std::string data_compressed;
size_t data_compressed_size;

size_t container_size = 0;
size_t container_size_compressed = 0;

void build_container(std::fstream& ofs, File::Package pkg, std::filesystem::path fsp)
{
	std::string filePath = fsp.string();
	std::string fileName = fsp.filename().string();

	chunkNamePlain = File::TypeToChunkName(stringify(File::ContainerType), pkg.container.type);
	chunkName = hash(chunkNamePlain);
	chunkNameLength = chunkName.length();

	buf = ReadAllBytes(filePath);
	data = std::string(begin(buf), end(buf));

	if (pkg.container.data_type == File::ContainerDataType::JSON)
		data = json::parse(data).dump();

	pkg.container.data = data.c_str();
	pkg.container.size = data.size();

	container_size += pkg.container.size;

	data_compressed = compress(pkg.container.data, pkg.container.size, PACKAGE_COMPRESSION_LEVEL);
	data_compressed_size = data_compressed.size();

	container_size_compressed += data_compressed_size;

	ofs.write(reinterpret_cast<const char*>(&chunkNameLength), sizeof(chunkNameLength));
	ofs.write(chunkName.c_str(), chunkName.length());
	ofs.write(reinterpret_cast<const char*>(&pkg.container.data_type), sizeof(pkg.container.data_type));
	ofs.write(reinterpret_cast<const char*>(&data_compressed_size), sizeof(data_compressed_size));
	ofs.write(data_compressed.c_str(), data_compressed_size);

	std::cout << std::format("packing `{}`\t\t({} >> {}) [{} bytes >> {} bytes]", fileName, chunkNamePlain, chunkName, pkg.container.size, data_compressed_size) << std::endl;
}

void build_header(std::fstream& ofs, File::Package pkg, std::string chunkName)
{
	ofs.write(chunkName.c_str(), chunkName.length());
	ofs.write(reinterpret_cast<const char*>(&pkg.ver), sizeof(pkg.ver));
	ofs.write(reinterpret_cast<const char*>(&pkg.compress), sizeof(pkg.compress));
}

bool pack(File::Package pkg, std::string root)
{
	std::string pkgTypeText = File::TypeToChunkName(stringify(File::PackageType), pkg.type);
	auto ofs = std::fstream(pkgTypeText + ".pkg", std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		return false;

	build_header(ofs, pkg, pkgTypeText);

	auto workDir = (pkg.type == File::PackageType::DAT_STRING) ? "/local/us/string" : "/data";

	for (const auto& entry : std::filesystem::directory_iterator(root + workDir))
	{
		std::string filePath = entry.path().string();
		std::string fileName = entry.path().filename().string();

		std::string replaceData = pkg.type == File::PackageType::DAT_STRING ?
			(pkg.container.data_type == File::ContainerDataType::BINARY ? "_us.lod" : "_us.lod.json") :
			(pkg.container.data_type == File::ContainerDataType::BINARY ? ".lod" : ".lod.json");

		if (pkg.container.data_type == File::ContainerDataType::BINARY && fileName.find(".json") != std::string::npos)
			continue;

		if (fileName.find(replaceData) == std::string::npos)
			continue;

		fileName.replace(fileName.find(replaceData), std::string(replaceData).length(), "");

		containerType = File::ContainerType::UNKNOWN_CONTAINER;

		for (const auto& [key, value] : File::FileMap)
			if (key == fileName)
				containerType = value;

		pkg.container.type = containerType;

		if (containerType == File::ContainerType::UNKNOWN_CONTAINER)
		{
			std::cout << "Couldn't build " << fileName << " file container" << std::endl;
			continue;
		}

		build_container(ofs, pkg, filePath);

		//auto data_decompressed = decompress(data_compressed.c_str(), data_compressed.size());
		//std::cout << data_decompressed << std::endl;
		//std::ofstream(filePath + ".out", std::ios::binary).write(data_decompressed.c_str(), data_decompressed.length());
	}

	float percent = ((float)container_size - (float)container_size_compressed) / (float)container_size * 100;
	std::cout << std::format("\n[level {}] Overall reduced size: {}% ({} bytes >> {} bytes)\n", PACKAGE_COMPRESSION_LEVEL, round(percent), container_size, container_size_compressed);
	ofs.close();

	return true;
}

int main()
{
	File::Package pkg
	{
		.type = File::PackageType::DAT,
		.ver = 1,
		.compress = true,
		.container = {
			.data_type = File::ContainerDataType::BINARY
		}
	};

	pack(pkg, "C:/Users/Administrator/Desktop/ClientNov/");

	std::cout << "Press any key to exit..." << std::endl;
	std::getchar();

	return true;
}
