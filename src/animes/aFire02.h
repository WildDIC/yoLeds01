// #include "waveClass.h"



/* 
		Костерок №02 

	far00 - active phaze ticks peaces
	far01 - background fader pieces

*/
void aFire02pre()
{
	yo.name010 = "Density";
	yo.name100 = "In/Out ticks";
	yo.name255 = "Cooldown ticks";
	yo.name355 = "Candle blink value";
	yo.nameSpeed = "Active phase ticks x30";

	for ( int ind = 0; ind < NUM_LEDS; ind++)
	{
		w.aSTATUS[ind] = random8( 6);
		w.aVALUE[ind] = random8( 100);
	}
}

void aFire02() 
{
	if ( led.isChanged())
	{
		w.far00 = 255. / ( yo.currentSpeed * 30);
		w.far01 = 255. / ( yo.AUX100);
	}

    for (int pos = 0; pos < NUM_LEDS; pos++)
	{	
		if ( w.aVALUE[pos] <= 0)
		{
			w.aSTATUS[pos] += 1;

			switch ( w.aSTATUS[pos])
			{
				case 2:{
					w.aVALUE[pos] = yo.currentSpeed * 30;					
					break;}				
				case 3:{
					w.aVALUE[pos] = yo.AUX100;
					break;}
				case 4:{
					w.aVALUE[pos] = yo.AUX255;
					leds[pos] = CRGB::Black;
					break;}					
				default:{
					w.aVALUE[pos] = 255;
					w.aSTATUS[pos] = 5;
					break;}
			}
		}
		else{
			w.aVALUE[pos] -= 1;

			switch ( w.aSTATUS[pos])
			{
				case 1:
					leds[pos] = led.hsv2rgb( led.GCfPH( 1, false, 255 - w.far01 * w.aVALUE[pos], 0, true)); 
					break;			
				case 2:
					leds[pos] = led.hsv2rgb( led.GCfPH(  255 - w.far00 * w.aVALUE[pos], false, 255, 0, true)); 
					break;			
				case 3:
					leds[pos] = led.hsv2rgb( led.GCfPH( 255, false, w.far01 * w.aVALUE[pos], 0, true));
					break;
				default:
					break;
			}
		}
	}	        

    for ( int pos01 = 0; pos01 < yo.AUX010; pos01++)
	{
        uint8_t pos = random8( NUM_LEDS);

		if ( w.aSTATUS[pos] > 4)
		{
			w.aSTATUS[pos] = 1;
			w.aVALUE[pos]  = yo.AUX100;
		}
    }
    // FastLED.show();
	// delay( 1);
}

// /* 
// 		Костерок №02 

// 	var00 - active phaze ticks peaces
// 	var01 - background fader pieces

// */
// void funcFire02pre(){
// 	// yo.name010 = "Density";
// 	// yo.name100 = "In/Out ticks";
// 	// yo.name255 = "Cooldown ticks";
// 	// yo.nameSpeed = "Active phase ticks x15";

// 	for ( int ind = 0; ind < NUM_LEDS; ind++){
// 		w.aSTATUS[ind] = random8( 5);
// 		w.aVALUE[ind] = random8( 30);
// 	}
// }

// void funcFire02() {
// 	// uint8_t foundNEW = 0;

//     for (int pos = 0; pos < NUM_LEDS; pos++){	

// 		if ( led.aVALUE[pos] <= 0){
// 			led.aSTATUS[pos] +=1;

// 			switch ( led.aSTATUS[pos]){
// 				case 2:
// 					// LEDS_VALUE[pos] = beatsin88( 14, 20, 50);
// 					led.aVALUE[pos] = yo.currentSpeed * 15;
// 					nvar00 = 120 / led.aVALUE[pos];
// 					break;			
// 				case 3:
// 					led.aVALUE[pos] = yo.AUX100;
// 					nvar01 = 255 / yo.AUX100;
// 					break;
// 				case 4:
// 					led.aVALUE[pos] = yo.AUX255;
// 					leds[pos] = CRGB::Black;
// 					break;						
// 				case 6:
// 					led.aVALUE[pos] = 255;
// 					led.aSTATUS[pos] = 5;
// 					break;
// 				default:
// 					break;
// 			}
// 		}
// 		else{
// 			led.aVALUE[pos] -= 1;

// 			switch (led.aSTATUS[pos]){
// 				case 1:
// 					leds[pos] = led.GCfP( 1, false, 255 - nvar01 * led.aVALUE[pos]); 
// 					break;			
// 				case 2:
// 					leds[pos] = led.GCfP(  120 - nvar00 * led.aVALUE[pos], true);   //, random8( 230, 255));				
// 					break;			
// 				case 3:
// 					leds[pos] = led.GCfP( 120, true, nvar01 * led.aVALUE[pos]); //LEDS_VALUE[pos] /= 1.2); 
// 					break;

// 				default:
// 					break;
// 			}
// 		}
// 	}	        

//     for ( int pos01 = 0; pos01 < yo.AUX010; pos01++){
//         int pos = random8( NUM_LEDS);

// 		if ( led.aSTATUS[pos] > 4 || led.aSTATUS[pos] < 1){
// 			led.aSTATUS[pos] = 1;
// 			led.aVALUE[pos]  = yo.AUX100;
// 		}
//     }
//     FastLED.show();
// 	// delay( yo.currentSpeed);
// }


// waveClass initFire02( uint16_t id){
// 	waveClass animeClass( id, "Костерок №2");
// 	animeClass.nAUX010 = "Density";
// 	animeClass.nAUX100 = "In/Out ticks";
// 	animeClass.nAUX255 = "Cooldown ticks";
// 	animeClass.nSpeed = "Active phase ticks x15";
// 	animeClass.anime = &funcFire02;
// 	animeClass.aninePre = &funcFire02pre;
// 	return animeClass;
// }
