#include "includes.h"

// execution callbacks..
void callbacks::SkinUpdate() {
	g_skins.m_update = true;
}

void callbacks::ForceFullUpdate() {
	//static DWORD tick{};
	//
	//if (tick != g_winapi.GetTickCount()) {
	//	g_csgo.cl_fullupdate->m_callback();
	//	tick = g_winapi.GetTickCount();
	//}
	//

	g_csgo.m_cl->m_delta_tick = -1;
}

void callbacks::ToggleThirdPerson() {
	g_visuals.m_thirdperson = !g_visuals.m_thirdperson;
}



void callbacks::ToggleLeft() {
	g_hvh.m_left = !g_hvh.m_left;
	g_hvh.m_right = false;
	g_hvh.m_back = false;
}

void callbacks::ToggleRight() {
	g_hvh.m_right = !g_hvh.m_right;
	g_hvh.m_left = false;
	g_hvh.m_back = false;
}

void callbacks::ToggleBack() {
	g_hvh.m_back = !g_hvh.m_back;
	g_hvh.m_left = false;
	g_hvh.m_right = false;
}

void callbacks::ToggleFakeLatency() {
	g_aimbot.m_fake_latency = !g_aimbot.m_fake_latency;
}

void callbacks::ToggleKillfeed() {
	KillFeed_t* feed = (KillFeed_t*)g_csgo.m_hud->FindElement(HASH("SFHudDeathNoticeAndBotStatus"));
	if (feed)
		g_csgo.ClearNotices(feed);
}

void callbacks::SaveHotkeys() {
	g_config.SaveHotkeys();
}

void callbacks::ConfigLoad1() {
	g_aimbot.m_fake_latency = false;
	g_config.load(&g_menu.main, XOR("1.cfg"));
	g_menu.main.config.config.select(1 - 1);

	core.print(tfm::format(XOR("Loaded config 1\n")));
}

void callbacks::ConfigLoad2() {
	g_aimbot.m_fake_latency = false;
	g_config.load(&g_menu.main, XOR("2.cfg"));
	g_menu.main.config.config.select(2 - 1);
	core.print(tfm::format(XOR("Loaded config 2\n")));
}

void callbacks::ConfigLoad3() {
	g_aimbot.m_fake_latency = false;
	g_config.load(&g_menu.main, XOR("3.cfg"));
	g_menu.main.config.config.select(3 - 1);
	core.print(tfm::format(XOR("Loaded config 3\n")));
}

void callbacks::ConfigLoad4() {
	g_aimbot.m_fake_latency = false;
	g_config.load(&g_menu.main, XOR("4.cfg"));
	g_menu.main.config.config.select(4 - 1);
	core.print(tfm::format(XOR("Loaded config 4\n")));
}

void callbacks::ConfigLoad5() {
	g_aimbot.m_fake_latency = false;
	g_config.load(&g_menu.main, XOR("5.cfg"));
	g_menu.main.config.config.select(5 - 1);
	core.print(tfm::format(XOR("Loaded config 5\n")));
}

void callbacks::ConfigLoad6() {
	g_aimbot.m_fake_latency = false;
	g_config.load(&g_menu.main, XOR("6.cfg"));
	g_menu.main.config.config.select(6 - 1);
	core.print(tfm::format(XOR("Loaded config 6\n")));
}

void callbacks::ConfigLoad() {
	g_aimbot.m_fake_latency = false;
	std::string config = g_menu.main.config.config.GetActiveItem();
	std::string file = tfm::format(XOR("%s.cfg"), config.data());

	g_config.load(&g_menu.main, file);
	core.print(tfm::format(XOR("Loaded config %s\n"), config.data()));
	g_notify.add(tfm::format(XOR("Loaded config %s\n"), config.data()));
}

void callbacks::ConfigSave() {
	g_aimbot.m_fake_latency = false;
	std::string config = g_menu.main.config.config.GetActiveItem();
	std::string file = tfm::format(XOR("%s.cfg"), config.data());

	g_config.save(&g_menu.main, file);
	core.print(tfm::format(XOR("Saved config %s\n"), config.data()));
	g_notify.add(tfm::format(XOR("Saved config %s\n"), config.data()));
}

void callbacks::mrx1() {
	g_csgo.m_engine->ExecuteClientCmd((XOR("connect 178.32.80.148:27015")));
}

void callbacks::mrx2() {
	g_csgo.m_engine->ExecuteClientCmd((XOR("connect 178.32.80.148:27030")));
}

