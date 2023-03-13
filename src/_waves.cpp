// #include "config.h"
// #include "leds.h"
// #include "waves.h"



// /*
//  * Android loading circle
//  */
// void aAndroid() {
// 	baza++;
// 	for(uint16_t i = 0; i < NUM_LEDS; i++) { leds[i] = ledGCfP( i); }

// 	if ( var01 > 40) { 				var00 = 1;}						// убываем
// 	else{	if (var01 < 2) var00 = 0;}								// растем

// 	uint16_t a = var02;  	// точка отрисовки

// 	if (var00 == 0)  {
// 		if ( baza %3 == 1) {a++;}
// 		else {var01++;}
// 	} else  {
// 		a++;
// 		if ( baza %3 != 1) var01--;
// 	}

// 	if (a >= NUM_LEDS) a = 0; 		// переход в начало

// 	if (a + var01 < NUM_LEDS)  {
// 		for(int i = a; i < a+var01; i++) { 				 leds[i] = blend( yo.c1, leds[i], var01);}
// 	} else {
// 		for(int i = a; i < NUM_LEDS; i++) {				 leds[i] = blend( yo.c1, leds[i], var01);}
// 		for(int i = 0; i < var01 - (NUM_LEDS -a); i++) { leds[i] = blend( yo.c1, leds[i], var01);}
// 	}
// 	var02 = a;
	
// 	// FastLED.show();
// 	delay( yo.currentSpeed * 2);
// }





// /* 
// 		Костерок №01 
// */
// void aFire01()
// {    
// 	leds[random8(NUM_LEDS)] = ledGCfP( random8( 255));  
// 	// leds[random8(NUM_LEDS)] = CHSV( yoPal[random8( 255)].h, yo.currentSaturn, random8( 200, 255)); 
// 	leds[random8(NUM_LEDS)].nscale8( random8(100));

// 	if ( random8() < 35)
// 	{
// 		fadeToBlackBy(leds, NUM_LEDS, 10);	
// 	}
//     // FastLED.show();
// 	delay(yo.currentSpeed * 2);
// }




// возвращает цвет огня для одного пикселя
// CHSV getFireColor(int val) {
//   	// чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
//   	return CHSV(
//         HUE_START + map(val, 0, 255, 0, HUE_GAP),                    // H
//         constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),       // S
//         constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
//     );
// }





// /* 
// 		Моргалочка 

// 	aux010 - color change speed	
// 	led.aVALUE, aux100 - blink speed
// 	aux255 - count leds
// 	led.aSTATUS - timeshift for beatsin8
	
// 	var00 - aux010 keeper
// 	var01 - leds light count
// 	var02 - aux100 keeper
// 	color - colorID
// 	baza  - current activity ID
// 	count - baza keeper for in/out
// 	status- fadein/out counter/statuser

// 	1 - left wave
// 	2 - beatsin with random tshift
// 	3 - right wave
// 	4 - noise
// */

// void aBlinkenPre(){  
// 	yo.name010 = "Color speed";
// 	yo.name100 = "Blink speed";
// 	yo.name255 = "Leds count";
// 	status = 0;
// }

// void aBlinken(){

// 	far00 += 0.003 * yo.AUX010;
// 	color = far00;

// 	EVERY_N_SECONDS( 65) {	
// 		// count += 1;
// 		count = random8( 1, 5);  // +1 becoz THIS IS RANDOM!!!

// 		if ( count != baza)	{
// 			status = yo.currentBrightness + 1; 
// 		}
// 	} 

// 	// Fade IN/OUT
// 	if ( status != 0){
// 		if ( status == 1){
// 			baza 	= count;
// 			status 	= yo.currentBrightness * -1;
// 			FastLED.delay( 200);
// 			fill_solid( leds, NUM_LEDS, CRGB::Black);	
// 		}
// 		else if ( status > 1) { 
// 			FastLED.setBrightness( status-- - 1);}
// 		else{ 
// 			FastLED.setBrightness( yo.currentBrightness + status++ );}
// 	}
	
