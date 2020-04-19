#pragma once

struct AimbotData_t
{
	AimbotData_t( ) = default;
	AimbotData_t( player_t* p ) : pl( p ){};

	std::vector< math::vec3_t > points;
	player_t* pl;
};

namespace aimbot
{
	void work( );
}