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

void aNoiseMordor(){ 
	w.var02 	   	= 50;
	w.color 	   	= 20;
	w.baza 		= 40;
	yo.name010 	= "Background speed";
	yo.name100 	= "Background scale";
	yo.name255 	= "Palette scale";
	yo.nameSpeed = "Anime speed";
}
void aNoiseFires(){  
	w.var02 	   	= 0;
	w.color 		= 0;
	w.baza		= 70;
	yo.name010 	= "Background speed";
	yo.name100 	= "Background scale";
	yo.name255 	= "Palette scale";
	yo.nameSpeed = "Anime speed";
}

void aNoise()
{
    for (int i = 0; i < NUM_LEDS; i++) 
	{		
		w.var00 = inoise8(    i * ( yo.AUX255 >> 1), millis() / yo.currentSpeed);
		w.var01 = inoise8(    i * ( yo.AUX100     ), millis() / yo.AUX010);
		
		w.var00 = constrain( w.var00, w.baza, 200);
		w.var00 = map( w.var00, w.baza, 200, w.color, 255);

		w.var01 = constrain( w.var01, 60, 200);
		w.var01 = map( w.var01, 60, 200, w.var02, 255);

    	leds[i] = led.GCfP( w.var00, false, w.var01, 0, true);      	
    }
	// FastLED.show();
}