// 	// фиксики	
// 	if ( yo.currentSpeed < 4){
// 		fadeToBlackBy(leds, NUM_LEDS, 2); 

// 		uint8_t pos = inoise8( color * 10, millis() / 5); // * 100);
// 		pos = map(pos, 30, 225, 0, NUM_LEDS - 1);  	
// 		leds[pos] = CRGB( yo.c1);	
	
// 		if ( yo.currentSpeed < 3){
// 			pos = inoise8( color * 10, millis() / 4); // * 100);
// 			pos = map(pos, 30, 225, 0, NUM_LEDS - 1);  	
// 			leds[pos] = CRGB( yo.c2);
// 		}
// 	}

// 	//перерасчет при смене настроек с сайта
// 	if ( var00 != yo.AUX255 || var02 != yo.AUX100){
// 		var00 = yo.AUX255;
// 		var02 = yo.AUX100;
// 		var01 = NUM_LEDS / yo.AUX255 + 1; 			 	// колличество рабочих диодов

// 		for ( int i = 0; i < var01; i++) {
// 			led.aSTATUS[i] = random8();
// 			led.aVALUE[i]  = yo.AUX100 + random8( 5);
// 			led.aFEDOR[i]  = ( 255 * i) / var01;		// предрасчет таймшифта для битсина для бегущих полосок. просто, потому, что могу это сделать здесь, а не в цикле.
// 		}
// 		fill_solid( leds, NUM_LEDS, CRGB::Black);		
// 	}

// 	// рисуем всякое
// 	switch ( baza){
// 		case 1:
// 			for ( int i = 0; i < var01; i++) {	
// 				leds[i * yo.AUX255] = ledGCfP( color, false, beatsin8( yo.AUX100, 0, 255, 0, led.aFEDOR[i])); 
// 			}
// 			break;
// 		case 2:
// 			for ( int i = 0; i < var01; i++) {	
// 				leds[i * yo.AUX255] = ledGCfP( color, false, beatsin8( led.aVALUE[i], 0, 255, 0, led.aSTATUS[i])); 
// 			}
// 			break;
// 		case 3:
// 			for ( int i = 0; i < var01; i++) {	
// 				leds[i * yo.AUX255] = ledGCfP( color, false, beatsin8( yo.AUX100, 0, 255, 0, 255 - led.aFEDOR[i])); 
// 			}
// 			break;
// 		case 4:
// 			for ( int i = 0; i < var01; i++) {	

// 				uint8_t noise = inoise8( i * 100, millis() / 4);
// 				noise = constrain( noise, 65, 200);
// 				noise = map( noise, 65, 200, 0, 255);
// 				leds[i * yo.AUX255] = ledGCfP( color, false, noise); 
// 			}
// 			break;
// 		case 5:
// 			// var00 = beatsin8( 10, 0, var01 - 1, 0, 0);
// 			// var02 = beatsin8( 20, 0, var01 - 1, 0, 0);
// 			// leds[ yo.AUX255 * (( var00 + var02) / 2)]  = CHSV( color, 255, 255);

// 			// var00 = beatsin8( 10, 0, var01 - 1, 0, 128);
// 			// var02 = beatsin8( 20, 0, var01 - 1, 0, 128);
// 			// leds[ yo.AUX255 * (( var00 + var02) / 2)]  = CHSV( color, 255, 255);

// 			// fadeToBlackBy(leds, NUM_LEDS, 1);
// 			break;
// 		case 6:
// 			// for ( int i = 0; i < var01; i++) {	
// 			// 	uint16_t sinBeat   = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
//   			// 	uint16_t sinBeat2  = beatsin16(30, 0, NUM_LEDS - 1, 0, 21845);
// 			// 	uint16_t sinBeat3  = beatsin16(30, 0, NUM_LEDS - 1, 0, 43690);

