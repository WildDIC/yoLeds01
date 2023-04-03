// #include "waveClass.h"




/* 
		iNoise8 HUE
*/

void aCreepingPre(){
	yo.nameSpeed 	= "Anime speed";
	yo.name010 		= "Anime scale";
	yo.name100		= "Color count";
	yo.name255		= "Color Begin";
	yo.isNeedUpWeb = true;
}

void aCreeping()
{
  	for (int i = 0; i < NUM_LEDS; i++) 
	{ 	    
		uint8_t noise = inoise8( 0, i * ( yo.AUX010 << 2), millis() / yo.currentSpeed); 
        noise = constrain( noise, 50, 200);
        noise = map( noise, 50, 200, 0, 255);

        uint8_t color  = map( noise, 0, 255, yo.AUX255, yo.AUX255 + yo.AUX100);
        uint8_t saturn = map( noise, 0, 255, 255, 220);

        leds[i] = CHSV( color, saturn, noise);
	}	
  	// FastLED.show();
  	// delay(yo.currentSpeed);
}

