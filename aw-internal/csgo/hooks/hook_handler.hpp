#pragma once

struct hook_info_t
{
	hook_info_t( ) = default;
	hook_info_t( int index, void* replace ) : m_index( index ), m_replace( replace ) {}

	int m_index;
	void* m_replace;
};

struct hook_t
{
	hook_t( ) = default;
	hook_t( void* table ) : m_table( table ), m_hook( hook::hook_t( uintptr_t( table ) ) )
	{
		m_hook.init( );
	}

	void* m_table;
	hook::hook_t m_hook;
	std::vector< hook_info_t > m_hook_info;
};

struct hook_handler_t;

namespace hooks
{
	std::unordered_map< uint32_t, hook_t > &get_map( );
	hook_handler_t &get( );

	void init( );
	void undo( );

	enum idx : int
	{
		should_draw_fog = 17,
		override_view = 18,
		create_move = 24,
		get_viewmodel_fov = 35,
		do_post_screen_space_fx = 44,
		is_hltv = 93,
		level_init_post_entity = 6,
		level_shutdown = 7,
		frame_stage_notify = 37,
		lock_cursor = 67,
		draw_set_color = 15,
		reload_font = 4,
		engine_paint = 14,
		draw_model_execute = 21,
		scene_end = 9,
		render_smoke_overlay = 41,
		get_material = 84,
		do_extra_bone_proc = 195,
		setup_bones = 13
	};
}

template< typename func_sig >
inline func_sig create_hook_impl( const uint32_t token, void* table, const uint32_t index, void* func )
{
	auto& map = hooks::get_map( );

	if ( map.find( token ) == map.end( ) )
		map.insert( std::make_pair( token, hook_t( table ) ) );

	auto &map_entry = map[ token ];
	auto &current_info = map_entry.m_hook_info.emplace_back( index, func );

	try
	{
		map_entry.m_hook.hook( current_info.m_index, current_info.m_replace );

		return map_entry.m_hook.get_original< func_sig >( current_info.m_index );
	}
	catch ( const std::out_of_range &err ){}

	return reinterpret_cast< func_sig >( nullptr );
}

inline bool create_event_callback_impl( std::string_view event_name, const std::function< void( IGameEvent* e ) > &callback )
{
	event_handler::add( event_name, callback );
	return true;
}

#define REGISTERS uintptr_t ecx, uintptr_t edx

#define CREATE_HOOK( hooker, index, func ) \
using type_fn_ ## func = decltype( &func ); \
type_fn_ ## func orig_ ## func = create_hook_impl< type_fn_ ## func >( HASH( #hooker ), hooker, index, reinterpret_cast< void* >( func ) ); \

#define CREATE_HOOK_OVERRIDE( hooker, index, func, type ) \
using type_fn = type; \
type_fn_ ## func orig_ ## func = create_hook_impl< type_fn_ ## func >( HASH( #hooker ), hooker, index, reinterpret_cast< void* >( func ) ); \

#define CREATE_EVENT_CALLBACK( func ) bool m_event_ ## func = create_event_callback_impl( #func, func );

using namespace hooks;

struct hook_handler_t
{
	hook_handler_t( ) = default;
	~hook_handler_t( ) = default;

	static void __fastcall paint( REGISTERS, int mode );
	static bool __fastcall create_move( REGISTERS, float flInputSampleTime, CUserCmd* cmd );
	static void __fastcall frame_stage_notify( REGISTERS, client_frame_stage_t stage );
	static bool __fastcall draw_fog( REGISTERS );
	static float __stdcall viewmodel_fov( );
	static void __fastcall override_view( REGISTERS, CViewSetup* setup );
	static bool __fastcall do_screen_effects( REGISTERS, const CViewSetup* setup);
	static bool __fastcall is_hltv( REGISTERS );
	static void __fastcall reload_fonts( REGISTERS );

	static void player_hurt( IGameEvent* e );
	static void player_step( IGameEvent* e );

	CREATE_HOOK( ctx::csgo.enginevgui, idx::engine_paint, paint );
	CREATE_HOOK( ctx::csgo.clientmode, idx::create_move, create_move );
	CREATE_HOOK( ctx::csgo.client, idx::frame_stage_notify, frame_stage_notify );
	CREATE_HOOK( ctx::csgo.clientmode, idx::should_draw_fog, draw_fog );
	CREATE_HOOK( ctx::csgo.clientmode, idx::get_viewmodel_fov, viewmodel_fov );
	CREATE_HOOK( ctx::csgo.clientmode, idx::override_view, override_view );
	CREATE_HOOK( ctx::csgo.clientmode, idx::do_post_screen_space_fx, do_screen_effects );
	CREATE_HOOK( ctx::csgo.engine, idx::is_hltv, is_hltv );

	CREATE_HOOK( ctx::csgo.scheme_manager, idx::reload_font, reload_fonts );

	CREATE_EVENT_CALLBACK( player_hurt );
	CREATE_EVENT_CALLBACK( player_step );
};
