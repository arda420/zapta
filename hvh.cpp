#include "includes.h"

HVH g_hvh{ };;
/*
float HVH::Distortion() {
	auto local = core.m_local;
	if (!local || local->m_iHealth() <= 0 || !local->alive())
		return FLT_MAX;

	static float flRetValue = FLT_MAX;

	if (!*core.m_packet) {
		static float flLastMovingLBY = FLT_MAX;
		static bool bDistortYaw = false;
		static bool bGeneratedRandomYaw = false;
		static float flRandomDistort = FLT_MAX;
		static int nDistortionAttempts = 0;
		static float flTimeElapsed = FLT_MAX;
		static bool bIntensityWasAtLowest = false;
		static bool bIntensityWasAtHighest = false;
		static bool bReGeneratedYaw = false;

		if (!g_hvh.m_right && !g_hvh.m_left && !g_hvh.m_back) {
			flRetValue = 0.f;
		}

		if (g_hvh.m_right || g_hvh.m_left || g_hvh.m_back) {
			if (g_hvh.m_right) {
				flRetValue = 90.f;
			}
			if (g_hvh.m_back) {
				flRetValue = 180.f;
			}
			if (g_hvh.m_left) {
				flRetValue = -90.f;
			}
		}


		bool bLocalMoving = local->m_vecVelocity().length() > 0.1f;

		if (bLocalMoving) {
			flLastMovingLBY = local->m_flLowerBodyYawTarget();

			bGeneratedRandomYaw = false;

			bIntensityWasAtLowest = bIntensityWasAtHighest = bReGeneratedYaw = false;
		}

		if (!bLocalMoving && flLastMovingLBY != FLT_MAX) {
			// since we saved our last move yaw (that any player could've got and resolved us perfectly)
			// our real is still most likely in very close proximity to the last saved yaw, which means that any good
			// hack will attempt to shoot at our last moving lby with some sort of variation to attempt to 
			// hit our head. let's get as far away from our last moving lby as possible.
			if (!bDistortYaw) { //if( fabs( local->m_flLowerBodyYawTarget( ) - flLastMovingLBY ) < 15.f ) {
				bDistortYaw = true;
			}

			// let's distort our yaw
			if (bDistortYaw) {
				float flDistortTolerance = 256.f;
				float flDistortIntensity = (floor(sin(g_csgo.m_globals->m_realtime * 4.20f) * (flDistortTolerance / 2 - 1) + flDistortTolerance / 2)) / 256.f;

				if (flDistortIntensity >= 0.9f && !bIntensityWasAtHighest) {
					bIntensityWasAtHighest = true;
				}

				if (flDistortIntensity <= 0.0f && !bIntensityWasAtLowest && bIntensityWasAtHighest) {
					bIntensityWasAtLowest = true;
				}

				// hehe, let's keep goin in a circle!
				if (bIntensityWasAtLowest && bIntensityWasAtHighest) {
					bGeneratedRandomYaw = false;
					bReGeneratedYaw = true;
				}

				if (!bGeneratedRandomYaw) {
					// let's generate some random yaw that we will base the "distortion" off
					//std::uniform_int_distribution random(-180, 180);
					flRandomDistort = g_csgo.RandomInt(-180, 180);

					// let's only allow medium distortions, we don't want to be
					// distorting a tiny yaw because that will do no good.
					// was 35
					if (fabs(flRandomDistort) > 35.f || fabs(flRandomDistort) < -35.f) // if( flRandomDistort < -35.f || flRandomDistort > 35.f )
						bGeneratedRandomYaw = true;
				}

				// let's start at our last move lby and go from there.
				flRetValue = flLastMovingLBY;
				flRetValue += (flRandomDistort * flDistortIntensity);

				float flTimeDelta = fabs(g_csgo.m_globals->m_realtime - flTimeElapsed);

				// more than enough time has passed, let's check up on the distortion
				if (flTimeDelta > 3.5f) {
					// if our yaw is already different enough, then we're done here. was 60
					if (fabs(local->m_flLowerBodyYawTarget() - flLastMovingLBY) > 60.f) {
						// make sure we've fucked this shit enough
						if (bReGeneratedYaw) {
							// let's stop here.
							bDistortYaw = false;
						}

						// let's finalize our distorted yaw
						flRetValue = flLastMovingLBY + fabs(local->m_flLowerBodyYawTarget() - flLastMovingLBY);

						// let's reset everything else too.
						nDistortionAttempts = 0;
						bGeneratedRandomYaw = false;
						flLastMovingLBY = flRandomDistort = FLT_MAX;

						// let's return now.
					jmpForceRet:
						return flRetValue;
					}
					// something didn't go right, let's continue.
					else {
						// we failed to distort twice now, fuck it, let's just do it
						// manually and pray to allah our head doesn't get hit.
						if (nDistortionAttempts >= 2) {
							// let's stop here.
							bDistortYaw = false;

							// mergh, random number, whatever.
							flRetValue = flLastMovingLBY + 75.f;

							// let's reset everything else now.
							nDistortionAttempts = 0;
							bGeneratedRandomYaw = false;
							flLastMovingLBY = flRandomDistort = FLT_MAX;

							// let's return for now.
							goto jmpForceRet;
						}
						else {
							// note the amount of times our distortions have failed.
							nDistortionAttempts++;

							// generate a new random yaw next time.
							bGeneratedRandomYaw = false;
						}
					}
				}
			}
		}
	}

	return flRetValue;
}

void HVH::DoDistortion() {
	if (!core.m_processing)
		return;

	else if (!g_menu.main.antiaim.distortion.get())
		return;

	else if (!g_csgo.m_engine->IsConnected())
		return;

	else if (!core.m_local->alive())
		return;

	else if (g_csgo.m_engine->IsPaused())
		return;

	bool bDoDistort = true;

	if (g_hvh.m_left || g_hvh.m_right || g_hvh.m_back) {
		bDoDistort = false;
		return;
	}

	if (!core.m_ground)
		bDoDistort = false;

	static float flLastMoveTime = FLT_MAX;
	static float flLastMoveYaw = FLT_MAX;
	static bool bGenerate = true;
	static float flGenerated = 0.f;
	auto distortdelta = g_menu.main.antiaim.distortion_amount.get();
	auto distortspeed = g_menu.main.antiaim.distortion_speed.get();
	if (core.m_speed > 5.f && core.m_ground && !g_input.GetKeyState(g_menu.main.movement.fakewalk.get())) {
		flLastMoveTime = g_csgo.m_globals->m_realtime;
		flLastMoveYaw = core.m_local->m_flLowerBodyYawTarget();

		if (true)
			bDoDistort = false;
	}

	if (flLastMoveTime == FLT_MAX)
		return;

	if (flLastMoveYaw == FLT_MAX)
		return;

	if (!bDoDistort) {
		bGenerate = true;
	}

	if (!g_menu.main.antiaim.force_turn.get()) {
		if (bDoDistort) {
			if (true) {
				float flDistortion = std::sin((g_csgo.m_globals->m_realtime * distortspeed * 2) * 0.5f + 0.5f);

				core.m_cmd->m_view_angles.y += distortdelta * flDistortion;
				return;
			}

			if (bGenerate) {
				float flNormalised = std::remainderf(45.f, 360.f);

				flGenerated = g_csgo.RandomFloat(-flNormalised, flNormalised);
				bGenerate = false;
			}

			float flDelta = fabs(flLastMoveYaw - core.m_local->m_flLowerBodyYawTarget());
			core.m_cmd->m_view_angles.y += flDelta + flGenerated;
		}
	}
	else {
		if (bDoDistort) {
			if (true) {
				distortspeed *= 100;
				core.m_cmd->m_view_angles.y += std::fmod(g_csgo.m_globals->m_curtime * distortspeed, 360.f);
				return;
			}
		}
	}
}
*/

