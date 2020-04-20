#include "../../csgo.hpp"

namespace skinchanger
{
	void apply( weapon_t* weapon, weapon_index_t index )
	{

	}

	void update( )
	{
		if ( !ctx::client.cmd )
			return;

		if ( !ctx::client.local || !ctx::client.local->is_alive( ) )
			return;

		auto weapons_handle = ctx::client.local->get_weapons( );

		if ( !weapons_handle )
			return;

		player_info_t info;

		ctx::csgo.engine->GetPlayerInfo( ctx::csgo.engine->GetLocalPlayer( ), &info );

		for ( auto i = 0; weapons_handle[ i ]; i++ )
		{
			auto weapon = entity_t::get< weapon_t >( static_cast< basehandle_t >( weapons_handle[ i ] ) );

			if ( !weapon )
				continue;


		}
	}
}