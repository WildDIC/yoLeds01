#ifndef __LEDS_H
#define __LEDS_H

extern CRGB leds[NUM_LEDS];            // Массив ленты

class Ledas{
	public: // спецификатор доступа public
		// waveClass( int i, String n, bool s = false){	// конструктор класса
		// 	id = i;		
		// 	name = n;
		// 	statik = s;
		bool changed = false;   		// something chaged from web or irda
		
		/*Возвращает true ( bool Ledas.changed), 
		если в настройках с сайта или ИРы что-то поменялось.
		Сбрасывается на false, после первого обращения к себе.*/
		bool isChanged(){
			bool result = this->changed;
			this->changed = false;
			return result;
		}

		CRGB hsv2rgb( CHSV hsv);
		CHSV rgb2hsv( CRGB rgb);

		void startUP();
		void powerOFF();
		static void powerON();
		static void powerONOFF();

		static void reset();
		static void UPWhite();
		static void UP();
		void OFF();
		void blink();
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
		static void setColors(	CRGB c1, CRGB c2, CRGB c3);

		static void changeSpeed( int delta);
		static void changeTemperature( int delta);
		static void changeBrightness( int delta);
		static void changeSaturation( int delta);

		CRGB GCfP( uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false);
		CRGB GCfP( CRGBPalette16 colorPalette, uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false);
		
		CHSV GCfPH( uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false);
		CHSV GCfPH( CHSVPalette16 colorPalette, uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false);

		CRGB blend( CRGB c1, CRGB c2, uint16_t blend);

		uint8_t beat(  uint8_t scale = 4);
		uint8_t beat8( uint8_t speed, uint8_t scale = 8);

		uint8_t circle8(uint8_t in);
		uint8_t circle( uint8_t ind, uint8_t total, uint8_t ts = 0);

		uint8_t beatCircle(   accum88 beats_per_minute, uint8_t timeShift = 0, uint32_t timeScale = 8);
		uint8_t beatCircle8(  accum88 beats_per_minute, uint8_t highest = 255, uint8_t timeShift = 0, uint32_t timeScale = 8);
		uint8_t beatCircle88( accum88 beats_per_minute, uint8_t lowest = 0, uint8_t highest = 255, uint8_t timeShift = 0, uint32_t timeScale = 8);
};

extern Ledas led;

#endif