void callbacks::mrx3() {
	g_csgo.m_engine->ExecuteClientCmd((XOR("connect 178.32.80.148:27031")));
}
void callbacks::emporium() {
	g_csgo.m_engine->ExecuteClientCmd((XOR("connect 162.248.92.227:27015")));
}

void callbacks::HiddenCvar() {
	core.UnlockHiddenConvars();
}

bool callbacks::IsBaimHealth() {
	return g_menu.main.aimbot.baim2.get(1);
}

bool callbacks::IsAfterMisses() {
	return (g_menu.main.aimbot.baim2.get(4) || g_menu.main.aimbot.baim1.get(5));
}
/*
bool callbacks::IsFovOn() {
	return g_menu.main.aimbot.fov.get();
}
*/
bool callbacks::IsWeaponGeneral() {
	return g_menu.main.aimbot.weapon_select.get() == 0;
}

bool callbacks::IsWeaponAuto() {
	return g_menu.main.aimbot.weapon_select.get() == 1;
}

bool callbacks::IsWeaponAWP() {
	return g_menu.main.aimbot.weapon_select.get() == 2;
}

bool callbacks::IsWeaponScout() {
	return g_menu.main.aimbot.weapon_select.get() == 3;
}

bool callbacks::IsWeaponPistol() {
	return g_menu.main.aimbot.weapon_select.get() == 4;
}

bool callbacks::IsWeaponHeavy() {
	return g_menu.main.aimbot.weapon_select.get() == 5;
}


bool callbacks::IsHitchanceOnGeneral() {
	return g_menu.main.aimbot.hitchance_general.get();
}

bool callbacks::IsHitchanceOnAuto() {
	return g_menu.main.aimbot.hitchance_auto.get();
}

bool callbacks::IsHitchanceOnAWP() {
	return g_menu.main.aimbot.hitchance_awp.get();
}

bool callbacks::IsHitchanceOnScout() {
	return g_menu.main.aimbot.hitchance_scout.get();
}

bool callbacks::IsHitchanceOnPistols() {
	return g_menu.main.aimbot.hitchance_pistols.get();
}

bool callbacks::IsHitchanceOnHeavy() {
	return g_menu.main.aimbot.hitchance_heavy.get();
}

bool callbacks::IsPenetrationOnGeneral() {
	return g_menu.main.aimbot.penetrate_general.get();
}

bool callbacks::IsPenetrationOnAuto() {
	return g_menu.main.aimbot.penetrate_auto.get();
}

bool callbacks::IsPenetrationOnAWP() {
	return g_menu.main.aimbot.penetrate_awp.get();
}

bool callbacks::IsPenetrationOnScout() {
	return g_menu.main.aimbot.penetrate_scout.get();
}

bool callbacks::IsPenetrationOnPistols() {
	return g_menu.main.aimbot.penetrate_pistols.get();
}

bool callbacks::IsPenetrationOnHeavy() {
	return g_menu.main.aimbot.penetrate_heavy.get();
}

bool callbacks::IsMultipointOnGeneral() {
	return !g_menu.main.aimbot.multipoint_general.GetActiveIndices().empty();
}

bool callbacks::IsMultipointOnAuto() {
	return !g_menu.main.aimbot.multipoint_auto.GetActiveIndices().empty();
}

bool callbacks::IsMultipointOnAWP() {
	return !g_menu.main.aimbot.multipoint_awp.GetActiveIndices().empty();
}

bool callbacks::IsMultipointOnScout() {
	return !g_menu.main.aimbot.multipoint_scout.GetActiveIndices().empty();
}

bool callbacks::IsMultipointOnPistols() {
	return !g_menu.main.aimbot.multipoint_pistols.GetActiveIndices().empty();
}

bool callbacks::IsMultipointOnHeavy() {
	return !g_menu.main.aimbot.multipoint_heavy.GetActiveIndices().empty();
}

bool callbacks::IsMultipointBodyOnGeneral() {
	return g_menu.main.aimbot.multipoint_general.get(2);
}

bool callbacks::IsMultipointBodyOnAuto() {
	return g_menu.main.aimbot.multipoint_auto.get(2);
}

bool callbacks::IsMultipointBodyOnAWP() {
	return g_menu.main.aimbot.multipoint_awp.get(2);
}

bool callbacks::IsMultipointBodyOnScout() {
	return g_menu.main.aimbot.multipoint_scout.get(2);
}

bool callbacks::IsMultipointBodyOnPistols() {
	return g_menu.main.aimbot.multipoint_pistols.get(2);
}

bool callbacks::IsMultipointBodyOnHeavy() {
	return g_menu.main.aimbot.multipoint_heavy.get(2);
}


