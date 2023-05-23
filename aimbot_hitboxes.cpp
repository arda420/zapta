#include "includes.h"

void AimPlayer::SetupHitboxes(LagRecord* record, bool history) {
	// reset hitboxes.
	m_hitboxes.clear();

	if (core.m_weapon_id == ZEUS) {
		// hitboxes for the zeus.
		m_hitboxes.push_back({ HITBOX_BODY, HitscanMode::PREFER });
		return;
	}

	/* baim conditions */
	bool only_baim{ false };
	bool double_tap{ false };
	MultiDropdown o_baim = g_menu.main.aimbot.baim2;
	MultiDropdown p_baim = g_menu.main.aimbot.baim1;

	if (p_baim.get(0)) // always
		m_hitboxes.push_back({ HITBOX_BODY, HitscanMode::PREFER });

	if (p_baim.get(1)) // lethal
		m_hitboxes.push_back({ HITBOX_BODY, HitscanMode::LETHAL });


	if (o_baim.get(0)) { // always
		only_baim = true;
		m_hitboxes.push_back({ HITBOX_BODY, HitscanMode::PREFER });
	}

	if (o_baim.get(1) && !(record->m_pred_flags & FL_ONGROUND)) {
		only_baim = true;
		m_hitboxes.push_back({ HITBOX_BODY, HitscanMode::PREFER });
	}

	std::vector< size_t > hitbox{ g_aimbot.FindHitboxes() };
	if (hitbox.empty())
		return;


	for (const auto& h : hitbox) {
		// head.
		if (h == 0 && !only_baim || !double_tap) {
			m_hitboxes.push_back({ HITBOX_HEAD, HitscanMode::NORMAL });
		}

		// chest.
		if (h == 1) {
			m_hitboxes.push_back({ HITBOX_THORAX, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_CHEST, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_UPPER_CHEST, HitscanMode::NORMAL });
		}

		// stomach.
		if (h == 2) {
			m_hitboxes.push_back({ HITBOX_PELVIS, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_BODY, HitscanMode::NORMAL });
		}

		// arms.
		if (h == 3) {
			m_hitboxes.push_back({ HITBOX_L_UPPER_ARM, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_R_UPPER_ARM, HitscanMode::NORMAL });
		}

		// legs.
		if (h == 4) {
			m_hitboxes.push_back({ HITBOX_L_THIGH, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_R_THIGH, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_L_CALF, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_R_CALF, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_L_FOOT, HitscanMode::NORMAL });
			m_hitboxes.push_back({ HITBOX_R_FOOT, HitscanMode::NORMAL });
		}
	}
}

auto Aimbot::FindMultipoints() {
	switch (core.m_weapon_id) {
	case G3SG1: {
		return g_menu.main.aimbot.multipoint_auto;
		break;
	}
	case SCAR20: {
		return g_menu.main.aimbot.multipoint_auto;
		break;
	}
	case SSG08: {
		return g_menu.main.aimbot.multipoint_scout;
		break;
	}
	case AWP: {
		return g_menu.main.aimbot.multipoint_awp;
		break;
	}
	default: {
		return g_menu.main.aimbot.multipoint_default;
		break;
	}
	}
}

