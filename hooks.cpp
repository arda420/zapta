#include "includes.h"

Hooks                g_hooks{ };;
CustomEntityListener g_custom_entity_listener{ };;


// definitions, you can put this in hooks.h lol
struct Voice_Vader
{
	char cheat_name[13];
};

struct VoiceDataCustom
{
	uint32_t xuid_low{};
	uint32_t xuid_high{};
	int32_t sequence_bytes{};
	uint32_t section_number{};
	uint32_t uncompressed_sample_offset{};

	__forceinline uint8_t* get_raw_data()
	{
		return (uint8_t*)this;
	}
};

struct CSVCMsg_VoiceData_Legacy
{
	char pad_0000[8]; //0x0000
	int32_t client; //0x0008
	int32_t audible_mask; //0x000C
	uint32_t xuid_low{};
	uint32_t xuid_high{};
	void* voide_data_; //0x0018
	int32_t proximity; //0x001C
	//int32_t caster; //0x0020
	int32_t format; //0x0020
	int32_t sequence_bytes; //0x0024
	uint32_t section_number; //0x0028
	uint32_t uncompressed_sample_offset; //0x002C

	__forceinline VoiceDataCustom get_data()
	{
		VoiceDataCustom cdata;
		cdata.xuid_low = xuid_low;
		cdata.xuid_high = xuid_high;
		cdata.sequence_bytes = sequence_bytes;
		cdata.section_number = section_number;
		cdata.uncompressed_sample_offset = uncompressed_sample_offset;
		return cdata;
	}
};


void __fastcall Hooks::VoiceData(void* msg) {
	if (!msg) {
		g_hooks.m_client_state.GetOldMethod< VoiceData_t >(24)(this, msg);
		return;
	}

	CSVCMsg_VoiceData_Legacy* m = (CSVCMsg_VoiceData_Legacy*)msg;
	int sender_index = m->client + 1;
	VoiceDataCustom data = m->get_data();

	if (!core.m_local) {
		g_hooks.m_client_state.GetOldMethod< VoiceData_t >(24)(this, msg);
		return;
	}

	if (core.m_local->index() == sender_index) {
		g_hooks.m_client_state.GetOldMethod< VoiceData_t >(24)(this, msg);
		return;
	}

	if (m->format != 0) {
		g_hooks.m_client_state.GetOldMethod< VoiceData_t >(24)(this, msg);
		return;
	}

	// check if its empty
	if (data.section_number == 0 && data.sequence_bytes == 0 && data.uncompressed_sample_offset == 0) {
		g_hooks.m_client_state.GetOldMethod< VoiceData_t >(24)(this, msg);
		return;
	}

	Voice_Vader* packet = (Voice_Vader*)data.get_raw_data();
	player_info_t player_info;

	if (g_csgo.m_engine->GetPlayerInfo(sender_index, &player_info)) {
		if (!strcmp(packet->cheat_name, XorStr("vader.techballs"))) { // vader user
			core.vader_user.push_back(player_info.m_user_id);
		}

		if (!strcmp(packet->cheat_name, XorStr("vader.techbetaballs"))) { // vader beta
			core.vader_beta.push_back(player_info.m_user_id);
		}

		if (!strcmp(packet->cheat_name, XorStr("vader.techdevballs"))) { // vader dev
			core.vader_dev.push_back(player_info.m_user_id);
		}

		if (!strcmp(packet->cheat_name, XorStr("vader.tech")) || !strcmp(packet->cheat_name, XorStr("vader.tech2"))) { // vader crack
			core.vader_crack.push_back(player_info.m_user_id);
		}

		AimPlayer* data = &g_aimbot.m_players[sender_index - 1];

		if (m->xuid_low == 43955 || m->xuid_low == 43969 || m->xuid_low == 43803 || m->sequence_bytes == -858993664) { // kaaba by vmexit
			core.kaaba_crack_vmexit.push_back(player_info.m_user_id);
			data->m_networked_angle = m->section_number; // little hint besides networking kaaba/cheese beta crack
		}

		if (m->sequence_bytes == 321420420) { // cheese beta crack
			core.kaaba_crack_vmexit_sv.push_back(player_info.m_user_id);
			data->m_networked_angle = m->section_number;
		}

		if (m->sequence_bytes == 421420420) { // cheese leak
			core.cheese_leak_lol.push_back(player_info.m_user_id);
		}

		if (m->sequence_bytes == 420420420) { // cheese
			core.cheese_smth_idfk.push_back(player_info.m_user_id);
		}

		if (m->sequence_bytes == -918206803) // dopium hi
		{
			core.dopium_lell.push_back(player_info.m_user_id);
		}

		// xuid low/high, sequence_bytes etc. dumper
		//if (g_menu.main.misc.notifications.get(8)) {
			core.print("from: [%s] | low: [%i] | high: [%i] | sequence_bytes: [%i] | mask [%i] | sample_offs [%i] | section number [%i] \n", player_info.m_name, m->xuid_low, m->xuid_high, m->sequence_bytes, m->audible_mask, m->uncompressed_sample_offset, m->section_number);
		//}
	}

	g_hooks.m_client_state.GetOldMethod< VoiceData_t >(24)(this, msg);
}

