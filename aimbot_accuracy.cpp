#include "includes.h"

bool Aimbot::CheckHitchance(Player* player, const ang_t& angle) {

	constexpr float HITCHANCE_MAX = 100.f;
	/*constexpr*/ int SEED_MAX = (256);

	vec3_t     start{ core.m_shoot_pos }, end, fwd, right, up, dir, wep_spread;
	float      inaccuracy, spread;
	CGameTrace tr;
	size_t     total_hits{ }, needed_hits{ (size_t)std::ceil((FindHitchance() * SEED_MAX) / HITCHANCE_MAX) };

	// setup calculation parameters.
	const auto round_acc = [](const float accuracy) { return roundf(accuracy * 1000.f) / 1000.f; };
	const auto sniper = core.m_weapon->m_iItemDefinitionIndex() == AWP || core.m_weapon->m_iItemDefinitionIndex() == G3SG1 || core.m_weapon->m_iItemDefinitionIndex() == SCAR20 || core.m_weapon->m_iItemDefinitionIndex() == SSG08;
	const auto crouched = core.m_local->m_fFlags() & IN_DUCK;

	// get needed directional vectors.
	math::AngleVectors(angle, &fwd, &right, &up);

	// store off inaccuracy / spread ( these functions are quite intensive and we only need them once ).
	inaccuracy = core.m_weapon->GetInaccuracy();
	spread = core.m_weapon->GetSpread();

	const auto info = core.m_weapon_info;
	if (!info)
		return false;

	// no need for hitchance, if we can't increase it anyway.
	if (crouched) {
		if (round_acc(inaccuracy) == round_acc(sniper ? info->m_inaccuracy_crouch_alt : info->m_inaccuracy_crouch))
			return true;
	}
	else {
		if (round_acc(inaccuracy) == round_acc(sniper ? info->m_inaccuracy_stand_alt : info->m_inaccuracy_stand))
			return true;
	}

	// update accuracy pentalty
	core.m_weapon->UpdateAccuracyPenalty();

	// iterate all possible seeds.
	for (int i{ }; i <= SEED_MAX; ++i) {
		// get spread.
		wep_spread = core.m_weapon->CalculateSpread(i, inaccuracy, spread);

		// get spread direction.
		dir = (fwd + (right * wep_spread.x) + (up * wep_spread.y)).normalized();

		// get end of trace.
		end = start + (dir * core.m_weapon_info->m_range);

		// setup ray and trace.
		g_csgo.m_engine_trace->ClipRayToEntity(Ray(start, end), MASK_SHOT, player, &tr);

		// check if we hit a valid player / hitgroup on the player and increment total hits.
		if (tr.m_entity == player && game::IsValidHitgroup(tr.m_hitgroup))
			++total_hits;

		// we made it.
		if (total_hits >= needed_hits)
			return true;

		// we cant make it anymore.
		if ((SEED_MAX - i + total_hits) < needed_hits)
			return false;
	}

	return false;
}