bool AimPlayer::SetupHitboxPoints(LagRecord* record, BoneArray* bones, int index, std::vector< vec3_t >& points) {
	// reset points.
	points.clear();

	// multipoint
	auto multipoint = g_aimbot.FindMultipoints();

	const model_t* model = m_player->GetModel();
	if (!model)
		return false;

	studiohdr_t* hdr = g_csgo.m_model_info->GetStudioModel(model);
	if (!hdr)
		return false;

	mstudiohitboxset_t* set = hdr->GetHitboxSet(m_player->m_nHitboxSet());
	if (!set)
		return false;

	mstudiobbox_t* bbox = set->GetHitbox(index);
	if (!bbox)
		return false;

	// get hitbox scales.
	float scale = g_aimbot.FindScale() / 100.f;
	float bscale = g_aimbot.FindBodyScale() / 100.f;

	// these indexes represent boxes.
	if (bbox->m_radius <= 0.f) {
		// references: 
		//      https://developer.valvesoftware.com/wiki/Rotation_Tutorial
		//      CBaseAnimating::GetHitboxBonePosition
		//      CBaseAnimating::DrawServerHitboxes

		// convert rotation angle to a matrix.
		matrix3x4_t rot_matrix;
		g_csgo.AngleMatrix(bbox->m_angle, rot_matrix);

		// apply the rotation to the entity input space (local).
		matrix3x4_t matrix;
		math::ConcatTransforms(bones[bbox->m_bone], rot_matrix, matrix);

		// extract origin from matrix.
		vec3_t origin = matrix.GetOrigin();

		// compute raw center point.
		vec3_t center = (bbox->m_mins + bbox->m_maxs) / 2.f;

		// the feet hiboxes have a side, heel and the toe.
		if (index == HITBOX_R_FOOT || index == HITBOX_L_FOOT) {
			float d1 = (bbox->m_mins.z - center.z) * 0.875f;

			// invert.
			if (index == HITBOX_L_FOOT)
				d1 *= -1.f;

			// side is more optimal then center.
			points.push_back({ center.x, center.y, center.z + d1 });
			if (multipoint.get(3)) {
				// get point offset relative to center point
				// and factor in hitbox scale.
				float d2 = (bbox->m_mins.x - center.x) * scale;
				float d3 = (bbox->m_maxs.x - center.x) * scale;

				// heel.
				points.push_back({ center.x + d2, center.y, center.z });

				// toe.
				points.push_back({ center.x + d3, center.y, center.z });
			}
		}

		// nothing to do here we are done.
		if (points.empty())
			return false;

		// rotate our bbox points by their correct angle
		// and convert our points to world space.
		for (auto& p : points) {
			// VectorRotate.
			// rotate point by angle stored in matrix.
			p = { p.dot(matrix[0]), p.dot(matrix[1]), p.dot(matrix[2]) };

			// transform point to world space.
			p += origin;
		}
	}

	// these hitboxes are capsules.
	else {
		// factor in the pointscale.
		float r = bbox->m_radius * scale;
		float br = bbox->m_radius * bscale;

		// compute raw center point.
		vec3_t center = (bbox->m_mins + bbox->m_maxs) / 2.f;

		// head has 5 points.
		if (index == HITBOX_HEAD) {
			// add center.
			points.push_back(center);

			if (multipoint.get(0)) {
				// rotation matrix 45 degrees.
				// https://math.stackexchange.com/questions/383321/rotating-x-y-points-45-degrees
				// std::cos( deg_to_rad( 45.f ) )
				constexpr float rotation = 0.70710678f;

				// top/back 45 deg.
				// this is the best spot to shoot at.
				points.push_back({ bbox->m_maxs.x + (rotation * r), bbox->m_maxs.y + (-rotation * r), bbox->m_maxs.z });

				// right.
				points.push_back({ bbox->m_maxs.x, bbox->m_maxs.y, bbox->m_maxs.z + r });

				// left.
				points.push_back({ bbox->m_maxs.x, bbox->m_maxs.y, bbox->m_maxs.z - r });

				// back.
				points.push_back({ bbox->m_maxs.x, bbox->m_maxs.y - r, bbox->m_maxs.z });

				// get animstate ptr.
				CCSGOPlayerAnimState* state = record->m_player->m_PlayerAnimState();

				// add this point only under really specific circumstances.
				// if we are standing still and have the lowest possible pitch pose.
				if (state && record->m_anim_velocity.length() <= 0.1f && record->m_eye_angles.x <= state->m_min_pitch) {

					// bottom point.
					points.push_back({ bbox->m_maxs.x - r, bbox->m_maxs.y, bbox->m_maxs.z });
				}
			}
		}

		// body has 5 points.
		else if (index == HITBOX_BODY) {
			// center.
			points.push_back(center);

			// back.
			if (multipoint.get(2))
				points.push_back({ center.x, bbox->m_maxs.y - br, center.z });
		}

		else if (index == HITBOX_PELVIS || index == HITBOX_UPPER_CHEST) {
			// back.
			points.push_back({ center.x, bbox->m_maxs.y - r, center.z });
		}

		// other stomach/chest hitboxes have 2 points.
		else if (index == HITBOX_THORAX || index == HITBOX_CHEST) {
			// add center.
			points.push_back(center);

			// add extra point on back.
			if (multipoint.get(1))
				points.push_back({ center.x, bbox->m_maxs.y - r, center.z });
		}

		else if (index == HITBOX_R_CALF || index == HITBOX_L_CALF) {
			// add center.
			points.push_back(center);

			// half bottom.
			if (multipoint.get(3))
				points.push_back({ bbox->m_maxs.x - (bbox->m_radius / 2.f), bbox->m_maxs.y, bbox->m_maxs.z });
		}

		else if (index == HITBOX_R_THIGH || index == HITBOX_L_THIGH) {
			// add center.
			points.push_back(center);
		}

		// arms get only one point.
		else if (index == HITBOX_R_UPPER_ARM || index == HITBOX_L_UPPER_ARM) {
			// elbow.
			points.push_back({ bbox->m_maxs.x + bbox->m_radius, center.y, center.z });
		}

		// nothing left to do here.
		if (points.empty())
			return false;

		// transform capsule points.
		for (auto& p : points)
			math::VectorTransform(p, bones[bbox->m_bone], p);
	}

	return true;
}