void HVH::IdealPitch() {
	CCSGOPlayerAnimState* state = core.m_local->m_PlayerAnimState();
	if (!state)
		return;

	core.m_cmd->m_view_angles.x = state->m_min_pitch;
}

void HVH::AntiAimPitch() {
	bool safe = g_menu.main.config.mode.get() == 0;

	switch (m_pitch) {
	case 1:
		// down.
		core.m_cmd->m_view_angles.x = 89.f;
		break;

	case 2:
		// up.
		core.m_cmd->m_view_angles.x = -89.f;
		break;

	case 3:
		// random.
		core.m_cmd->m_view_angles.x = g_csgo.RandomFloat(safe ? -89.f : -720.f, safe ? 89.f : 720.f);
		break;

	case 4:
		// ideal.
		IdealPitch();
		break;

	default:
		break;
	}
}

void HVH::AutoDirection() {
	// constants.
	constexpr float STEP{ 4.f };
	constexpr float RANGE{ 32.f };

	// best target.
	struct AutoTarget_t { float fov; Player* player; };
	AutoTarget_t target{ 180.f + 1.f, nullptr };

	// iterate players.
	for (int i{ 1 }; i <= g_csgo.m_globals->m_max_clients; ++i) {
		Player* player = g_csgo.m_entlist->GetClientEntity< Player* >(i);

		// validate player.
		if (!g_aimbot.IsValidTarget(player))
			continue;

		// skip dormant players.
		if (player->dormant())
			continue;

		// get best target based on fov.
		float fov = math::GetFOV(core.m_view_angles, core.m_shoot_pos, player->WorldSpaceCenter());

		if (fov < target.fov) {
			target.fov = fov;
			target.player = player;
		}
	}

	if (!target.player) {
		// we have a timeout.
		if (m_auto_last > 0.f && m_auto_time > 0.f && g_csgo.m_globals->m_curtime < (m_auto_last + m_auto_time))
			return;

		// set angle to backwards.
		m_auto = math::NormalizedAngle(m_view - 180.f);
		m_auto_dist = -1.f;
		return;
	}

	/*
	* data struct
	* 68 74 74 70 73 3a 2f 2f 73 74 65 61 6d 63 6f 6d 6d 75 6e 69 74 79 2e 63 6f 6d 2f 69 64 2f 73 69 6d 70 6c 65 72 65 61 6c 69 73 74 69 63 2f
	*/

	// construct vector of angles to test.
	std::vector< AdaptiveAngle > angles{ };
	angles.emplace_back(m_view - 180.f);
	angles.emplace_back(m_view + 90.f);
	angles.emplace_back(m_view - 90.f);

	// start the trace at the enemy shoot pos.
	vec3_t start = target.player->GetShootPosition();

	// see if we got any valid result.
	// if this is false the path was not obstructed with anything.
	bool valid{ false };

	// iterate vector of angles.
	for (auto it = angles.begin(); it != angles.end(); ++it) {

		// compute the 'rough' estimation of where our head will be.
		vec3_t end{ core.m_shoot_pos.x + std::cos(math::deg_to_rad(it->m_yaw)) * RANGE,
			core.m_shoot_pos.y + std::sin(math::deg_to_rad(it->m_yaw)) * RANGE,
			core.m_shoot_pos.z };

		// draw a line for debugging purposes.
		//g_csgo.m_debug_overlay->AddLineOverlay( start, end, 255, 0, 0, true, 0.1f );

		// compute the direction.
		vec3_t dir = end - start;
		float len = dir.normalize();

		// should never happen.
		if (len <= 0.f)
			continue;

		// step thru the total distance, 4 units per step.
		for (float i{ 0.f }; i < len; i += STEP) {
			// get the current step position.
			vec3_t point = start + (dir * i);

			// get the contents at this point.
			int contents = g_csgo.m_engine_trace->GetPointContents(point, MASK_SHOT_HULL);

			// contains nothing that can stop a bullet.
			if (!(contents & MASK_SHOT_HULL))
				continue;

			float mult = 1.f;

			// over 50% of the total length, prioritize this shit.
			if (i > (len * 0.5f))
				mult = 1.25f;

			// over 75% of the total length, prioritize this shit.
			if (i > (len * 0.75f))
				mult = 1.25f;

			// over 90% of the total length, prioritize this shit.
			if (i > (len * 0.9f))
				mult = 2.f;

			// append 'penetrated distance'.
			it->m_dist += (STEP * mult);

			// mark that we found anything.
			valid = true;
		}
	}

	if (!valid) {
		// set angle to backwards.
		m_auto = math::NormalizedAngle(m_view - 180.f);
		m_auto_dist = -1.f;
		return;
	}

	// put the most distance at the front of the container.
	std::sort(angles.begin(), angles.end(),
		[](const AdaptiveAngle& a, const AdaptiveAngle& b) {
			return a.m_dist > b.m_dist;
		});

	// the best angle should be at the front now.
	AdaptiveAngle* best = &angles.front();

	// check if we are not doing a useless change.
	if (best->m_dist != m_auto_dist) {
		// set yaw to the best result.
		m_auto = math::NormalizedAngle(best->m_yaw);
		m_auto_dist = best->m_dist;
		m_auto_last = g_csgo.m_globals->m_curtime;
	}
}

