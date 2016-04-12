#pragma once

#include <vector>
#include <type_traits>

namespace ohmrgb {
	// http://wiki.lividinstruments.com/images/thumb/4/4d/Ohm64_MIDI_Defaults.png/600px-Ohm64_MIDI_Defaults.png

	class Controls {
	public:
		enum class ID : std::size_t {
			GRID_1_1 = 0, GRID_1_2 = 8, GRID_1_3 = 16, GRID_1_4 = 24, GRID_1_5 = 32, GRID_1_6 = 40, GRID_1_7 = 48, GRID_1_8 = 56,
			GRID_2_1 = 1, GRID_2_2 = 9, GRID_2_3 = 17, GRID_2_4 = 25, GRID_2_5 = 33, GRID_2_6 = 41, GRID_2_7 = 49, GRID_2_8 = 57,
			GRID_3_1 = 2, GRID_3_2 = 10, GRID_3_3 = 18, GRID_3_4 = 26, GRID_3_5 = 34, GRID_3_6 = 42, GRID_3_7 = 50, GRID_3_8 = 58,
			GRID_4_1 = 3, GRID_4_2 = 11, GRID_4_3 = 19, GRID_4_4 = 27, GRID_4_5 = 35, GRID_4_6 = 43, GRID_4_7 = 50, GRID_4_8 = 59,
			GRID_5_1 = 4, GRID_5_2 = 12, GRID_5_3 = 20, GRID_5_4 = 28, GRID_5_5 = 36, GRID_5_6 = 44, GRID_5_7 = 52, GRID_5_8 = 60,
			GRID_6_1 = 5, GRID_6_2 = 13, GRID_6_3 = 21, GRID_6_4 = 29, GRID_6_5 = 37, GRID_6_6 = 45, GRID_6_7 = 53, GRID_6_8 = 61,
			GRID_7_1 = 6, GRID_7_2 = 14, GRID_7_3 = 22, GRID_7_4 = 30, GRID_7_5 = 38, GRID_7_6 = 46, GRID_7_7 = 54, GRID_7_8 = 62,
			GRID_8_1 = 7, GRID_8_2 = 15, GRID_8_3 = 23, GRID_8_4 = 31, GRID_8_5 = 39, GRID_8_6 = 47, GRID_8_7 = 55, GRID_8_8 = 63,

			XFADE_L = 64, XFADE = 24, XFADE_R = 72,

			SLIDE_1 = 23, SLIDE_2 = 22, SLIDE_3 = 15, SLIDE_4 = 14, SLIDE_5 = 5, SLIDE_6 = 7, SLIDE_7 = 6, SLIDE_8 = 4,
			SLIDE_1_BT = 65, SLIDE_2_BT = 73, SLIDE_3_BT = 66, SLIDE_4_BT = 74, SLIDE_5_BT = 67, SLIDE_6_BT = 75, SLIDE_7_BT = 68, SLIDE_8_BT = 76,

			F_1_1 = 69, F_1_2 = 70, F_1_3 = 71,
			F_2_1 = 77, F_2_2 = 78, F_2_3 = 79,

			KNOB_L_1_1 = 17, KNOB_L_1_2 = 16, KNOB_L_1_3 = 9, KNOB_L_1_4 = 8,
			KNOB_L_2_1 = 19, KNOB_L_2_2 = 18, KNOB_L_2_3 = 11, KNOB_L_2_4 = 10,
			KNOB_L_3_1 = 21, KNOB_L_3_2 = 20, KNOB_L_3_3 = 13, KNOB_L_3_4 = 12,

			KNOB_R_1_1 = 3, KNOB_R_1_2 = 1, KNOB_R_1_3 = 0, KNOB_R_1_4 = 2,

			BPM = 87
		};

		const static std::vector< std::vector< ID > > GRID_BY_INDEX;
	};


	class SysexCommand
	{
	public:
		typedef unsigned char byte_t;
		typedef std::vector< byte_t > bytes_t;

		SysexCommand( const bytes_t& bytes );

		operator bytes_t& ( ) { return getBytes(); }
		bool operator == ( const SysexCommand &rhs ) { return mBytes == rhs.mBytes; }
		bool operator != ( const SysexCommand &rhs ) { return !( *this == rhs ); }

		bytes_t& getBytes() { return mBytes; }

	protected:
		std::vector< unsigned char > mBytes;

	};

	enum class LEDColor : SysexCommand::byte_t {
		red = 0b00000001, green = 0b00000010, blue = 0b00000100, none = 0b00000000,
		white = 0b00000111
	};

	using color_t = std::underlying_type< LEDColor >::type;

