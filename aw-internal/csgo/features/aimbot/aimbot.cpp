#include "../../csgo.hpp"

namespace aimbot
{
	bool is_valid( player_t* pl )
	{
		if ( pl->IsDormant( ) )
			return false;

		if( pl == ctx::client.local )
			return false;

		if ( !pl->is_alive( ) || pl->get_flags( ).has_flag( flags_t::fl_frozen ) )
			return false;

		if ( pl->is_immune( ) )
			return false;

		return true;
	}

	bool can_shoot( weapon_t* weapon )
	{
		if ( !weapon || weapon->get_ammo( ) <= 0 )
			return false;
		
		if ( ( weapon->get_definition_index( ) == weapon_index_t::weapon_revolver ) && ( weapon->ready_time( ) > ctx::csgo.globals->curtime ) )
			return false;

		return true;
	}

	void select_points( AimbotData_t &data )
	{
		const auto append_point = []( AimbotData_t &data, math::vec3_t point, player_t* pl )
		{
			if ( point.zero( ) )
				return;

			if ( !ctx::client.local->can_see_pos( pl, point ) )
				return;

			data.points.push_back( point );
		};

		for ( auto i = config::get< bool >( ctx::cfg.aim_body ) ? 2 : 0; i < Hitboxes_t::hitbox_max; i++ )
		{
			append_point( data, data.pl->get_hitbox_pos( i ), data.pl );
		}
	}

	void select_angles( AimbotData_t &data )
	{
		if ( data.points.empty( ) )
			return;

		ctx::client.cmd->viewangles = math::calc_angle( ctx::client.local->get_eye_pos( ), data.points.front( ) );

		if ( config::get< bool >( ctx::cfg.aim_recoilcompensation ) )
		{
			ctx::client.cmd->viewangles -= ctx::client.local->get_punch_angle() * 2;
		}

		if ( !config::get< bool >( ctx::cfg.aim_silent ) )
		{
			ctx::csgo.engine->SetViewAngles( ctx::client.cmd->viewangles );
		}

		if ( config::get< bool >( ctx::cfg.aim_shoot ) )
		{
			ctx::client.cmd->buttons.add_flag( ButtonFlags_t::in_attack );
		}
	}

	void work( )
	{
		if ( !config::get< bool >( ctx::cfg.aim_enable ) )
			return;

		if ( !ctx::client.cmd )
			return;

		if ( !ctx::client.local || !ctx::client.local->is_alive( ) )
			return;

		auto weapon = entity_t::get< weapon_t >( ctx::client.local->get_weapon_handle( ) );

		if ( !can_shoot( weapon ) )
			return;

		game::for_every_player( []( player_t* pl ) -> bool {
			if ( !is_valid( pl ) )
				return false;

			AimbotData_t data( pl );
	
			select_points( data );
			select_angles( data );

			if ( !data.points.empty( ) )
				data.points.clear( );

			return false;
		}, ( config::get< bool >( ctx::cfg.aim_friendly ) ? game::NO_FLAG : game::ENEMY_ONLY ) );
	}
}