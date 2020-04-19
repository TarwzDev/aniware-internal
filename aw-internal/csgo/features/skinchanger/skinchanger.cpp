#include "../../csgo.hpp"

namespace skinchanger
{
	void update( )
	{
		if ( !ctx::client.cmd )
			return;

		if ( !ctx::client.local || !ctx::client.local->is_alive( ) )
			return;
	}
}