void HVH::GetAntiAimDirection() {
	// edge aa.
	if (g_menu.main.antiaim.edge.get() && core.m_local->m_vecVelocity().length() < 320.f) {

		ang_t ang;
		if (DoEdgeAntiAim(core.m_local, ang)) {
			m_direction = ang.y;
			return;
		}
	}

	// lock while standing..
	bool lock = g_menu.main.antiaim.dir_lock.get();

	// save view, depending if locked or not.
	if ((lock && core.m_speed > 0.1f) || !lock)
		m_view = core.m_cmd->m_view_angles.y;

	if (m_base_angle > 0) {
		// 'static'.
		if (m_base_angle == 1)
			m_view = 0.f;

		// away options.
		else {
			float  best_fov{ std::numeric_limits< float >::max() };
			float  best_dist{ std::numeric_limits< float >::max() };
			float  fov, dist;
			Player* target, * best_target{ nullptr };

			for (int i{ 1 }; i <= g_csgo.m_globals->m_max_clients; ++i) {
				target = g_csgo.m_entlist->GetClientEntity< Player* >(i);

				if (!g_aimbot.IsValidTarget(target))
					continue;

				if (target->dormant())
					continue;

				// 'away crosshair'.
				if (m_base_angle == 2) {

					// check if a player was closer to our crosshair.
					fov = math::GetFOV(core.m_view_angles, core.m_shoot_pos, target->WorldSpaceCenter());
					if (fov < best_fov) {
						best_fov = fov;
						best_target = target;
					}
				}

				// 'away distance'.
				else if (m_base_angle == 3) {

					// check if a player was closer to us.
					dist = (target->m_vecOrigin() - core.m_local->m_vecOrigin()).length_sqr();
					if (dist < best_dist) {
						best_dist = dist;
						best_target = target;
					}
				}
			}

			if (best_target) {
				// todo - dex; calculate only the yaw needed for this (if we're not going to use the x component that is).
				ang_t angle;
				math::VectorAngles(best_target->m_vecOrigin() - core.m_local->m_vecOrigin(), angle);
				m_view = angle.y;
			}
		}
	}

	// switch direction modes.
	switch (m_dir) {

		// auto.
	case 0:
		AutoDirection();
		m_direction = m_auto;

		if (g_hvh.m_left)
			m_direction = m_view + 90.f;
		if (g_hvh.m_right)
			m_direction = m_view - 90.f;
		if (g_hvh.m_back)
			m_direction = m_view + 180.f;
		break;

		// backwards.
	case 1:
		m_direction = m_view + 180.f;

		if (g_hvh.m_left)
			m_direction = m_view + 90.f;
		if (g_hvh.m_right)
			m_direction = m_view - 90.f;
		if (g_hvh.m_back)
			m_direction = m_view + 180.f;
		break;

		// left.
	case 2:
		m_direction = m_view + 90.f;
		if (g_hvh.m_left)
			m_direction = m_view + 90.f;
		if (g_hvh.m_right)
			m_direction = m_view - 90.f;
		if (g_hvh.m_back)
			m_direction = m_view + 180.f;
		break;

		// right.
	case 3:
		m_direction = m_view - 90.f;
		if (g_hvh.m_left)
			m_direction = m_view + 90.f;
		if (g_hvh.m_right)
			m_direction = m_view - 90.f;
		if (g_hvh.m_back)
			m_direction = m_view + 180.f;
		break;

		// custom.
	case 4:
		m_direction = m_view + m_dir_custom;
		if (g_hvh.m_left)
			m_direction = m_view + 90.f;
		if (g_hvh.m_right)
			m_direction = m_view - 90.f;
		if (g_hvh.m_back)
			m_direction = m_view + 180.f;
		break;

	case 5:
		break;
	default:
		break;
	}

	// normalize the direction.
	math::NormalizeAngle(m_direction);
}