// 			// 	leds[sinBeat]   = CRGB::Blue;
// 			// 	leds[sinBeat2]  = CRGB::Red;
// 			// 	leds[sinBeat3]  = CRGB::White;
				
// 			// 	fadeToBlackBy(leds, NUM_LEDS, 10);
// 			// }
// 			break;
// 		default:
// 			baza = 1;
// 			break;
// 	}
// 	FastLED.show();
// 	delay( yo.currentSpeed);
// }





// // the original levels for the leds (mix of yellow and red) that we define in setup()
// unsigned int r[NUM_LEDS], g[NUM_LEDS], b[NUM_LEDS];
// // the new levels we randomized
// unsigned int rx[NUM_LEDS], gx[NUM_LEDS], bx[NUM_LEDS];
// // the levels to approach the new levels by tweaning (these we use to set the neopixels)
// double rz[NUM_LEDS], gz[NUM_LEDS], bz[NUM_LEDS];
// // the diff to the new levels to twean to them in 10 steps
// double dr[NUM_LEDS], dg[NUM_LEDS], db[NUM_LEDS];

// void aFire03pre() {
// 	for (int i=0; i<NUM_LEDS; i++) {
// 		if (i%3==0) {
// 			r[i] = 70;
// 			g[i] = 0;
// 			b[i] = 0;
// 		}
// 		if (i%3==1) {
// 			r[i] = 60;
// 			g[i] = 30;
// 			b[i] = 0;
// 		}
// 		if (i%3==2) {
// 			r[i] = 100;
// 			g[i] = 70;
// 			b[i] = 0;
// 		}
		
// 		// r[i] = ledGCfP( i).r;
// 		// g[i] = ledGCfP( i).g;
// 		// b[i] = ledGCfP( i).b;
// 	}        
// }

// void aFire03() {
// // twean to the new values all the time
//   for (int i=0; i<NUM_LEDS; i++) {
//     rz[i] += dr[i];
//     gz[i] += dg[i];
//     bz[i] += db[i];

//     // to guard from overflow or accidental unwanted flickering
//     if (rz[i]<0) rz[i] = 0;
//     if (rz[i]>255) rz[i] = 255;
//     if (gz[i]<0) gz[i] = 0;
//     if (gz[i]>255) gz[i] = 255;
//     if (bz[i]<0) bz[i] = 0;
//     if (bz[i]>255) bz[i] = 255;
//   }

//   count++;
//   if (count>9) {   // we set new levels now after 10 iterations
//     count = 0;

// 	for ( int ind=0; ind < NUM_LEDS / 12; ind++){
// 		// set new levels based on a factor, and this in those 3 'groups' of leds
//     	for (int j=0; j<3; j++) {
//       		float z = 10.0/random(4, 11);   // min is inclusive, max is exclusive (giving range from 0.4 to 1.0)
//       		for (int i=0; i<4; i++) {

//         		int idx = (( ind * 12) + ( j * 4) + i);
        	
// 				rx[idx] = (int) (r[idx] * z);
//         		gx[idx] = (int) (g[idx] * z);
//         		bx[idx] = (int) (b[idx] * z);
//       		}
//     	}
// 	}    

//     // calculate the diff values (1/10th step)
//     for (int i=0; i<NUM_LEDS; i++) {
//       dr[i] = (rx[i] - rz[i])/10;
//       dg[i] = (gx[i] - gz[i])/10;
//       db[i] = (bx[i] - bz[i])/10;
//     }
//   }

//   // update the leds
//   for (int i=0; i<NUM_LEDS; i++) {
//     leds[i] = CRGB( (int)rz[i], (int)gz[i], (int)bz[i]);
// 	// strip.setPixelColor(i, strip.Color((int)rz[i], (int)gz[i], (int)bz[i], 255) );
//   }
// //   FastLED.show();
// 	delay( yo.currentSpeed * 2);
// //   delay(10);    // run our loop at approx 100Hz; so new LED levels reach every ~100 ms (~10Hz)
// }

