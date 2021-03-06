﻿class CfgPatches
{
    class adv_aceSplint
    {
        units[] = {
			"adv_aceSplint_splintItem"
		};
        weapons[] = {
			"adv_aceSplint_splint"
		};
        requiredVersion = 1.68;
        requiredAddons[] = {
			"ace_medical"
		};
		version = "1.0.1";
		versionStr = "1.0.1";
		author = "[SeL] Belbo // Adrian";
		authorUrl = "http://spezialeinheit-luchs.de/";
    };
};

#define MACRO_ADDITEM(ITEM,COUNT) class _xx_##ITEM { \
    name = #ITEM; \
    count = COUNT; \
}

class CfgFunctions {
	class adv_aceSplint {
		tag = "adv_aceSplint";
		class init {
			file = "adv_aceSplint\functions";
			class init { postInit = 1; };
			class canSplint {};
			class diag {};
			class splint_local {};
			class splint {};
		};
	};
};

class cfgWeapons {
	class ACE_ItemCore;
	class CBA_MiscItem_ItemInfo;
	
    class adv_aceSplint_splint: ACE_ItemCore {
        scope = 2;
        displayName = "$STR_ADV_ACESPLINT_DISPLAYNAME";
        descriptionShort = "$STR_ADV_ACESPLINT_DESCRIPTION";
        descriptionUse = "$STR_ADV_ACESPLINT_DESCRIPTION";
        picture = "\adv_aceSplint\ui\splint.paa";
        class ItemInfo: CBA_MiscItem_ItemInfo {
            mass = 3;
        };
	};
};

class cfgVehicles {
	class Item_Base_F;
	
	class adv_aceSplint_splintItem: Item_Base_F {
        scope = 2;
        scopeCurator = 2;
        displayName = "$STR_ADV_ACESPLINT_DISPLAYNAME";
        author = "[SeL] Belbo";
        vehicleClass = "Items";
        class TransportItems {
            MACRO_ADDITEM(adv_aceSplint_splint,1);
        };
	};
	
	//ace_medical_actions:
	class Man;
	class CAManBase: Man {
		class ACE_Actions {
			#define EXCEPTIONS exceptions[] = {};
			#include "ace_medical_actions.hpp"
			class ACE_MainActions {
				class Medical {
                    #undef EXCEPTIONS
                    #define EXCEPTIONS exceptions[] = {"isNotInside"};
					#include "ace_medical_actions.hpp"
				};
			};
		};
		class ACE_SelfActions {
			class Medical {
				#include "ace_medical_actions.hpp"
			};
		};
	};
};

class ACE_Medical_Actions {
	class Advanced {
		class fieldDressing;
		class splint: fieldDressing {
            displayName = "$STR_ADV_ACESPLINT_ACTION";
			displayNameProgress = "$STR_ADV_ACESPLINT_PROGRESS";
			items[] = {"adv_aceSplint_splint"};
			allowedSelections[] = {"hand_l", "hand_r", "leg_l", "leg_r"};
			condition = "[_this select 1, _this select 2] call adv_aceSplint_fnc_canSplint";
			allowSelfTreatment = 1;
			patientStateCondition = 1;
			treatmentTime = 8;
			requiredMedic = 0;
			itemConsumed = 1;
			callbackSuccess = "adv_aceSplint_fnc_splint";
		};
	};
};