bool HVH::DoEdgeAntiAim(Player* player, ang_t& out) {
	CGameTrace trace;
	static CTraceFilterSimple_game filter{ };

	if (player->m_MoveType() == MOVETYPE_LADDER)
		return false;

	// skip this player in our traces.
	filter.SetPassEntity(player);

	// get player bounds.
	vec3_t mins = player->m_vecMins();
	vec3_t maxs = player->m_vecMaxs();

	// make player bounds bigger.
	mins.x -= 20.f;
	mins.y -= 20.f;
	maxs.x += 20.f;
	maxs.y += 20.f;

	// get player origin.
	vec3_t start = player->GetAbsOrigin();

	// offset the view.
	start.z += 56.f;

	g_csgo.m_engine_trace->TraceRay(Ray(start, start, mins, maxs), CONTENTS_SOLID, (ITraceFilter*)&filter, &trace);
	if (!trace.m_startsolid)
		return false;

	float  smallest = 1.f;
	vec3_t plane;

	// trace around us in a circle, in 20 steps (anti-degree conversion).
	// find the closest object.
	for (float step{ }; step <= math::pi_2; step += (math::pi / 10.f)) {
		// extend endpoint x units.
		vec3_t end = start;

		// set end point based on range and step.
		end.x += std::cos(step) * 32.f;
		end.y += std::sin(step) * 32.f;

		g_csgo.m_engine_trace->TraceRay(Ray(start, end, { -1.f, -1.f, -8.f }, { 1.f, 1.f, 8.f }), CONTENTS_SOLID, (ITraceFilter*)&filter, &trace);

		// we found an object closer, then the previouly found object.
		if (trace.m_fraction < smallest) {
			// save the normal of the object.
			plane = trace.m_plane.m_normal;
			smallest = trace.m_fraction;
		}
	}

	// no valid object was found.
	if (smallest == 1.f || plane.z >= 0.1f)
		return false;

	// invert the normal of this object
	// this will give us the direction/angle to this object.
	vec3_t inv = -plane;
	vec3_t dir = inv;
	dir.normalize();

	// extend point into object by 24 units.
	vec3_t point = start;
	point.x += (dir.x * 24.f);
	point.y += (dir.y * 24.f);

	// check if we can stick our head into the wall.
	if (g_csgo.m_engine_trace->GetPointContents(point, CONTENTS_SOLID) & CONTENTS_SOLID) {
		// trace from 72 units till 56 units to see if we are standing behind something.
		g_csgo.m_engine_trace->TraceRay(Ray(point + vec3_t{ 0.f, 0.f, 16.f }, point), CONTENTS_SOLID, (ITraceFilter*)&filter, &trace);

		// we didnt start in a solid, so we started in air.
		// and we are not in the ground.
		if (trace.m_fraction < 1.f && !trace.m_startsolid && trace.m_plane.m_normal.z > 0.7f) {
			// mean we are standing behind a solid object.
			// set our angle to the inversed normal of this object.
			out.y = math::rad_to_deg(std::atan2(inv.y, inv.x));
			return true;
		}
	}

	// if we arrived here that mean we could not stick our head into the wall.
	// we can still see if we can stick our head behind/asides the wall.

	// adjust bounds for traces.
	mins = { (dir.x * -3.f) - 1.f, (dir.y * -3.f) - 1.f, -1.f };
	maxs = { (dir.x * 3.f) + 1.f, (dir.y * 3.f) + 1.f, 1.f };

	// move this point 48 units to the left 
	// relative to our wall/base point.
	vec3_t left = start;
	left.x = point.x - (inv.y * 48.f);
	left.y = point.y - (inv.x * -48.f);

	g_csgo.m_engine_trace->TraceRay(Ray(left, point, mins, maxs), CONTENTS_SOLID, (ITraceFilter*)&filter, &trace);
	float l = trace.m_startsolid ? 0.f : trace.m_fraction;

	// move this point 48 units to the right 
	// relative to our wall/base point.
	vec3_t right = start;
	right.x = point.x + (inv.y * 48.f);
	right.y = point.y + (inv.x * -48.f);

	g_csgo.m_engine_trace->TraceRay(Ray(right, point, mins, maxs), CONTENTS_SOLID, (ITraceFilter*)&filter, &trace);
	float r = trace.m_startsolid ? 0.f : trace.m_fraction;

	// both are solid, no edge.
	if (l == 0.f && r == 0.f)
		return false;

	// set out to inversed normal.
	out.y = math::rad_to_deg(std::atan2(inv.y, inv.x));

	// left started solid.
	// set angle to the left.
	if (l == 0.f) {
		out.y += 90.f;
		return true;
	}

	// right started solid.
	// set angle to the right.
	if (r == 0.f) {
		out.y -= 90.f;
		return true;
	}

	return false;
}