bool callbacks::IsAntiAimModeStand() {
	return g_menu.main.antiaim.mode.get() == 0;
}

bool callbacks::HasStandYaw() {
	return g_menu.main.antiaim.yaw_stand.get() > 0;
}

bool callbacks::IsStandYawJitter() {
	return g_menu.main.antiaim.yaw_stand.get() == 2;
}

bool callbacks::IsStandYawRotate() {
	return g_menu.main.antiaim.yaw_stand.get() == 3;
}

bool callbacks::IsStandYawRnadom() {
	return g_menu.main.antiaim.yaw_stand.get() == 4;
}

bool callbacks::IsStandDirAuto() {
	return g_menu.main.antiaim.dir_stand.get() == 0;
}

bool callbacks::IsStandDirCustom() {
	return g_menu.main.antiaim.dir_stand.get() == 4;
}

bool callbacks::IsAntiAimModeWalk() {
	return g_menu.main.antiaim.mode.get() == 1;
}

bool callbacks::WalkHasYaw() {
	return g_menu.main.antiaim.yaw_walk.get() > 0;
}

bool callbacks::IsWalkYawJitter() {
	return g_menu.main.antiaim.yaw_walk.get() == 2;
}

bool callbacks::IsWalkYawRotate() {
	return g_menu.main.antiaim.yaw_walk.get() == 3;
}

bool callbacks::IsWalkYawRandom() {
	return g_menu.main.antiaim.yaw_walk.get() == 4;
}

bool callbacks::IsWalkDirAuto() {
	return g_menu.main.antiaim.dir_walk.get() == 0;
}

bool callbacks::IsWalkDirCustom() {
	return g_menu.main.antiaim.dir_walk.get() == 4;
}

bool callbacks::IsAntiAimModeAir() {
	return g_menu.main.antiaim.mode.get() == 2;
}

bool callbacks::AirHasYaw() {
	return g_menu.main.antiaim.yaw_air.get() > 0;
}

bool callbacks::IsAirYawJitter() {
	return g_menu.main.antiaim.yaw_air.get() == 2;
}

bool callbacks::IsAirYawRotate() {
	return g_menu.main.antiaim.yaw_air.get() == 3;
}

bool callbacks::IsAirYawRandom() {
	return g_menu.main.antiaim.yaw_air.get() == 4;
}

bool callbacks::IsAirDirAuto() {
	return g_menu.main.antiaim.dir_air.get() == 0;
}

bool callbacks::IsAirDirCustom() {
	return g_menu.main.antiaim.dir_air.get() == 4;
}

bool callbacks::IsFakeAntiAimRelative() {
	return g_menu.main.antiaim.fake_yaw.get() == 2;
}

bool callbacks::IsTransparentProps() {
	return g_menu.main.visuals.transparent_props.get();
}

bool callbacks::IsNightMode() {
	return g_menu.main.visuals.world.get() == 1;
}

bool callbacks::IsSkyBoxChange() {
	return g_menu.main.misc.skyboxchange.get();
}
/*
bool callbacks::IsDamageVisible() {
	return g_menu.main.aimbot.minimal_damage.get() == 1;
}
*/
bool callbacks::IsCustomLby() {
	return g_menu.main.antiaim.body_fake_stand.get() == 5;
}
/*
bool callbacks::IsDamageInVisible() {
	return g_menu.main.aimbot.penetrate_minimal_damage.get() == 1;
}
*/
bool callbacks::IsFakeAntiAimJitter() {
	return g_menu.main.antiaim.fake_yaw.get() == 3;
}

bool callbacks::IsConfigMM() {
	return g_menu.main.config.mode.get() == 0;
}

bool callbacks::IsConfigNS() {
	return g_menu.main.config.mode.get() == 1;
}

bool callbacks::IsConfig1() {
	return g_menu.main.config.config.get() == 0;
}

bool callbacks::IsConfig2() {
	return g_menu.main.config.config.get() == 1;
}

bool callbacks::IsConfig3() {
	return g_menu.main.config.config.get() == 2;
}

bool callbacks::IsConfig4() {
	return g_menu.main.config.config.get() == 3;
}

bool callbacks::IsConfig5() {
	return g_menu.main.config.config.get() == 4;
}

bool callbacks::IsConfig6() {
	return g_menu.main.config.config.get() == 5;
}

// weaponcfgs callbacks.
bool callbacks::DEAGLE() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::DEAGLE;
}

bool callbacks::ELITE() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::ELITE;
}

bool callbacks::FIVESEVEN() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::FIVESEVEN;
}

bool callbacks::GLOCK() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::GLOCK;
}

