#include <FastLED.h>
#include "header.h"

CRGB leds[NUM_LEDS];
CHSV yoPalette[NUM_COLORS];
uint8_t LEDS_HUE[NUM_LEDS];
uint8_t LEDS_FEDOR[NUM_LEDS];

void powerONOFF(){
	if ( yo.ONOFF) {
		yo.ONOFF = false;
		FastLED.setMaxPowerInMilliWatts(0);
		FastLED.show();
	} else {
		yo.ONOFF = true;
		FastLED.setMaxPowerInMilliWatts(50000);
		FastLED.show();
	}
	Serial.printf( "State: %d\n", yo.ONOFF);  
}

void ledOFF(){ 
	fill_solid( leds, NUM_LEDS, CRGB::Black); 
	for ( int pos = 0; pos < NUM_LEDS; pos++){
		LEDS_HUE[pos] = LEDS_FEDOR[pos] = 0;
	}
	FastLED.show(); }

void ledUPWhite(){
  	yo.ONOFF = false;
  	for( int i = 0; i < NUM_LEDS; ++i) {
      	leds[i] = CRGB( 255,255,255); 
    }
  	powerONOFF();
}

void ledUP(){  
	// fill_gradient_RGB( leds, NUM_LEDS, CRGB::Red, CRGB::Green); 	
	for ( int pos = 0; pos < NUM_COLORS; pos++){ leds[pos] = CHSV( yoPalette[pos]); }
	FastLED.show();
}

void ledBlink(){
	FastLED.setMaxPowerInMilliWatts(0);
	FastLED.show();
	delay(2);
	FastLED.setMaxPowerInMilliWatts(50000);
	FastLED.show();
}

void changeSpeed( int delta){
	yo.currentSpeed += delta;
	if ( yo.currentSpeed > 100){ 
		yo.currentSpeed = 100; 
		ledBlink();
	} else if ( yo.currentSpeed < 0){ 
		yo.currentSpeed = 0;
		ledBlink();
	}
	Serial.printf( "Speed: %d\n", yo.currentSpeed);
}

void changeTemperature( int delta){
	yo.currentTemp += delta;
	if ( yo.currentTemp > TEMP_IND_MAX){ 
		yo.currentTemp = TEMP_IND_MAX; 
		temperList[yo.currentTemp] = 0xFFFFFF;
		ledBlink();
	} else if ( yo.currentTemp < 0){ 
		yo.currentTemp = 0; 
		ledBlink();
	}  
	
	FastLED.setTemperature( temperList[yo.currentTemp] );
	FastLED.show();
	Serial.printf( "Temperature: #%d (%x)\n", yo.currentTemp, temperList[yo.currentTemp]);
}

void changeBrightness( int delta){  
  	yo.currentBrightness = FastLED.getBrightness() + delta;
  	if ( yo.currentBrightness > 255){
    	yo.currentBrightness = 255;
		ledBlink();
  	} else if ( yo.currentBrightness <= 5){
	    yo.currentBrightness = 5;
		ledBlink();
  	}  
  	Serial.printf( "Brightness: %d. \n", yo.currentBrightness);  
  	FastLED.setBrightness( yo.currentBrightness);
  	FastLED.show();
}

void changeSaturation( int delta){
	yo.currentSaturn += delta;	
	if ( yo.currentSaturn > 255){ 
		yo.currentSaturn = 255; 
		ledBlink();
	} else if ( yo.currentSaturn < 0){ 
		yo.currentSaturn = 0;
		ledBlink();
	}
	yo.antiSaturn = 255 - yo.currentSaturn;
	Serial.printf( "Saturation: %d ( anti: %d)\n", yo.currentSaturn, yo.antiSaturn);
}
