#pragma once

class AimbotTab : public Tab {
public:
	// col1.
	Checkbox	  enable;
	Checkbox	  silent;
	Dropdown	  selection;
	Dropdown	  weapon_select;
	MultiDropdown hitbox_general;
	MultiDropdown hitbox_history_general;
	MultiDropdown multipoint_general;
	Slider		  scale_general;
	Slider		  body_scale_general;
	Slider		  minimal_damage_general;
	Checkbox	  minimal_damage_hp_general;
	Checkbox	  penetrate_general;
	Slider		  penetrate_minimal_damage_general;
	Checkbox	  penetrate_minimal_damage_hp_general;

	MultiDropdown hitbox_auto;
	MultiDropdown hitbox_history_auto;
	MultiDropdown multipoint_auto;
	Slider		  scale_auto;
	Slider		  body_scale_auto;
	Slider		  minimal_damage_auto;
	Checkbox	  minimal_damage_hp_auto;
	Checkbox	  penetrate_auto;
	Slider		  penetrate_minimal_damage_auto;
	Checkbox	  penetrate_minimal_damage_hp_auto;

	MultiDropdown hitbox_awp;
	MultiDropdown hitbox_history_awp;
	MultiDropdown multipoint_awp;
	Slider		  scale_awp;
	Slider		  body_scale_awp;
	Slider		  minimal_damage_awp;
	Checkbox	  minimal_damage_hp_awp;
	Checkbox	  penetrate_awp;
	Slider		  penetrate_minimal_damage_awp;
	Checkbox	  penetrate_minimal_damage_hp_awp;

	MultiDropdown hitbox_heavy;
	MultiDropdown hitbox_history_heavy;
	MultiDropdown multipoint_heavy;
	Slider		  scale_heavy;
	Slider		  body_scale_heavy;
	Slider		  minimal_damage_heavy;
	Checkbox	  minimal_damage_hp_heavy;
	Checkbox	  penetrate_heavy;
	Slider		  penetrate_minimal_damage_heavy;
	Checkbox	  penetrate_minimal_damage_hp_heavy;

	MultiDropdown hitbox_scout;
	MultiDropdown hitbox_history_scout;
	MultiDropdown multipoint_scout;
	Slider		  scale_scout;
	Slider		  body_scale_scout;
	Slider		  minimal_damage_scout;
	Checkbox	  minimal_damage_hp_scout;
	Checkbox	  penetrate_scout;
	Slider		  penetrate_minimal_damage_scout;
	Checkbox	  penetrate_minimal_damage_hp_scout;

	MultiDropdown hitbox_pistols;
	MultiDropdown hitbox_history_pistols;
	MultiDropdown multipoint_pistols;
	Slider		  scale_pistols;
	Slider		  body_scale_pistols;
	Slider		  minimal_damage_pistols;
	Checkbox	  minimal_damage_hp_pistols;
	Checkbox	  penetrate_pistols;
	Slider		  penetrate_minimal_damage_pistols;
	Checkbox	  penetrate_minimal_damage_hp_pistols;
	Checkbox      debugaim;
	Colorpicker   debugaimcol;


	Checkbox      hitchance_general;
	Slider	      hitchance_amount_general;

	Checkbox      hitchance_auto;
	Slider	      hitchance_amount_auto;

	Checkbox      hitchance_awp;
	Slider	      hitchance_amount_awp;

	Checkbox      hitchance_heavy;
	Slider	      hitchance_amount_heavy;

	Checkbox      hitchance_scout;
	Slider	      hitchance_amount_scout;

	Checkbox      hitchance_pistols;
	Slider	      hitchance_amount_pistols;

