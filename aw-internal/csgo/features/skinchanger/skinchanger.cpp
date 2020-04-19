#include "../../csgo.hpp"

namespace skinchanger
{
	void update( )
	{
		if ( !ctx::client.cmd )
			return;

		if ( !ctx::client.local || !ctx::client.local->is_alive( ) )
			return;

		for ( auto i = 0; ctx::client.local->get_weapons( )[ i ]; i++ )
		{
			auto weapon = entity_t::get< weapon_t >( ctx::client.local->get_weapons( )[ i ] );	

			if ( !weapon )
				continue;

			auto index = weapon->get_definition_index( );
		}
	}
}