	inline LEDColor operator | ( LEDColor a, LEDColor b )
	{
		return (LEDColor)( static_cast<color_t>( a ) | static_cast<color_t>( b ) );
	}

	inline LEDColor operator & ( LEDColor a, LEDColor b )
	{
		return (LEDColor)( static_cast<color_t>( a ) & static_cast<color_t>( b ) );
	}

	// http://wiki.lividinstruments.com/wiki/OhmRGB#OhmRGB_Sysex
	/*
	 All (81) LED indicators can be set to one of 7 colors or off with this
	 command. There are (42) bytes. Values must be 7F or less. The first 3 bits
	 in a Byte control the R, G, and B values respectively for a single
	 indicator, the next three bits control the RGB for the next LED in the
	 column, and the last bit is ignored. The positions in the list do not
	 conveniently line up with the positions of indicators on the Ohm64.

	 The LED columns and rows do not conveniently match up with the physical
	 layout of the Button columns and rows. Using codes as C.R to specify column
	 and row, the LED codes are as follows (all codes are decimal in this
	 table):

	 64 button grid:

	 56 48 40 32 24 16 8  0
	 60 52 44 36 28 20 12 4
	 57 49 41 33 25 17 9  1
	 61 53 45 37 29 21 13 5
	 58 50 42 34 26 18 10 2
	 62 54 46 38 30 22 14 6
	 59 51 43 35 27 19 11 3
	 63 55 47 39 31 23 15 7

	 Left/Right crossfader:

	 74 75

	 1-8 Slider 'mute':

	 66 67 70 71 79 78 77 76

	 F-buttons:

	 64 68 72
	 65 69 73

	 BPM:

	 80
	 */
	class SetAllLEDs : public SysexCommand {
	public:
		enum class ID : std::size_t {
			GRID_1_1 = 56, GRID_1_2 = 48, GRID_1_3 = 40, GRID_1_4 = 32, GRID_1_5 = 24, GRID_1_6 = 16, GRID_1_7 = 8, GRID_1_8 = 0,
			GRID_2_1 = 60, GRID_2_2 = 52, GRID_2_3 = 44, GRID_2_4 = 36, GRID_2_5 = 28, GRID_2_6 = 20, GRID_2_7 = 12, GRID_2_8 = 4,
			GRID_3_1 = 57, GRID_3_2 = 49, GRID_3_3 = 41, GRID_3_4 = 33, GRID_3_5 = 25, GRID_3_6 = 17, GRID_3_7 = 9, GRID_3_8 = 1,
			GRID_4_1 = 61, GRID_4_2 = 53, GRID_4_3 = 45, GRID_4_4 = 37, GRID_4_5 = 29, GRID_4_6 = 21, GRID_4_7 = 13, GRID_4_8 = 5,
			GRID_5_1 = 58, GRID_5_2 = 50, GRID_5_3 = 42, GRID_5_4 = 34, GRID_5_5 = 26, GRID_5_6 = 18, GRID_5_7 = 10, GRID_5_8 = 2,
			GRID_6_1 = 62, GRID_6_2 = 54, GRID_6_3 = 46, GRID_6_4 = 38, GRID_6_5 = 30, GRID_6_6 = 22, GRID_6_7 = 14, GRID_6_8 = 6,
			GRID_7_1 = 59, GRID_7_2 = 51, GRID_7_3 = 43, GRID_7_4 = 35, GRID_7_5 = 27, GRID_7_6 = 19, GRID_7_7 = 11, GRID_7_8 = 3,
			GRID_8_1 = 63, GRID_8_2 = 55, GRID_8_3 = 47, GRID_8_4 = 39, GRID_8_5 = 31, GRID_8_6 = 23, GRID_8_7 = 15, GRID_8_8 = 7,

			XFADE_L = 74, XFADE_R = 75,

			SLIDE_1 = 66, SLIDE_2 = 67, SLIDE_3 = 70, SLIDE_4 = 71, SLIDE_5 = 79, SLIDE_6 = 78, SLIDE_7 = 77, SLIDE_8 = 76,

			F_1_1 = 64, F_1_2 = 68, F_1_3 = 72,
			F_2_1 = 65, F_2_2 = 69, F_2_3 = 73,

			BPM = 80
		};

		const static std::vector< std::vector< ID > > GRID_BY_INDEX;


		SetAllLEDs();
		SetAllLEDs( const LEDColor &c );

		SetAllLEDs& setAll( const LEDColor &c );
		SetAllLEDs& set( const ID &lid, const LEDColor &c );
	};