void HVH::DoRealAntiAim() {
	// if we have a yaw antaim.
	if (m_yaw > 0) {

		// if we have a yaw active, which is true if we arrived here.
		// set the yaw to the direction before applying any other operations.
		core.m_cmd->m_view_angles.y = m_direction;

		bool stand = g_menu.main.antiaim.body_fake_stand.get() > 0 && m_mode == AntiAimMode::STAND;
		bool air = g_menu.main.antiaim.body_fake_air.get() > 0 && m_mode == AntiAimMode::AIR;

		// one tick before the update.
		if (stand && !core.m_lag && g_csgo.m_globals->m_curtime >= (core.m_body_pred - core.m_anim_frame) && g_csgo.m_globals->m_curtime < core.m_body_pred) {
			// z mode.
			if (g_menu.main.antiaim.body_fake_stand.get() == 4)
				core.m_cmd->m_view_angles.y -= 90.f;
		}

		float custom = g_menu.main.antiaim.body_fake_stand_custom.get();
		static int negative = false;

		if (g_menu.main.antiaim.body_fake_stand_fakewalk.get()) {
			// check if we will have a lby fake this tick.
			if (!core.m_lag && g_csgo.m_globals->m_curtime >= core.m_body_pred && (stand || air) && !g_input.GetKeyState(g_menu.main.movement.fakewalk.get())) {
				// there will be an lbyt update on this tick.
				if (stand) {
					switch (g_menu.main.antiaim.body_fake_stand.get()) {

						// left.
					case 1:
						core.m_cmd->m_view_angles.y += 110.f;
						break;

						// right.
					case 2:
						core.m_cmd->m_view_angles.y -= 110.f;
						break;

						// opposite.
					case 3:
						core.m_cmd->m_view_angles.y += 180.f;
						break;

						// z.
					case 4:
						core.m_cmd->m_view_angles.y += 90.f;
						break;

					case 5:
						core.m_cmd->m_view_angles.y += custom;
						break;

					case 6:
						//core.m_cmd->m_view_angles.y += 180.f;
						negative ? core.m_cmd->m_view_angles.y += 85.f : core.m_cmd->m_view_angles.y -= 93.f;
						negative = !negative;
						break;
					}
				}

				else if (air) {
					switch (g_menu.main.antiaim.body_fake_air.get()) {

						// left.
					case 1:
						core.m_cmd->m_view_angles.y += 90.f;
						break;

						// right.
					case 2:
						core.m_cmd->m_view_angles.y -= 90.f;
						break;

						// opposite.
					case 3:
						core.m_cmd->m_view_angles.y += 180.f;
						break;
					}
				}
			}
		}
		else if (!core.m_lag && g_csgo.m_globals->m_curtime >= core.m_body_pred && (stand || air)) {
			// there will be an lbyt update on this tick.
			if (stand) {
				core.m_cmd->m_view_angles.z = 30.f;
				switch (g_menu.main.antiaim.body_fake_stand.get()) {
					// left.
				case 1:
					core.m_cmd->m_view_angles.y += 110.f;
					break;

					// right.
				case 2:
					core.m_cmd->m_view_angles.y -= 110.f;
					break;

					// opposite.
				case 3:
					core.m_cmd->m_view_angles.y += 180.f;
					break;

					// z.
				case 4:
					core.m_cmd->m_view_angles.y += 90.f;
					break;

				case 5:
					core.m_cmd->m_view_angles.y += custom;
					break;

				case 6:
					//core.m_cmd->m_view_angles.y += 180.f;
					negative ? core.m_cmd->m_view_angles.y += 85.f : core.m_cmd->m_view_angles.y -= 93.f;
					negative = !negative;
					break;
				}
				core.m_cmd->m_view_angles.z = 0.f;
			}

			else if (air) {
				switch (g_menu.main.antiaim.body_fake_air.get()) {

					// left.
				case 1:
					core.m_cmd->m_view_angles.y += 90.f;
					break;

					// right.
				case 2:
					core.m_cmd->m_view_angles.y -= 90.f;
					break;

					// opposite.
				case 3:
					core.m_cmd->m_view_angles.y += 180.f;
					break;
				}
			}
		}

		// run normal aa code.
		else {
			switch (m_yaw) {

				// direction.
			case 1:
				// do nothing, yaw already is direction.
				break;

				// jitter.
			case 2: {

				// get the range from the menu.
				float range = m_jitter_range / 2.f;

				// set angle.
				core.m_cmd->m_view_angles.y += g_csgo.RandomFloat(-range, range);
				break;
			}

				  // rotate.
			case 3: {
				// set base angle.
				core.m_cmd->m_view_angles.y = (m_direction - m_rot_range / 2.f);

				// apply spin.
				core.m_cmd->m_view_angles.y += std::fmod(g_csgo.m_globals->m_curtime * (m_rot_speed * 20.f), m_rot_range);

				break;
			}
				  // random.
			default:
				break;
			}
		}
	}

	// normalize angle.
	math::NormalizeAngle(core.m_cmd->m_view_angles.y);
}

