#include "waveClass.h"


/* 
		Костерок №02 

	var00 - active phaze ticks peaces
	var01 - background fader pieces

*/
void funcFire02pre(){
	// yo.name010 = "Density";
	// yo.name100 = "In/Out ticks";
	// yo.name255 = "Cooldown ticks";
	// yo.nameSpeed = "Active phase ticks x15";

	for ( int ind = 0; ind < NUM_LEDS; ind++){
		LEDS_STATUS[ind] = random8( 5);
		LEDS_VALUE[ind] = random8( 30);
	}
}

void funcFire02() {
	// uint8_t foundNEW = 0;

    for (int pos = 0; pos < NUM_LEDS; pos++){	

		if ( LEDS_VALUE[pos] <= 0){
			LEDS_STATUS[pos] +=1;

			switch (LEDS_STATUS[pos]){
				case 2:
					// LEDS_VALUE[pos] = beatsin88( 14, 20, 50);
					LEDS_VALUE[pos] = yo.currentSpeed * 15;
					nvar00 = 120 / LEDS_VALUE[pos];
					break;			
				case 3:
					LEDS_VALUE[pos] = yo.AUX100;
					nvar01 = 255 / yo.AUX100;
					break;
				case 4:
					LEDS_VALUE[pos] = yo.AUX255;
					leds[pos] = CRGB::Black;
					break;						
				case 6:
					LEDS_VALUE[pos] = 255;
					LEDS_STATUS[pos] = 5;
					break;
				default:
					break;
			}
		}
		else{
			LEDS_VALUE[pos] -= 1;

			switch (LEDS_STATUS[pos]){
				case 1:
					leds[pos] = ledGCfP( 1, false, 255 - nvar01 * LEDS_VALUE[pos]); 
					break;			
				case 2:
					leds[pos] = ledGCfP(  120 - nvar00 * LEDS_VALUE[pos], true);   //, random8( 230, 255));				
					break;			
				case 3:
					leds[pos] = ledGCfP( 120, true, nvar01 * LEDS_VALUE[pos]); //LEDS_VALUE[pos] /= 1.2); 
					break;

				default:
					break;
			}
		}
	}	        

    for ( int pos01 = 0; pos01 < yo.AUX010; pos01++){
        int pos = random8( NUM_LEDS);

		if ( LEDS_STATUS[pos] > 4 || LEDS_STATUS[pos] < 1){
			LEDS_STATUS[pos] = 1;
			LEDS_VALUE[pos]  = yo.AUX100;
		}
    }
    FastLED.show();
	delay( yo.currentSpeed);
}


waveClass initFire02(){
	waveClass animeClass( 212321, "Костерок №2");
	animeClass.nAUX010 = "Density";
	animeClass.nAUX100 = "In/Out ticks";
	animeClass.nAUX255 = "Cooldown ticks";
	animeClass.nSpeed = "Active phase ticks x15";
	animeClass.anime = &funcFire02;
	animeClass.aninePre = &funcFire02pre;
	return animeClass;
}