	/*
	0A : Map Analog Inputs
	F0 00 01 61 07 0A (25)*[LL HH] F7
	
	This command updates the MIDI map for all (25) Analog inputs. If HH is 00,
	then LL specifies the 7-bit Control number, but only valid control numbers
	00 to 78 are accepted. If HH is 01, then LL selects between 14-bit Control
	numbers and Pitch Bend. In the latter case, LL between 60 and 6F specifies
	a Pitch Bend message on Channel (1) through (16), respectively. Otherwise,
	LL selects a 14-bit Control number, of which the only valid control numbers
	are 00 to 1F. All other values for LL, 20 through 5F and 70 through 7F are
	reserved for future use. Values of HH above 1 are similarly reserved.
	
	There are (25) sets of LL HH value pairs in this message, each
	corresponding to the index of an Analog input. These indices do not
	conveniently match up with the physical layout. The index codes are
	arranged as follows (all indices are decimal in this table, and start with
	0):
	
	crossfader: 24 eight faders, from left to right: 23, 22, 15, 14, 5, 7, 6, 4
	upper left knobs: 17, 16, 9, 8 19, 18, 11, 10 21, 20, 13, 12 right knobs:
	3, 1, 0, 2

	The OhmRGB responds with ACK when finished processing this command.
	*/
	class MapAnalogInputs : public SysexCommand
	{
	public:
		enum class ID : std::size_t {
			XFADE = 24,

			SLIDE_1 = 23, SLIDE_2 = 22, SLIDE_3 = 15, SLIDE_4 = 14,
			SLIDE_5 = 5, SLIDE_6 = 7, SLIDE_7 = 6, SLIDE_8 = 4,

			KNOB_L_1_1 = 17, KNOB_L_1_2 = 16, KNOB_L_1_3 = 9, KNOB_L_1_4 = 8,
			KNOB_L_2_1 = 19, KNOB_L_2_2 = 18, KNOB_L_2_3 = 11, KNOB_L_2_4 = 10,
			KNOB_L_3_1 = 21, KNOB_L_3_2 = 20, KNOB_L_3_3 = 13, KNOB_L_3_4 = 12,

			KNOB_R_1_1 = 3, KNOB_R_1_2 = 1, KNOB_R_1_3 = 0, KNOB_R_1_4 = 2,

			MIN = 0, MAX = 24
		};

		// Map to a 7-bit control
		enum class Control : byte_t {
			MIN = 0x00, MAX = 0x78
		};

		// Map to a 14-bit pitch bend channel
		enum class PitchBend : byte_t {
			CHANNEL_1 = 0x60, CHANNEL_2, CHANNEL_3, CHANNEL_4, CHANNEL_5,
			CHANNEL_6, CHANNEL_7, CHANNEL_8, CHANNEL_9, CHANNEL_10, CHANNEL_11,
			CHANNEL_12, CHANNEL_13, CHANNEL_14, CHANNEL_15, CHANNEL_16,
			MIN = 0x60, MAX = 0x6F
		};
		typedef PitchBend PB;

		// Map to a 14-bit control
		enum class ContinuousControl : byte_t {
			C0 = 0x00, C1, C2, C3, C4, C5, C6, C7, C8, C9,
			C10, C11, C12, C13,	C14, C15, C16, C17, C18, C19,
			C20, C21, C22, C23, C24, C25, C26, C27,	C28, C29,
			C30, C31,
			MIN = 0x00, MAX = 0x1F
		};
		typedef ContinuousControl CC;

		MapAnalogInputs();

		MapAnalogInputs& set( const ID & id, const byte_t & LL, const byte_t & HH );
		MapAnalogInputs& set( const ID & id, const Control & c );
		MapAnalogInputs& set( const ID & id, const PitchBend & pb );
		MapAnalogInputs& set( const ID & id, const ContinuousControl & cc );

		template< typename T >
		MapAnalogInputs& set( const ID & fromId, const ID & toId, const T & startV )
		{
			const int iFrom = (int)fromId;
			const int iTo = (int)fromId;
			const byte_t startByte = (byte_t)startV;

			if ( startByte + ( iTo - iFrom ) > (byte_t)T::MAX ) {
				throw std::out_of_range( "starting control value is too high to assign all requested ids" );
			}

			for ( int i = iFrom; i <= iTo; ++i ) {
				set( (ID)i, (T)( startByte + ( i - iFrom ) ) );
			}

			return *this;
		}

		template< typename T >
		MapAnalogInputs & setAll( const T & startV )
		{
			return set( ID::MIN, ID::MAX, startV );
		}

		template< typename T >
		MapAnalogInputs( const T & startV ) : MapAnalogInputs() { setAll( startV ); }
	};

}