void HVH::DoFakeAntiAim() {
	// do fake yaw operations.

	// enforce this otherwise low fps dies.
	// cuz the engine chokes or w/e
	// the fake became the real, think this fixed it.
	*core.m_packet = true;

	switch (g_menu.main.antiaim.fake_yaw.get()) {

		// default.
	case 1:
		// set base to opposite of direction.
		core.m_cmd->m_view_angles.y = m_direction + 180.f;

		// apply 45 degree jitter.
		core.m_cmd->m_view_angles.y += g_csgo.RandomFloat(-90.f, 90.f);
		break;

		// relative.
	case 2:
		// set base to opposite of direction.
		core.m_cmd->m_view_angles.y = m_direction + 180.f;

		// apply offset correction.
		core.m_cmd->m_view_angles.y += g_menu.main.antiaim.fake_relative.get();
		break;

		// relative jitter.
	case 3: {
		// get fake jitter range from menu.
		float range = g_menu.main.antiaim.fake_jitter_range.get() / 2.f;

		// set base to opposite of direction.
		core.m_cmd->m_view_angles.y = m_direction + 180.f;

		// apply jitter.
		core.m_cmd->m_view_angles.y += g_csgo.RandomFloat(-range, range);
		break;
	}

		  // rotate.
	case 4:
		core.m_cmd->m_view_angles.y = m_direction + 90.f + std::fmod(g_csgo.m_globals->m_curtime * 360.f, 180.f);
		break;

		// random.
	case 5:
		core.m_cmd->m_view_angles.y = g_csgo.RandomFloat(-180.f, 180.f);
		break;

		// local view.
	case 6:
		core.m_cmd->m_view_angles.y = core.m_view_angles.y;
		break;

		// slow rotate
	case 7:
		// set base to opposite of direction.
		core.m_cmd->m_view_angles.y = m_direction + 100.f + std::fmod(g_csgo.m_globals->m_curtime * 100.f, 120.f);
		break;
	default:
		break;
	}

	// normalize fake angle.
	math::NormalizeAngle(core.m_cmd->m_view_angles.y);
}

