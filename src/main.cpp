
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

int main()
{
	std::string localizationRoot = "C:/Users/Administrator/Desktop/ClientNov/Local/us";

	std::map<std::string, File::ContainerType> FileMap
	{
		{ "strAction",			File::ContainerType::ACTION_STRING			},
		{ "strAffinity",		File::ContainerType::AFFINITY_STRING			},
		{ "strCatalog",			File::ContainerType::CATALOG_STRING			},
		{ "strClient",			File::ContainerType::SYSTEM_STRING			},
		{ "strCombo",			File::ContainerType::COMBO_STRING			},
		{ "strHelp",			File::ContainerType::HELP_STRING			},
		{ "strItemCollection",		File::ContainerType::ITEMCOLLECTION_STRING		},
		{ "strItem",			File::ContainerType::ITEM_STRING			},
		{ "strLacarette",		File::ContainerType::LACARETTE_STRING			},
		{ "strNPCHelp",			File::ContainerType::NPCHELP_STRING			},
		{ "strNpcName",			File::ContainerType::NPC_STRING				},
		{ "strNPCShop",			File::ContainerType::NPCSHOP_STRING			},
		{ "strOption",			File::ContainerType::OPTION_STRING			},
		{ "strQuest",			File::ContainerType::QUEST_STRING			},
		{ "strRareOption",		File::ContainerType::RAREOPTION_STRING			},
		{ "strSetItem",			File::ContainerType::SETITEM_STRING			},
		{ "strSkill",			File::ContainerType::SKILL_STRING			},
		{ "strSSkill",			File::ContainerType::SPECIALSKILL_STRING		}
	};

	File::Package pkg;

	pkg.type = File::PackageType::DAT_STRING;
	pkg.container_data_type = File::ContainerDataType::JSON;
	pkg.ver = 1;
	pkg.compress = true;

	std::string pkgTypeText = File::TypeToChunkName(stringify(File::PackageType), pkg.type);
	auto ofs = std::fstream(pkgTypeText + ".pkg", std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		return false;

	ofs.write(pkgTypeText.c_str(), pkgTypeText.length());
	ofs.write(reinterpret_cast<const char*>(&pkg.ver), sizeof(pkg.ver));
	ofs.write(reinterpret_cast<const char*>(&pkg.compress), sizeof(pkg.compress));

	std::string data;
	std::vector<char> buf;

	int all = 0;
	int all_compressed = 0;

	for (const auto& entry : std::filesystem::directory_iterator(localizationRoot + "/string"))
	{
		std::string filePath = entry.path().string();
		std::string fileName = entry.path().filename().string();
		std::string replaceData = pkg.container_data_type == File::ContainerDataType::BINARY ? "_us.lod" : "_us.lod.json";

		if (pkg.container_data_type == File::ContainerDataType::BINARY && fileName.find(".json") != std::string::npos)
			continue;

		if (fileName.find(replaceData) == std::string::npos)
			continue;
		
		fileName.replace(fileName.find(replaceData), std::string(replaceData).length(), "");

		File::ContainerType containerType = File::ContainerType::UNKNOWN_CONTAINER;

		for (const auto& [key, value] : FileMap)
			if (key == fileName)
				containerType = value;

		pkg.container_type = containerType;

		if (containerType == File::ContainerType::UNKNOWN_CONTAINER)
		{
			std::cout << "Couldn't pack " << fileName << " file" << std::endl;
			continue;
		}

		buf = ReadAllBytes(filePath);
		data = std::string(begin(buf), end(buf));

		if(pkg.container_data_type == File::ContainerDataType::JSON)
			data = json::parse(data).dump();

		pkg.container_data = data.c_str();
		pkg.container_size = data.size();

		all += pkg.container_size;

		std::string chunkNamePlain = File::TypeToChunkName(stringify(File::ContainerType), pkg.container_type);
		std::string chunkName = hash(chunkNamePlain);

		auto data_compressed = compress(pkg.container_data, pkg.container_size, PACKAGE_COMPRESSION_LEVEL);
		auto data_compressed_size = data_compressed.size();

		all_compressed += data_compressed_size;

		std::cout << std::format("Packing `{}`\t\t({} >> {}) [before: {} bytes, after: {} bytes]", fileName, chunkNamePlain, chunkName, pkg.container_size, data_compressed_size) << std::endl;

		ofs.write(chunkName.c_str(), chunkName.length());
		ofs.write(reinterpret_cast<const char*>(&pkg.container_data_type), sizeof(pkg.container_data_type));
		ofs.write(reinterpret_cast<const char*>(&data_compressed_size), sizeof(data_compressed_size));
		ofs.write(data_compressed.c_str(), data_compressed_size);

		//auto data_decompressed = decompress(data_compressed.c_str(), data_compressed.size());
		//std::cout << data_decompressed << std::endl;
	}

	float percent = ((float)all - (float)all_compressed) / (float)all * 100;
	std::cout << std::format("\nOverall reduced size: {}% ({} >> {})\n", round(percent), all, all_compressed);
	ofs.close();

	std::cout << "Press any key to exit..." << std::endl;
	std::getchar();

	return true;
}