void Pitch_proxy( CRecvProxyData *data, Address ptr, Address out ) {
	// normalize this fucker.
	math::NormalizeAngle( data->m_Value.m_Float );

	// clamp to remove retardedness.
	math::clamp( data->m_Value.m_Float, -90.f, 90.f );

	// call original netvar proxy.
	if ( g_hooks.m_Pitch_original )
		g_hooks.m_Pitch_original( data, ptr, out );
}

void Body_proxy( CRecvProxyData *data, Address ptr, Address out ) {
	Stack stack;

	static Address RecvTable_Decode{ pattern::find( g_csgo.m_engine_dll, XOR( "EB 0D FF 77 10" ) ) };

	// call from entity going into pvs.
	if ( stack.next( ).next( ).ReturnAddress( ) != RecvTable_Decode ) {
		// convert to player.
		Player *player = ptr.as< Player * >( );

		// store data about the update.
		g_resolver.OnBodyUpdate( player, data->m_Value.m_Float );
	}

	// call original proxy.
	if ( g_hooks.m_Body_original )
		g_hooks.m_Body_original( data, ptr, out );
}

void AbsYaw_proxy( CRecvProxyData *data, Address ptr, Address out ) {
	// convert to ragdoll.
	//Ragdoll* ragdoll = ptr.as< Ragdoll* >( );

	// get ragdoll owner.
	//Player* player = ragdoll->GetPlayer( );

	// get data for this player.
	/*AimPlayer* aim = &g_aimbot.m_players[ player->index( ) - 1 ];

	if( player && aim ) {
	if( !aim->m_records.empty( ) ) {
	LagRecord* match{ nullptr };

	// iterate records.
	for( const auto &it : aim->m_records ) {
	// find record that matches with simulation time.
	if( it->m_sim_time == player->m_flSimulationTime( ) ) {
	match = it.get( );
	break;
	}
	}

	// we have a match.
	// and it is standing
	// TODO; add air?
	if( match /*&& match->m_mode == Resolver::Modes::RESOLVE_STAND*/// ) {
	/*	RagdollRecord record;
	record.m_record   = match;
	record.m_rotation = math::NormalizedAngle( data->m_Value.m_Float );
	record.m_delta    = math::NormalizedAngle( record.m_rotation - match->m_lbyt );

	float death = math::NormalizedAngle( ragdoll->m_flDeathYaw( ) );

	// store.
	//aim->m_ragdoll.push_front( record );

	//core.print( tfm::format( XOR( "rot %f death %f delta %f\n" ), record.m_rotation, death, record.m_delta ).data( ) );
	}
	}*/
	//}

	// call original netvar proxy.
	if ( g_hooks.m_AbsYaw_original )
		g_hooks.m_AbsYaw_original( data, ptr, out );
}

void Force_proxy( CRecvProxyData *data, Address ptr, Address out ) {
	// convert to ragdoll.
	Ragdoll *ragdoll = ptr.as< Ragdoll * >( );

	// get ragdoll owner.
	Player *player = ragdoll->GetPlayer( );

	// we only want this happening to noobs we kill.
	if ( g_menu.main.misc.ragdoll_force.get( ) && core.m_local && player && player->enemy( core.m_local ) ) {
		// get m_vecForce.
		vec3_t vel = { data->m_Value.m_Vector[ 0 ], data->m_Value.m_Vector[ 1 ], data->m_Value.m_Vector[ 2 ] };

		// give some speed to all directions.
		vel *= 1000.f;

		// boost z up a bit.
		if ( vel.z <= 1.f )
			vel.z = 2.f;

		vel.z *= 2.f;

		// don't want crazy values for this... probably unlikely though?
		math::clamp( vel.x, std::numeric_limits< float >::lowest( ), std::numeric_limits< float >::max( ) );
		math::clamp( vel.y, std::numeric_limits< float >::lowest( ), std::numeric_limits< float >::max( ) );
		math::clamp( vel.z, std::numeric_limits< float >::lowest( ), std::numeric_limits< float >::max( ) );

		// set new velocity.
		data->m_Value.m_Vector[ 0 ] = vel.x;
		data->m_Value.m_Vector[ 1 ] = vel.y;
		data->m_Value.m_Vector[ 2 ] = vel.z;
	}

	if ( g_hooks.m_Force_original )
		g_hooks.m_Force_original( data, ptr, out );
}

