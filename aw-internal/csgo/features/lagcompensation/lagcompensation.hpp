#pragma once

struct CompensationRecord_t
{
	float simulation_time;

	math::vec3_t view, head;

	player_t* pl;

	math::matrix3x4_t matrix[ 128 ];
};

struct ConVars_t
{
	bool initialize = true;

	ConVar *update_rate, *max_update_rate, *interp, *interp_ratio, *min_interp_ratio, *max_interp_ratio, *max_unlag;
};

extern std::deque< CompensationRecord_t > records[ 65 ];

extern ConVars_t cvars;

namespace lagcompensation
{
	bool valid_tick( float time );
	void update( );
}