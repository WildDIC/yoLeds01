#ifndef __WAVE_CLASS_H
#define __WAVE_CLASS_H

#include "../config.h"
#include <FastLED.h>
#include "leds.h"

// typedef void (*func_ptr)(int);

uint8_t base00;     // изменение оттенка LED
// int status;
// int color;
// int count;
// uint8_t var00, var01, var02;
// float far00, far01;

// uint8_t baza = 0;     // изменение оттенка LED
// int status = 0;
// int color = 0;
// int count = 0;
uint8_t nvar00 = 0, nvar01 = 0, nvar02 = 0;
// float far00 = 0, far01 = 0;


class waveClass{
	public: // спецификатор доступа public
		int id;				
		String name;
		bool statik;

		waveClass( int i, String n, bool s = false){	// конструктор класса
			id = i;		
			name = n;
			statik = s;
		} 

		uint8_t minSpeed = 0,  minAUX010 = 0,  minAUX100 =   0, minAUX255 =   0, minSaturn =   0, minTemp = 0;
		uint8_t maxSpeed = 20, maxAUX010 = 10, maxAUX100 = 100, maxAUX255 = 255, maxSaturn = 255, maxTemp = TEMP_IND_MAX;
		String nSpeed = "Speed", nAUX010 = "AUX010", nAUX100 = "AUX100", nAUX255 = "AUX255";

		CRGB c1 = CRGB::Red, c2 = CRGB::Green, c3 = CRGB::Blue;
	
		// int status = 0, color = 0, count = 0;
		// uint8_t baza = 0;

		uint8_t palette = 10;

		void (*anime)(void);
		void (*aninePre)(void);
		void (*aninePost)(void);

		// /*Main animate function*/
		virtual void animate(){} 
		// /*Pre run function*/
		// virtual void pre(){}
		// /*Post run function*/
		// virtual void post(){}
};

#endif