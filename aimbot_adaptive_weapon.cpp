#include "includes.h"

std::vector< size_t > Aimbot::FindHitboxes() {
	int id = core.m_weapon_id;
	switch (id) {
	case G3SG1: {
		return g_menu.main.aimbot.hitbox_auto.GetActiveIndices();
		break;
	}
	case SCAR20: {
		return g_menu.main.aimbot.hitbox_auto.GetActiveIndices();
		break;
	}
	case SSG08: {
		return g_menu.main.aimbot.hitbox_scout.GetActiveIndices();
		break;
	}
	case AWP: {
		return g_menu.main.aimbot.hitbox_awp.GetActiveIndices();
		break;
	}
	default: {
		return g_menu.main.aimbot.hitbox_default.GetActiveIndices();
		break;
	}
	}
}

int Aimbot::FindHitchance() {
	switch (core.m_weapon_id) {
	case G3SG1: {
		return g_menu.main.aimbot.hitchance_auto.get();
		break;
	}
	case SCAR20: {
		return g_menu.main.aimbot.hitchance_auto.get();
		break;
	}
	case SSG08: {
		return g_menu.main.aimbot.hitchance_scout.get();
		break;
	}
	case AWP: {
		return g_menu.main.aimbot.hitchance_awp.get();
		break;
	}
	default: {
		return g_menu.main.aimbot.hitchance_default.get();
		break;
	}
	}
}

int Aimbot::FindScale() {
	switch (core.m_weapon_id) {
	case G3SG1: {
		return g_menu.main.aimbot.scale_auto.get();
		break;
	}
	case SCAR20: {
		return g_menu.main.aimbot.scale_auto.get();
		break;
	}
	case SSG08: {
		return g_menu.main.aimbot.scale_scout.get();
		break;
	}
	case AWP: {
		return g_menu.main.aimbot.scale_awp.get();
		break;
	}
	default: {
		return g_menu.main.aimbot.scale_default.get();
		break;
	}
	}
}

int Aimbot::FindBodyScale() {
	switch (core.m_weapon_id) {
	case G3SG1: {
		return g_menu.main.aimbot.body_scale_auto.get();
		break;
	}
	case SCAR20: {
		return g_menu.main.aimbot.body_scale_auto.get();
		break;
	}
	case SSG08: {
		return g_menu.main.aimbot.body_scale_scout.get();
		break;
	}
	case AWP: {
		return g_menu.main.aimbot.body_scale_awp.get();
		break;
	}
	default: {
		return g_menu.main.aimbot.body_scale_default.get();
		break;
	}
	}
}

int Aimbot::FindMindamage() {
	int id = core.m_weapon_id;
	switch (id) {
	case G3SG1: {
		return g_menu.main.aimbot.mindmg_auto.get();
		break;
	}
	case SCAR20: {
		return g_menu.main.aimbot.mindmg_auto.get();
		break;
	}
	case SSG08: {
		return g_menu.main.aimbot.mindmg_scout.get();
		break;
	}
	case AWP: {
		return g_menu.main.aimbot.mindmg_awp.get();
		break;
	}
	default: {
		return g_menu.main.aimbot.mindmg_default.get();
		break;
	}
	}
}
