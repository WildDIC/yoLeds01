#include "config.h"
#include "leds.h"
#include "waves.h"



uint8_t baza = 0;     // изменение оттенка LED
int color = 0;
uint8_t var00, var01, var02;
float far00, far01;

// #include "waveClass.h"
// waveClass anima01( 1, 2, 3);
// void anima01::getDate() override
// {
// }


/* Бегущая радужная вэйв */
void animWave01(){
	fadeToBlackBy(leds, NUM_LEDS, 4);
	leds[beatsin8(13, 0, NUM_LEDS - 1)] = ledGCfP( baza++, false);
	FastLED.show();
}




/* Костерок №01 */
void animWave02(){    
	leds[random8(NUM_LEDS)] = ledGCfP( random8( 255));  
	// leds[random8(NUM_LEDS)] = CHSV( yoPal[random8( 255)].h, yo.currentSaturn, random8( 200, 255)); 
	leds[random8(NUM_LEDS)].nscale8( random8(100));
	if ( random8() < 35){
		fadeToBlackBy(leds, NUM_LEDS, 10);	
	}
    FastLED.show();
	delay(yo.currentSpeed / 2);
}


/* 
	iNoise8 test

	var00  - color index
	var01  - background value
	var02  - background lowest value
	color  - speed randomizer ( +-2)

	AUX010 - speed
	AUX100 - background scale
	AUX255 - color scale
 */

void animWave03mordor(){ var02 = 50;}
void animWave03fires(){  var02 = 0;}

void animWave03(){

	// EVERY_N_SECONDS( 10){
	// 	color = random( -2, 2);
	// }

    for (int i = 0; i < NUM_LEDS; i++) {
		
		// var00 = ( inoise8( i * ( yo.AUX255 / 4), millis() / yo.AUX010) - 20) * 1.2;
		var00 = inoise8( i * ( yo.AUX255 >> 1), millis() / ( yo.currentSpeed));
		var01 = inoise8( i * ( yo.AUX100     ), millis() / ( yo.AUX010));
		
		var00 = constrain( var00, 65, 200);
		var00 = map( var00, 65, 200, 0, 245);

		var01 = constrain( var01, 65, 200);
		var01 = map( var01, 65, 200, var02, 255);

    	leds[i] = ledGCfP( var00, false, var01);      	
    }
	FastLED.show();
}





/* 8 волн с разной скоротью и наложением цвета */
void animWave04(){
	fadeToBlackBy(leds, NUM_LEDS, 4);
    for (int i = 4; i < 12; i++) {
      	leds[beatsin8( i, 0, NUM_LEDS - 1)] |= ledGCfP( baza+=16, true, 255, 0);  // ЖДОБАВИТЬСАТУРАЦИИИИИИИИИИИИИИИИИИИИИИИИИИИИ
    }
	FastLED.show();
}




/* Ползущая радуга с проблесками беленьких диодов */
void animWave05(){
    baza+=1;
  	for (int i = 0; i < NUM_LEDS; i++) { leds[i] = ledGCfP( (i+baza)*3, true);	}
	
    if (random8() < 40) { leds[ random8(NUM_LEDS)] = CRGB::White; }
  	FastLED.show();
  	delay(yo.currentSpeed * 4);
}




/* Вжух-вжух радуга из цента типа странной цветомузыки */
void animWave06(){
	uint8_t rand = random8( 1, TOP_INDEX);
    for (int i = 0; i < rand; i++ ) {
		leds[TOP_INDEX + i] = ledGCfP( i*3);
		leds[TOP_INDEX - i] = ledGCfP( i*3);
        delay( 100 / rand);
        FastLED.show();
	}
	for (int i = rand; i > 0; i-- ) {
		leds[TOP_INDEX + i] = CRGB::Black;
		leds[TOP_INDEX - i] = CRGB::Black;
		FastLED.show();
        delay( 100 / rand);		
	}	
}




// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 50
#define MINUS 10
bool gReverseDirection = false;

/* Fire 2012 */
void animWave07(){
  static byte heat[NUM_LEDS];
  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS-MINUS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / ( NUM_LEDS-MINUS)) + 2));
    }
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS-MINUS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS-MINUS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-MINUS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
	FastLED.show(); // display this frame
}