void HVH::AntiAim() {
	bool attack, attack2;

	if (!g_menu.main.antiaim.enable.get())
		return;

	attack = core.m_cmd->m_buttons & IN_ATTACK;
	attack2 = core.m_cmd->m_buttons & IN_ATTACK2;


	if (core.m_weapon && core.m_weapon_fire) {
		bool knife = core.m_weapon_type == WEAPONTYPE_KNIFE && core.m_weapon_id != ZEUS;
		bool revolver = core.m_weapon_id == REVOLVER;

		// if we are in attack and can fire, do not anti-aim.
		if (attack || (attack2 && (knife || revolver)))
			return;
	}



	// disable conditions.
	if (g_csgo.m_gamerules->m_bFreezePeriod() || (core.m_flags & FL_FROZEN) || (core.m_cmd->m_buttons & IN_USE))
		return;

	// grenade throwing
	// CBaseCSGrenade::ItemPostFrame()
	// https://github.com/VSES/SourceEngine2007/blob/master/src_main/game/shared/cstrike/weapon_basecsgrenade.cpp#L209
	if (core.m_weapon_type == WEAPONTYPE_GRENADE
		&& (!core.m_weapon->m_bPinPulled() || attack || attack2)
		&& core.m_weapon->m_fThrowTime() > 0.f && core.m_weapon->m_fThrowTime() < g_csgo.m_globals->m_curtime)
		return;

	m_mode = AntiAimMode::STAND;

	if ((core.m_buttons & IN_JUMP) || !(core.m_flags & FL_ONGROUND))
		m_mode = AntiAimMode::AIR;

	else if (core.m_speed > 0.1f)
		m_mode = AntiAimMode::WALK;

	// load settings.
	if (m_mode == AntiAimMode::STAND) {
		m_pitch = g_menu.main.antiaim.pitch_stand.get();
		m_yaw = g_menu.main.antiaim.yaw_stand.get();
		m_jitter_range = g_menu.main.antiaim.jitter_range_stand.get();
		m_rot_range = g_menu.main.antiaim.rot_range_stand.get();
		m_rot_speed = g_menu.main.antiaim.rot_speed_stand.get();
		m_rand_update = g_menu.main.antiaim.rand_update_stand.get();
		m_dir = g_menu.main.antiaim.dir_stand.get();
		m_dir_custom = g_menu.main.antiaim.dir_custom_stand.get();
		m_base_angle = g_menu.main.antiaim.base_angle_stand.get();
		m_auto_time = g_menu.main.antiaim.dir_time_stand.get();
	}

	else if (m_mode == AntiAimMode::WALK) {
		m_pitch = g_menu.main.antiaim.pitch_walk.get();
		m_yaw = g_menu.main.antiaim.yaw_walk.get();
		m_jitter_range = g_menu.main.antiaim.jitter_range_walk.get();
		m_rot_range = g_menu.main.antiaim.rot_range_walk.get();
		m_rot_speed = g_menu.main.antiaim.rot_speed_walk.get();
		m_rand_update = g_menu.main.antiaim.rand_update_walk.get();
		m_dir = g_menu.main.antiaim.dir_walk.get();
		m_dir_custom = g_menu.main.antiaim.dir_custom_walk.get();
		m_base_angle = g_menu.main.antiaim.base_angle_walk.get();
		m_auto_time = g_menu.main.antiaim.dir_time_walk.get();
	}

	else if (m_mode == AntiAimMode::AIR) {
		m_pitch = g_menu.main.antiaim.pitch_air.get();
		m_yaw = g_menu.main.antiaim.yaw_air.get();
		m_jitter_range = g_menu.main.antiaim.jitter_range_air.get();
		m_rot_range = g_menu.main.antiaim.rot_range_air.get();
		m_rot_speed = g_menu.main.antiaim.rot_speed_air.get();
		m_rand_update = g_menu.main.antiaim.rand_update_air.get();
		m_dir = g_menu.main.antiaim.dir_air.get();
		m_dir_custom = g_menu.main.antiaim.dir_custom_air.get();
		m_base_angle = g_menu.main.antiaim.base_angle_air.get();
		m_auto_time = g_menu.main.antiaim.dir_time_air.get();
	}

	// set pitch.
	AntiAimPitch();

	// if we have any yaw.
	if (m_yaw > 0) {
		// set direction.
		GetAntiAimDirection();
	}

	// we have no real, but we do have a fake.
	else if (g_menu.main.antiaim.fake_yaw.get() > 0)
		m_direction = core.m_cmd->m_view_angles.y;

	if (g_menu.main.antiaim.fake_yaw.get()) {
		// do not allow 2 consecutive sendpacket true if faking angles.
		if (*core.m_packet && core.m_old_packet)
			*core.m_packet = false;

		// run the real on sendpacket false.
		if (!*core.m_packet || !*core.m_final_packet)
			DoRealAntiAim();

		// run the fake on sendpacket true.
		else DoFakeAntiAim();
	}

	// no fake, just run real.
	else DoRealAntiAim();
}

