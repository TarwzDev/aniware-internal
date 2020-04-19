#include "../../csgo.hpp"

void __fastcall hook_handler_t::frame_stage_notify( REGISTERS, client_frame_stage_t stage )
{
	switch ( stage )
	{
		case FRAME_NET_UPDATE_END:
			lagcompensation::update( );
			break;

		case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
			skinchanger::update( );
			break;
	}

	hooks::get( ).orig_frame_stage_notify( ecx, edx, stage );
}