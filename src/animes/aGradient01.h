// #include "waveClass.h"


/*
 * Gradient run base function
   far01, 
  yo.AUX100 - длина полоски
  yo.AUX255 - скорость движения палитры
 */
void aGradient01pre(){ w.var00 = 1; w.far01 = 50.0;}
void aGradient02pre(){ w.var00 = 2; w.far01 = 50.0;}
void aGradient03pre(){ w.var00 = 3; w.far01 = 50.0;}

void aGradient() 
{
	uint16_t nc = millis() * yo.AUX255 >> 16;

	uint16_t counter = millis() * ( yo.currentSpeed << 1);
	uint16_t pp = counter * NUM_LEDS >> 16; 		// 60 61 62
		
	int p1 = pp-NUM_LEDS;		// -60 -59  -58
	int p2 = pp+NUM_LEDS; 		// 180 181  182

	for(uint16_t i = 0; i < NUM_LEDS; i++)	
	{
		w.far00 = MIN( abs(pp-i), MIN( abs(p1-i), abs(p2-i)));
		w.far00 = (yo.AUX100 > w.far00) ? w.far00/yo.AUX100 * 200 : 200;

		if ( w.var00 == 1){ w.var01 = nc;}
		else if ( w.var00 == 2){ w.var01 = i + nc;}
		else { w.var01 = i;}
		
		leds[i] = led.blend( led.GCfP( w.var01), yo.c1, w.far00); // val
	}
	// FastLED.show();
	delay( yo.currentSpeed );
}


