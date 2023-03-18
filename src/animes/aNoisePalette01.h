// #include "waveClass.h"



/* 			
		iNoise8 test

	var00  - color index
	var01  - background value
	var02  - background lowest value
	color  - color lowest value from palette

	AUX010 - speed
	AUX100 - background scale
	AUX255 - color scale
 */

void aNoiseMordor()
{ 
	v.var02 	= 50;
	v.color 	= 20;
	v.baza 		= 40;
	yo.name010 	= "Background speed";
	yo.name100 	= "Background scale";
	yo.name255 	= "Palette scale";
	yo.name455 	= "Color shift speed";
	yo.nameSpeed = "Anime speed";
}

void aNoiseFires()
{  
	v.var02 	= 1;
	v.color 	= 1;
	v.baza		= 70;
	yo.name010 	= "Background speed";
	yo.name100 	= "Background scale";
	yo.name255 	= "Palette scale";
	yo.name455 	= "Color shift speed";
	yo.nameSpeed = "Anime speed";
}


void aNoise()
{
    for (int i = 0; i < NUM_LEDS; i++) 
	{		
		uint8_t colorID = inoise8( i * ( yo.AUX255 >> 1), millis() / yo.currentSpeed);
		uint8_t backVal = inoise8( i * ( yo.AUX100     ), millis() / yo.AUX010);
		
		colorID = constrain( colorID, v.baza, 200);
		colorID = map( colorID, v.baza, 200, v.color, 255);

		backVal = constrain( backVal, 60, 200);
		backVal = map( backVal, 60, 200, v.var02, 255);

		leds[i] = led.GCfPH( colorID, false, backVal);  
    }
	// FastLED.show();
}


