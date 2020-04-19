#pragma once

enum FlowType_t : int
{
	flow_outgoing = 0,
	flow_incoming,
	max_flows,
};

struct INetChannelInfo
{
	enum SignalType_t : int
	{
		generic,
		localplayer,
		otherplayers,
		entities,
		sounds,
		events,
		usermessages,
		entmessages,
		voice,
		stringtable,
		move,
		stringcmd,
		signon,
		total,
	};

	VFUNC( 10, GetLatency( const int flow ), float( __thiscall* )( void*, const int ) )( flow );
	VFUNC( 11, GetAverageLatency( const int flow ), float( __thiscall* )( void*, const int ) )( flow );
	VFUNC( 12, GetAverageLoss( const int flow ), float( __thiscall* )( void*, const int ) )( flow );
	VFUNC( 13, GetAverageChoke( const int flow ), float( __thiscall* )( void*, const int ) )( flow );
	VFUNC( 14, GetAverageData( const int flow ), float( __thiscall* )( void*, const int ) )( flow );
	VFUNC( 15, GetAveragePackets( const int flow ), float( __thiscall* )( void*, const int ) )( flow );
};