void HVH::SendPacket() {
	// if not the last packet this shit wont get sent anyway.
	// fix rest of hack by forcing to false.
	if (!*core.m_final_packet)
		*core.m_packet = false;



	else {
		// fake-lag enabled.
		if (g_menu.main.antiaim.lag_enable.get() && !g_csgo.m_gamerules->m_bFreezePeriod() && !(core.m_flags & FL_FROZEN)) {
			// limit of lag.
			int limit = std::min((int)g_menu.main.antiaim.lag_limit.get(), core.m_max_lag);

			// indicates wether to lag or not.
			bool active{ };

			// get current origin.
			vec3_t cur = core.m_local->m_vecOrigin();

			// get prevoius origin.
			vec3_t prev = core.m_net_pos.empty() ? core.m_local->m_vecOrigin() : core.m_net_pos.front().m_pos;

			// delta between the current origin and the last sent origin.
			float delta = (cur - prev).length_sqr();

			auto activation = g_menu.main.antiaim.lag_active.GetActiveIndices();
			for (auto it = activation.begin(); it != activation.end(); it++) {

				// move.
				if (*it == 0 && delta > 0.1f && core.m_speed > 0.1f) {
					active = true;
					break;
				}

				// air.
				else if (*it == 1 && ((core.m_buttons & IN_JUMP) || !(core.m_flags & FL_ONGROUND))) {
					active = true;
					break;
				}

				// crouch.
				else if (*it == 2 && core.m_local->m_bDucking()) {
					active = true;
					break;
				}
			}

			if (active) {
				int mode = g_menu.main.antiaim.lag_mode.get();

				// max.
				if (mode == 0)
					*core.m_packet = false;

				// break.
				else if (mode == 1 && delta <= 4096.f)
					*core.m_packet = false;

				// random.
				else if (mode == 2) {
					// compute new factor.
					if (core.m_lag >= m_random_lag)
						m_random_lag = g_csgo.RandomInt(2, limit);

					// factor not met, keep choking.
					else *core.m_packet = false;
				}

				// break step.
				else if (mode == 3) {
					// normal break.
					if (m_step_switch) {
						if (delta <= 4096.f)
							*core.m_packet = false;
					}

					// max.
					else *core.m_packet = false;
				}

				if (core.m_lag >= limit)
					*core.m_packet = true;
			}
		}
	}

	if (!g_menu.main.antiaim.lag_land.get()) {
		vec3_t                start = core.m_local->m_vecOrigin(), end = start, vel = core.m_local->m_vecVelocity();
		CTraceFilterWorldOnly filter;
		CGameTrace            trace;

		// gravity.
		vel.z -= (g_csgo.sv_gravity->GetFloat() * g_csgo.m_globals->m_interval);

		// extrapolate.
		end += (vel * g_csgo.m_globals->m_interval);

		// move down.
		end.z -= 2.f;

		g_csgo.m_engine_trace->TraceRay(Ray(start, end), MASK_SOLID, &filter, &trace);

		// check if landed.
		if (trace.m_fraction != 1.f && trace.m_plane.m_normal.z > 0.7f && !(core.m_flags & FL_ONGROUND))
			*core.m_packet = true;
	}

	// force fake-lag to 14 when fakelagging.
	if (g_input.GetKeyState(g_menu.main.movement.fakewalk.get())) {
		*core.m_packet = false;
	}




	// do not lag while shooting.
	/*if (!m_fakeduck && core.m_old_shot)
		*core.m_packet = true;*/

		// we somehow reached the maximum amount of lag.
		// we cannot lag anymore and we also cannot shoot anymore since we cant silent aim.
	if (core.m_lag >= core.m_max_lag) {
		// set bSendPacket to true.
		*core.m_packet = true;

		// disable firing, since we cannot choke the last packet.
		core.m_weapon_fire = false;
	}
}