void Hooks::init() {
	// hook wndproc.
	auto m_hWindow = FindWindowA(XOR("Valve001"), NULL);
	m_old_wndproc = (WNDPROC)g_winapi.SetWindowLongA(m_hWindow, GWL_WNDPROC, util::force_cast<LONG>(Hooks::WndProc));

	// setup normal VMT hooks.
	m_panel.init(g_csgo.m_panel);
	m_panel.add(IPanel::PAINTTRAVERSE, util::force_cast(&Hooks::PaintTraverse));

	m_client.init(g_csgo.m_client);
	m_client.add(CHLClient::LEVELINITPREENTITY, util::force_cast(&Hooks::LevelInitPreEntity));
	m_client.add(CHLClient::LEVELINITPOSTENTITY, util::force_cast(&Hooks::LevelInitPostEntity));
	m_client.add(CHLClient::LEVELSHUTDOWN, util::force_cast(&Hooks::LevelShutdown));
	m_client.add(CHLClient::FRAMESTAGENOTIFY, util::force_cast(&Hooks::FrameStageNotify));
	m_client.add(CHLClient::USRCMDTODELTABUFFER, util::force_cast(&Hooks::WriteUsercmdDeltaToBuffer));

	m_engine.init(g_csgo.m_engine);
	m_engine.add(IVEngineClient::ISCONNECTED, util::force_cast(&Hooks::IsConnected));
	m_engine.add(IVEngineClient::ISHLTV, util::force_cast(&Hooks::IsHLTV));

	m_prediction.init(g_csgo.m_prediction);
	m_prediction.add(CPrediction::INPREDICTION, util::force_cast(&Hooks::InPrediction));
	m_prediction.add(CPrediction::RUNCOMMAND, util::force_cast(&Hooks::RunCommand));

	m_client_mode.init(g_csgo.m_client_mode);
	m_client_mode.add(IClientMode::SHOULDDRAWPARTICLES, util::force_cast(&Hooks::ShouldDrawParticles));
	m_client_mode.add(IClientMode::SHOULDDRAWFOG, util::force_cast(&Hooks::ShouldDrawFog));
	m_client_mode.add(IClientMode::OVERRIDEVIEW, util::force_cast(&Hooks::OverrideView));
	m_client_mode.add(IClientMode::CREATEMOVE, util::force_cast(&Hooks::CreateMove));
	m_client_mode.add(IClientMode::DOPOSTSPACESCREENEFFECTS, util::force_cast(&Hooks::DoPostScreenSpaceEffects));

	m_surface.init(g_csgo.m_surface);
	m_surface.add(ISurface::LOCKCURSOR, util::force_cast(&Hooks::LockCursor));
	m_surface.add(ISurface::PLAYSOUND, util::force_cast(&Hooks::PlaySoundA));
	m_surface.add(ISurface::ONSCREENSIZECHANGED, util::force_cast(&Hooks::OnScreenSizeChanged));

	m_model_render.init(g_csgo.m_model_render);
	m_model_render.add(IVModelRender::DRAWMODELEXECUTE, util::force_cast(&Hooks::DrawModelExecute));

	m_render_view.init(g_csgo.m_render_view);
	m_render_view.add(IVRenderView::SCENEEND, util::force_cast(&Hooks::SceneEnd));

	m_shadow_mgr.init(g_csgo.m_shadow_mgr);
	m_shadow_mgr.add(IClientShadowMgr::COMPUTESHADOWDEPTHTEXTURES, util::force_cast(&Hooks::ComputeShadowDepthTextures));

	m_view_render.init(g_csgo.m_view_render);
	m_view_render.add(CViewRender::ONRENDERSTART, util::force_cast(&Hooks::OnRenderStart));
	m_view_render.add(CViewRender::RENDERVIEW, util::force_cast(&Hooks::RenderView));
	m_view_render.add(CViewRender::RENDER2DEFFECTSPOSTHUD, util::force_cast(&Hooks::Render2DEffectsPostHUD));
	m_view_render.add(CViewRender::RENDERSMOKEOVERLAY, util::force_cast(&Hooks::RenderSmokeOverlay));

	m_match_framework.init(g_csgo.m_match_framework);
	m_match_framework.add(CMatchFramework::GETMATCHSESSION, util::force_cast(&Hooks::GetMatchSession));

	m_material_system.init(g_csgo.m_material_system);
	m_material_system.add(IMaterialSystem::OVERRIDECONFIG, util::force_cast(&Hooks::OverrideConfig));

	m_fire_bullets.init(g_csgo.TEFireBullets);
	m_fire_bullets.add(7, util::force_cast(&Hooks::PostDataUpdate));

	g_custom_entity_listener.init();

	// cvar hooks.
	m_debug_spread.init(g_csgo.weapon_debug_spread_show);
	m_debug_spread.add(ConVar::GETINT, util::force_cast(&Hooks::DebugSpreadGetInt));

	m_net_show_fragments.init(g_csgo.net_showfragments);
	m_net_show_fragments.add(ConVar::GETBOOL, util::force_cast(&Hooks::NetShowFragmentsGetBool));

	// set netvar proxies.
	g_netvars.SetProxy(HASH("DT_CSPlayer"), HASH("m_angEyeAngles[0]"), Pitch_proxy, m_Pitch_original);
	g_netvars.SetProxy(HASH("DT_CSPlayer"), HASH("m_flLowerBodyYawTarget"), Body_proxy, m_Body_original);
	g_netvars.SetProxy(HASH("DT_CSRagdoll"), HASH("m_vecForce"), Force_proxy, m_Force_original);
	g_netvars.SetProxy(HASH("DT_CSRagdoll"), HASH("m_flAbsYaw"), AbsYaw_proxy, m_AbsYaw_original);
}