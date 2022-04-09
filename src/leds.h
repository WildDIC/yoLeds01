#include <FastLED.h>
#include "header.h"

CRGB leds[NUM_LEDS];            // Массив ленты
CHSV yoPalette[NUM_COLORS];     // Кастомная палитра градиента двух цветов
uint8_t LEDS_HUE[NUM_LEDS];     // Массив для хранения ХУЕв цветов диодов (0-255)   
uint8_t LEDS_FEDOR[NUM_LEDS];   // Массив для хранения Яркости диодов (0-255)


/* Включаем / выключаем питание (!!!) ленты, 
тормозим анимацию и переходим ждущий режим (delay)  */
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

/* Сброс ленты в черное и обнуление LEDS_массивов диодов */
void ledOFF(){ 
	fill_solid( leds, NUM_LEDS, CRGB::Black); 
	for ( int pos = 0; pos < NUM_LEDS; pos++){
		LEDS_HUE[pos] = LEDS_FEDOR[pos] = 0;
	}
	FastLED.show(); }

/* Включаем беленькую */
void ledUPWhite(){
  	yo.ONOFF = false;
  	for( int i = 0; i < NUM_LEDS; ++i) {
      	leds[i] = CRGB( 255,255,255); 
    }
  	powerONOFF();
}

/* Включаем тестовое, сейчас = палитра */
void ledUP(){  
	// fill_gradient_RGB( leds, NUM_LEDS, CRGB::Red, CRGB::Green); 	
	for ( int pos = 0; pos < NUM_COLORS; pos++){ leds[pos] = CHSV( yoPalette[pos]); }
	FastLED.show();
}

/* Моргаем кратенько черненьким, при достижении края параметров */
void ledBlink(){
	FastLED.setMaxPowerInMilliWatts(0);
	FastLED.show();
	delay(2);
	FastLED.setMaxPowerInMilliWatts(50000);
	FastLED.show();
}

/* Меняем общуу срость анимации (0-...)
* @param delta +/- yo.currentSpeed.
*/
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

/* Меняем общуу температуру цвета ленты (0-255)
* @param delta +/- yo.currentTemp.
*/
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

/* Меняем общуу яркость ленты (0-255)
* @param delta +/- yo.currentBrightness.
*/
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

/* Меняем общуу сатурацию ленты (0-255)
* @param delta +/- yo.currentSaturn.
*/
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
