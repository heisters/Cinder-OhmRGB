#include "OhmRGB.h"

using namespace std;
using namespace ohmrgb;


SysexCommand::SysexCommand( const bytes_t& bytes ) :
	mBytes( bytes )
{

}

MapAnalogInputs::MapAnalogInputs() :
	SysexCommand( { 0xF0, 0x00, 0x01, 0x61, 0x07, 0x0A } )
{
	for ( int i = 0; i < 50; ++i ) mBytes.push_back( 0x00 );
	mBytes.push_back( 0xF7 );
}

MapAnalogInputs & ohmrgb::MapAnalogInputs::set( const ID & id, const byte_t & LL, const byte_t & HH )
{
	int iLL = (int)id * 2 + 6;
	int iHH = iLL + 1;

	mBytes[ iLL ] = LL;
	mBytes[ iHH ] = HH;

	return *this;
}

MapAnalogInputs& MapAnalogInputs::set( const ID &id, const Control& c )
{
	return set( id, (byte_t)c, 0x00 );
}
MapAnalogInputs& MapAnalogInputs::set( const ID &id, const PitchBend& pb )
{
	return set( id, (byte_t)pb, 0x01 );
}
MapAnalogInputs& MapAnalogInputs::set( const ID &id, const ContinuousControl& cc )
{
	return set( id, (byte_t)cc, 0x01 );
}



const vector< vector< SetAllLEDs::ID > > SetAllLEDs::GRID_BY_INDEX{
    {
        SetAllLEDs::ID::GRID_1_1, SetAllLEDs::ID::GRID_1_2, SetAllLEDs::ID::GRID_1_3, SetAllLEDs::ID::GRID_1_4, SetAllLEDs::ID::GRID_1_5, SetAllLEDs::ID::GRID_1_6, SetAllLEDs::ID::GRID_1_7, SetAllLEDs::ID::GRID_1_8
    },
    {
        SetAllLEDs::ID::GRID_2_1, SetAllLEDs::ID::GRID_2_2, SetAllLEDs::ID::GRID_2_3, SetAllLEDs::ID::GRID_2_4, SetAllLEDs::ID::GRID_2_5, SetAllLEDs::ID::GRID_2_6, SetAllLEDs::ID::GRID_2_7, SetAllLEDs::ID::GRID_2_8
    },
    {
        SetAllLEDs::ID::GRID_3_1, SetAllLEDs::ID::GRID_3_2, SetAllLEDs::ID::GRID_3_3, SetAllLEDs::ID::GRID_3_4, SetAllLEDs::ID::GRID_3_5, SetAllLEDs::ID::GRID_3_6, SetAllLEDs::ID::GRID_3_7, SetAllLEDs::ID::GRID_3_8
    },
    {
        SetAllLEDs::ID::GRID_4_1, SetAllLEDs::ID::GRID_4_2, SetAllLEDs::ID::GRID_4_3, SetAllLEDs::ID::GRID_4_4, SetAllLEDs::ID::GRID_4_5, SetAllLEDs::ID::GRID_4_6, SetAllLEDs::ID::GRID_4_7, SetAllLEDs::ID::GRID_4_8
    },
    {
        SetAllLEDs::ID::GRID_5_1, SetAllLEDs::ID::GRID_5_2, SetAllLEDs::ID::GRID_5_3, SetAllLEDs::ID::GRID_5_4, SetAllLEDs::ID::GRID_5_5, SetAllLEDs::ID::GRID_5_6, SetAllLEDs::ID::GRID_5_7, SetAllLEDs::ID::GRID_5_8
    },
    {
        SetAllLEDs::ID::GRID_6_1, SetAllLEDs::ID::GRID_6_2, SetAllLEDs::ID::GRID_6_3, SetAllLEDs::ID::GRID_6_4, SetAllLEDs::ID::GRID_6_5, SetAllLEDs::ID::GRID_6_6, SetAllLEDs::ID::GRID_6_7, SetAllLEDs::ID::GRID_6_8
    },
    {
        SetAllLEDs::ID::GRID_7_1, SetAllLEDs::ID::GRID_7_2, SetAllLEDs::ID::GRID_7_3, SetAllLEDs::ID::GRID_7_4, SetAllLEDs::ID::GRID_7_5, SetAllLEDs::ID::GRID_7_6, SetAllLEDs::ID::GRID_7_7, SetAllLEDs::ID::GRID_7_8
    },
    {
        SetAllLEDs::ID::GRID_8_1, SetAllLEDs::ID::GRID_8_2, SetAllLEDs::ID::GRID_8_3, SetAllLEDs::ID::GRID_8_4, SetAllLEDs::ID::GRID_8_5, SetAllLEDs::ID::GRID_8_6, SetAllLEDs::ID::GRID_8_7, SetAllLEDs::ID::GRID_8_8
    }
};