bool AimPlayer::GetBestAimPosition(vec3_t& aim, float& damage, LagRecord* record) {
	bool                  done, pen;
	float                 dmg, pendmg;
	HitscanData_t         scan;
	std::vector< vec3_t > points;

	// get player hp.
	int hp = std::min(100, m_player->m_iHealth());

	bool cfo = g_aimbot.m_damage_toggle;
	int override_value = g_menu.main.aimbot.override_value.get();

	if (core.m_weapon_id == ZEUS) {
		dmg = pendmg = hp;
		pen = true;
	}

	else {
		dmg = cfo ? override_value : g_aimbot.FindMindamage();

		pendmg = dmg;
		pen = true;
	}

	// write all data of this record l0l.
	record->cache();

	// iterate hitboxes.
	for (const auto& it : m_hitboxes) {
		done = false;

		// setup points on hitbox.
		if (!SetupHitboxPoints(record, record->m_bones, it.m_index, points))
			continue;

		// iterate points on hitbox.
		for (const auto& point : points) {
			penetration::PenetrationInput_t in;

			in.m_damage = dmg;
			in.m_damage_pen = pendmg;
			in.m_can_pen = pen;
			in.m_target = m_player;
			in.m_from = core.m_local;
			in.m_pos = point;

			// ignore mindmg.
			if (it.m_mode == HitscanMode::LETHAL || it.m_mode == HitscanMode::LETHAL2)
				in.m_damage = in.m_damage_pen = 1.f;

			penetration::PenetrationOutput_t out;

			// we can hit p!
			if (penetration::run(&in, &out)) {

				// nope we did not hit head..
				if (it.m_index == HITBOX_HEAD && out.m_hitgroup != HITGROUP_HEAD)
					continue;

				// prefered hitbox, just stop now.
				if (it.m_mode == HitscanMode::PREFER)
					done = true;

				// this hitbox requires lethality to get selected, if that is the case.
				// we are done, stop now.
				else if (it.m_mode == HitscanMode::LETHAL && out.m_damage >= m_player->m_iHealth())
					done = true;

				// 2 shots will be sufficient to kill.
				else if (it.m_mode == HitscanMode::LETHAL2 && (out.m_damage * 2.f) >= m_player->m_iHealth())
					done = true;

				// this hitbox has normal selection, it needs to have more damage.
				else if (it.m_mode == HitscanMode::NORMAL) {
					// from L3D makes aimbot shoot faster.
					float best_damage_per_hitbox = 0, distance_to_center = 0;
					auto distance = point.dist_to(points.front());

					if (best_damage_per_hitbox > 0 && (out.m_damage >= best_damage_per_hitbox || (out.m_damage >= (best_damage_per_hitbox - 15)) && distance < distance_to_center)) {
						scan.m_damage = out.m_damage;
						scan.m_hitbox = it.m_index;
						scan.m_pos = point;
						best_damage_per_hitbox = out.m_damage;
						distance_to_center = distance;
					}
					else {
						if (((out.m_damage > scan.m_damage || (out.m_damage >= (scan.m_damage - 15)) && distance < distance_to_center) || done)) {
							// save new best data.
							scan.m_damage = out.m_damage;
							scan.m_pos = point;
							scan.m_hitbox = it.m_index;
							best_damage_per_hitbox = out.m_damage;
							distance_to_center = distance;
						}
					}
				}

				// we found a preferred / lethal hitbox.
				if (done) {
					// save new best data.
					scan.m_damage = out.m_damage;
					scan.m_pos = point;
					scan.m_hitbox = it.m_index;
					break;
				}
			}
		}

		// ghetto break out of outer loop.
		if (done)
			break;
	}

	// we found something that we can damage.
	// set out vars.
	if (scan.m_damage > 0.f) {
		aim = scan.m_pos;
		damage = scan.m_damage;
		return true;
	}

	return false;
}
