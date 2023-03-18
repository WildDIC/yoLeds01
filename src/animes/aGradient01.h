// #include "waveClass.h"


/*
 * Gradient run base function
   far01, 
  yo.AUX100 - длина полоски
  yo.AUX255 - скорость движения палитры
 */
void aGradient01pre(){ v.var00 = 1; v.far01 = 50.0;}
void aGradient02pre(){ v.var00 = 2; v.far01 = 50.0;}
void aGradient03pre(){ v.var00 = 3; v.far01 = 50.0;}

void aGradient() 
{
	uint16_t nc = millis() * yo.AUX255 >> 16;

	uint16_t counter = millis() * ( yo.currentSpeed << 1);
	uint16_t pp = counter * NUM_LEDS >> 16; 		// 60 61 62
		
	int p1 = pp-NUM_LEDS;		// -60 -59  -58
	int p2 = pp+NUM_LEDS; 		// 180 181  182

	for(uint16_t i = 0; i < NUM_LEDS; i++)	
	{
		v.far00 = MIN( abs(pp-i), MIN( abs(p1-i), abs(p2-i)));
		v.far00 = (yo.AUX100 > v.far00) ? v.far00/yo.AUX100 * 200 : 200;

		if ( v.var00 == 1){ v.var01 = nc;}
		else if ( v.var00 == 2){ v.var01 = i + nc;}
		else { v.var01 = i;}
		
		leds[i] = led.blend( led.GCfP( v.var01), yo.c1, v.far00); // val
	}
	// FastLED.show();
	delay( yo.currentSpeed );
}


