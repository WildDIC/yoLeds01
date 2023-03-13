// #include "waveClass.h"


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
void aFire2012(){
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
	// FastLED.show(); // display this frame
	delay( yo.currentSpeed * 2);
}