/* Костерок №02 */

void animWave08pre(){
	for ( int ind = 0; ind < NUM_LEDS; ind++){
		LEDS_STATUS[ind] = random8( 5);
		LEDS_VALUE[ind] = random8( 30);
	}
}

void animWave08() {
	// uint8_t foundNEW = 0;

    for (int pos = 0; pos < NUM_LEDS; pos++){	

		if ( LEDS_VALUE[pos] <= 0){
			LEDS_STATUS[pos] +=1;

			switch (LEDS_STATUS[pos]){
				case 2:
					// LEDS_VALUE[pos] = beatsin88( 14, 20, 50);
					LEDS_VALUE[pos] = 30;
					break;			
				case 3:
					LEDS_VALUE[pos] = yo.AUX100;
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
		}else{
			LEDS_VALUE[pos] -= 1;

			switch (LEDS_STATUS[pos]){
				case 1:
					leds[pos] = ledGCfP( 1, false, 255 - ( 255 / yo.AUX100) * LEDS_VALUE[pos]); 
					break;			
				case 2:
					// leds[pos] = ledGCfP( 120 - LEDS_VALUE[pos] * 4, true,  inoise8( pos, millis() / 5) + 40);
					leds[pos] = ledGCfP( 120 - LEDS_VALUE[pos] * 4, true);   //, random8( 230, 255));				
					delay( 1);
					break;			
				case 3:
					leds[pos] = ledGCfP( 120, true, ( 255 / yo.AUX100) * LEDS_VALUE[pos]); //LEDS_VALUE[pos] /= 1.2); 
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
			// if ( foundNEW += 1 > 4){
			// 	break;
			// }
        // }
    }
    FastLED.show();
	// Serial.printf( "%d ( %d, %d, %d)- %d \n", leds[1], leds[1].r, leds[1].g, leds[1].b, LEDS_HUE[1]);
}



/*
			4 wavwes + 1 beatSin
*/
void animWave09pre(){
	#define NUM_SEGMENTS 3
	#define SPEED_WAVE 13
	#define SAT_DIVINE 20

	for ( int ind = 0; ind < NUM_SEGMENTS; ind++){
		LEDS_HUE[ind] = random8( 255);
	}
}
/* 4 симметричные волны навстречу с наложением цвета */
void animWave09() {
 	if ( ++baza > NUM_LEDS) { baza = 0; }
    fadeToBlackBy(leds, NUM_LEDS, 6);

    for ( int ind = 0; ind < NUM_SEGMENTS; ind++){
        int pos = (baza + ind * NUM_LEDS / NUM_SEGMENTS) % NUM_LEDS;

        leds[pos] 			  |= ledGCfP( LEDS_HUE[ind]++, false, 200, SAT_DIVINE);
        leds[NUM_LEDS - pos]  |= ledGCfP( LEDS_HUE[ind]++, false, 200, SAT_DIVINE);
    }
	leds[beatsin8( SPEED_WAVE, 0, NUM_LEDS - 1)] |=  ledGCfP( myPal[6].palette, baza, false);
     
    FastLED.show();        
  	delay( yo.currentSpeed * 2);
}


/*
		XXX beatSin WAVES
*/
void animaWave10(){
	baza++;
    fadeToBlackBy(leds, NUM_LEDS, 8);

	for ( uint8_t i = 1; i < 9; i++)	{
		color = 255 * i / 8;
		leds[beatsin8( 10 + i, 0, NUM_LEDS - 1, 0, color)] = ledGCfP( baza + color);
	}	

    FastLED.show();
}



/*
 * Gradient run base function
   far01, 
  yo.AUX100 - длина полоски
  yo.AUX255 - скорость движения палитры
 */
void animaWave11p1(){ var00 = 1; far01 = 50.0;}
void animaWave11p2(){ var00 = 2; far01 = 50.0;}
void animaWave11p3(){ var00 = 3; far01 = 50.0;}

void animaWave11() {
	uint16_t nc = millis() * yo.AUX255 >> 16;

	uint16_t counter = millis() * ( yo.currentSpeed << 1);
	uint16_t pp = counter * NUM_LEDS >> 16;
		
	int p1 = pp-NUM_LEDS;
	int p2 = pp+NUM_LEDS;

	for(uint16_t i = 0; i < NUM_LEDS; i++)	{
		far00 = MIN( abs(pp-i), MIN( abs(p1-i), abs(p2-i)));
		far00 = (yo.AUX100 > far00) ? far00/yo.AUX100 * 200 : 200;

		if ( var00 == 1){ var01 = nc;}
		else if ( var00 == 2){ var01 = i + nc;}
		else { var01 = i;}
		
		leds[i] = ledBlend( ledGCfP( var01), yo.c1, far00); // val
		// leds[i] = blend( ledGCfP( var01), yo.c1, val); // val
		// leds[i] = blend( yo.c1, ledGCfP( var01), val); // val
	}

	FastLED.show();
}





/*
 * Android loading circle
 */
void animaWave12() {
	baza++;
	for(uint16_t i = 0; i < NUM_LEDS; i++) { leds[i] = ledGCfP( i); }

	if ( var01 > 40) { 				var00 = 1;}						// убываем
	else{	if (var01 < 2) var00 = 0;}								// растем

	uint16_t a = var02;  	// точка отрисовки

	if (var00 == 0)  {
		if ( baza %3 == 1) {a++;}
		else {var01++;}
	} else  {
		a++;
		if ( baza %3 != 1) var01--;
	}

	if (a >= NUM_LEDS) a = 0; 		// переход в начало

	if (a + var01 < NUM_LEDS)  {
		for(int i = a; i < a+var01; i++) { 				 leds[i] = blend( yo.c1, leds[i], var01);}
	} else {
		for(int i = a; i < NUM_LEDS; i++) {				 leds[i] = blend( yo.c1, leds[i], var01);}
		for(int i = 0; i < var01 - (NUM_LEDS -a); i++) { leds[i] = blend( yo.c1, leds[i], var01);}
	}
	var02 = a;
	
	FastLED.show();
	delay( yo.currentSpeed * 2);
}






// the original levels for the leds (mix of yellow and red) that we define in setup()
unsigned int r[NUM_LEDS], g[NUM_LEDS], b[NUM_LEDS];
// the new levels we randomized
unsigned int rx[NUM_LEDS], gx[NUM_LEDS], bx[NUM_LEDS];
// the levels to approach the new levels by tweaning (these we use to set the neopixels)
double rz[NUM_LEDS], gz[NUM_LEDS], bz[NUM_LEDS];
// the diff to the new levels to twean to them in 10 steps
double dr[NUM_LEDS], dg[NUM_LEDS], db[NUM_LEDS];

int count = 0;

void animaWave13pre() {
	for (int i=0; i<NUM_LEDS; i++) {
		if (i%3==0) {
			r[i] = 70;
			g[i] = 0;
			b[i] = 0;
		}
		if (i%3==1) {
			r[i] = 60;
			g[i] = 30;
			b[i] = 0;
		}
		if (i%3==2) {
			r[i] = 100;
			g[i] = 70;
			b[i] = 0;
		}
		
		// r[i] = ledGCfP( i).r;
		// g[i] = ledGCfP( i).g;
		// b[i] = ledGCfP( i).b;
	}        
}

void animaWave13() {
// twean to the new values all the time
  for (int i=0; i<NUM_LEDS; i++) {
    rz[i] += dr[i];
    gz[i] += dg[i];
    bz[i] += db[i];

    // to guard from overflow or accidental unwanted flickering
    if (rz[i]<0) rz[i] = 0;
    if (rz[i]>255) rz[i] = 255;
    if (gz[i]<0) gz[i] = 0;
    if (gz[i]>255) gz[i] = 255;
    if (bz[i]<0) bz[i] = 0;
    if (bz[i]>255) bz[i] = 255;
  }

  count++;
  if (count>9) {   // we set new levels now after 10 iterations
    count = 0;

	for ( int ind=0; ind < NUM_LEDS / 12; ind++){
		// set new levels based on a factor, and this in those 3 'groups' of leds
    	for (int j=0; j<3; j++) {
      		float z = 10.0/random(4, 11);   // min is inclusive, max is exclusive (giving range from 0.4 to 1.0)
      		for (int i=0; i<4; i++) {

        		int idx = (( ind * 12) + ( j * 4) + i);
        	
				rx[idx] = (int) (r[idx] * z);
        		gx[idx] = (int) (g[idx] * z);
        		bx[idx] = (int) (b[idx] * z);
      		}
    	}
	}    

    // calculate the diff values (1/10th step)
    for (int i=0; i<NUM_LEDS; i++) {
      dr[i] = (rx[i] - rz[i])/10;
      dg[i] = (gx[i] - gz[i])/10;
      db[i] = (bx[i] - bz[i])/10;
    }
  }

  // update the leds
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB( (int)rz[i], (int)gz[i], (int)bz[i]);
	// strip.setPixelColor(i, strip.Color((int)rz[i], (int)gz[i], (int)bz[i], 255) );
  }
  FastLED.show();

//   delay(10);    // run our loop at approx 100Hz; so new LED levels reach every ~100 ms (~10Hz)
}



/* 
	Моргалочка 

	aux010 - color change speed	
	LEDS_VALUE, aux100 - blink speed
	aux255 - count leds
	LEDS_STATUS - timeshift for beatsin8
	
	var00 - aux010 keeper
	var01 - leds light count
	var02 - aux100 keeper
	color - colorID
	baza  - current activity ID

	1 - left wave
	2 - beatsin with random tshift
	3 - right wave
	4 - noise
*/
uint8_t status = 0;

void animaWave14(){

	far00 += 0.003 * yo.AUX010;
	color = far00;

	EVERY_N_SECONDS( 45) {

		for ( uint8_t i = 0; i < 70; i++){
			FastLED.setBrightness( qsub8( yo.currentBrightness, i * 3));
			delay( 4);
			FastLED.show();
		}			

		status = 1;
		baza += 1;
		// baza = random8( 1, 4);
	}

	if ( status > 0){
		if ( status < yo.currentBrightness){
			FastLED.setBrightness( status++);
		}
		else{
			status = 0;
		}
	}	

	// fadeToBlackBy(leds, NUM_LEDS, 8); 

	if ( var00 != yo.AUX255 || var02 != yo.AUX100){
		var00 = yo.AUX255;
		var02 = yo.AUX100;
		var01 = NUM_LEDS / yo.AUX255 + 1;

		for ( int i = 0; i < var01; i++) {
			LEDS_STATUS[i] = random8();
			LEDS_VALUE[i] = yo.AUX100 + random8( 5);
		}

		fill_solid( leds, NUM_LEDS, CRGB::Black);		
	}
	else{
		switch ( baza){
		case 1:
			for ( int i = 0; i < var01; i++) {	
				leds[i * yo.AUX255] = ledGCfP( color, false, beatsin8( yo.AUX100, 0, 255, 0, ( 255 * i) / var01)); 
			}
			break;
		
		case 2:
			for ( int i = 0; i < var01; i++) {	
				leds[i * yo.AUX255] = ledGCfP( color, false, beatsin8( LEDS_VALUE[i], 0, 255, 0, LEDS_STATUS[i])); 
			}
			break;

		case 3:
			for ( int i = 0; i < var01; i++) {	
				leds[i * yo.AUX255] = ledGCfP( color, false, beatsin8( yo.AUX100, 0, 255, 0, 255 - ( 255 * i) / var01)); 
			}
			break;

		case 4:
			for ( int i = 0; i < var01; i++) {	

				uint8_t noise = inoise8( i * 100, millis() / 3);
				noise = constrain( noise, 65, 200);
				noise = map( noise, 65, 200, 0, 255);

				leds[i * yo.AUX255] = ledGCfP( color, false, noise); 
			}
			break;

		default:
			baza = 1;
			break;
		}
    }

  	// uint8_t pos = inoise8( color * 10, millis() / 5); // * 100);
  	// // pos = constrain(pos, 11000, 55000);
  	// pos = map(pos, 30, 225, 0, NUM_LEDS - 1);  	
	// leds[pos] = CRGB( 60, 0, 0);

	FastLED.show();
}