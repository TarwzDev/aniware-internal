#pragma once

struct IVRenderView 
{
	VFUNC( 4, SetBlend( float blend ), void( __thiscall* )( void*, float ) )( blend );
	VFUNC( 6, SetColorModulation( float* color ), void( __thiscall* )( void*, float* ) )( color );
};