bool callbacks::AK47() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::AK47;
}

bool callbacks::AUG() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::AUG;
}

bool callbacks::AWP() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::AWP;
}

bool callbacks::FAMAS() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::FAMAS;
}

bool callbacks::G3SG1() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::G3SG1;
}

bool callbacks::GALIL() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::GALIL;
}

bool callbacks::M249() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::M249;
}

bool callbacks::M4A4() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::M4A4;
}

bool callbacks::MAC10() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::MAC10;
}

bool callbacks::P90() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::P90;
}

bool callbacks::UMP45() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::UMP45;
}

bool callbacks::XM1014() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::XM1014;
}

bool callbacks::BIZON() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::BIZON;
}

bool callbacks::MAG7() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::MAG7;
}

bool callbacks::NEGEV() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::NEGEV;
}

bool callbacks::SAWEDOFF() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::SAWEDOFF;
}

bool callbacks::TEC9() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::TEC9;
}

bool callbacks::P2000() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::P2000;
}

bool callbacks::MP7() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::MP7;
}

bool callbacks::MP9() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::MP9;
}

bool callbacks::NOVA() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::NOVA;
}

bool callbacks::P250() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::P250;
}

bool callbacks::SCAR20() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::SCAR20;
}

bool callbacks::SG553() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::SG553;
}

bool callbacks::SSG08() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::SSG08;
}

bool callbacks::M4A1S() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::M4A1S;
}

bool callbacks::USPS() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::USPS;
}

bool callbacks::CZ75A() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::CZ75A;
}

bool callbacks::REVOLVER() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::REVOLVER;
}

bool callbacks::KNIFE_BAYONET() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_BAYONET;
}

bool callbacks::KNIFE_FLIP() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_FLIP;
}

bool callbacks::KNIFE_GUT() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_GUT;
}

bool callbacks::KNIFE_KARAMBIT() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_KARAMBIT;
}

bool callbacks::KNIFE_M9_BAYONET() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_M9_BAYONET;
}

bool callbacks::KNIFE_HUNTSMAN() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_HUNTSMAN;
}

bool callbacks::KNIFE_FALCHION() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_FALCHION;
}

bool callbacks::KNIFE_BOWIE() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_BOWIE;
}

bool callbacks::KNIFE_BUTTERFLY() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_BUTTERFLY;
}

bool callbacks::KNIFE_SHADOW_DAGGERS() {
	if (!g_csgo.m_engine->IsInGame() || !core.m_processing)
		return false;

	return core.m_weapon_id == Weapons_t::KNIFE_SHADOW_DAGGERS;
}

//rage
bool callbacks::AUTO_STOP() {
	return g_menu.main.movement.autostop_always_on.get();
}


bool callbacks::IsOverrideDamage() {
	return g_menu.main.aimbot.override_dmg_key.get() != -1;
}
void callbacks::ToggleDMG() {
	g_aimbot.m_damage_toggle = !g_aimbot.m_damage_toggle;
}

bool callbacks::AUTO_PEEK() {
	return g_menu.main.movement.autopeekcheck.get();
}

bool callbacks::IMPACT_BEAMS() {
	return g_menu.main.visuals.impact_beams.get();
}

bool callbacks::DEBUG_AIM() {
	return g_menu.main.aimbot.debugaim.get();
}

bool callbacks::MANUALCOL() {
	return g_menu.main.antiaim.manul_antiaim.get();
}

bool callbacks::BULLET_TRACERS() {
	return g_menu.main.visuals.bullet_tracers.get();
}

bool callbacks::ASPECT_RATIO() {
	return g_menu.main.misc.aspectcheck.get();
}

//players


//selection

bool callbacks::health_selection() {
	return g_menu.main.players.health_style.get() == 1;
}



//chams
bool callbacks::IsChamsSelection0() {
	return g_menu.main.players.chams_entity_selection.get() == 0;
}

bool callbacks::LocalGlowChamsSelection()
{
	return g_menu.main.players.chams_entity_selection.get() == 0 && g_menu.main.players.chams_local_mat.get() == 4;
}

bool callbacks::IsChamsSelection1() {
	return g_menu.main.players.chams_entity_selection.get() == 1;
}

bool callbacks::EnemyGlowChamsSelection()
{
	return g_menu.main.players.chams_entity_selection.get() == 1 && g_menu.main.players.chams_enemy_mat.get() == 4;
}

bool callbacks::IsChamsSelection2() {
	return g_menu.main.players.chams_entity_selection.get() == 2;
}

bool callbacks::IsChamsSelection3() {
	return g_menu.main.players.chams_entity_selection.get() == 3;
}