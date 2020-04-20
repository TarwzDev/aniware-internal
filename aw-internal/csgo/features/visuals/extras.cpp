#include "../../csgo.hpp"

namespace extras
{
	void fov( )
	{
		int screen[ 2 ], radius = static_cast< int >( config::get< float >( ctx::cfg.aim_fov ) ), segments = ( M_PI * 2 ) * radius;

		if ( ctx::csgo.engine->GetScreenSize( screen[ 0 ], screen[ 1 ] ) )
		{
			render::circle( { static_cast< float >( screen[ 0 ] ) * 0.5f, static_cast< float >( screen[ 1 ] ) * 0.5f }, radius, segments, { 255, 255, 255 } );
		}
	}

	void render( )
	{
		if ( config::get< float >( ctx::cfg.aim_fov ) )
			fov( );
	}
}