SetAllLEDs::SetAllLEDs() :
	SysexCommand( { 0xF0, 0x00, 0x01, 0x61, 0x07, 0x04 } )
{
    for ( int i = 0; i < 42; ++i ) mBytes.push_back( 0x00 );
	mBytes.push_back( 0xF7 );
}

SetAllLEDs::SetAllLEDs( const LEDColor &c ) :
SetAllLEDs()
{
    setAll( c );
}

SetAllLEDs& SetAllLEDs::setAll( const LEDColor &c )
{
    for ( int i = 0; i < 81; ++i ) set( (ID)i, c );
    return *this;
}

SetAllLEDs& SetAllLEDs::set( const ID &lid, const LEDColor &c )
{
    int i_lid = (int)lid;
    int i = i_lid / 2 + 6;
    int shift = ( i_lid % 2 ) * 3;

    unsigned char mask = 0b00000111 << shift;
    unsigned char color = (unsigned char)c << shift;

    mBytes[ i ] = ( mBytes[ i ] & ~mask ) | color;

    return *this;
}


const vector< vector< Controls::ID > > Controls::GRID_BY_INDEX{
	{ Controls::ID::GRID_1_1, Controls::ID::GRID_1_2, Controls::ID::GRID_1_3, Controls::ID::GRID_1_4, Controls::ID::GRID_1_5, Controls::ID::GRID_1_6, Controls::ID::GRID_1_7, Controls::ID::GRID_1_8 },
	{ Controls::ID::GRID_2_1, Controls::ID::GRID_2_2, Controls::ID::GRID_2_3, Controls::ID::GRID_2_4, Controls::ID::GRID_2_5, Controls::ID::GRID_2_6, Controls::ID::GRID_2_7, Controls::ID::GRID_2_8 },
	{ Controls::ID::GRID_3_1, Controls::ID::GRID_3_2, Controls::ID::GRID_3_3, Controls::ID::GRID_3_4, Controls::ID::GRID_3_5, Controls::ID::GRID_3_6, Controls::ID::GRID_3_7, Controls::ID::GRID_3_8 },
	{ Controls::ID::GRID_4_1, Controls::ID::GRID_4_2, Controls::ID::GRID_4_3, Controls::ID::GRID_4_4, Controls::ID::GRID_4_5, Controls::ID::GRID_4_6, Controls::ID::GRID_4_7, Controls::ID::GRID_4_8 },
	{ Controls::ID::GRID_5_1, Controls::ID::GRID_5_2, Controls::ID::GRID_5_3, Controls::ID::GRID_5_4, Controls::ID::GRID_5_5, Controls::ID::GRID_5_6, Controls::ID::GRID_5_7, Controls::ID::GRID_5_8 },
	{ Controls::ID::GRID_6_1, Controls::ID::GRID_6_2, Controls::ID::GRID_6_3, Controls::ID::GRID_6_4, Controls::ID::GRID_6_5, Controls::ID::GRID_6_6, Controls::ID::GRID_6_7, Controls::ID::GRID_6_8 },
	{ Controls::ID::GRID_7_1, Controls::ID::GRID_7_2, Controls::ID::GRID_7_3, Controls::ID::GRID_7_4, Controls::ID::GRID_7_5, Controls::ID::GRID_7_6, Controls::ID::GRID_7_7, Controls::ID::GRID_7_8 },
	{ Controls::ID::GRID_8_1, Controls::ID::GRID_8_2, Controls::ID::GRID_8_3, Controls::ID::GRID_8_4, Controls::ID::GRID_8_5, Controls::ID::GRID_8_6, Controls::ID::GRID_8_7, Controls::ID::GRID_8_8 },
};
