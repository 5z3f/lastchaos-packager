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
        APET_DATA,
        ACTION_DATA,
        AFFINITY_DATA,
        CATALOG_DATA,
        COMBO_DATA,
        EVENT_DATA,
        ITEM_DATA,
        ITEMCOLLECTION_DATA,
        ITEMEXCHANGE_DATA,
        ITEMFORTUNE_DATA,
        JEWELCOMPOS_DATA,
        LACARETTE_DATA,
        MAKEITEM_DATA,
        NPC_DATA,
        MOBHELP_DATA,
        NPCHELP_DATA,
        MOONSTONE_DATA,
        NOTICE_DATA,
        OPTION_DATA,
        PETAI_DATA,
        QUEST_DATA,
        RAIDOBJECTLIST_DATA,
        RAREOPTION_DATA,
        SETITEM_DATA,
        SHOP_DATA,
        SKILL_DATA,
        SPECIALSKILL_DATA,
        CONTAINER_DATA,
        TITLE_DATA,
        ZONE_DATA,

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
        // data
        { ContainerType::ACTION_DATA,           "pkgacd"    },
        { ContainerType::AFFINITY_DATA,         "pkgafd"    },
        { ContainerType::APET_DATA,             "pkgapd"    },
        { ContainerType::CATALOG_DATA,          "pkgctd"    },
        { ContainerType::COMBO_DATA,            "pkgcbd"    },
        { ContainerType::EVENT_DATA,            "pkgevd"    },
        { ContainerType::ITEM_DATA,             "pkgimd"    },
        { ContainerType::ITEMCOLLECTION_DATA,   "pkgicd"    },
        { ContainerType::ITEMEXCHANGE_DATA,     "pkgixd"    },
        { ContainerType::ITEMFORTUNE_DATA,      "pkgifd"    },
        { ContainerType::JEWELCOMPOS_DATA,      "pkgjcd"    },
        { ContainerType::LACARETTE_DATA,        "pkglcd"    },
        { ContainerType::MAKEITEM_DATA,         "pkgmid"    },
        { ContainerType::NPC_DATA,              "pkgncd"    },
        { ContainerType::MOBHELP_DATA,          "pkgmhd"    },
        { ContainerType::NPCHELP_DATA,          "pkgnhd"    },
        { ContainerType::MOONSTONE_DATA,        "pkgmsd"    },
        { ContainerType::NOTICE_DATA,           "pkgntd"    },
        { ContainerType::OPTION_DATA,           "pkgotd"    },
        { ContainerType::PETAI_DATA,            "pkgpad"    },
        { ContainerType::QUEST_DATA,            "pkgqtd"    },
        { ContainerType::RAIDOBJECTLIST_DATA,   "pkgrld"    },
        { ContainerType::RAREOPTION_DATA,       "pkgrod"    },
        { ContainerType::SETITEM_DATA,          "pkgsid"    },
        { ContainerType::SHOP_DATA,             "pkgspd"    },
        { ContainerType::SKILL_DATA,            "pkgskd"    },
        { ContainerType::SPECIALSKILL_DATA,     "pkgssd"    },
        { ContainerType::CONTAINER_DATA,        "pkgscd"    },
        { ContainerType::TITLE_DATA,            "pkgttd"    },
        { ContainerType::ZONE_DATA,             "pkgznd"    },

        // string
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

    std::map<std::string, File::ContainerType> FileMap
    {
        // data
        { "actions",            File::ContainerType::ACTION_DATA            },
        { "affinity",           File::ContainerType::AFFINITY_DATA          },
        { "bigpet",             File::ContainerType::APET_DATA              },
        { "catalog",            File::ContainerType::CATALOG_DATA           },
        { "combo",              File::ContainerType::COMBO_DATA             },
        { "event_usa",          File::ContainerType::EVENT_DATA             },
        { "itemAll",			File::ContainerType::ITEM_DATA              },
        { "itemCollection",     File::ContainerType::ITEMCOLLECTION_DATA    },
        { "item_exchange",      File::ContainerType::ITEMEXCHANGE_DATA      },
        { "itemFortune",		File::ContainerType::ITEMFORTUNE_DATA       },
        { "JewelCompos",		File::ContainerType::JEWELCOMPOS_DATA       },
        { "lacarette",			File::ContainerType::LACARETTE_DATA         },
        { "MakeItem_usa",		File::ContainerType::MAKEITEM_DATA          },
        { "mobAll",				File::ContainerType::NPC_DATA               },
        { "mobhelp",			File::ContainerType::MOBHELP_DATA           },
        { "npchelp",			File::ContainerType::NPCHELP_DATA           },
        { "moonstone",			File::ContainerType::MOONSTONE_DATA         },
        { "notice",				File::ContainerType::NOTICE_DATA            },
        { "option",				File::ContainerType::OPTION_DATA            },
        { "PetAI_usa",			File::ContainerType::PETAI_DATA             },
        { "questAll",			File::ContainerType::QUEST_DATA             },
        { "raidobjectlist",		File::ContainerType::RAIDOBJECTLIST_DATA    },
        { "rareoption",		    File::ContainerType::RAREOPTION_DATA        },
        { "setItemALL",		    File::ContainerType::SETITEM_DATA           },
        { "shopAll",		    File::ContainerType::SHOP_DATA              },
        { "skills",		        File::ContainerType::SKILL_DATA             },
        { "sskill",		        File::ContainerType::SPECIALSKILL_DATA      },
        { "smc",		        File::ContainerType::CONTAINER_DATA         },
        { "titletool",		    File::ContainerType::TITLE_DATA             },
        { "ZoneFlag",		    File::ContainerType::ZONE_DATA              },

        // string
        { "strAction",			File::ContainerType::ACTION_STRING          },
        { "strAffinity",		File::ContainerType::AFFINITY_STRING        },
        { "strCatalog",			File::ContainerType::CATALOG_STRING			},
        { "strClient",			File::ContainerType::SYSTEM_STRING			},
        { "strCombo",			File::ContainerType::COMBO_STRING           },
        { "strHelp",			File::ContainerType::HELP_STRING            },
        { "strItemCollection",	File::ContainerType::ITEMCOLLECTION_STRING  },
        { "strItem",			File::ContainerType::ITEM_STRING            },
        { "strLacarette",		File::ContainerType::LACARETTE_STRING       },
        { "strNPCHelp",			File::ContainerType::NPCHELP_STRING			},
        { "strNpcName",			File::ContainerType::NPC_STRING				},
        { "strNPCShop",			File::ContainerType::NPCSHOP_STRING			},
        { "strOption",			File::ContainerType::OPTION_STRING			},
        { "strQuest",			File::ContainerType::QUEST_STRING           },
        { "strRareOption",		File::ContainerType::RAREOPTION_STRING		},
        { "strSetItem",			File::ContainerType::SETITEM_STRING			},
        { "strSkill",			File::ContainerType::SKILL_STRING           },
        { "strSSkill",			File::ContainerType::SPECIALSKILL_STRING    },
    };

    struct Package
    {
        PackageType type;
        int ver;
        bool compress;
        struct Container {
            ContainerDataType data_type;
            ContainerType type;
            const char* data;
            size_t size;
        };
        Container container;
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