	// col2.
	Dropdown      zoom;
	Checkbox      nospread;
	Checkbox      norecoil;
	Checkbox      ignor_limbs;
	Checkbox      lagfix;
	Checkbox	  correct;
	MultiDropdown baim1;
	MultiDropdown baim2;
	MultiDropdown head1;
	Slider        misses;
	Slider        baim_hp;
	Keybind       baim_key;
	Checkbox	  override_dmg_ind;
	Keybind       override_dmg_key;
	Slider        override_dmg_value;


public:
	void init() {
		// title.
		SetTitle(XOR("Aimbot"));

		enable.setup(XOR("Enable"), XOR("enable"));
		RegisterElement(&enable);

		silent.setup(XOR("Silent aimbot"), XOR("silent"));
		RegisterElement(&silent);

		selection.setup(XOR("Target selection"), XOR("selection"), { XOR("Distance"), XOR("Crosshair"), XOR("Damage"), XOR("Health"), XOR("Lag"), XOR("Height") });
		RegisterElement(&selection);

		weapon_select.setup(XOR("Weapon"), XOR("weapon_configs"), { XOR("General"), XOR("Auto"), XOR("AWP"), XOR("Scout"), XOR("Pistols"), XOR("Heavy pistols") });
		RegisterElement(&weapon_select);

		/* General */

		hitchance_general.setup(XOR("Hitchance"), XOR("hitchance_general"));
		hitchance_general.AddShowCallback(callbacks::IsConfigMM); //fixed pos in menu being super low compared to other hitchance sliders
		hitchance_general.AddShowCallback(callbacks::IsWeaponGeneral);
		RegisterElement(&hitchance_general);

		hitchance_amount_general.setup("", XOR("hitchance_amount_general"), 1.f, 100.f, false, 0, 50.f, 1.f, XOR(L"%"));
		hitchance_amount_general.AddShowCallback(callbacks::IsConfigMM);
		hitchance_amount_general.AddShowCallback(callbacks::IsWeaponGeneral);
		hitchance_amount_general.AddShowCallback(callbacks::IsHitchanceOnGeneral);
		RegisterElement(&hitchance_amount_general);

		hitbox_general.setup(XOR("Hitbox"), XOR("hitbox_general"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_general.AddShowCallback(callbacks::IsWeaponGeneral);
		RegisterElement(&hitbox_general);

		hitbox_history_general.setup(XOR("Hitbox history"), XOR("hitbox_history_general"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_history_general.AddShowCallback(callbacks::IsWeaponGeneral);
		RegisterElement(&hitbox_history_general);

		multipoint_general.setup(XOR("Multipoint"), XOR("multipoint_general"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Legs") });
		multipoint_general.AddShowCallback(callbacks::IsWeaponGeneral);
		RegisterElement(&multipoint_general);

		scale_general.setup("", XOR("hitbox_scale_general"), 1.f, 100.f, false, 0, 90.f, 1.f, XOR(L"%"));
		scale_general.AddShowCallback(callbacks::IsWeaponGeneral);
		scale_general.AddShowCallback(callbacks::IsMultipointOnGeneral);
		RegisterElement(&scale_general);

		body_scale_general.setup(XOR("Stomach hitbox scale"), XOR("body_hitbox_scale_general"), 1.f, 100.f, true, 0, 50.f, 1.f, XOR(L"%"));
		body_scale_general.AddShowCallback(callbacks::IsWeaponGeneral);
		body_scale_general.AddShowCallback(callbacks::IsMultipointBodyOnGeneral);
		RegisterElement(&body_scale_general);

		hitchance_auto.setup(XOR("Hitchance"), XOR("hitchance_auto"));
		hitchance_auto.AddShowCallback(callbacks::IsConfigMM);
		hitchance_auto.AddShowCallback(callbacks::IsWeaponAuto);
		RegisterElement(&hitchance_auto);

		hitchance_amount_auto.setup("", XOR("hitchance_amount_auto"), 1.f, 100.f, false, 0, 50.f, 1.f, XOR(L"%"));
		hitchance_amount_auto.AddShowCallback(callbacks::IsConfigMM);
		hitchance_amount_auto.AddShowCallback(callbacks::IsWeaponAuto);
		hitchance_amount_auto.AddShowCallback(callbacks::IsHitchanceOnAuto);
		RegisterElement(&hitchance_amount_auto);

		hitchance_awp.setup(XOR("Hitchance"), XOR("hitchance_awp"));
		hitchance_awp.AddShowCallback(callbacks::IsConfigMM);
		hitchance_awp.AddShowCallback(callbacks::IsWeaponAWP);
		RegisterElement(&hitchance_awp);

		hitchance_amount_awp.setup("", XOR("hitchance_amount_awp"), 1.f, 100.f, false, 0, 50.f, 1.f, XOR(L"%"));
		hitchance_amount_awp.AddShowCallback(callbacks::IsConfigMM);
		hitchance_amount_awp.AddShowCallback(callbacks::IsHitchanceOnAWP);
		hitchance_amount_awp.AddShowCallback(callbacks::IsWeaponAWP);
		RegisterElement(&hitchance_amount_awp);

		hitchance_scout.setup(XOR("Hitchance"), XOR("hitchance_scout"));
		hitchance_scout.AddShowCallback(callbacks::IsConfigMM);
		hitchance_scout.AddShowCallback(callbacks::IsWeaponScout);
		RegisterElement(&hitchance_scout);

		hitchance_amount_scout.setup("", XOR("hitchance_amount_scout"), 1.f, 100.f, false, 0, 50.f, 1.f, XOR(L"%"));
		hitchance_amount_scout.AddShowCallback(callbacks::IsConfigMM);
		hitchance_amount_scout.AddShowCallback(callbacks::IsHitchanceOnScout);
		hitchance_amount_scout.AddShowCallback(callbacks::IsWeaponScout);
		RegisterElement(&hitchance_amount_scout);

		hitchance_pistols.setup(XOR("Hitchance"), XOR("hitchance_pistols"));
		hitchance_pistols.AddShowCallback(callbacks::IsConfigMM);
		hitchance_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		RegisterElement(&hitchance_pistols);

		hitchance_amount_pistols.setup("", XOR("hitchance_amount_pistols"), 1.f, 100.f, false, 0, 50.f, 1.f, XOR(L"%"));
		hitchance_amount_pistols.AddShowCallback(callbacks::IsConfigMM);
		hitchance_amount_pistols.AddShowCallback(callbacks::IsHitchanceOnPistols);
		hitchance_amount_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		RegisterElement(&hitchance_amount_pistols);

		hitchance_heavy.setup(XOR("Hitchance"), XOR("hitchance_heavy"));
		hitchance_heavy.AddShowCallback(callbacks::IsConfigMM);
		hitchance_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		RegisterElement(&hitchance_heavy);

		hitchance_amount_heavy.setup("", XOR("hitchance_amount_heavy"), 1.f, 100.f, false, 0, 50.f, 1.f, XOR(L"%"));
		hitchance_amount_heavy.AddShowCallback(callbacks::IsConfigMM);
		hitchance_amount_heavy.AddShowCallback(callbacks::IsHitchanceOnHeavy);
		hitchance_amount_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		RegisterElement(&hitchance_amount_heavy);

		minimal_damage_general.setup(XOR("Minimum damage"), XOR("minimal_damage_general"), 1.f, 100.f, true, 0, 40.f, 1.f);
		minimal_damage_general.AddShowCallback(callbacks::IsWeaponGeneral);
		RegisterElement(&minimal_damage_general);

		/*minimal_damage_hp_general.setup(XOR("auto damage"), XOR("minimal_damage_hp_general"));
		minimal_damage_hp_general.AddShowCallback(callbacks::IsWeaponGeneral);
		minimal_damage_hp_general.AddShowCallback(callbacks::IsDamageVisibleGeneral);
		RegisterElement(&minimal_damage_hp_general);*/

		penetrate_general.setup(XOR("Autowall"), XOR("penetrate_general"));
		penetrate_general.AddShowCallback(callbacks::IsWeaponGeneral);
		RegisterElement(&penetrate_general);

		//penetrate_minimal_damage_general.setup("", XOR("penetrate_minimal_damage_general"), 1.f, 100.f, false, 0, 30.f, 1.f);
		//penetrate_minimal_damage_general.AddShowCallback(callbacks::IsWeaponGeneral);
		//penetrate_minimal_damage_general.AddShowCallback(callbacks::IsPenetrationOnGeneral);
		//RegisterElement(&penetrate_minimal_damage_general);

		//penetrate_minimal_damage_hp_general.setup(XOR("auto damage"), XOR("penetrate_minimal_damage_hp_general"));
		//penetrate_minimal_damage_hp_general.AddShowCallback(callbacks::IsWeaponGeneral);
		//penetrate_minimal_damage_hp_general.AddShowCallback(callbacks::IsDamageInVisibleGeneral);
		//penetrate_minimal_damage_hp_general.AddShowCallback(callbacks::IsPenetrationOnGeneral);
		//RegisterElement(&penetrate_minimal_damage_hp_general);

		/* Auto */

		hitbox_auto.setup(XOR("Hitbox"), XOR("hitbox_auto"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_auto.AddShowCallback(callbacks::IsWeaponAuto);
		RegisterElement(&hitbox_auto);

		hitbox_history_auto.setup(XOR("Hitbox history"), XOR("hitbox_history_auto"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_history_auto.AddShowCallback(callbacks::IsWeaponAuto);
		RegisterElement(&hitbox_history_auto);

		multipoint_auto.setup(XOR("Multipoint"), XOR("multipoint_auto"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Legs") });
		multipoint_auto.AddShowCallback(callbacks::IsWeaponAuto);
		RegisterElement(&multipoint_auto);

		scale_auto.setup("", XOR("hitbox_scale_auto"), 1.f, 100.f, false, 0, 90.f, 1.f, XOR(L"%"));
		scale_auto.AddShowCallback(callbacks::IsWeaponAuto);
		scale_auto.AddShowCallback(callbacks::IsMultipointOnAuto);
		RegisterElement(&scale_auto);

		body_scale_auto.setup(XOR("Stomach hitbox scale"), XOR("body_hitbox_scale_auto"), 1.f, 100.f, true, 0, 50.f, 1.f, XOR(L"%"));
		body_scale_auto.AddShowCallback(callbacks::IsWeaponAuto);
		body_scale_auto.AddShowCallback(callbacks::IsMultipointBodyOnAuto);
		RegisterElement(&body_scale_auto);

		minimal_damage_auto.setup(XOR("Minimum damage"), XOR("minimal_damage_auto"), 1.f, 125.f, true, 0, 40.f, 1.f);
		minimal_damage_auto.AddShowCallback(callbacks::IsWeaponAuto);
		RegisterElement(&minimal_damage_auto);


		/*minimal_damage_hp_auto.setup(XOR("auto damage"), XOR("minimal_damage_hp_auto"));
		minimal_damage_hp_auto.AddShowCallback(callbacks::IsWeaponAuto);
		minimal_damage_hp_auto.AddShowCallback(callbacks::IsDamageVisibleAuto);
		RegisterElement(&minimal_damage_hp_auto);*/

		penetrate_auto.setup(XOR("Autowall"), XOR("penetrate_auto"));
		penetrate_auto.AddShowCallback(callbacks::IsWeaponAuto);
		RegisterElement(&penetrate_auto);

		/*penetrate_minimal_damage_auto.setup("", XOR("penetrate_minimal_damage_auto"), 1.f, 100.f, false, 0, 30.f, 1.f);
		penetrate_minimal_damage_auto.AddShowCallback(callbacks::IsWeaponAuto);
		penetrate_minimal_damage_auto.AddShowCallback(callbacks::IsPenetrationOnAuto);
		RegisterElement(&penetrate_minimal_damage_auto);

		penetrate_minimal_damage_hp_auto.setup(XOR("auto damage"), XOR("penetrate_minimal_damage_hp_auto"));
		penetrate_minimal_damage_hp_auto.AddShowCallback(callbacks::IsWeaponAuto);
		penetrate_minimal_damage_hp_auto.AddShowCallback(callbacks::IsDamageInVisibleAuto);
		penetrate_minimal_damage_hp_auto.AddShowCallback(callbacks::IsPenetrationOnAuto);
		RegisterElement(&penetrate_minimal_damage_hp_auto);*/

		/* AWP */

		hitbox_awp.setup(XOR("Hitbox"), XOR("hitbox_awp"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_awp.AddShowCallback(callbacks::IsWeaponAWP);
		RegisterElement(&hitbox_awp);

		hitbox_history_awp.setup(XOR("Hitbox history"), XOR("hitbox_history_awp"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_history_awp.AddShowCallback(callbacks::IsWeaponAWP);
		RegisterElement(&hitbox_history_awp);

		multipoint_awp.setup(XOR("Multipoint"), XOR("multipoint_awp"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Legs") });
		multipoint_awp.AddShowCallback(callbacks::IsWeaponAWP);
		RegisterElement(&multipoint_awp);

		scale_awp.setup("", XOR("hitbox_scale_awp"), 1.f, 100.f, false, 0, 90.f, 1.f, XOR(L"%"));
		scale_awp.AddShowCallback(callbacks::IsWeaponAWP);
		scale_awp.AddShowCallback(callbacks::IsMultipointOnAWP);
		RegisterElement(&scale_awp);

		body_scale_awp.setup(XOR("Stomach hitbox scale"), XOR("body_hitbox_scale_awp"), 1.f, 100.f, true, 0, 50.f, 1.f, XOR(L"%"));
		body_scale_awp.AddShowCallback(callbacks::IsWeaponAWP);
		body_scale_awp.AddShowCallback(callbacks::IsMultipointBodyOnAWP);
		RegisterElement(&body_scale_awp);

		minimal_damage_awp.setup(XOR("Minimum damage"), XOR("minimal_damage_awp"), 1.f, 125.f, true, 0, 40.f, 1.f);
		minimal_damage_awp.AddShowCallback(callbacks::IsWeaponAWP);
		RegisterElement(&minimal_damage_awp);

		/*minimal_damage_hp_awp.setup(XOR("auto damage"), XOR("minimal_damage_hp_awp"));
		minimal_damage_hp_awp.AddShowCallback(callbacks::IsWeaponAWP);
		minimal_damage_hp_awp.AddShowCallback(callbacks::IsDamageVisibleAWP);
		RegisterElement(&minimal_damage_hp_awp);*/

		penetrate_awp.setup(XOR("Autowall"), XOR("penetrate_awp"));
		penetrate_awp.AddShowCallback(callbacks::IsWeaponAWP);
		RegisterElement(&penetrate_awp);

		/*penetrate_minimal_damage_awp.setup("", XOR("penetrate_minimal_damage_awp"), 1.f, 100.f, false, 0, 30.f, 1.f);
		penetrate_minimal_damage_awp.AddShowCallback(callbacks::IsWeaponAWP);
		penetrate_minimal_damage_awp.AddShowCallback(callbacks::IsPenetrationOnAWP);
		RegisterElement(&penetrate_minimal_damage_awp);

		penetrate_minimal_damage_hp_awp.setup(XOR("auto damage"), XOR("penetrate_minimal_damage_hp_awp"));
		penetrate_minimal_damage_hp_awp.AddShowCallback(callbacks::IsWeaponAWP);
		penetrate_minimal_damage_hp_awp.AddShowCallback(callbacks::IsDamageInVisibleAWP);
		penetrate_minimal_damage_hp_awp.AddShowCallback(callbacks::IsPenetrationOnAWP);
		RegisterElement(&penetrate_minimal_damage_hp_awp);*/

		/* Scout */

		hitbox_scout.setup(XOR("Hitbox"), XOR("hitbox_scout"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_scout.AddShowCallback(callbacks::IsWeaponScout);
		RegisterElement(&hitbox_scout);

		hitbox_history_scout.setup(XOR("Hitbox history"), XOR("hitbox_history_scout"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_history_scout.AddShowCallback(callbacks::IsWeaponScout);
		RegisterElement(&hitbox_history_scout);

		multipoint_scout.setup(XOR("Multipoint"), XOR("multipoint_scout"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Legs") });
		multipoint_scout.AddShowCallback(callbacks::IsWeaponScout);
		RegisterElement(&multipoint_scout);

		scale_scout.setup("", XOR("hitbox_scale_scout"), 1.f, 100.f, false, 0, 90.f, 1.f, XOR(L"%"));
		scale_scout.AddShowCallback(callbacks::IsWeaponScout);
		scale_scout.AddShowCallback(callbacks::IsMultipointOnScout);
		RegisterElement(&scale_scout);

		body_scale_scout.setup(XOR("Stomach hitbox scale"), XOR("body_hitbox_scale_scout"), 1.f, 100.f, true, 0, 50.f, 1.f, XOR(L"%"));
		body_scale_scout.AddShowCallback(callbacks::IsWeaponScout);
		body_scale_scout.AddShowCallback(callbacks::IsMultipointBodyOnScout);
		RegisterElement(&body_scale_scout);

		minimal_damage_scout.setup(XOR("Minimum damage"), XOR("minimal_damage_scout"), 1.f, 125.f, true, 0, 40.f, 1.f);
		minimal_damage_scout.AddShowCallback(callbacks::IsWeaponScout);
		RegisterElement(&minimal_damage_scout);


		/*minimal_damage_hp_scout.setup(XOR("auto damage"), XOR("minimal_damage_hp_scout"));
		minimal_damage_hp_scout.AddShowCallback(callbacks::IsWeaponScout);
		minimal_damage_hp_scout.AddShowCallback(callbacks::IsDamageVisibleScout);
		RegisterElement(&minimal_damage_hp_scout);*/

		penetrate_scout.setup(XOR("Autowall"), XOR("penetrate_scout"));
		penetrate_scout.AddShowCallback(callbacks::IsWeaponScout);
		RegisterElement(&penetrate_scout);

		/*penetrate_minimal_damage_scout.setup("", XOR("penetrate_minimal_damage_scout"), 1.f, 100.f, false, 0, 30.f, 1.f);
		penetrate_minimal_damage_scout.AddShowCallback(callbacks::IsWeaponScout);
		penetrate_minimal_damage_scout.AddShowCallback(callbacks::IsPenetrationOnScout);
		RegisterElement(&penetrate_minimal_damage_scout);

		penetrate_minimal_damage_hp_scout.setup(XOR("auto damage"), XOR("penetrate_minimal_damage_hp_scout"));
		penetrate_minimal_damage_hp_scout.AddShowCallback(callbacks::IsWeaponScout);
		penetrate_minimal_damage_hp_scout.AddShowCallback(callbacks::IsDamageInVisibleScout);
		penetrate_minimal_damage_hp_scout.AddShowCallback(callbacks::IsPenetrationOnScout);
		RegisterElement(&penetrate_minimal_damage_hp_scout);*/

		/* Pistols */

		hitbox_pistols.setup(XOR("Hitbox"), XOR("hitbox_pistols"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		RegisterElement(&hitbox_pistols);

		hitbox_history_pistols.setup(XOR("Hitbox history"), XOR("hitbox_history_pistols"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_history_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		RegisterElement(&hitbox_history_pistols);

		multipoint_pistols.setup(XOR("Multipoint"), XOR("multipoint_pistols"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Legs") });
		multipoint_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		RegisterElement(&multipoint_pistols);

		scale_pistols.setup("", XOR("hitbox_scale_pistols"), 1.f, 100.f, false, 0, 90.f, 1.f, XOR(L"%"));
		scale_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		scale_pistols.AddShowCallback(callbacks::IsMultipointOnPistols);
		RegisterElement(&scale_pistols);

		body_scale_pistols.setup(XOR("Stomach hitbox scale"), XOR("body_hitbox_scale_pistols"), 1.f, 100.f, true, 0, 50.f, 1.f, XOR(L"%"));
		body_scale_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		body_scale_pistols.AddShowCallback(callbacks::IsMultipointBodyOnPistols);
		RegisterElement(&body_scale_pistols);

		minimal_damage_pistols.setup(XOR("Minimum damage"), XOR("minimal_damage_pistols"), 1.f, 125.f, true, 0, 40.f, 1.f);
		minimal_damage_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		RegisterElement(&minimal_damage_pistols);

		/*.setup(XOR("auto damage"), XOR("minimal_damage_hp_pistols"));
		minimal_damage_hp_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		minimal_damage_hp_pistols.AddShowCallback(callbacks::IsDamageVisiblePistols);
		RegisterElement(&minimal_damage_hp_pistols);*/

		penetrate_pistols.setup(XOR("Autowall"), XOR("penetrate_pistols"));
		penetrate_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		RegisterElement(&penetrate_pistols);

		/*penetrate_minimal_damage_pistols.setup("", XOR("penetrate_minimal_damage_pistols"), 1.f, 100.f, false, 0, 30.f, 1.f);
		penetrate_minimal_damage_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		penetrate_minimal_damage_pistols.AddShowCallback(callbacks::IsPenetrationOnPistols);
		RegisterElement(&penetrate_minimal_damage_pistols);

		penetrate_minimal_damage_hp_pistols.setup(XOR("auto damage"), XOR("penetrate_minimal_damage_hp_pistols"));
		penetrate_minimal_damage_hp_pistols.AddShowCallback(callbacks::IsWeaponPistol);
		penetrate_minimal_damage_hp_pistols.AddShowCallback(callbacks::IsDamageInVisiblePistols);
		penetrate_minimal_damage_hp_pistols.AddShowCallback(callbacks::IsPenetrationOnPistols);
		RegisterElement(&penetrate_minimal_damage_hp_pistols);*/

		/* Heavy Pistols */

		hitbox_heavy.setup(XOR("Hitbox"), XOR("hitbox_heavy"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		RegisterElement(&hitbox_heavy);

		hitbox_history_heavy.setup(XOR("Hitbox history"), XOR("hitbox_history_heavy"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Arms"), XOR("Legs"), XOR("Feet") });
		hitbox_history_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		RegisterElement(&hitbox_history_heavy);

		multipoint_heavy.setup(XOR("Multipoint"), XOR("multipoint_heavy"), { XOR("Head"), XOR("Chest"), XOR("Body"), XOR("Legs") });
		multipoint_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		RegisterElement(&multipoint_heavy);

		scale_heavy.setup("", XOR("hitbox_scale_heavy"), 1.f, 100.f, false, 0, 90.f, 1.f, XOR(L"%"));
		scale_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		scale_heavy.AddShowCallback(callbacks::IsMultipointOnHeavy);
		RegisterElement(&scale_heavy);

		body_scale_heavy.setup(XOR("Stomach hitbox scale"), XOR("body_hitbox_scale_heavy"), 1.f, 100.f, true, 0, 50.f, 1.f, XOR(L"%"));
		body_scale_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		body_scale_heavy.AddShowCallback(callbacks::IsMultipointBodyOnHeavy);
		RegisterElement(&body_scale_heavy);

		minimal_damage_heavy.setup(XOR("Minimum damage"), XOR("minimal_damage_heavy"), 1.f, 125.f, true, 0, 40.f, 1.f);
		minimal_damage_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		RegisterElement(&minimal_damage_heavy);

		/*minimal_damage_hp_heavy.setup(XOR("auto damage"), XOR("minimal_damage_hp_heavy"));
		minimal_damage_hp_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		minimal_damage_hp_heavy.AddShowCallback(callbacks::IsDamageVisibleHeavy);
		RegisterElement(&minimal_damage_hp_heavy);*/

		penetrate_heavy.setup(XOR("Autowall"), XOR("penetrate_heavy"));
		penetrate_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		RegisterElement(&penetrate_heavy);

		/*penetrate_minimal_damage_heavy.setup("", XOR("penetrate_minimal_damage_heavy"), 1.f, 100.f, false, 0, 30.f, 1.f);
		penetrate_minimal_damage_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		penetrate_minimal_damage_heavy.AddShowCallback(callbacks::IsPenetrationOnHeavy);
		RegisterElement(&penetrate_minimal_damage_heavy);

		penetrate_minimal_damage_hp_heavy.setup(XOR("auto damage"), XOR("penetrate_minimal_damage_hp_heavy"));
		penetrate_minimal_damage_hp_heavy.AddShowCallback(callbacks::IsWeaponHeavy);
		penetrate_minimal_damage_hp_heavy.AddShowCallback(callbacks::IsDamageInVisibleHeavy);
		penetrate_minimal_damage_hp_heavy.AddShowCallback(callbacks::IsPenetrationOnHeavy);
		RegisterElement(&penetrate_minimal_damage_hp_heavy);*/


		debugaim.setup(XOR("Onshot hitbox"), XOR("debugaim"));
		RegisterElement(&debugaim);

		debugaimcol.setup(XOR("Color"), XOR("debugaimcol"), colors::white);
		debugaimcol.AddShowCallback(callbacks::DEBUG_AIM);
		RegisterElement(&debugaimcol);

		// col2.
		zoom.setup(XOR("Auto-scope"), XOR("zoom"), { XOR("Off"), XOR("Always"), XOR("Hitchance fail") });
		RegisterElement(&zoom, 1);

		nospread.setup(XOR("Compensate spread"), XOR("nospread"));
		nospread.AddShowCallback(callbacks::IsConfigNS);
		RegisterElement(&nospread, 1);

		norecoil.setup(XOR("Compensate recoil"), XOR("norecoil"));
		RegisterElement(&norecoil, 1);


		ignor_limbs.setup(XOR("Ignore limbs when moving"), XOR("ignor_limbs"));
		RegisterElement(&ignor_limbs, 1);

		lagfix.setup(XOR("Predict fake-lag"), XOR("lagfix"));
		RegisterElement(&lagfix, 1);

		correct.setup(XOR("Correct anti-aim"), XOR("correct"));
		RegisterElement(&correct, 1);

		baim1.setup(XOR("Prefer body aim"), XOR("baim1"), { XOR("Always"), XOR("Lethal"), XOR("Lethal x2"), XOR("Fake"), XOR("In air"), XOR("After x misses") });
		RegisterElement(&baim1, 1);

		baim2.setup(XOR("Only body aim"), XOR("baim2"), { XOR("Always"), XOR("Health"), XOR("Fake"), XOR("In air"), XOR("After x misses") });
		RegisterElement(&baim2, 1);

		baim_hp.setup("", XOR("baim_hp"), 1.f, 50.f, false, 0, 20.f, 1.f, XOR(L"hp"));
		baim_hp.AddShowCallback(callbacks::IsBaimHealth);
		RegisterElement(&baim_hp, 1);

		misses.setup("", XOR("Misses"), 1.f, 10.f, false, 0, 2.f, 1.f);
		misses.AddShowCallback(callbacks::IsAfterMisses);
		RegisterElement(&misses, 1);

		head1.setup(XOR("Prefer head aim"), XOR("head1"), { XOR("Always"), XOR("Running"), XOR("Resolved"), XOR("In air") });
		RegisterElement(&head1, 1);

		baim_key.setup(XOR("Body aim on key"), XOR("body aim on key"));
		RegisterElement(&baim_key, 1);

		override_dmg_ind.setup(XOR("Override dmg indicator"), XOR("override_dmg_ind"));
		RegisterElement(&override_dmg_ind, 1);

		override_dmg_key.setup(XOR("Override damage"), XOR("override_dmg"));
		override_dmg_key.SetToggleCallback(callbacks::ToggleDMG);
		RegisterElement(&override_dmg_key, 1);

		override_dmg_value.setup(" ", XOR("dmg_override"), 1.f, 100.f, false, 0, 1.f, 1.f, XOR(L"hp"));
		override_dmg_value.AddShowCallback(callbacks::IsOverrideDamage);
		RegisterElement(&override_dmg_value, 1);


	}
};


class AntiAimTab : public Tab {
public:
	// col 1.
	Checkbox enable;
	Checkbox edge;
	Dropdown mode;

	Dropdown pitch_stand;
	Dropdown yaw_stand;
	Slider   jitter_range_stand;
	Slider   rot_range_stand;
	Slider   rot_speed_stand;
	Slider   rand_update_stand;
	Dropdown dir_stand;
	Slider   dir_time_stand;
	Slider   dir_custom_stand;
	Checkbox dir_lock;
	//Checkbox pitch_fake_stand;
	Checkbox body_fake_stand_fakewalk;
	Dropdown base_angle_stand;
	Dropdown body_fake_stand;
	Slider	 body_fake_stand_custom;

	Dropdown pitch_walk;
	Dropdown yaw_walk;
	Slider   jitter_range_walk;
	Slider   rot_range_walk;
	Slider   rot_speed_walk;
	Slider   rand_update_walk;
	Dropdown dir_walk;
	Slider	 dir_time_walk;
	Slider   dir_custom_walk;
	Dropdown base_angle_walk;

	Dropdown pitch_air;
	Dropdown yaw_air;
	Slider   jitter_range_air;
	Slider   rot_range_air;
	Slider   rot_speed_air;
	Slider   rand_update_air;
	Dropdown dir_air;
	Slider   dir_time_air;
	Slider   dir_custom_air;
	Dropdown base_angle_air;
	Dropdown body_fake_air;
	//Checkbox distortion;
	//Checkbox force_turn;
	//Slider   distortion_amount;
	//Slider   distortion_speed;
	//MultiDropdown distortion_additive;

	// col 2.
	Dropdown fake_yaw;
	Slider	 fake_relative;
	Slider	 fake_jitter_range;

	Checkbox      lag_enable;
	MultiDropdown lag_active;
	Dropdown      lag_mode;
	Slider        lag_limit;
	Checkbox      lag_land;

	Colorpicker   color_manul_antiaim;
	Checkbox	  manul_antiaim;
	Checkbox	  draw_angles;
	Checkbox	  draw_angles_chams;
	Colorpicker   color_draw_angles_chams;
	Slider        draw_angles_chams_blend;
	Keybind		  left;
	Keybind		  right;
	Keybind		  back;

public:
	void init() {
		SetTitle(XOR("Anti-aim"));

		enable.setup(XOR("Enable"), XOR("enable"));
		RegisterElement(&enable);

		edge.setup(XOR("Edge"), XOR("edge"));
		RegisterElement(&edge);

		mode.setup("", XOR("mode"), { XOR("Stand"), XOR("Walk"), XOR("Air") }, false);
		RegisterElement(&mode);

		// stand.
		pitch_stand.setup(XOR("Pitch"), XOR("pitch_stnd"), { XOR("Off"), XOR("Down"), XOR("Up"), XOR("Random"), XOR("Ideal") });
		pitch_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		RegisterElement(&pitch_stand);

		yaw_stand.setup(XOR("Yaw"), XOR("yaw_stnd"), { XOR("Off"), XOR("Direction"), XOR("Jitter"), XOR("Rotate"), XOR("Random") }); //, XOR("Distortion")
		yaw_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		RegisterElement(&yaw_stand);

		jitter_range_stand.setup("", XOR("jitter_range_stnd"), 1.f, 180.f, false, 0, 45.f, 5.f, XOR(L"°"));
		jitter_range_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		jitter_range_stand.AddShowCallback(callbacks::IsStandYawJitter);
		RegisterElement(&jitter_range_stand);

		rot_range_stand.setup("", XOR("rot_range_stnd"), 0.f, 360.f, false, 0, 360.f, 5.f, XOR(L"°"));
		rot_range_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		rot_range_stand.AddShowCallback(callbacks::IsStandYawRotate);
		RegisterElement(&rot_range_stand);

		rot_speed_stand.setup("", XOR("rot_speed_stnd"), 1.f, 100.f, false, 0, 10.f, 1.f, XOR(L"%"));
		rot_speed_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		rot_speed_stand.AddShowCallback(callbacks::IsStandYawRotate);
		RegisterElement(&rot_speed_stand);

		rand_update_stand.setup("", XOR("rand_update_stnd"), 0.f, 1.f, false, 1, 0.f, 0.1f);
		rand_update_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		rand_update_stand.AddShowCallback(callbacks::IsStandYawRnadom);
		RegisterElement(&rand_update_stand);

		dir_stand.setup(XOR("Direction"), XOR("dir_stnd"), { XOR("Auto"), XOR("Backwards"), XOR("Left"), XOR("Right"), XOR("Custom") });
		dir_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_stand.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&dir_stand);

		dir_time_stand.setup("", XOR("dir_time_stnd"), 0.f, 10.f, false, 0, 0.f, 1.f, XOR(L"s"));
		dir_time_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_time_stand.AddShowCallback(callbacks::HasStandYaw);
		dir_time_stand.AddShowCallback(callbacks::IsStandDirAuto);
		RegisterElement(&dir_time_stand);

		dir_custom_stand.setup("", XOR("dir_custom_stnd"), -180.f, 180.f, false, 0, 0.f, 5.f, XOR(L"°"));
		dir_custom_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_custom_stand.AddShowCallback(callbacks::HasStandYaw);
		dir_custom_stand.AddShowCallback(callbacks::IsStandDirCustom);
		RegisterElement(&dir_custom_stand);

		base_angle_stand.setup(XOR("Base angle"), XOR("base_angle_stand"), { XOR("Off"), XOR("Static"), XOR("Away crosshair"), XOR("Away distance") });
		base_angle_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		base_angle_stand.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&base_angle_stand);

		body_fake_stand.setup(XOR("Fake body"), XOR("body_fake_stnd"), { XOR("Off"), XOR("Left"), XOR("Right"), XOR("Opposite"), XOR("Z"), XOR("Twist"), XOR("Twist z"), XOR("Resolver breaker") });
		body_fake_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		body_fake_stand.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&body_fake_stand);

		dir_lock.setup(XOR("Lock direction"), XOR("dir_lock"));
		dir_lock.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_lock.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&dir_lock);

		/*pitch_fake_stand.setup(XOR("fake up"), XOR("pitch_fake_stand"));
		pitch_fake_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		pitch_fake_stand.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&pitch_fake_stand);*/

		body_fake_stand_fakewalk.setup(XOR("Disbale fake body while fakewalking"), XOR("body_fake_stand_fakewalk"));
		body_fake_stand_fakewalk.AddShowCallback(callbacks::IsAntiAimModeStand);
		body_fake_stand_fakewalk.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&body_fake_stand_fakewalk);

		body_fake_stand_custom.setup(XOR("Lby custom"), XOR("body_fake_stand_custom"), -70, 70, false, 0, 0, 1.f, XOR(L"°"));
		body_fake_stand_custom.AddShowCallback(callbacks::IsAntiAimModeStand);
		//body_fake_stand_custom.AddShowCallback(callbacks::HasStandYaw);
		body_fake_stand_custom.AddShowCallback(callbacks::IsCustomLby);
		RegisterElement(&body_fake_stand_custom);

		/*body_fake_stand_custom.setup(XOR("lby custom"), XOR("body_fake_stand_custom"), -70, 70, false, 0, 0, 1.f, XOR(L"°"));
		body_fake_stand_custom.AddShowCallback(callbacks::IsAntiAimModeStand);
		//body_fake_stand_custom.AddShowCallback(callbacks::HasStandYaw);
		body_fake_stand_custom.AddShowCallback(callbacks::IsCustomLby);
		RegisterElement(&body_fake_stand_custom);

		/*dir_time_stand.setup("", XOR("dir_time_stnd"), 0.f, 10.f, false, 0, 0.f, 1.f, XOR(L"s"));
		dir_time_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_time_stand.AddShowCallback(callbacks::HasStandYaw);
		dir_time_stand.AddShowCallback(callbacks::IsStandDirAuto);
		RegisterElement(&dir_time_stand);
		lag_limit.setup(XOR("limit"), XOR("lag_limit"), 2, 16, true, 0, 2, 1.f);*/


		// walk.
		pitch_walk.setup(XOR("Pitch"), XOR("pitch_walk"), { XOR("Off"), XOR("Down"), XOR("Up"), XOR("Random"), XOR("Ideal") });
		pitch_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		RegisterElement(&pitch_walk);

		yaw_walk.setup(XOR("Yaw"), XOR("yaw_walk"), { XOR("Off"), XOR("Direction"), XOR("Jitter"), XOR("Rotate"), XOR("Random") });
		yaw_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		RegisterElement(&yaw_walk);

		jitter_range_walk.setup("", XOR("jitter_range_walk"), 1.f, 180.f, false, 0, 45.f, 5.f, XOR(L"°"));
		jitter_range_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		jitter_range_walk.AddShowCallback(callbacks::IsWalkYawJitter);
		RegisterElement(&jitter_range_walk);

		rot_range_walk.setup("", XOR("rot_range_walk"), 0.f, 360.f, false, 0, 360.f, 5.f, XOR(L"°"));
		rot_range_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		rot_range_walk.AddShowCallback(callbacks::IsWalkYawRotate);
		RegisterElement(&rot_range_walk);

		rot_speed_walk.setup("", XOR("rot_speed_walk"), 1.f, 100.f, false, 0, 10.f, 1.f, XOR(L"%"));
		rot_speed_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		rot_speed_walk.AddShowCallback(callbacks::IsWalkYawRotate);
		RegisterElement(&rot_speed_walk);

		rand_update_walk.setup("", XOR("rand_update_walk"), 0.f, 1.f, false, 1, 0.f, 0.1f);
		rand_update_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		rand_update_walk.AddShowCallback(callbacks::IsWalkYawRandom);
		RegisterElement(&rand_update_walk);

		dir_walk.setup(XOR("Direction"), XOR("dir_walk"), { XOR("Auto"), XOR("Backwards"), XOR("Left"), XOR("Right"), XOR("Custom") });
		dir_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		dir_walk.AddShowCallback(callbacks::WalkHasYaw);
		RegisterElement(&dir_walk);

		dir_time_walk.setup("", XOR("dir_time_walk"), 0.f, 10.f, false, 0, 0.f, 1.f, XOR(L"s"));
		dir_time_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		dir_time_walk.AddShowCallback(callbacks::WalkHasYaw);
		dir_time_walk.AddShowCallback(callbacks::IsWalkDirAuto);
		RegisterElement(&dir_time_walk);

		dir_custom_walk.setup("", XOR("dir_custom_walk"), -180.f, 180.f, false, 0, 0.f, 5.f, XOR(L"°"));
		dir_custom_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		dir_custom_walk.AddShowCallback(callbacks::WalkHasYaw);
		dir_custom_walk.AddShowCallback(callbacks::IsWalkDirCustom);
		RegisterElement(&dir_custom_walk);

		base_angle_walk.setup(XOR("Base angle"), XOR("base_angle_walk"), { XOR("Off"), XOR("Static"), XOR("Away crosshair"), XOR("Away distance") });
		base_angle_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		base_angle_walk.AddShowCallback(callbacks::WalkHasYaw);
		RegisterElement(&base_angle_walk);

		// air.
		pitch_air.setup(XOR("Pitch"), XOR("pitch_air"), { XOR("Off"), XOR("Down"), XOR("Up"), XOR("Random"), XOR("Ideal") });
		pitch_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		RegisterElement(&pitch_air);

		yaw_air.setup(XOR("Yaw"), XOR("yaw_air"), { XOR("Off"), XOR("Direction"), XOR("Jitter"), XOR("Rotate"), XOR("Random") });
		yaw_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		RegisterElement(&yaw_air);

		jitter_range_air.setup("", XOR("jitter_range_air"), 1.f, 180.f, false, 0, 45.f, 5.f, XOR(L"°"));
		jitter_range_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		jitter_range_air.AddShowCallback(callbacks::IsAirYawJitter);
		RegisterElement(&jitter_range_air);

		rot_range_air.setup("", XOR("rot_range_air"), 0.f, 360.f, false, 0, 360.f, 5.f, XOR(L"°"));
		rot_range_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		rot_range_air.AddShowCallback(callbacks::IsAirYawRotate);
		RegisterElement(&rot_range_air);

		rot_speed_air.setup("", XOR("rot_speed_air"), 1.f, 100.f, false, 0, 10.f, 1.f, XOR(L"%"));
		rot_speed_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		rot_speed_air.AddShowCallback(callbacks::IsAirYawRotate);
		RegisterElement(&rot_speed_air);

		rand_update_air.setup("", XOR("rand_update_air"), 0.f, 1.f, false, 1, 0.f, 0.1f);
		rand_update_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		rand_update_air.AddShowCallback(callbacks::IsAirYawRandom);
		RegisterElement(&rand_update_air);

		dir_air.setup(XOR("Direction"), XOR("dir_air"), { XOR("Auto"), XOR("Backwards"), XOR("Left"), XOR("Right"), XOR("Custom") });
		dir_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		dir_air.AddShowCallback(callbacks::AirHasYaw);
		RegisterElement(&dir_air);

		dir_time_air.setup("", XOR("dir_time_air"), 0.f, 10.f, false, 0, 0.f, 1.f, XOR(L"s"));
		dir_time_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		dir_time_air.AddShowCallback(callbacks::AirHasYaw);
		dir_time_air.AddShowCallback(callbacks::IsAirDirAuto);
		RegisterElement(&dir_time_air);

		dir_custom_air.setup("", XOR("dir_custom_air"), -180.f, 180.f, false, 0, 0.f, 5.f, XOR(L"°"));
		dir_custom_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		dir_custom_air.AddShowCallback(callbacks::AirHasYaw);
		dir_custom_air.AddShowCallback(callbacks::IsAirDirCustom);
		RegisterElement(&dir_custom_air);

		base_angle_air.setup(XOR("Base angle"), XOR("base_angle_air"), { XOR("Off"), XOR("Static"), XOR("Away crosshair"), XOR("Away distance") });
		base_angle_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		base_angle_air.AddShowCallback(callbacks::AirHasYaw);
		RegisterElement(&base_angle_air);

		body_fake_air.setup(XOR("Fake body"), XOR("body_fake_air"), { XOR("Off"), XOR("Left"), XOR("Right"), XOR("Opposite"), XOR("180z") });
		body_fake_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		body_fake_air.AddShowCallback(callbacks::AirHasYaw);
		RegisterElement(&body_fake_air);

		/*
		distortion.setup(XOR("distortion"), XOR("distortion"));
		RegisterElement(&distortion);

		distortion_amount.setup("", XOR("distortion_amount"), 1.f, 360.f, false, 0, 75.f, 5.f, XOR(L"�"));
		distortion_amount.AddShowCallback(callbacks::DistortionEnabled);
		RegisterElement(&distortion_amount);

		distortion_speed.setup("", XOR("distortion_speed"), 1.f, 100.f, false, 0, 45.f, 5.f, XOR(L"%"));
		distortion_speed.AddShowCallback(callbacks::DistortionEnabled);
		RegisterElement(&distortion_speed);

		force_turn.setup(XOR("force turn"), XOR("force_turn"));
		force_turn.AddShowCallback(callbacks::DistortionEnabled);
		RegisterElement(&force_turn);
		*/

		// col2.
		fake_yaw.setup(XOR("Fake yaw"), XOR("fake_yaw"), { XOR("Off"), XOR("Default"), XOR("Relative"), XOR("Jitter"), XOR("Rotate"), XOR("Random"), XOR("Local view"), XOR("Baconator") });
		RegisterElement(&fake_yaw, 1);

		fake_relative.setup("", XOR("fake_relative"), -90.f, 90.f, false, 0, 0.f, 5.f, XOR(L"°"));
		fake_relative.AddShowCallback(callbacks::IsFakeAntiAimRelative);
		RegisterElement(&fake_relative, 1);

		fake_jitter_range.setup("", XOR("fake_jitter_range"), 1.f, 90.f, false, 0, 0.f, 5.f, XOR(L"°"));
		fake_jitter_range.AddShowCallback(callbacks::IsFakeAntiAimJitter);
		RegisterElement(&fake_jitter_range, 1);

		// col 2.
		lag_enable.setup(XOR("Fake-lag"), XOR("lag_enable"));
		RegisterElement(&lag_enable, 1);

		lag_active.setup("", XOR("lag_active"), { XOR("Move"), XOR("Air"), XOR("Crouch") }, false);
		RegisterElement(&lag_active, 1);

		lag_mode.setup("", XOR("lag_mode"), { XOR("Max"), XOR("Break"), XOR("Random"), XOR("Break step") }, false);
		RegisterElement(&lag_mode, 1);

		lag_limit.setup(XOR("Limit"), XOR("lag_limit"), 2, 16, true, 0, 2, 1.f);
		RegisterElement(&lag_limit, 1);

		lag_land.setup(XOR("On land"), XOR("lag_land"));
		RegisterElement(&lag_land, 1);

		manul_antiaim.setup(XOR("Show manual anti-aim"), XOR("manual_antiaim"));
		RegisterElement(&manul_antiaim, 1);

		color_manul_antiaim.setup(XOR("Manual anti-aim color"), XOR("color_manul_antiaim"), colors::light_blue);
		color_manul_antiaim.AddShowCallback(callbacks::MANUALCOL);
		RegisterElement(&color_manul_antiaim, 1);

		draw_angles.setup(XOR("Draw angles"), XOR("draw_angles"));
		RegisterElement(&draw_angles, 1);

		//draw_angles_chams.setup(XOR("Draw fake chams"), XOR("draw_angles_chams"));
		//RegisterElement(&draw_angles_chams, 1);

		//color_draw_angles_chams.setup(XOR("Color fake chams"), XOR("color_draw_angles_chams"), colors::white);
		//RegisterElement(&color_draw_angles_chams, 1);

		//draw_angles_chams_blend.setup("", XOR("draw_angles_chams_blend"), 10.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		//RegisterElement(&draw_angles_chams_blend, 1);

		left.setup(XOR("Left"), XOR("left"));
		left.SetToggleCallback(callbacks::ToggleLeft);
		RegisterElement(&left);

		right.setup(XOR("Right"), XOR("right"));
		right.SetToggleCallback(callbacks::ToggleRight);
		RegisterElement(&right);

		back.setup(XOR("Back"), XOR("back"));
		back.SetToggleCallback(callbacks::ToggleBack);
		RegisterElement(&back);


	}
};

class PlayersTab : public Tab {
public:

	//enemy
	Checkbox box_enemy;
	Colorpicker   col_box_enemy;
	Checkbox      dormant;
	Checkbox name_enemy;
	Colorpicker   col_name_enemy;
	Checkbox glow;
	Colorpicker   glow_enemy;
	Slider        glow_blend;
	Checkbox health_enemy;
	Dropdown health_style;
	Colorpicker   health_1;
	Colorpicker   health_2;
	Checkbox weapon_enemy;
	Dropdown      weapon_mode;
	Checkbox skeleton_enemy;
	Colorpicker   col_skeleton_enemy;
	Checkbox      ammo;
	Colorpicker   ammo_color;
	MultiDropdown flags_enemy;


	//friendly
	Checkbox   box_friendly;
	Colorpicker   col_box_friendly;
	Checkbox name_friendly;
	Colorpicker glow_friendly;

	Checkbox health_friendly;
	Checkbox weapon_friendly;
	Checkbox skeleton_friendly;
	MultiDropdown flags_friendly;
	Colorpicker   col_skeleton_friendly;

	//col 2
	Dropdown	  chams_entity_selection;
	Checkbox      chams_local;
	Checkbox      fake_indicator;
	Dropdown	  chams_local_mat;
	Colorpicker   chams_local_col;
	Colorpicker   chams_local2_col;
	Slider        chams_local_blend;
	Checkbox      chams_local_scope;
	Slider		  chams_local_scope_blend;

	MultiDropdown chams_enemy;
	Dropdown	  chams_enemy_mat;
	Colorpicker   chams_enemy_vis;
	Colorpicker   chams_enemy2_vis;
	Colorpicker   chams_enemy_invis;
	Colorpicker   chams_enemy2_invis;
	Slider        chams_enemy_blend;
	Checkbox      chams_enemy_history;
	Dropdown	  chams_enemy_history_mat;
	Colorpicker   chams_enemy_history_col;
	Slider        chams_enemy_history_blend;

	MultiDropdown chams_friendly;
	Dropdown	  chams_friendly_mat;
	Colorpicker   chams_friendly_vis;
	Colorpicker   chams_friendly_invis;
	Slider        chams_friendly_blend;

public:
	void init() {
		SetTitle(XOR("Players"));


		//enemy
		box_enemy.setup(XOR("Box"), XOR("box_enemy"));
		RegisterElement(&box_enemy);

		col_box_enemy.setup(XOR("Box color"), XOR("col_box_enemy"), { 255, 255, 255 });
		RegisterElement(&col_box_enemy);

		dormant.setup(XOR("Dormant enemies"), XOR("dormant"));
		RegisterElement(&dormant);

		name_enemy.setup(XOR("Name"), XOR("name_enemy"));
		RegisterElement(&name_enemy);

		col_name_enemy.setup(XOR("Name color"), XOR("col_name_color"), colors::white);
		RegisterElement(&col_name_enemy);

		glow.setup(XOR("Glow"), XOR("glow"));
		RegisterElement(&glow);

		glow_enemy.setup(XOR("Enemy color"), XOR("glow_enemy"), { 132, 60, 120 });
		RegisterElement(&glow_enemy);

		glow_blend.setup("", XOR("glow_blend"), 10.f, 100.f, false, 0, 60.f, 1.f, XOR(L"%")); //38
		RegisterElement(&glow_blend);

		health_enemy.setup(XOR("Health"), XOR("health_enemy"));
		RegisterElement(&health_enemy);

		health_style.setup(XOR("Health style"), XOR("health_style"), { XOR("Normal"), XOR("Gradient") });
		RegisterElement(&health_style);

		health_1.setup(XOR("Health gradient 1"), XOR("health_1"), { 132, 60, 120 });
		health_1.AddShowCallback(callbacks::health_selection);
		RegisterElement(&health_1);

		health_2.setup(XOR("Health gradient 2"), XOR("health_2"), { 132, 60, 120 });
		health_2.AddShowCallback(callbacks::health_selection);
		RegisterElement(&health_2);


		skeleton_enemy.setup(XOR("Skeleton"), XOR("skeleton_enemy"));
		RegisterElement(&skeleton_enemy);

		col_skeleton_enemy.setup(XOR("Enemy color"), XOR("col_skeleton_enemy"), { 255, 255, 255 });
		RegisterElement(&col_skeleton_enemy);

		flags_enemy.setup(XOR("Flags enemy"), XOR("flags_enemy"), { XOR("Money"), XOR("Armor"), XOR("Scoped"), XOR("Flashed"), XOR("Reloading"), XOR("Bomb"),  XOR("Ping"), XOR("Resolver") });
		RegisterElement(&flags_enemy);

		weapon_enemy.setup(XOR("Weapon"), XOR("weapon_enemy"));
		RegisterElement(&weapon_enemy);

		ammo.setup(XOR("Ammo"), XOR("ammo"));
		RegisterElement(&ammo);

		ammo_color.setup(XOR("Color"), XOR("ammo_color"), colors::burgundy);
		RegisterElement(&ammo_color);



		//col 2

		chams_entity_selection.setup("Chams selection", XOR("chams_entity_selection"), { XOR("Local"), XOR("Enemy"), XOR("Friendly"), XOR("History") });
		RegisterElement(&chams_entity_selection, 1);

		chams_local.setup(XOR("Chams local"), XOR("chams_local"));
		chams_local.AddShowCallback(callbacks::IsChamsSelection0);
		RegisterElement(&chams_local, 1);

		chams_local_mat.setup(XOR("Chams local material"), XOR("chams_local_mat"), { XOR("Material"), XOR("Flat"), XOR("Metallic"), XOR("Shaded"), XOR("Glow"), XOR("Stick man"), XOR("test") });
		chams_local_mat.AddShowCallback(callbacks::IsChamsSelection0);
		RegisterElement(&chams_local_mat, 1);

		chams_local_col.setup(XOR("Color"), XOR("chams_local_col"), { 255, 255, 200 });
		chams_local_col.AddShowCallback(callbacks::IsChamsSelection0);
		RegisterElement(&chams_local_col, 1);

		chams_local2_col.setup(XOR("Glow color"), XOR("chams_local2_col"), { 255, 255, 200 });
		chams_local2_col.AddShowCallback(callbacks::LocalGlowChamsSelection);
		RegisterElement(&chams_local2_col, 1);

		chams_local_blend.setup("", XOR("chams_local_blend"), 0.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		chams_local_blend.AddShowCallback(callbacks::IsChamsSelection0);
		RegisterElement(&chams_local_blend, 1);

		chams_local_scope.setup(XOR("Blend when scoped"), XOR("chams_local_scope"));
		chams_local_scope.AddShowCallback(callbacks::IsChamsSelection0);
		RegisterElement(&chams_local_scope, 1);

		chams_enemy.setup(XOR("Chams enemy"), XOR("chams_enemy"), { XOR("Visible"), XOR("Invisible") });
		chams_enemy.AddShowCallback(callbacks::IsChamsSelection1);
		RegisterElement(&chams_enemy, 1);

		chams_enemy_mat.setup(XOR("Chams enemy material"), XOR("chams_enemy_mat"), { XOR("Material"), XOR("Flat"), XOR("Metallic"), XOR("Shaded"), XOR("Glow"), XOR("test1"), XOR("test2") });
		chams_enemy_mat.AddShowCallback(callbacks::IsChamsSelection1);
		RegisterElement(&chams_enemy_mat, 1);

		chams_enemy_vis.setup(XOR("Color visible"), XOR("chams_enemy_vis"), colors::gamesense_accent);
		chams_enemy_vis.AddShowCallback(callbacks::IsChamsSelection1);
		RegisterElement(&chams_enemy_vis, 1);

		chams_enemy2_vis.setup(XOR("Glow color"), XOR("chams_enemy2_vis"), { 255, 255, 200 });
		chams_enemy2_vis.AddShowCallback(callbacks::EnemyGlowChamsSelection);
		RegisterElement(&chams_enemy2_vis, 1);

		chams_enemy_invis.setup(XOR("Color invisible"), XOR("chams_enemy_invis"), { 60, 120, 180 });
		chams_enemy_invis.AddShowCallback(callbacks::IsChamsSelection1);
		RegisterElement(&chams_enemy_invis, 1);

		chams_enemy2_invis.setup(XOR("Glow color"), XOR("chams_enemy2_invis"), { 255, 255, 200 });
		chams_enemy2_invis.AddShowCallback(callbacks::EnemyGlowChamsSelection);
		RegisterElement(&chams_enemy2_invis, 1);

		chams_enemy_blend.setup("", XOR("chams_enemy_blend"), 10.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%")); //38 for exact skeet
		chams_enemy_blend.AddShowCallback(callbacks::IsChamsSelection1);
		RegisterElement(&chams_enemy_blend, 1);

		chams_friendly.setup(XOR("Chams friendly"), XOR("chams_friendly"), { XOR("visible"), XOR("invisible") });
		chams_friendly.AddShowCallback(callbacks::IsChamsSelection2);
		RegisterElement(&chams_friendly, 1);

		chams_friendly_mat.setup(XOR("Chams friendly material"), XOR("chams_friendly_mat"), { XOR("material"), XOR("Flat"), XOR("Metallic"), XOR("Shaded"), XOR("Glow") });
		chams_friendly_mat.AddShowCallback(callbacks::IsChamsSelection2);
		RegisterElement(&chams_friendly_mat, 1);

		chams_friendly_vis.setup(XOR("Color visible"), XOR("chams_friendly_vis"), { 255, 200, 0 });
		chams_friendly_vis.AddShowCallback(callbacks::IsChamsSelection2);
		RegisterElement(&chams_friendly_vis, 1);

		chams_friendly_invis.setup(XOR("Color invisible"), XOR("chams_friendly_invis"), { 255, 50, 0 });
		chams_friendly_invis.AddShowCallback(callbacks::IsChamsSelection2);
		RegisterElement(&chams_friendly_invis, 1);

		chams_friendly_blend.setup("", XOR("chams_friendly_blend"), 10.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		chams_friendly_blend.AddShowCallback(callbacks::IsChamsSelection2);
		RegisterElement(&chams_friendly_blend, 1);

		chams_enemy_history.setup(XOR("Chams history"), XOR("chams_history"));
		chams_enemy_history.AddShowCallback(callbacks::IsChamsSelection3);
		RegisterElement(&chams_enemy_history, 1);

		chams_enemy_history_mat.setup(XOR("Chams history material"), XOR("chams_enemy_history_mat"), { XOR("material"), XOR("Flat"), XOR("Metallic"), XOR("Shaded"), XOR("Glow") });
		chams_enemy_history_mat.AddShowCallback(callbacks::IsChamsSelection3);
		RegisterElement(&chams_enemy_history_mat, 1);

		chams_enemy_history_col.setup(XOR("Color"), XOR("chams_history_col"), { 255, 255, 200 });
		chams_enemy_history_col.AddShowCallback(callbacks::IsChamsSelection3);
		RegisterElement(&chams_enemy_history_col, 1);

		chams_enemy_history_blend.setup("", XOR("chams_history_blend"), 10.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		chams_enemy_history_blend.AddShowCallback(callbacks::IsChamsSelection3);
		RegisterElement(&chams_enemy_history_blend, 1);
	}
};

class ModelsTab : public Tab {
public:

	Checkbox      offscreen;
	Colorpicker   offscreen_color;
	Slider offscreen_mode;
	Slider offscreen_mode1;
	Checkbox      lby_update;
	Colorpicker   lby_update_color;

	Checkbox grenwarning;
	Colorpicker grenlocal;
	Colorpicker grenenemy;
	Colorpicker grenfriendly;

public:
	void init() {
		SetTitle(XOR("Other"));

		//friendly
		offscreen.setup(XOR("Offscreen esp"), XOR("offscreen"));
		RegisterElement(&offscreen);

		offscreen_color.setup(XOR("Offscreen esp color"), XOR("offscreen_color"), colors::white);
		RegisterElement(&offscreen_color);

		offscreen_mode.setup(XOR("Offscreen size"), XOR("offscreen_mode"), 20.f, 200.f, true, 0, 100.f, 1.f, XOR(L""));
		RegisterElement(&offscreen_mode);

		offscreen_mode1.setup(XOR("Offscreen position"), XOR("offscreen_mode1"), 20.f, 200.f, true, 0, 200.f, 1.f, XOR(L""));
		RegisterElement(&offscreen_mode1);

		lby_update.setup(XOR("Lby update"), XOR("lby_update"));
		RegisterElement(&lby_update);

		lby_update_color.setup(XOR("Color"), XOR("lby_update_color"), colors::orange);
		RegisterElement(&lby_update_color);



		grenwarning.setup(XOR("Grenade warning"), XOR("grenwarning"));
		RegisterElement(&grenwarning, 1);


		grenlocal.setup(XOR("Local color"), XOR("gren_local"), colors::white);
		RegisterElement(&grenlocal, 1);

		grenenemy.setup(XOR("Enemy color"), XOR("gren_enemy"), colors::red);
		RegisterElement(&grenenemy, 1);

		grenfriendly.setup(XOR("Friendly color"), XOR("gren_friendly"), colors::yellowgreen);
		RegisterElement(&grenfriendly, 1);

	}
};

class VisualsTab : public Tab {
public:
	Checkbox      distance;
	Checkbox      items;
	Colorpicker   item_color;
	Checkbox      ammo;
	Colorpicker   dropammo_color;
	Checkbox      proj;
	Colorpicker   proj_color;
	Checkbox proj_range;
	MultiDropdown planted_c4;
	Checkbox      disableteam;
	Dropdown	  world;
	Slider        night_darkness;
	//	  world_color;
	Checkbox      transparent_props;
	Slider		  transparent_props_amount;
	Checkbox      enemy_radar;
	/*
	Checkbox	FogOverride; // butt
	Colorpicker	FogColor; // color
	Slider		FogStart; // slider
	Slider		FogEnd; // slider
	Slider		Fogdensity; // slider
	*/
	//Colorpicker      glowcolor;
	Checkbox bullet_tracers;
	Colorpicker bullet_tracers_col;
	Slider bullet_tracers_time;


	// col2.
	MultiDropdown removals;
	Checkbox removalstest;
	Checkbox      fov;
	Slider        fov_amt;
	Checkbox      fov_scoped;
	Checkbox      viewmodel_fov;
	Slider        viewmodel_fov_amt;
	Checkbox      spectators;
	Checkbox      force_xhair;
	Checkbox      spread_xhair;
	Colorpicker   spread_xhair_col;
	Slider        spread_xhair_blend;
	Checkbox      pen_crosshair;
	Checkbox      pen_damage;
	MultiDropdown indicators;
	Checkbox	  animated_ind;
	Colorpicker	  indicators_act_col;
	Checkbox      center_ind;
	Checkbox      tracers;
	Checkbox      impact_beams;
	Colorpicker   impact_beams_color;
	Colorpicker   impact_beams_hurt_color;
	Slider        impact_beams_time;
	Keybind       thirdperson;
	Slider		  thirdperson_distance;

public:
	void init() {
		SetTitle(XOR("Visuals"));

		items.setup(XOR("Dropped weapons"), XOR("items"));
		RegisterElement(&items);

		distance.setup(XOR("Distance weapons"), XOR("distance"));
		RegisterElement(&distance);

		item_color.setup(XOR("Color"), XOR("item_color"), colors::white);
		RegisterElement(&item_color);

		ammo.setup(XOR("Dropped weapons ammo"), XOR("ammo"));
		RegisterElement(&ammo);

		dropammo_color.setup(XOR("Color"), XOR("dropammo_color"), colors::light_blue);
		RegisterElement(&dropammo_color);

		proj.setup(XOR("Projectiles"), XOR("proj"));
		RegisterElement(&proj);

		proj_color.setup(XOR("Color"), XOR("proj_color"), colors::white);
		RegisterElement(&proj_color);

		proj_range.setup(XOR("Molotov range"), XOR("molotov_range"));
		RegisterElement(&proj_range);


		planted_c4.setup(XOR("Planted c4"), XOR("planted_c4"), { XOR("On screen (2D)"), XOR("On bomb (3D)"), XOR("Bomb timer (2D)"), XOR("Bomb rimer (3D)") });
		RegisterElement(&planted_c4);

		disableteam.setup(XOR("Do not render teammates"), XOR("disableteam"));
		RegisterElement(&disableteam);

		world.setup(XOR("World"), XOR("World"), { XOR("Off"), XOR("Night"), XOR("Fullbright") });
		world.SetCallback(Visuals::ModulateWorld);
		RegisterElement(&world);

		night_darkness.setup("", XOR("night_darkness"), 0.f, 100.f, false, 0, 10.f, 1.f, XOR(L"%"));
		night_darkness.SetCallback(Visuals::ModulateWorld);
		night_darkness.AddShowCallback(callbacks::IsNightMode);
		RegisterElement(&night_darkness);

		//world_color.setup(XOR("color"), XOR("world_color"), colors::burgundy);
		//RegisterElement(&world_color);

		transparent_props.setup(XOR("Transparent props"), XOR("transparent_props"));
		transparent_props.SetCallback(Visuals::ModulateWorld);
		RegisterElement(&transparent_props);

		transparent_props_amount.setup("", XOR("transparent_props_amount"), 0.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		transparent_props_amount.SetCallback(Visuals::ModulateWorld);
		transparent_props_amount.AddShowCallback(callbacks::IsTransparentProps);
		RegisterElement(&transparent_props_amount);

		enemy_radar.setup(XOR("Force enemies on radar"), XOR("enemy_radar"));
		RegisterElement(&enemy_radar);



		bullet_tracers.setup(XOR("Bullet tracers"), XOR("bullet_tracers"));
		RegisterElement(&bullet_tracers);

		bullet_tracers_time.setup(XOR(""), XOR("bullet_tracers_time"), 1.f, 10.f, false, 0, 1.f, 1.f, XOR(L"s"));
		bullet_tracers_time.AddShowCallback(callbacks::BULLET_TRACERS);
		RegisterElement(&bullet_tracers_time);

		bullet_tracers_col.setup(XOR("Bullet tracers color"), XOR("bullet_tracers_col"), colors::burgundy);
		bullet_tracers_col.AddShowCallback(callbacks::BULLET_TRACERS);
		RegisterElement(&bullet_tracers_col);


		// col2.
		removals.setup(XOR("Removals"), XOR("removals"), { XOR("Visual recoil"), XOR("Smoke grenades"), XOR("Fog"), XOR("Flashbangs"), ("Scope") });
		RegisterElement(&removals, 1);

		removalstest.setup(XOR("Scope test"), XOR("scopetest"));
		RegisterElement(&removalstest, 1);

		fov.setup(XOR("Override fov"), XOR("fov"));
		RegisterElement(&fov, 1);

		fov_amt.setup("", XOR("fov_amt"), 60.f, 140.f, false, 0, 90.f, 1.f, XOR(L"°"));
		RegisterElement(&fov_amt, 1);

		fov_scoped.setup(XOR("Override fov when scoped"), XOR("fov_scoped"));
		RegisterElement(&fov_scoped, 1);

		viewmodel_fov.setup(XOR("Override viewmodel fov"), XOR("viewmodel_fov"));
		RegisterElement(&viewmodel_fov, 1);

		viewmodel_fov_amt.setup("", XOR("viewmodel_fov_amt"), 60.f, 140.f, false, 0, 90.f, 1.f, XOR(L"°"));
		RegisterElement(&viewmodel_fov_amt, 1);

		spectators.setup(XOR("Show spectators"), XOR("spectators"));
		RegisterElement(&spectators, 1);

		force_xhair.setup(XOR("Force crosshair"), XOR("force_xhair"));
		RegisterElement(&force_xhair, 1);

		spread_xhair.setup(XOR("Visualize spread"), XOR("spread_xhair"));
		RegisterElement(&spread_xhair, 1);

		spread_xhair_col.setup(XOR("Visualize spread color"), XOR("spread_xhair_col"), colors::burgundy);
		RegisterElement(&spread_xhair_col, 1);

		spread_xhair_blend.setup("", XOR("spread_xhair_blend"), 10.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&spread_xhair_blend, 1);

		pen_crosshair.setup(XOR("Penetration crosshair"), XOR("pen_xhair"));
		RegisterElement(&pen_crosshair, 1);

		pen_damage.setup(XOR("Penetration crosshair damage"), XOR("pen_damage"));
		RegisterElement(&pen_damage, 1);

		indicators.setup(XOR("Indicators"), XOR("indicators"), { XOR("LBY"), XOR("Lag compensation"), XOR("Ping"), XOR("Mindmg override"), ("Body aim")});
		RegisterElement(&indicators, 1);

		animated_ind.setup(XOR("Animated indicators"), XOR("animated_ind"));
		RegisterElement(&animated_ind, 1);

		indicators_act_col.setup(XOR("Indicators active color"), XOR("indicators_act_col"), colors::light_blue);
		RegisterElement(&indicators_act_col, 1);


		tracers.setup(XOR("Grenade simulation"), XOR("tracers"));
		RegisterElement(&tracers, 1);


		impact_beams.setup(XOR("Bullet impact"), XOR("impact_beams"));
		RegisterElement(&impact_beams, 1);

		impact_beams_time.setup(XOR(""), XOR("impact_beams_time"), 1.f, 10.f, false, 0, 1.f, 1.f, XOR(L"s"));
		impact_beams_time.AddShowCallback(callbacks::IMPACT_BEAMS);
		RegisterElement(&impact_beams_time, 1);

		impact_beams_color.setup(XOR("Bullet impact color"), XOR("impact_beams_color"), colors::light_blue);
		impact_beams_color.AddShowCallback(callbacks::IMPACT_BEAMS);
		RegisterElement(&impact_beams_color, 1);

		impact_beams_hurt_color.setup(XOR("Bullet impact hurt color"), XOR("impact_beams_hurt_color"), colors::red);
		impact_beams_hurt_color.AddShowCallback(callbacks::IMPACT_BEAMS);
		RegisterElement(&impact_beams_hurt_color, 1);


		thirdperson.setup(XOR("Thirdperson"), XOR("thirdperson"));
		thirdperson.SetToggleCallback(callbacks::ToggleThirdPerson);
		RegisterElement(&thirdperson, 1);

		thirdperson_distance.setup(XOR(""), XOR("thirdperson_distance"), 50.f, 300.f, false, 0, 150.f, 1.f, XOR(L"°"));
		RegisterElement(&thirdperson_distance, 1);
	}
};

class MovementTab : public Tab {
public:
	Checkbox bhop;
	Checkbox airduck;
	Checkbox autostrafe;
	Keybind  cstrafe;
	Keybind  astrafe;
	Keybind  zstrafe;
	Slider   z_freq;
	Slider   z_dist;

	Keybind  fakewalk;
	Keybind  cripwalk;
	Checkbox autopeekcheck;
	Keybind  autopeek;
	Colorpicker autopeekindact;
	//Colorpicker autopeekindinact;
	Checkbox autostop_always_on;
	//Checkbox auto_stop_between_shots;

public:
	void init() {
		SetTitle(XOR("Move"));

		bhop.setup(XOR("Automatic jump"), XOR("bhop"));
		RegisterElement(&bhop);

		airduck.setup(XOR("Duck in air"), XOR("airduck"));
		RegisterElement(&airduck);

		autostrafe.setup(XOR("Automatic strafe"), XOR("autostrafe"));
		RegisterElement(&autostrafe);

		cstrafe.setup(XOR("C-strafe"), XOR("cstrafe"));
		RegisterElement(&cstrafe);

		astrafe.setup(XOR("A-strafe"), XOR("astrafe"));
		RegisterElement(&astrafe);

		zstrafe.setup(XOR("Z-strafe"), XOR("zstrafe"));
		RegisterElement(&zstrafe);

		z_freq.setup("", XOR("z_freq"), 1.f, 100.f, false, 0, 50.f, 0.5f, XOR(L"hz"));
		RegisterElement(&z_freq);

		z_dist.setup("", XOR("z_dist"), 1.f, 100.f, false, 0, 20.f, 0.5f, XOR(L"%"));
		RegisterElement(&z_dist);

		fakewalk.setup(XOR("Fake-walk"), XOR("fakewalk"));
		RegisterElement(&fakewalk, 1);


		autopeekcheck.setup(XOR("Autopeek"), XOR("autopeekcheck"));
		RegisterElement(&autopeekcheck, 1);

		autopeek.setup(XOR("Autopeek key"), XOR("autopeek"));
		autopeek.AddShowCallback(callbacks::AUTO_PEEK);
		RegisterElement(&autopeek, 1);
		
		autopeekindact.setup(XOR("Indicator color"), XOR("autopeek_col_act"), colors::light_blue);
		autopeekindact.AddShowCallback(callbacks::AUTO_PEEK);
		RegisterElement(&autopeekindact, 1);

		//autopeekindinact.setup(XOR("Autopeek ind inactive"), XOR("autopeek_col_inact"), colors::red);
		//RegisterElement(&autopeekindinact, 1);

		//cripwalk.setup(XOR("cripwalk"), XOR("cripwalk"));
		//RegisterElement(&cripwalk, 1);


		autostop_always_on.setup(XOR("Autostop"), XOR("auto_stop"));
		RegisterElement(&autostop_always_on, 1);


	}
};

class SkinsTab : public Tab {
public:
	Checkbox enable;

	Edit     id_deagle;
	Checkbox stattrak_deagle;
	Slider   quality_deagle;
	Slider	 seed_deagle;

	Edit     id_elite;
	Checkbox stattrak_elite;
	Slider   quality_elite;
	Slider	 seed_elite;

	Edit     id_fiveseven;
	Checkbox stattrak_fiveseven;
	Slider   quality_fiveseven;
	Slider	 seed_fiveseven;

	Edit     id_glock;
	Checkbox stattrak_glock;
	Slider   quality_glock;
	Slider	 seed_glock;

	Edit     id_ak47;
	Checkbox stattrak_ak47;
	Slider   quality_ak47;
	Slider	 seed_ak47;

	Edit     id_aug;
	Checkbox stattrak_aug;
	Slider   quality_aug;
	Slider	 seed_aug;

	Edit     id_awp;
	Checkbox stattrak_awp;
	Slider   quality_awp;
	Slider	 seed_awp;

	Edit     id_famas;
	Checkbox stattrak_famas;
	Slider   quality_famas;
	Slider	 seed_famas;

	Edit     id_g3sg1;
	Checkbox stattrak_g3sg1;
	Slider   quality_g3sg1;
	Slider	 seed_g3sg1;

	Edit     id_galil;
	Checkbox stattrak_galil;
	Slider   quality_galil;
	Slider	 seed_galil;

	Edit     id_m249;
	Checkbox stattrak_m249;
	Slider   quality_m249;
	Slider	 seed_m249;

	Edit     id_m4a4;
	Checkbox stattrak_m4a4;
	Slider   quality_m4a4;
	Slider	 seed_m4a4;

	Edit     id_mac10;
	Checkbox stattrak_mac10;
	Slider   quality_mac10;
	Slider	 seed_mac10;

	Edit     id_p90;
	Checkbox stattrak_p90;
	Slider   quality_p90;
	Slider	 seed_p90;

	Edit     id_ump45;
	Checkbox stattrak_ump45;
	Slider   quality_ump45;
	Slider	 seed_ump45;

	Edit     id_xm1014;
	Checkbox stattrak_xm1014;
	Slider   quality_xm1014;
	Slider	 seed_xm1014;

	Edit     id_bizon;
	Checkbox stattrak_bizon;
	Slider   quality_bizon;
	Slider	 seed_bizon;

	Edit     id_mag7;
	Checkbox stattrak_mag7;
	Slider   quality_mag7;
	Slider	 seed_mag7;

	Edit     id_negev;
	Checkbox stattrak_negev;
	Slider   quality_negev;
	Slider	 seed_negev;

	Edit     id_sawedoff;
	Checkbox stattrak_sawedoff;
	Slider   quality_sawedoff;
	Slider	 seed_sawedoff;

	Edit     id_tec9;
	Checkbox stattrak_tec9;
	Slider   quality_tec9;
	Slider	 seed_tec9;

	Edit     id_p2000;
	Checkbox stattrak_p2000;
	Slider   quality_p2000;
	Slider	 seed_p2000;

	Edit     id_mp7;
	Checkbox stattrak_mp7;
	Slider   quality_mp7;
	Slider	 seed_mp7;

	Edit     id_mp9;
	Checkbox stattrak_mp9;
	Slider   quality_mp9;
	Slider	 seed_mp9;

	Edit     id_nova;
	Checkbox stattrak_nova;
	Slider   quality_nova;
	Slider	 seed_nova;

	Edit     id_p250;
	Checkbox stattrak_p250;
	Slider   quality_p250;
	Slider	 seed_p250;

	Edit     id_scar20;
	Checkbox stattrak_scar20;
	Slider   quality_scar20;
	Slider	 seed_scar20;

	Edit     id_sg553;
	Checkbox stattrak_sg553;
	Slider   quality_sg553;
	Slider	 seed_sg553;

	Edit     id_ssg08;
	Checkbox stattrak_ssg08;
	Slider   quality_ssg08;
	Slider	 seed_ssg08;

	Edit     id_m4a1s;
	Checkbox stattrak_m4a1s;
	Slider   quality_m4a1s;
	Slider	 seed_m4a1s;

	Edit     id_usps;
	Checkbox stattrak_usps;
	Slider   quality_usps;
	Slider	 seed_usps;

	Edit     id_cz75a;
	Checkbox stattrak_cz75a;
	Slider   quality_cz75a;
	Slider	 seed_cz75a;

	Edit     id_revolver;
	Checkbox stattrak_revolver;
	Slider   quality_revolver;
	Slider	 seed_revolver;

	Edit     id_bayonet;
	Checkbox stattrak_bayonet;
	Slider   quality_bayonet;
	Slider	 seed_bayonet;

	Edit     id_flip;
	Checkbox stattrak_flip;
	Slider   quality_flip;
	Slider	 seed_flip;

	Edit     id_gut;
	Checkbox stattrak_gut;
	Slider   quality_gut;
	Slider	 seed_gut;

	Edit     id_karambit;
	Checkbox stattrak_karambit;
	Slider   quality_karambit;
	Slider	 seed_karambit;

	Edit     id_m9;
	Checkbox stattrak_m9;
	Slider   quality_m9;
	Slider	 seed_m9;

	Edit     id_huntsman;
	Checkbox stattrak_huntsman;
	Slider   quality_huntsman;
	Slider	 seed_huntsman;

	Edit     id_falchion;
	Checkbox stattrak_falchion;
	Slider   quality_falchion;
	Slider	 seed_falchion;

	Edit     id_bowie;
	Checkbox stattrak_bowie;
	Slider   quality_bowie;
	Slider	 seed_bowie;

	Edit     id_butterfly;
	Checkbox stattrak_butterfly;
	Slider   quality_butterfly;
	Slider	 seed_butterfly;

	Edit     id_daggers;
	Checkbox stattrak_daggers;
	Slider   quality_daggers;
	Slider	 seed_daggers;

	// col 2.
	Dropdown knife;
	Dropdown glove;
	Edit	 glove_id;

public:
	void init() {
		SetTitle(XOR("Skins"));

		enable.setup(XOR("Enable"), XOR("skins_enable"));
		enable.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&enable);

		// weapons...
		id_deagle.setup(XOR("Paintkit id"), XOR("id_deagle"), 3);
		id_deagle.SetCallback(callbacks::SkinUpdate);
		id_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&id_deagle);

		stattrak_deagle.setup(XOR("Stattrak"), XOR("stattrak_deagle"));
		stattrak_deagle.SetCallback(callbacks::SkinUpdate);
		stattrak_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&stattrak_deagle);

		quality_deagle.setup(XOR("Quality"), XOR("quality_deagle"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_deagle.SetCallback(callbacks::SkinUpdate);
		quality_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&quality_deagle);

		seed_deagle.setup(XOR("Seed"), XOR("seed_deagle"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_deagle.SetCallback(callbacks::SkinUpdate);
		seed_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&seed_deagle);

		id_elite.setup(XOR("Paintkit id"), XOR("id_elite"), 3);
		id_elite.SetCallback(callbacks::SkinUpdate);
		id_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&id_elite);

		stattrak_elite.setup(XOR("Stattrak"), XOR("stattrak_elite"));
		stattrak_elite.SetCallback(callbacks::SkinUpdate);
		stattrak_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&stattrak_elite);

		quality_elite.setup(XOR("Quality"), XOR("quality_elite"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_elite.SetCallback(callbacks::SkinUpdate);
		quality_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&quality_elite);

		seed_elite.setup(XOR("Seed"), XOR("seed_elite"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_elite.SetCallback(callbacks::SkinUpdate);
		seed_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&seed_elite);

		id_fiveseven.setup(XOR("Paintkit id"), XOR("id_fiveseven"), 3);
		id_fiveseven.SetCallback(callbacks::SkinUpdate);
		id_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&id_fiveseven);

		stattrak_fiveseven.setup(XOR("Stattrak"), XOR("stattrak_fiveseven"));
		stattrak_fiveseven.SetCallback(callbacks::SkinUpdate);
		stattrak_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&stattrak_fiveseven);

		quality_fiveseven.setup(XOR("Quality"), XOR("quality_fiveseven"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_fiveseven.SetCallback(callbacks::SkinUpdate);
		quality_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&quality_fiveseven);

		seed_fiveseven.setup(XOR("Seed"), XOR("seed_fiveseven"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_fiveseven.SetCallback(callbacks::SkinUpdate);
		seed_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&seed_fiveseven);

		id_glock.setup(XOR("Paintkit id"), XOR("id_glock"), 3);
		id_glock.SetCallback(callbacks::SkinUpdate);
		id_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&id_glock);

		stattrak_glock.setup(XOR("Stattrak"), XOR("stattrak_glock"));
		stattrak_glock.SetCallback(callbacks::SkinUpdate);
		stattrak_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&stattrak_glock);

		quality_glock.setup(XOR("Quality"), XOR("quality_glock"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_glock.SetCallback(callbacks::SkinUpdate);
		quality_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&quality_glock);

		seed_glock.setup(XOR("Seed"), XOR("seed_glock"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_glock.SetCallback(callbacks::SkinUpdate);
		seed_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&seed_glock);

		id_ak47.setup(XOR("Paintkit id"), XOR("id_ak47"), 3);
		id_ak47.SetCallback(callbacks::SkinUpdate);
		id_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&id_ak47);

		stattrak_ak47.setup(XOR("Stattrak"), XOR("stattrak_ak47"));
		stattrak_ak47.SetCallback(callbacks::SkinUpdate);
		stattrak_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&stattrak_ak47);

		quality_ak47.setup(XOR("Quality"), XOR("quality_ak47"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_ak47.SetCallback(callbacks::SkinUpdate);
		quality_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&quality_ak47);

		seed_ak47.setup(XOR("Seed"), XOR("seed_ak47"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_ak47.SetCallback(callbacks::SkinUpdate);
		seed_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&seed_ak47);

		id_aug.setup(XOR("Paintkit id"), XOR("id_aug"), 3);
		id_aug.SetCallback(callbacks::SkinUpdate);
		id_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&id_aug);

		stattrak_aug.setup(XOR("Stattrak"), XOR("stattrak_aug"));
		stattrak_aug.SetCallback(callbacks::SkinUpdate);
		stattrak_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&stattrak_aug);

		quality_aug.setup(XOR("Quality"), XOR("quality_aug"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_aug.SetCallback(callbacks::SkinUpdate);
		quality_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&quality_aug);

		seed_aug.setup(XOR("Seed"), XOR("seed_aug"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_aug.SetCallback(callbacks::SkinUpdate);
		seed_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&seed_aug);

		id_awp.setup(XOR("Paintkit id"), XOR("id_awp"), 3);
		id_awp.SetCallback(callbacks::SkinUpdate);
		id_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&id_awp);

		stattrak_awp.setup(XOR("Stattrak"), XOR("stattrak_awp"));
		stattrak_awp.SetCallback(callbacks::SkinUpdate);
		stattrak_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&stattrak_awp);

		quality_awp.setup(XOR("Quality"), XOR("quality_awp"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_awp.SetCallback(callbacks::SkinUpdate);
		quality_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&quality_awp);

		seed_awp.setup(XOR("Seed"), XOR("seed_awp"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_awp.SetCallback(callbacks::SkinUpdate);
		seed_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&seed_awp);

		id_famas.setup(XOR("Paintkit id"), XOR("id_famas"), 3);
		id_famas.SetCallback(callbacks::SkinUpdate);
		id_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&id_famas);

		stattrak_famas.setup(XOR("Stattrak"), XOR("stattrak_famas"));
		stattrak_famas.SetCallback(callbacks::SkinUpdate);
		stattrak_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&stattrak_famas);

		quality_famas.setup(XOR("Quality"), XOR("quality_famas"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_famas.SetCallback(callbacks::SkinUpdate);
		quality_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&quality_famas);

		seed_famas.setup(XOR("Seed"), XOR("seed_famas"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_famas.SetCallback(callbacks::SkinUpdate);
		seed_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&seed_famas);

		id_g3sg1.setup(XOR("Paintkit id"), XOR("id_g3sg1"), 3);
		id_g3sg1.SetCallback(callbacks::SkinUpdate);
		id_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&id_g3sg1);

		stattrak_g3sg1.setup(XOR("Stattrak"), XOR("stattrak_g3sg1"));
		stattrak_g3sg1.SetCallback(callbacks::SkinUpdate);
		stattrak_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&stattrak_g3sg1);

		quality_g3sg1.setup(XOR("Quality"), XOR("quality_g3sg1"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_g3sg1.SetCallback(callbacks::SkinUpdate);
		quality_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&quality_g3sg1);

		seed_g3sg1.setup(XOR("Seed"), XOR("seed_g3sg1"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_g3sg1.SetCallback(callbacks::SkinUpdate);
		seed_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&seed_g3sg1);

		id_galil.setup(XOR("Paintkit id"), XOR("id_galil"), 3);
		id_galil.SetCallback(callbacks::SkinUpdate);
		id_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&id_galil);

		stattrak_galil.setup(XOR("Stattrak"), XOR("stattrak_galil"));
		stattrak_galil.SetCallback(callbacks::SkinUpdate);
		stattrak_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&stattrak_galil);

		quality_galil.setup(XOR("Quality"), XOR("quality_galil"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_galil.SetCallback(callbacks::SkinUpdate);
		quality_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&quality_galil);

		seed_galil.setup(XOR("Seed"), XOR("seed_galil"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_galil.SetCallback(callbacks::SkinUpdate);
		seed_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&seed_galil);

		id_m249.setup(XOR("Paintkit id"), XOR("id_m249"), 3);
		id_m249.SetCallback(callbacks::SkinUpdate);
		id_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&id_m249);

		stattrak_m249.setup(XOR("Stattrak"), XOR("stattrak_m249"));
		stattrak_m249.SetCallback(callbacks::SkinUpdate);
		stattrak_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&stattrak_m249);

		quality_m249.setup(XOR("Quality"), XOR("quality_m249"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_m249.SetCallback(callbacks::SkinUpdate);
		quality_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&quality_m249);

		seed_m249.setup(XOR("Seed"), XOR("seed_m249"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_m249.SetCallback(callbacks::SkinUpdate);
		seed_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&seed_m249);

		id_m4a4.setup(XOR("Paintkit id"), XOR("id_m4a4"), 3);
		id_m4a4.SetCallback(callbacks::SkinUpdate);
		id_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&id_m4a4);

		stattrak_m4a4.setup(XOR("Stattrak"), XOR("stattrak_m4a4"));
		stattrak_m4a4.SetCallback(callbacks::SkinUpdate);
		stattrak_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&stattrak_m4a4);

		quality_m4a4.setup(XOR("Quality"), XOR("quality_m4a4"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_m4a4.SetCallback(callbacks::SkinUpdate);
		quality_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&quality_m4a4);

		seed_m4a4.setup(XOR("Seed"), XOR("seed_m4a4"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_m4a4.SetCallback(callbacks::SkinUpdate);
		seed_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&seed_m4a4);

		id_mac10.setup(XOR("Paintkit id"), XOR("id_mac10"), 3);
		id_mac10.SetCallback(callbacks::SkinUpdate);
		id_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&id_mac10);

		stattrak_mac10.setup(XOR("Stattrak"), XOR("stattrak_mac10"));
		stattrak_mac10.SetCallback(callbacks::SkinUpdate);
		stattrak_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&stattrak_mac10);

		quality_mac10.setup(XOR("Quality"), XOR("quality_mac10"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_mac10.SetCallback(callbacks::SkinUpdate);
		quality_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&quality_mac10);

		seed_mac10.setup(XOR("Seed"), XOR("seed_mac10"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_mac10.SetCallback(callbacks::SkinUpdate);
		seed_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&seed_mac10);

		id_p90.setup(XOR("Paintkit id"), XOR("id_p90"), 3);
		id_p90.SetCallback(callbacks::SkinUpdate);
		id_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&id_p90);

		stattrak_p90.setup(XOR("Stattrak"), XOR("stattrak_p90"));
		stattrak_p90.SetCallback(callbacks::SkinUpdate);
		stattrak_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&stattrak_p90);

		quality_p90.setup(XOR("Quality"), XOR("quality_p90"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_p90.SetCallback(callbacks::SkinUpdate);
		quality_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&quality_p90);

		seed_p90.setup(XOR("Seed"), XOR("seed_p90"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_p90.SetCallback(callbacks::SkinUpdate);
		seed_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&seed_p90);

		id_ump45.setup(XOR("Paintkit id"), XOR("id_ump45"), 3);
		id_ump45.SetCallback(callbacks::SkinUpdate);
		id_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&id_ump45);

		stattrak_ump45.setup(XOR("Stattrak"), XOR("stattrak_ump45"));
		stattrak_ump45.SetCallback(callbacks::SkinUpdate);
		stattrak_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&stattrak_ump45);

		quality_ump45.setup(XOR("Quality"), XOR("quality_ump45"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_ump45.SetCallback(callbacks::SkinUpdate);
		quality_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&quality_ump45);

		seed_ump45.setup(XOR("Seed"), XOR("seed_ump45"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_ump45.SetCallback(callbacks::SkinUpdate);
		seed_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&seed_ump45);

		id_xm1014.setup(XOR("Paintkit id"), XOR("id_xm1014"), 3);
		id_xm1014.SetCallback(callbacks::SkinUpdate);
		id_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&id_xm1014);

		stattrak_xm1014.setup(XOR("Stattrak"), XOR("stattrak_xm1014"));
		stattrak_xm1014.SetCallback(callbacks::SkinUpdate);
		stattrak_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&stattrak_xm1014);

		quality_xm1014.setup(XOR("Quality"), XOR("quality_xm1014"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_xm1014.SetCallback(callbacks::SkinUpdate);
		quality_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&quality_xm1014);

		seed_xm1014.setup(XOR("Seed"), XOR("seed_xm1014"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_xm1014.SetCallback(callbacks::SkinUpdate);
		seed_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&seed_xm1014);

		id_bizon.setup(XOR("Paintkit id"), XOR("id_bizon"), 3);
		id_bizon.SetCallback(callbacks::SkinUpdate);
		id_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&id_bizon);

		stattrak_bizon.setup(XOR("Stattrak"), XOR("stattrak_bizon"));
		stattrak_bizon.SetCallback(callbacks::SkinUpdate);
		stattrak_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&stattrak_bizon);

		quality_bizon.setup(XOR("Quality"), XOR("quality_bizon"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_bizon.SetCallback(callbacks::SkinUpdate);
		quality_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&quality_bizon);

		seed_bizon.setup(XOR("Seed"), XOR("seed_bizon"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_bizon.SetCallback(callbacks::SkinUpdate);
		seed_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&seed_bizon);

		id_mag7.setup(XOR("Paintkit id"), XOR("id_mag7"), 3);
		id_mag7.SetCallback(callbacks::SkinUpdate);
		id_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&id_mag7);

		stattrak_mag7.setup(XOR("Stattrak"), XOR("stattrak_mag7"));
		stattrak_mag7.SetCallback(callbacks::SkinUpdate);
		stattrak_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&stattrak_mag7);

		quality_mag7.setup(XOR("Quality"), XOR("quality_mag7"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_mag7.SetCallback(callbacks::SkinUpdate);
		quality_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&quality_mag7);

		seed_mag7.setup(XOR("Seed"), XOR("seed_mag7"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_mag7.SetCallback(callbacks::SkinUpdate);
		seed_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&seed_mag7);

		id_negev.setup(XOR("Paintkit id"), XOR("id_negev"), 3);
		id_negev.SetCallback(callbacks::SkinUpdate);
		id_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&id_negev);

		stattrak_negev.setup(XOR("Stattrak"), XOR("stattrak_negev"));
		stattrak_negev.SetCallback(callbacks::SkinUpdate);
		stattrak_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&stattrak_negev);

		quality_negev.setup(XOR("Quality"), XOR("quality_negev"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_negev.SetCallback(callbacks::SkinUpdate);
		quality_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&quality_negev);

		seed_negev.setup(XOR("Seed"), XOR("seed_negev"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_negev.SetCallback(callbacks::SkinUpdate);
		seed_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&seed_negev);

		id_sawedoff.setup(XOR("Paintkit id"), XOR("id_sawedoff"), 3);
		id_sawedoff.SetCallback(callbacks::SkinUpdate);
		id_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&id_sawedoff);

		stattrak_sawedoff.setup(XOR("Stattrak"), XOR("stattrak_sawedoff"));
		stattrak_sawedoff.SetCallback(callbacks::SkinUpdate);
		stattrak_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&stattrak_sawedoff);

		quality_sawedoff.setup(XOR("Quality"), XOR("quality_sawedoff"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_sawedoff.SetCallback(callbacks::SkinUpdate);
		quality_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&quality_sawedoff);

		seed_sawedoff.setup(XOR("Seed"), XOR("seed_sawedoff"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_sawedoff.SetCallback(callbacks::SkinUpdate);
		seed_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&seed_sawedoff);

		id_tec9.setup(XOR("Paintkit id"), XOR("id_tec9"), 3);
		id_tec9.SetCallback(callbacks::SkinUpdate);
		id_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&id_tec9);

		stattrak_tec9.setup(XOR("Stattrak"), XOR("stattrak_tec9"));
		stattrak_tec9.SetCallback(callbacks::SkinUpdate);
		stattrak_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&stattrak_tec9);

		quality_tec9.setup(XOR("Quality"), XOR("quality_tec9"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_tec9.SetCallback(callbacks::SkinUpdate);
		quality_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&quality_tec9);

		seed_tec9.setup(XOR("Seed"), XOR("seed_tec9"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_tec9.SetCallback(callbacks::SkinUpdate);
		seed_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&seed_tec9);

		id_p2000.setup(XOR("Paintkit id"), XOR("id_p2000"), 3);
		id_p2000.SetCallback(callbacks::SkinUpdate);
		id_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&id_p2000);

		stattrak_p2000.setup(XOR("Stattrak"), XOR("stattrak_p2000"));
		stattrak_p2000.SetCallback(callbacks::SkinUpdate);
		stattrak_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&stattrak_p2000);

		quality_p2000.setup(XOR("Quality"), XOR("quality_p2000"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_p2000.SetCallback(callbacks::SkinUpdate);
		quality_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&quality_p2000);

		seed_p2000.setup(XOR("Seed"), XOR("seed_p2000"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_p2000.SetCallback(callbacks::SkinUpdate);
		seed_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&seed_p2000);

		id_mp7.setup(XOR("Paintkit id"), XOR("id_mp7"), 3);
		id_mp7.SetCallback(callbacks::SkinUpdate);
		id_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&id_mp7);

		stattrak_mp7.setup(XOR("Stattrak"), XOR("stattrak_mp7"));
		stattrak_mp7.SetCallback(callbacks::SkinUpdate);
		stattrak_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&stattrak_mp7);

		quality_mp7.setup(XOR("Quality"), XOR("quality_mp7"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_mp7.SetCallback(callbacks::SkinUpdate);
		quality_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&quality_mp7);

		seed_mp7.setup(XOR("Seed"), XOR("seed_mp7"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_mp7.SetCallback(callbacks::SkinUpdate);
		seed_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&seed_mp7);

		id_mp9.setup(XOR("Paintkit id"), XOR("id_mp9"), 3);
		id_mp9.SetCallback(callbacks::SkinUpdate);
		id_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&id_mp9);

		stattrak_mp9.setup(XOR("Stattrak"), XOR("stattrak_mp9"));
		stattrak_mp9.SetCallback(callbacks::SkinUpdate);
		stattrak_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&stattrak_mp9);

		quality_mp9.setup(XOR("Quality"), XOR("quality_mp9"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_mp9.SetCallback(callbacks::SkinUpdate);
		quality_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&quality_mp9);

		seed_mp9.setup(XOR("Seed"), XOR("seed_mp9"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_mp9.SetCallback(callbacks::SkinUpdate);
		seed_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&seed_mp9);

		id_nova.setup(XOR("Paintkit id"), XOR("id_nova"), 3);
		id_nova.SetCallback(callbacks::SkinUpdate);
		id_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&id_nova);

		stattrak_nova.setup(XOR("Stattrak"), XOR("stattrak_nova"));
		stattrak_nova.SetCallback(callbacks::SkinUpdate);
		stattrak_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&stattrak_nova);

		quality_nova.setup(XOR("Quality"), XOR("quality_nova"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_nova.SetCallback(callbacks::SkinUpdate);
		quality_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&quality_nova);

		seed_nova.setup(XOR("Seed"), XOR("seed_nova"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_nova.SetCallback(callbacks::SkinUpdate);
		seed_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&seed_nova);

		id_p250.setup(XOR("Paintkit id"), XOR("id_p250"), 3);
		id_p250.SetCallback(callbacks::SkinUpdate);
		id_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&id_p250);

		stattrak_p250.setup(XOR("Stattrak"), XOR("stattrak_p250"));
		stattrak_p250.SetCallback(callbacks::SkinUpdate);
		stattrak_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&stattrak_p250);

		quality_p250.setup(XOR("Quality"), XOR("quality_p250"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_p250.SetCallback(callbacks::SkinUpdate);
		quality_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&quality_p250);

		seed_p250.setup(XOR("Seed"), XOR("seed_p250"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_p250.SetCallback(callbacks::SkinUpdate);
		seed_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&seed_p250);

		id_scar20.setup(XOR("Paintkit id"), XOR("id_scar20"), 3);
		id_scar20.SetCallback(callbacks::SkinUpdate);
		id_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&id_scar20);

		stattrak_scar20.setup(XOR("Stattrak"), XOR("stattrak_scar20"));
		stattrak_scar20.SetCallback(callbacks::SkinUpdate);
		stattrak_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&stattrak_scar20);

		quality_scar20.setup(XOR("Quality"), XOR("quality_scar20"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_scar20.SetCallback(callbacks::SkinUpdate);
		quality_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&quality_scar20);

		seed_scar20.setup(XOR("Seed"), XOR("seed_scar20"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_scar20.SetCallback(callbacks::SkinUpdate);
		seed_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&seed_scar20);

		id_sg553.setup(XOR("Paintkit id"), XOR("id_sg553"), 3);
		id_sg553.SetCallback(callbacks::SkinUpdate);
		id_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&id_sg553);

		stattrak_sg553.setup(XOR("Stattrak"), XOR("stattrak_sg553"));
		stattrak_sg553.SetCallback(callbacks::SkinUpdate);
		stattrak_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&stattrak_sg553);

		quality_sg553.setup(XOR("Quality"), XOR("quality_sg553"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_sg553.SetCallback(callbacks::SkinUpdate);
		quality_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&quality_sg553);

		seed_sg553.setup(XOR("Seed"), XOR("seed_sg553"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_sg553.SetCallback(callbacks::SkinUpdate);
		seed_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&seed_sg553);

		id_ssg08.setup(XOR("Paintkit id"), XOR("id_ssg08"), 3);
		id_ssg08.SetCallback(callbacks::SkinUpdate);
		id_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&id_ssg08);

		stattrak_ssg08.setup(XOR("Stattrak"), XOR("stattrak_ssg08"));
		stattrak_ssg08.SetCallback(callbacks::SkinUpdate);
		stattrak_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&stattrak_ssg08);

		quality_ssg08.setup(XOR("Quality"), XOR("quality_ssg08"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_ssg08.SetCallback(callbacks::SkinUpdate);
		quality_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&quality_ssg08);

		seed_ssg08.setup(XOR("Seed"), XOR("seed_ssg08"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_ssg08.SetCallback(callbacks::SkinUpdate);
		seed_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&seed_ssg08);

		id_m4a1s.setup(XOR("Paintkit id"), XOR("id_m4a1s"), 3);
		id_m4a1s.SetCallback(callbacks::SkinUpdate);
		id_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&id_m4a1s);

		stattrak_m4a1s.setup(XOR("Stattrak"), XOR("stattrak_m4a1s"));
		stattrak_m4a1s.SetCallback(callbacks::SkinUpdate);
		stattrak_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&stattrak_m4a1s);

		quality_m4a1s.setup(XOR("Quality"), XOR("quality_m4a1s"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_m4a1s.SetCallback(callbacks::SkinUpdate);
		quality_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&quality_m4a1s);

		seed_m4a1s.setup(XOR("Seed"), XOR("seed_m4a1s"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_m4a1s.SetCallback(callbacks::SkinUpdate);
		seed_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&seed_m4a1s);

		id_usps.setup(XOR("Paintkit id"), XOR("id_usps"), 3);
		id_usps.SetCallback(callbacks::SkinUpdate);
		id_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&id_usps);

		stattrak_usps.setup(XOR("Stattrak"), XOR("stattrak_usps"));
		stattrak_usps.SetCallback(callbacks::SkinUpdate);
		stattrak_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&stattrak_usps);

		quality_usps.setup(XOR("Quality"), XOR("quality_usps"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_usps.SetCallback(callbacks::SkinUpdate);
		quality_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&quality_usps);

		seed_usps.setup(XOR("Seed"), XOR("seed_usps"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_usps.SetCallback(callbacks::SkinUpdate);
		seed_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&seed_usps);

		id_cz75a.setup(XOR("Paintkit id"), XOR("id_cz75a"), 3);
		id_cz75a.SetCallback(callbacks::SkinUpdate);
		id_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&id_cz75a);

		stattrak_cz75a.setup(XOR("Stattrak"), XOR("stattrak_cz75a"));
		stattrak_cz75a.SetCallback(callbacks::SkinUpdate);
		stattrak_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&stattrak_cz75a);

		quality_cz75a.setup(XOR("Quality"), XOR("quality_cz75a"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_cz75a.SetCallback(callbacks::SkinUpdate);
		quality_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&quality_cz75a);

		seed_cz75a.setup(XOR("Seed"), XOR("seed_cz75a"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_cz75a.SetCallback(callbacks::SkinUpdate);
		seed_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&seed_cz75a);

		id_revolver.setup(XOR("Paintkit id"), XOR("id_revolver"), 3);
		id_revolver.SetCallback(callbacks::SkinUpdate);
		id_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&id_revolver);

		stattrak_revolver.setup(XOR("Stattrak"), XOR("stattrak_revolver"));
		stattrak_revolver.SetCallback(callbacks::SkinUpdate);
		stattrak_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&stattrak_revolver);

		quality_revolver.setup(XOR("Quality"), XOR("quality_revolver"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_revolver.SetCallback(callbacks::SkinUpdate);
		quality_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&quality_revolver);

		seed_revolver.setup(XOR("Seed"), XOR("seed_revolver"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_revolver.SetCallback(callbacks::SkinUpdate);
		seed_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&seed_revolver);

		id_bayonet.setup(XOR("Paintkit id"), XOR("id_bayonet"), 3);
		id_bayonet.SetCallback(callbacks::SkinUpdate);
		id_bayonet.AddShowCallback(callbacks::KNIFE_BAYONET);
		RegisterElement(&id_bayonet);

		stattrak_bayonet.setup(XOR("Stattrak"), XOR("stattrak_bayonet"));
		stattrak_bayonet.SetCallback(callbacks::SkinUpdate);
		stattrak_bayonet.AddShowCallback(callbacks::KNIFE_BAYONET);
		RegisterElement(&stattrak_bayonet);

		quality_bayonet.setup(XOR("Quality"), XOR("quality_bayonet"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_bayonet.SetCallback(callbacks::SkinUpdate);
		quality_bayonet.AddShowCallback(callbacks::KNIFE_BAYONET);
		RegisterElement(&quality_bayonet);

		seed_bayonet.setup(XOR("Seed"), XOR("seed_bayonet"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_bayonet.SetCallback(callbacks::SkinUpdate);
		seed_bayonet.AddShowCallback(callbacks::KNIFE_BAYONET);
		RegisterElement(&seed_bayonet);

		id_flip.setup(XOR("Paintkit id"), XOR("id_flip"), 3);
		id_flip.SetCallback(callbacks::SkinUpdate);
		id_flip.AddShowCallback(callbacks::KNIFE_FLIP);
		RegisterElement(&id_flip);

		stattrak_flip.setup(XOR("Stattrak"), XOR("stattrak_flip"));
		stattrak_flip.SetCallback(callbacks::SkinUpdate);
		stattrak_flip.AddShowCallback(callbacks::KNIFE_FLIP);
		RegisterElement(&stattrak_flip);

		quality_flip.setup(XOR("Quality"), XOR("quality_flip"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_flip.SetCallback(callbacks::SkinUpdate);
		quality_flip.AddShowCallback(callbacks::KNIFE_FLIP);
		RegisterElement(&quality_flip);

		seed_flip.setup(XOR("Seed"), XOR("seed_flip"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_flip.SetCallback(callbacks::SkinUpdate);
		seed_flip.AddShowCallback(callbacks::KNIFE_FLIP);
		RegisterElement(&seed_flip);

		id_gut.setup(XOR("Paintkit id"), XOR("id_gut"), 3);
		id_gut.SetCallback(callbacks::SkinUpdate);
		id_gut.AddShowCallback(callbacks::KNIFE_GUT);
		RegisterElement(&id_gut);

		stattrak_gut.setup(XOR("Stattrak"), XOR("stattrak_gut"));
		stattrak_gut.SetCallback(callbacks::SkinUpdate);
		stattrak_gut.AddShowCallback(callbacks::KNIFE_GUT);
		RegisterElement(&stattrak_gut);

		quality_gut.setup(XOR("Quality"), XOR("quality_gut"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_gut.SetCallback(callbacks::SkinUpdate);
		quality_gut.AddShowCallback(callbacks::KNIFE_GUT);
		RegisterElement(&quality_gut);

		seed_gut.setup(XOR("Seed"), XOR("seed_gut"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_gut.SetCallback(callbacks::SkinUpdate);
		seed_gut.AddShowCallback(callbacks::KNIFE_GUT);
		RegisterElement(&seed_gut);

		id_karambit.setup(XOR("Paintkit id"), XOR("id_karambit"), 3);
		id_karambit.SetCallback(callbacks::SkinUpdate);
		id_karambit.AddShowCallback(callbacks::KNIFE_KARAMBIT);
		RegisterElement(&id_karambit);

		stattrak_karambit.setup(XOR("Stattrak"), XOR("stattrak_karambit"));
		stattrak_karambit.SetCallback(callbacks::SkinUpdate);
		stattrak_karambit.AddShowCallback(callbacks::KNIFE_KARAMBIT);
		RegisterElement(&stattrak_karambit);

		quality_karambit.setup(XOR("Quality"), XOR("quality_karambit"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_karambit.SetCallback(callbacks::SkinUpdate);
		quality_karambit.AddShowCallback(callbacks::KNIFE_KARAMBIT);
		RegisterElement(&quality_karambit);

		seed_karambit.setup(XOR("Seed"), XOR("seed_karambit"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_karambit.SetCallback(callbacks::SkinUpdate);
		seed_karambit.AddShowCallback(callbacks::KNIFE_KARAMBIT);
		RegisterElement(&seed_karambit);

		id_m9.setup(XOR("Paintkit id"), XOR("id_m9"), 3);
		id_m9.SetCallback(callbacks::SkinUpdate);
		id_m9.AddShowCallback(callbacks::KNIFE_M9_BAYONET);
		RegisterElement(&id_m9);

		stattrak_m9.setup(XOR("Stattrak"), XOR("stattrak_m9"));
		stattrak_m9.SetCallback(callbacks::SkinUpdate);
		stattrak_m9.AddShowCallback(callbacks::KNIFE_M9_BAYONET);
		RegisterElement(&stattrak_m9);

		quality_m9.setup(XOR("Quality"), XOR("quality_m9"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_m9.SetCallback(callbacks::SkinUpdate);
		quality_m9.AddShowCallback(callbacks::KNIFE_M9_BAYONET);
		RegisterElement(&quality_m9);

		seed_m9.setup(XOR("Seed"), XOR("seed_m9"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_m9.SetCallback(callbacks::SkinUpdate);
		seed_m9.AddShowCallback(callbacks::KNIFE_M9_BAYONET);
		RegisterElement(&seed_m9);

		id_huntsman.setup(XOR("Paintkit id"), XOR("id_huntsman"), 3);
		id_huntsman.SetCallback(callbacks::SkinUpdate);
		id_huntsman.AddShowCallback(callbacks::KNIFE_HUNTSMAN);
		RegisterElement(&id_huntsman);

		stattrak_huntsman.setup(XOR("Stattrak"), XOR("stattrak_huntsman"));
		stattrak_huntsman.SetCallback(callbacks::SkinUpdate);
		stattrak_huntsman.AddShowCallback(callbacks::KNIFE_HUNTSMAN);
		RegisterElement(&stattrak_huntsman);

		quality_huntsman.setup(XOR("Quality"), XOR("quality_huntsman"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_huntsman.SetCallback(callbacks::SkinUpdate);
		quality_huntsman.AddShowCallback(callbacks::KNIFE_HUNTSMAN);
		RegisterElement(&quality_huntsman);

		seed_huntsman.setup(XOR("Seed"), XOR("seed_huntsman"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_huntsman.SetCallback(callbacks::SkinUpdate);
		seed_huntsman.AddShowCallback(callbacks::KNIFE_HUNTSMAN);
		RegisterElement(&seed_huntsman);

		id_falchion.setup(XOR("Paintkit id"), XOR("id_falchion"), 3);
		id_falchion.SetCallback(callbacks::SkinUpdate);
		id_falchion.AddShowCallback(callbacks::KNIFE_FALCHION);
		RegisterElement(&id_falchion);

		stattrak_falchion.setup(XOR("Stattrak"), XOR("stattrak_falchion"));
		stattrak_falchion.SetCallback(callbacks::SkinUpdate);
		stattrak_falchion.AddShowCallback(callbacks::KNIFE_FALCHION);
		RegisterElement(&stattrak_falchion);

		quality_falchion.setup(XOR("Quality"), XOR("quality_falchion"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_falchion.SetCallback(callbacks::SkinUpdate);
		quality_falchion.AddShowCallback(callbacks::KNIFE_FALCHION);
		RegisterElement(&quality_falchion);

		seed_falchion.setup(XOR("Seed"), XOR("seed_falchion"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_falchion.SetCallback(callbacks::SkinUpdate);
		seed_falchion.AddShowCallback(callbacks::KNIFE_FALCHION);
		RegisterElement(&seed_falchion);

		id_bowie.setup(XOR("Paintkit id"), XOR("id_bowie"), 3);
		id_bowie.SetCallback(callbacks::SkinUpdate);
		id_bowie.AddShowCallback(callbacks::KNIFE_BOWIE);
		RegisterElement(&id_bowie);

		stattrak_bowie.setup(XOR("Stattrak"), XOR("stattrak_bowie"));
		stattrak_bowie.SetCallback(callbacks::SkinUpdate);
		stattrak_bowie.AddShowCallback(callbacks::KNIFE_BOWIE);
		RegisterElement(&stattrak_bowie);

		quality_bowie.setup(XOR("Quality"), XOR("quality_bowie"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_bowie.SetCallback(callbacks::SkinUpdate);
		quality_bowie.AddShowCallback(callbacks::KNIFE_BOWIE);
		RegisterElement(&quality_bowie);

		seed_bowie.setup(XOR("Seed"), XOR("seed_bowie"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_bowie.SetCallback(callbacks::SkinUpdate);
		seed_bowie.AddShowCallback(callbacks::KNIFE_BOWIE);
		RegisterElement(&seed_bowie);

		id_butterfly.setup(XOR("Paintkit id"), XOR("id_butterfly"), 3);
		id_butterfly.SetCallback(callbacks::SkinUpdate);
		id_butterfly.AddShowCallback(callbacks::KNIFE_BUTTERFLY);
		RegisterElement(&id_butterfly);

		stattrak_butterfly.setup(XOR("Stattrak"), XOR("stattrak_butterfly"));
		stattrak_butterfly.SetCallback(callbacks::SkinUpdate);
		stattrak_butterfly.AddShowCallback(callbacks::KNIFE_BUTTERFLY);
		RegisterElement(&stattrak_butterfly);

		quality_butterfly.setup(XOR("Quality"), XOR("quality_butterfly"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_butterfly.SetCallback(callbacks::SkinUpdate);
		quality_butterfly.AddShowCallback(callbacks::KNIFE_BUTTERFLY);
		RegisterElement(&quality_butterfly);

		seed_butterfly.setup(XOR("Seed"), XOR("seed_butterfly"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_butterfly.SetCallback(callbacks::SkinUpdate);
		seed_butterfly.AddShowCallback(callbacks::KNIFE_BUTTERFLY);
		RegisterElement(&seed_butterfly);

		id_daggers.setup(XOR("Paintkit id"), XOR("id_daggers"), 3);
		id_daggers.SetCallback(callbacks::SkinUpdate);
		id_daggers.AddShowCallback(callbacks::KNIFE_SHADOW_DAGGERS);
		RegisterElement(&id_daggers);

		stattrak_daggers.setup(XOR("Stattrak"), XOR("stattrak_daggers"));
		stattrak_daggers.SetCallback(callbacks::SkinUpdate);
		stattrak_daggers.AddShowCallback(callbacks::KNIFE_SHADOW_DAGGERS);
		RegisterElement(&stattrak_daggers);

		quality_daggers.setup(XOR("Quality"), XOR("quality_daggers"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_daggers.SetCallback(callbacks::SkinUpdate);
		quality_daggers.AddShowCallback(callbacks::KNIFE_SHADOW_DAGGERS);
		RegisterElement(&quality_daggers);

		seed_daggers.setup(XOR("Seed"), XOR("seed_daggers"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_daggers.SetCallback(callbacks::SkinUpdate);
		seed_daggers.AddShowCallback(callbacks::KNIFE_SHADOW_DAGGERS);
		RegisterElement(&seed_daggers);

		// col 2.
		knife.setup(XOR("Knife model"), XOR("skins_knife_model"), { XOR("Off"), XOR("Bayonet"), XOR("Bowie"), XOR("Butterfly"), XOR("Falchion"), XOR("Flip"), XOR("Gut"), XOR("Huntsman"), XOR("Karambit"), XOR("M9 bayonet"), XOR("Daggers") });
		knife.SetCallback(callbacks::SkinUpdate);
		RegisterElement(&knife, 1);

		glove.setup(XOR("Glove model"), XOR("skins_glove_model"), { XOR("Off"), XOR("Bloodhound"), XOR("Sport"), XOR("Driver"), XOR("Handwraps"), XOR("Moto"), XOR("Specialist") });
		glove.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&glove, 1);

		glove_id.setup(XOR("Glove paintkit id"), XOR("skins_glove_id"), 2);
		glove_id.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&glove_id, 1);
	}
};

class MiscTab : public Tab {
public:
	// col1.
	MultiDropdown buy1;
	MultiDropdown buy2;
	MultiDropdown buy3;
	MultiDropdown notifications;
	Keybind       fake_latency;
	Slider		  fake_latency_amt;

	// col2.
	Dropdown hitsounds;
	Checkbox aspectcheck;
	Slider aspect;
	Checkbox skyboxchange;
	Dropdown skybox;
	Checkbox unlock;
	Checkbox hitmarker;
	Checkbox killstreak;
	Checkbox ragdoll_force;
	Checkbox killfeed;
	Checkbox clantag;
	Checkbox slide_walk;
	Checkbox watermark;
	Checkbox discordrpc;
	Dropdown hitsound;
	Button   HiddenCvar;
	Button   ForceUpdate;

public:
	void init() {
		SetTitle(XOR("Misc"));

		buy1.setup(XOR("Auto buy items"), XOR("auto_buy1"),
			{
				XOR("Ssg08"),
				XOR("AWP"),
				XOR("Scar20"),
				XOR("G3sg1"),
			});
		RegisterElement(&buy1);

		buy2.setup("", XOR("auto_buy2"),
			{
				XOR("Glock"),
				XOR("Usp_silencer"),
				XOR("Elite"),
				XOR("P250"),
				XOR("Tec9"),
				XOR("Deagle"),
			}, false);
		RegisterElement(&buy2);

		buy3.setup("", XOR("auto_buy3"),
			{
				XOR("Vest"),
				XOR("Vesthelm"),
				XOR("Taser"),
				XOR("Defuser"),
				XOR("Heavyarmor"),
				XOR("Molotov"),
				XOR("Incgrenade"),
				XOR("Hegrenade"),
				XOR("Smokegrenade"),
			}, false);
		RegisterElement(&buy3);

		notifications.setup(XOR("Notifications"), XOR("notifications"), { XOR("Damage"), XOR("Harmed"), XOR("Purchases"), XOR("Bomb"), XOR("Defuse") });
		RegisterElement(&notifications);




		fake_latency.setup(XOR("Fake latency"), XOR("fake_latency"));
		fake_latency.SetToggleCallback(callbacks::ToggleFakeLatency);
		RegisterElement(&fake_latency);

		fake_latency_amt.setup("", XOR("fake_latency_amt"), 50.f, 1000.f, false, 0, 200.f, 50.f, XOR(L"ms"));
		RegisterElement(&fake_latency_amt);



		// col2.

		hitsounds.setup(XOR("Hitsound"), XOR("hitsounds"), { XOR("Off"), XOR("zapta"), XOR("Arena switch"), XOR("Bameware") });
		RegisterElement(&hitsounds, 1);

		aspectcheck.setup(XOR("Aspect ratio"), XOR("aspectcheck"));
		RegisterElement(&aspectcheck, 1);

		aspect.setup(XOR("Aspect Ratio"), XOR("aspect"), 0.f, 2.f, false, 1, 0.f, 0.1f);
		aspect.AddShowCallback(callbacks::ASPECT_RATIO);
		RegisterElement(&aspect, 1);

		hitmarker.setup(XOR("Hitmarker"), XOR("hitmarker"));
		RegisterElement(&hitmarker, 1);

		skyboxchange.setup(XOR("Skybox"), XOR("skyboxchange"));
		RegisterElement(&skyboxchange, 1);

		skybox.setup(XOR("Skyboxes"), XOR("skybox"), { XOR("Tibet"),XOR("Embassy"),XOR("Italy"),XOR("Daylight"),XOR("Cloudy"),XOR("Night 1"),XOR("Night 2"),XOR("Night Flat"),XOR("Day HD"),XOR("Day"),XOR("Rural"),XOR("Vertigo HD"),XOR("Vertigo Blue HD"),XOR("Vertigo"),XOR("Vietnam"),XOR("Dusty Sky"),XOR("Jungle"),XOR("Nuke"),XOR("Office") });
		skybox.AddShowCallback(callbacks::IsSkyBoxChange);
		RegisterElement(&skybox, 1);


		unlock.setup(XOR("Unlock inventory in-game"), XOR("unlock_inventory"));
		RegisterElement(&unlock, 1);

	/*	killstreak.setup(XOR("killstreak"), XOR("killstreak"));
		RegisterElement(&killstreak, 1);)*/

		ragdoll_force.setup(XOR("Ragdoll force"), XOR("ragdoll_force"));
		RegisterElement(&ragdoll_force, 1);

		killfeed.setup(XOR("Preserve killfeed"), XOR("killfeed"));
		killfeed.SetCallback(callbacks::ToggleKillfeed);
		RegisterElement(&killfeed, 1);

		clantag.setup(XOR("Clantag"), XOR("clantag"));
		RegisterElement(&clantag, 1);


		slide_walk.setup(XOR("Slide walk"), XOR("slide_walk"));
		RegisterElement(&slide_walk, 1);

		watermark.setup(XOR("Watermark"), XOR("watermark"));
		RegisterElement(&watermark, 1);

		discordrpc.setup(XOR("Discord rich presence"), XOR("discordrpc"));
		RegisterElement(&discordrpc, 1);

		HiddenCvar.setup(XOR("Unlock hidden cvars"));
		HiddenCvar.SetCallback(callbacks::HiddenCvar);
		RegisterElement(&HiddenCvar, 1);

		ForceUpdate.setup(XOR("Force update"));
		ForceUpdate.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&ForceUpdate, 1);
	}
};

class ConfigTab : public Tab {
public:
	Colorpicker menu_color;
	Button   mrx1;
	Button   mrx2;
	Button   mrx3;
	Button emporium;

	Dropdown mode;
	Dropdown config;
	Keybind  key1;
	Keybind  key2;
	Keybind  key3;
	Keybind  key4;
	Keybind  key5;
	Keybind  key6;
	Button   save;
	Button   load;

public:

	void init() {
		SetTitle(XOR("Config"));

		menu_color.setup(XOR("Menu color"), XOR("menu_color"), colors::light_blue, &g_gui.m_color);
		RegisterElement(&menu_color);

		mrx1.setup(XOR("Connect to MrX #1"));
		mrx1.SetCallback(callbacks::mrx1);
		RegisterElement(&mrx1);

		mrx2.setup(XOR("Connect to MrX #2"));
		mrx2.SetCallback(callbacks::mrx2);
		RegisterElement(&mrx2);

		mrx3.setup(XOR("Connect to MrX #3"));
		mrx3.SetCallback(callbacks::mrx3);
		RegisterElement(&mrx3);

		emporium.setup(XOR("Connect to emporium #1"));
		emporium.SetCallback(callbacks::emporium);
		RegisterElement(&emporium);

		mode.setup(XOR("Safety mode"), XOR("mode"), { XOR("Matchmaking"), XOR("No-spread") });
		RegisterElement(&mode, 1);

		config.setup(XOR("Config"), XOR("cfg"), { XOR("1"), XOR("2"), XOR("3"), XOR("4"), XOR("5"), XOR("6") });
		config.RemoveFlags(ElementFlags::SAVE);
		RegisterElement(&config, 1);

		key1.setup(XOR("Config key 1"), XOR("cfg_key1"));
		key1.RemoveFlags(ElementFlags::SAVE);
		key1.SetCallback(callbacks::SaveHotkeys);
		key1.AddShowCallback(callbacks::IsConfig1);
		key1.SetToggleCallback(callbacks::ConfigLoad1);
		RegisterElement(&key1, 1);

		key2.setup(XOR("Config key 2"), XOR("cfg_key2"));
		key2.RemoveFlags(ElementFlags::SAVE);
		key2.SetCallback(callbacks::SaveHotkeys);
		key2.AddShowCallback(callbacks::IsConfig2);
		key2.SetToggleCallback(callbacks::ConfigLoad2);
		RegisterElement(&key2, 1);

		key3.setup(XOR("Config key 3"), XOR("cfg_key3"));
		key3.RemoveFlags(ElementFlags::SAVE);
		key3.SetCallback(callbacks::SaveHotkeys);
		key3.AddShowCallback(callbacks::IsConfig3);
		key3.SetToggleCallback(callbacks::ConfigLoad3);
		RegisterElement(&key3, 1);

		key4.setup(XOR("Config key 4"), XOR("cfg_key4"));
		key4.RemoveFlags(ElementFlags::SAVE);
		key4.SetCallback(callbacks::SaveHotkeys);
		key4.AddShowCallback(callbacks::IsConfig4);
		key4.SetToggleCallback(callbacks::ConfigLoad4);
		RegisterElement(&key4, 1);

		key5.setup(XOR("Config key 5"), XOR("cfg_key5"));
		key5.RemoveFlags(ElementFlags::SAVE);
		key5.SetCallback(callbacks::SaveHotkeys);
		key5.AddShowCallback(callbacks::IsConfig5);
		key5.SetToggleCallback(callbacks::ConfigLoad5);
		RegisterElement(&key5, 1);

		key6.setup(XOR("Config key 6"), XOR("cfg_key6"));
		key6.RemoveFlags(ElementFlags::SAVE);
		key6.SetCallback(callbacks::SaveHotkeys);
		key6.AddShowCallback(callbacks::IsConfig6);
		key6.SetToggleCallback(callbacks::ConfigLoad6);
		RegisterElement(&key6, 1);

		save.setup(XOR("Save"));
		save.SetCallback(callbacks::ConfigSave);
		RegisterElement(&save, 1);

		load.setup(XOR("Load"));
		load.SetCallback(callbacks::ConfigLoad);
		RegisterElement(&load, 1);
	}
};

class MainForm : public Form {
public:
	// aimbot.
	AimbotTab    aimbot;
	AntiAimTab   antiaim;

	// visuals.
	PlayersTab	 players;
	ModelsTab	models;
	VisualsTab	 visuals;

	// misc.
	MovementTab  movement;
	SkinsTab     skins;
	MiscTab	     misc;
	ConfigTab	 config;

public:
	void init() {
		SetPosition(350, 350);
		SetSize(525, 570);

		// aim.
		RegisterTab(&aimbot);
		aimbot.init();

		RegisterTab(&antiaim);
		antiaim.init();

		// visuals.
		RegisterTab(&players);
		players.init();

		RegisterTab(&models);
		models.init();

		RegisterTab(&visuals);
		visuals.init();

		// misc.
		RegisterTab(&movement);
		movement.init();

		RegisterTab(&misc);
		misc.init();

		RegisterTab(&skins);
		skins.init();

		RegisterTab(&config);
		config.init();
	}
};

class Menu {
public:
	MainForm main;

public:
	void init() {
		main.init();
		g_gui.RegisterForm(&main, VK_INSERT);
	}
};

extern Menu g_menu;