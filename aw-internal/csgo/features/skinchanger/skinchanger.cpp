#include "../../csgo.hpp"

namespace skinchanger
{
	bool can_shoot( weapon_t* weapon )
	{
		if ( !weapon || weapon->get_ammo( ) <= 0 )
			return false;

		if ( weapon->get_definition_index( ) == weapon_revolver && weapon->ready_time( ) > ctx::csgo.globals->curtime )
			return false;

		return true;
	}

	void work()
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
	}
}