#include "includes.h"

void c_tickshift::handle_doubletap() {

	bool no_dt = m_double_tap && core.m_weapon_id != REVOLVER;

	if (!no_dt && m_charged) {
		m_charge_timer = 0;
		m_tick_to_shift = core.goalshift;
	}

	if (!no_dt) return;


	bool can_shoot = core.m_weapon_fire || core.m_weapon->m_flNextPrimaryAttack() <= g_csgo.m_globals->m_curtime - game::TICKS_TO_TIME(14);

	if (!m_charged) {
		if (m_charge_timer > game::TIME_TO_TICKS(.5)) { // .5 seconds after shifting, lets recharge
			m_tick_to_recharge = core.goalshift;
		}
		else {

			if (!g_aimbot.m_target) {
				m_charge_timer++;
			}

			if (core.m_cmd->m_buttons & IN_ATTACK && can_shoot && core.m_weapon_type != WEAPONTYPE_GRENADE) {
				m_charge_timer = 0;
			}
		}
	}
	/*
	if (g_input.GetKeyState(g_menu.main.movement.fakewalk.get())) {
		m_charge_timer = 0;
		m_charged = false;
	}
	*/

	if (core.m_cmd->m_buttons & IN_ATTACK && can_shoot && m_charged && core.m_weapon_type != WEAPONTYPE_GRENADE && core.m_weapon_id != REVOLVER) {
		// shot.. lets shift tickbase back so we can dt.
		m_charge_timer = 0;
		m_tick_to_shift = core.goalshift;
		m_shift_cmd = core.m_cmd->m_command_number;
		m_shift_tickbase = core.m_local->m_nTickBase();
		//g_aimbot.dt_aim = true;
		*core.m_packet = false;
	}

	if (!m_charged) {
		m_charged_ticks = 0;
	}
}

void CL_Move(float accumulated_extra_samples, bool bFinalTick) {
	if (g_tickshift.m_tick_to_recharge > 0) {
		g_tickshift.m_tick_to_recharge--;
		g_tickshift.m_charged_ticks++;
		if (g_tickshift.m_tick_to_recharge == 0) {
			g_tickshift.m_charged = true;
			g_aimbot.dt_aim = false;
		}
		return; // increment ticksforprocessing by not creating any usercmd's
	}

	o_CLMove(accumulated_extra_samples, bFinalTick);
	g_tickshift.m_shifted = false;
	if (g_tickshift.m_tick_to_shift > 0) {
		g_tickshift.m_shifting = true;
		for (; g_tickshift.m_tick_to_shift > 0; g_tickshift.m_tick_to_shift--) {
			o_CLMove(accumulated_extra_samples, bFinalTick);
			g_tickshift.m_charged_ticks--;
		}
		g_tickshift.m_charged = false; // were just going to assume. not correct.
		g_tickshift.m_shifting = false;
		g_tickshift.m_shifted = true;
	}
}
