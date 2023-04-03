#ifndef __LEDS_H
#define __LEDS_H

extern CRGB leds[NUM_LEDS];            // Массив ленты

class Ledas{
	public: // спецификатор доступа public
		CRGB hsv2rgb( const CHSV& hsv);
		CHSV rgb2hsv( const CRGB& rgb);

		void startUP();
		void powerOFF();
		static void powerON();
		static void powerONOFF();

		static void reset();
		void OFF();
		void blinkLong();
		void blinkShort();
		void fadeOUT();

		static void setSpeed( 	int value);
		static void setAUX010(	int value);
		static void setAUX100( 	int value);
		static void setAUX255( 	int value);
		static void setAUX355( 	int value);
		static void setAUX455( 	int value);
		static void setSaturation( int value);
		static void setTemperature(int value);
		static void setBrightness( int value);
		static void setColors(	const CRGB& c1, const CRGB& c2, const CRGB& c3);

		static void changeSpeed( int delta);
		static void changeTemperature( int delta);
		static void changeBrightness( int delta);
		static void changeSaturation( int delta);

		CRGB GCfP( uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false);
		CRGB GCfP( const struct CRGBPalette16& colorPalette, uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false);
		
		CHSV GCfPH( uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false);
		CHSV GCfPH( const struct CHSVPalette16& colorPalette, uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false);

		CRGB blend( const CRGB& c1, const CRGB& c2, uint16_t blend);

		uint8_t beat(  uint8_t bpm = 4);
		uint8_t beat8( uint8_t bpm, uint8_t timeScale = 8);

		uint8_t saw8(uint8_t in);
		uint8_t circle8(uint8_t in);
		uint8_t circle( uint8_t ind, uint8_t total, uint8_t ts = 0);

		uint8_t beatCircle(   accum88 bpm = 8, uint8_t timeShift = 0, 	uint8_t timeScale = 8);
		uint8_t beatCircle8(  accum88 bpm = 8, uint8_t highest = 255, 	uint8_t timeShift = 0, 	 uint8_t timeScale = 8);
		uint8_t beatCircle88( accum88 bpm = 8, uint8_t lowest 	= 0, 	uint8_t highest   = 255, uint8_t timeShift = 0, uint8_t timeScale = 8);
	
		uint8_t valueChange( uint8_t value, int delta = 1, uint8_t min = 0, uint8_t max = 255);
	private:
};

extern Ledas led;

#endif


/*

-=> hsv2rgb.cpp

void hsv2rgb_rainbow( const CHSV& hsv, CRGB& rgb)
{
    uint16_t region, remainder, p, q, t;
    
    if (hsv.s == 0) {	rgb.r = hsv.v;	rgb.g = hsv.v;	rgb.b = hsv.v;		return;}
    
    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 
    
    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * 		 remainder)  >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;
    
    switch (region) {
        case 0:		rgb.r = hsv.v; 	rgb.g = t; 		rgb.b = p;		break;
        case 1:		rgb.r = q; 		rgb.g = hsv.v; 	rgb.b = p;    	break;
        case 2: 	rgb.r = p; 		rgb.g = hsv.v; 	rgb.b = t;    	break;
        case 3:		rgb.r = p; 		rgb.g = q; 		rgb.b = hsv.v;  break;
        case 4: 	rgb.r = t; 		rgb.g = p; 		rgb.b = hsv.v;  break;
        default:	rgb.r = hsv.v; 	rgb.g = p; 		rgb.b = q;   	break;
    }
}


*/