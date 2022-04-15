uint8_t baza = 0;     // изменение оттенка LED
int color = 0;


/* Бегущая радужная вэйв */
void animWave01(){
	fadeToBlackBy(leds, NUM_LEDS, 4);
	int pos = beatsin8(13, 0, NUM_LEDS - 1);
	leds[pos] += CHSV( yoPal[baza++].h, yo.currentSaturn, 255);
	FastLED.show();
	delay(yo.currentSpeed);
}

/* Костерок №01 */
void animWave02(){    
	leds[random8(NUM_LEDS)] = CHSV( yoPal[random8( 255)].h, yo.currentSaturn, random8( 200, 255)); 
	leds[random8(NUM_LEDS)].nscale8( random8(100));
	if ( random8() < 35){
		fadeToBlackBy(leds, NUM_LEDS, random8( 20));	
	}
    FastLED.show();
	delay(yo.currentSpeed / 2);
}

/* Моргающий градиент радуги = хуета */
void animWave03(){
	// for (int i = 0; i < NUM_LEDS; i++) {
    //   	leds[i].nscale8(250);
    // }
    for (int i = 0; i < NUM_LEDS; i++) {
    	leds[i] = CHSV( yoPal[baza++].h, yo.currentSaturn, 255);
      	FastLED.show();
    }
	delay(yo.currentSpeed);
}

/* 8 волн с разной скоротью и наложением цвета */
void animWave04(){
	fadeToBlackBy(leds, NUM_LEDS, 2);
    for (int i = 0; i < 8; i++) {
      	leds[beatsin8(i + 7, 0, NUM_LEDS - 1)] |= CHSV(  yoPal[baza+=16].h, yo.currentSaturn-50, 255);
      	// leds[beatsin8(i + 7, 0, NUM_LEDS - 1)] |= CHSV(baza+=16, yo.currentSaturn-50, 255);
    }
	FastLED.show();
    delay(yo.currentSpeed);
}

/* Ползущая радуга с проблесками беленьких диодов */
void animWave05(){
	// fill_rainbow( leds, NUM_LEDS, baza++, 7);
  	for (int i = 0; i < NUM_LEDS; i++) {
    	leds[i] = CHSV( yoPal[baza+=7].h, yo.currentSaturn, 255);
  	}
	if (random8() < 40) { 
		leds[ random8(NUM_LEDS) ] = CRGB::White; 
	}
	for ( int i = 0; i < NUM_LEDS; i++){ 
		leds[i].addToRGB(yo.antiSaturn);	
	}
  	FastLED.show();
  	delay(yo.currentSpeed + 10);
}

/* Вжух-вжух радуга из цента типа странной цветомузыки */
void animWave06(){
	uint8_t rand = random8( 1, TOP_INDEX);
    for (int i = 0; i < rand; i++ ) {
		leds[TOP_INDEX + i] = CHSV( yoPal[i*3].h, yo.currentSaturn, 255);
		leds[TOP_INDEX - i] = CHSV( yoPal[i*3].h, yo.currentSaturn, 255);
        delay( 100 / rand);
        FastLED.show();
	}
	for (int i = rand; i > 0; i-- ) {
		leds[TOP_INDEX + i] = CHSV(0, yo.currentSaturn, 0);
		leds[TOP_INDEX - i] = CHSV(0, yo.currentSaturn, 0);
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
	FastLED.delay(yo.currentSpeed / 5);
}

/* Костерок №02 */
void animWave08() {
	uint8_t foundNEW = 0;

    for (int pos = 0; pos < NUM_LEDS; pos++){	
        if ( LEDS_HUE[pos] > 1){
			LEDS_HUE[pos] -= 1;
            leds[pos] = CHSV( yoPal[LEDS_HUE[pos]*10].h, yo.currentSaturn, random8(220, 255));
            if ( LEDS_HUE[pos] <= 1){
                LEDS_FEDOR[pos] = 255;    
            }
			delay( 1);
        }
        if ( LEDS_FEDOR[pos] >= 10){
		    leds[pos] = CHSV( yoPal[LEDS_HUE[pos]*10].h, yo.currentSaturn, LEDS_FEDOR[pos] /= 1.1); 
        } 
    }	        
    for ( int pos01 = 0; pos01 < 10; pos01++){
        int pos = random8( NUM_LEDS);
        if ( LEDS_HUE[pos] <= 1 && LEDS_FEDOR[pos] <= 10) {
            LEDS_HUE[pos] = 25;
			if ( foundNEW += 1 > 3){
				break;
			}
        }
    }
    FastLED.show();
	// Serial.printf( "%d ( %d, %d, %d)- %d \n", leds[1], leds[1].r, leds[1].g, leds[1].b, LEDS_HUE[1]);
	delay(yo.currentSpeed);
}


//////////////////////////////////////////////////////////////////////////////////////////
//											WAVE09
//////////////////////////////////////////////////////////////////////////////////////////

void animWave09pre(){
	#define NUM_SEGMENTS 3
	#define SPEED_WAVE 13
	#define SAT_DIVINE 3

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

        leds[pos] 			 |= CHSV( yoPal[LEDS_HUE[ind]++].h, yo.currentSaturn / SAT_DIVINE, 200);
        leds[NUM_LEDS - pos] |= CHSV( yoPal[LEDS_HUE[ind]++].h, yo.currentSaturn / SAT_DIVINE, 200);		
    }
	leds[beatsin8( SPEED_WAVE, 0, NUM_LEDS - 1)] |= CHSV( baza << 1, yo.currentSaturn, 255);
     
    FastLED.show();        
  	delay( yo.currentSpeed * 2);
}


    // fadeToBlackBy(leds, NUM_LEDS, 8);
    // int pos01 = beatsin16(10, 0, NUM_LEDS - 1, 0, 0);
    // int pos02 = NUM_LEDS-pos01-1;
    // int pos03 = beatsin16(10, 11, NUM_LEDS - 12, 0);
    // int pos04 = NUM_LEDS-pos03-1;