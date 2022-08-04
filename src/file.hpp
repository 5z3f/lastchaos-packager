#pragma once

#include <string>
#include <map>
#include <iostream>

namespace File
{
    #define stringify(x) #x

    enum PackageType
    {
        DAT,        // data
        DAT_STRING, // data string
        MAP,        // worlds
        GEO,        // 3d containers
        UNKNOWN
    };

    std::map<File::PackageType, std::string> PackageTypeMap
    {
        { PackageType::DAT,         "pkgdat"    },
        { PackageType::DAT_STRING,  "pkgdats"   },
        { PackageType::MAP,         "pkgmap"    },
        { PackageType::GEO,         "pkggeo"    },
        // audio ?
    };

    enum ContainerType
    {
        ITEM_DATA,
        NPC_DATA,

        ACTION_STRING,
        AFFINITY_STRING,
        CATALOG_STRING,
        SYSTEM_STRING,
        COMBO_STRING,
        HELP_STRING,
        ITEMCOLLECTION_STRING,
        ITEM_STRING,
        LACARETTE_STRING,
        NPC_STRING,
        NPCHELP_STRING,
        NPCSHOP_STRING,
        OPTION_STRING,
        QUEST_STRING,
        RAREOPTION_STRING,
        SETITEM_STRING,
        SKILL_STRING,
        SPECIALSKILL_STRING,

        UNKNOWN_CONTAINER
    };

    enum ContainerDataType
    {
        BINARY,
        JSON
    };

    std::map<ContainerType, std::string> ContainerTypeMap
    {
        { ContainerType::ACTION_STRING,         "pkgacs"    },
        { ContainerType::AFFINITY_STRING,       "pkgafs"    },
        { ContainerType::CATALOG_STRING,        "pkgcts"    },
        { ContainerType::SYSTEM_STRING,         "pkgsys"    },
        { ContainerType::COMBO_STRING,          "pkgcbs"    },
        { ContainerType::HELP_STRING,           "pkghps"    },
        { ContainerType::ITEMCOLLECTION_STRING, "pkgics"    },
        { ContainerType::ITEM_STRING,           "pkgims"    },
        { ContainerType::LACARETTE_STRING,      "pkglrs"    },
        { ContainerType::NPC_STRING,            "pkgncs"    },
        { ContainerType::NPCHELP_STRING,        "pkgnhs"    },
        { ContainerType::NPCSHOP_STRING,        "pkgnss"    },
        { ContainerType::OPTION_STRING,         "pkgons"    },
        { ContainerType::QUEST_STRING,          "pkgqts"    },
        { ContainerType::RAREOPTION_STRING,     "pkgros"    },
        { ContainerType::SETITEM_STRING,        "pkgsis"    },
        { ContainerType::SKILL_STRING,          "pkgsks"    },
        { ContainerType::SPECIALSKILL_STRING,   "pkgsss"    }
    };

    struct Package
    {
        PackageType type;
        int ver;
        bool compress;
        ContainerType container_type;
        ContainerDataType container_data_type;
        const char* container_data;
        size_t container_size;
    };

    std::string TypeToChunkName(std::string type, auto k)
    {
        std::string chunkName;

        if (type == "File::PackageType")
        {
            for (const auto& [key, value] : File::PackageTypeMap)
                if (key == k)
                    chunkName = value;
        }
        else if (type == "File::ContainerType")
        {
            for (const auto& [key, value] : File::ContainerTypeMap)
                if (key == k)
                    chunkName = value;
        }

        return chunkName;
    };

};