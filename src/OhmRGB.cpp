#include "OhmRGB.h"

using namespace std;

const vector< vector< LEDs::ID > > LEDs::GRID_BY_INDEX{
    {
        LEDs::ID::GRID_1_1, LEDs::ID::GRID_1_2, LEDs::ID::GRID_1_3, LEDs::ID::GRID_1_4, LEDs::ID::GRID_1_5, LEDs::ID::GRID_1_6, LEDs::ID::GRID_1_7, LEDs::ID::GRID_1_8
    },
    {
        LEDs::ID::GRID_2_1, LEDs::ID::GRID_2_2, LEDs::ID::GRID_2_3, LEDs::ID::GRID_2_4, LEDs::ID::GRID_2_5, LEDs::ID::GRID_2_6, LEDs::ID::GRID_2_7, LEDs::ID::GRID_2_8
    },
    {
        LEDs::ID::GRID_3_1, LEDs::ID::GRID_3_2, LEDs::ID::GRID_3_3, LEDs::ID::GRID_3_4, LEDs::ID::GRID_3_5, LEDs::ID::GRID_3_6, LEDs::ID::GRID_3_7, LEDs::ID::GRID_3_8
    },
    {
        LEDs::ID::GRID_4_1, LEDs::ID::GRID_4_2, LEDs::ID::GRID_4_3, LEDs::ID::GRID_4_4, LEDs::ID::GRID_4_5, LEDs::ID::GRID_4_6, LEDs::ID::GRID_4_7, LEDs::ID::GRID_4_8
    },
    {
        LEDs::ID::GRID_5_1, LEDs::ID::GRID_5_2, LEDs::ID::GRID_5_3, LEDs::ID::GRID_5_4, LEDs::ID::GRID_5_5, LEDs::ID::GRID_5_6, LEDs::ID::GRID_5_7, LEDs::ID::GRID_5_8
    },
    {
        LEDs::ID::GRID_6_1, LEDs::ID::GRID_6_2, LEDs::ID::GRID_6_3, LEDs::ID::GRID_6_4, LEDs::ID::GRID_6_5, LEDs::ID::GRID_6_6, LEDs::ID::GRID_6_7, LEDs::ID::GRID_6_8
    },
    {
        LEDs::ID::GRID_7_1, LEDs::ID::GRID_7_2, LEDs::ID::GRID_7_3, LEDs::ID::GRID_7_4, LEDs::ID::GRID_7_5, LEDs::ID::GRID_7_6, LEDs::ID::GRID_7_7, LEDs::ID::GRID_7_8
    },
    {
        LEDs::ID::GRID_8_1, LEDs::ID::GRID_8_2, LEDs::ID::GRID_8_3, LEDs::ID::GRID_8_4, LEDs::ID::GRID_8_5, LEDs::ID::GRID_8_6, LEDs::ID::GRID_8_7, LEDs::ID::GRID_8_8
    }
};


LEDs::LEDs() :
bytes( { 0xF0, 0x00, 0x01, 0x61, 0x07, 0x04 } )
{
    for ( int i = 0; i < 42; ++i ) bytes.push_back( 0x00 );
    bytes.push_back( 0xF7 );
}

LEDs::LEDs( const COLOR &c ) :
LEDs()
{
    setAll( c );
}

LEDs& LEDs::setAll( const COLOR &c )
{
    for ( int i = 0; i < 81; ++i ) set( (ID)i, c );
    return *this;
}

LEDs& LEDs::set( const ID &lid, const COLOR &c )
{
    int i_lid = (int)lid;
    int i = i_lid / 2 + 6;
    int shift = ( i_lid % 2 ) * 3;

    unsigned char mask = 0b00000111 << shift;
    unsigned char color = (unsigned char)c << shift;

    bytes[ i ] = ( bytes[ i ] & ~mask ) | color;

    return *this;
}
