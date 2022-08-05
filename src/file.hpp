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
        { DAT,          "pkgdat"    },
        { DAT_STRING,   "pkgdats"   },
        { MAP,          "pkgmap"    },
        { GEO,          "pkggeo"    },
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
        { ACTION_DATA,           "pkgacd"    },
        { AFFINITY_DATA,         "pkgafd"    },
        { APET_DATA,             "pkgapd"    },
        { CATALOG_DATA,          "pkgctd"    },
        { COMBO_DATA,            "pkgcbd"    },
        { EVENT_DATA,            "pkgevd"    },
        { ITEM_DATA,             "pkgimd"    },
        { ITEMCOLLECTION_DATA,   "pkgicd"    },
        { ITEMEXCHANGE_DATA,     "pkgixd"    },
        { ITEMFORTUNE_DATA,      "pkgifd"    },
        { JEWELCOMPOS_DATA,      "pkgjcd"    },
        { LACARETTE_DATA,        "pkglcd"    },
        { MAKEITEM_DATA,         "pkgmid"    },
        { NPC_DATA,              "pkgncd"    },
        { MOBHELP_DATA,          "pkgmhd"    },
        { NPCHELP_DATA,          "pkgnhd"    },
        { MOONSTONE_DATA,        "pkgmsd"    },
        { NOTICE_DATA,           "pkgntd"    },
        { OPTION_DATA,           "pkgotd"    },
        { PETAI_DATA,            "pkgpad"    },
        { QUEST_DATA,            "pkgqtd"    },
        { RAIDOBJECTLIST_DATA,   "pkgrld"    },
        { RAREOPTION_DATA,       "pkgrod"    },
        { SETITEM_DATA,          "pkgsid"    },
        { SHOP_DATA,             "pkgspd"    },
        { SKILL_DATA,            "pkgskd"    },
        { SPECIALSKILL_DATA,     "pkgssd"    },
        { CONTAINER_DATA,        "pkgscd"    },
        { TITLE_DATA,            "pkgttd"    },
        { ZONE_DATA,             "pkgznd"    },

        // string
        { ACTION_STRING,         "pkgacs"    },
        { AFFINITY_STRING,       "pkgafs"    },
        { CATALOG_STRING,        "pkgcts"    },
        { SYSTEM_STRING,         "pkgsys"    },
        { COMBO_STRING,          "pkgcbs"    },
        { HELP_STRING,           "pkghps"    },
        { ITEMCOLLECTION_STRING, "pkgics"    },
        { ITEM_STRING,           "pkgims"    },
        { LACARETTE_STRING,      "pkglrs"    },
        { NPC_STRING,            "pkgncs"    },
        { NPCHELP_STRING,        "pkgnhs"    },
        { NPCSHOP_STRING,        "pkgnss"    },
        { OPTION_STRING,         "pkgons"    },
        { QUEST_STRING,          "pkgqts"    },
        { RAREOPTION_STRING,     "pkgros"    },
        { SETITEM_STRING,        "pkgsis"    },
        { SKILL_STRING,          "pkgsks"    },
        { SPECIALSKILL_STRING,   "pkgsss"    }
    };

    std::map<std::string, File::ContainerType> FileMap
    {
        // data
        { "actions",            ACTION_DATA             },
        { "affinity",           AFFINITY_DATA           },
        { "bigpet",             APET_DATA               },
        { "catalog",            CATALOG_DATA            },
        { "combo",              COMBO_DATA              },
        { "event_usa",          EVENT_DATA              },
        { "itemAll",            ITEM_DATA               },
        { "itemCollection",     ITEMCOLLECTION_DATA     },
        { "item_exchange",      ITEMEXCHANGE_DATA       },
        { "itemFortune",        ITEMFORTUNE_DATA        },
        { "JewelCompos",        JEWELCOMPOS_DATA        },
        { "lacarette",          LACARETTE_DATA          },
        { "MakeItem_usa",       MAKEITEM_DATA           },
        { "mobAll",             NPC_DATA                },
        { "mobhelp",            MOBHELP_DATA            },
        { "npchelp",            NPCHELP_DATA            },
        { "moonstone",          MOONSTONE_DATA          },
        { "notice",             NOTICE_DATA             },
        { "option",             OPTION_DATA             },
        { "PetAI_usa",          PETAI_DATA              },
        { "questAll",           QUEST_DATA              },
        { "raidobjectlist",     RAIDOBJECTLIST_DATA     },
        { "rareoption",         RAREOPTION_DATA         },
        { "setItemALL",         SETITEM_DATA            },
        { "shopAll",            SHOP_DATA               },
        { "skills",             SKILL_DATA              },
        { "sskill",             SPECIALSKILL_DATA       },
        { "smc",                CONTAINER_DATA          },
        { "titletool",          TITLE_DATA              },
        { "ZoneFlag",           ZONE_DATA               },

        // string
        { "strAction",			ACTION_STRING           },
        { "strAffinity",		AFFINITY_STRING         },
        { "strCatalog",         CATALOG_STRING			},
        { "strClient",			SYSTEM_STRING           },
        { "strCombo",			COMBO_STRING            },
        { "strHelp",			HELP_STRING             },
        { "strItemCollection",	ITEMCOLLECTION_STRING   },
        { "strItem",			ITEM_STRING             },
        { "strLacarette",		LACARETTE_STRING        },
        { "strNPCHelp",         NPCHELP_STRING			},
        { "strNpcName",         NPC_STRING			    },
        { "strNPCShop",         NPCSHOP_STRING			},
        { "strOption",			OPTION_STRING			},
        { "strQuest",			QUEST_STRING            },
        { "strRareOption",		RAREOPTION_STRING		},
        { "strSetItem",         SETITEM_STRING			},
        { "strSkill",			SKILL_STRING            },
        { "strSSkill",			SPECIALSKILL_STRING     },
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