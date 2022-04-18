#define MAX_POWER 50000
#include "palettes.h"

CRGB leds[NUM_LEDS];            // Массив ленты
// CHSV *yoPal; 			    	// Активная поллитра из массива поллитр: myPal
uint8_t LEDS_HUE[NUM_LEDS];     // Массив для хранения ХУЕв цветов диодов (0-255)   
uint8_t LEDS_FEDOR[NUM_LEDS];   // Массив для хранения Яркости диодов (0-255)


/* Настраиваем и инициализируем FastLED ленту, кастомную палитру и уходим в черное...*/
void ledsStartUP(){
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); 
	fill_solid( leds, NUM_LEDS, CRGB::Black); 	
	// ledFadeOUT();
	FastLED.show();
}

/* Забираем цвет colorID из указанной colorPalette палитры.
@param colorPalette цветовая паллитка, если не указано - текущая, из myPal[ind].palette или имя
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true) или брать как есть (false) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к каждому каналу ( 0-255) типа сатурации, но нет...
@param blenType размытие переходов между цветами ( 0-1) */
CRGB ledGCfP( CRGBPalette16 colorPalette, uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, TBlendType blenType = LINEARBLEND){
	if ( isMapped){ colorID = ( colorID * 255) / ( NUM_LEDS -1); }	
	CRGB color = ColorFromPalette( colorPalette, colorID, brightness, blenType); 
	if ( addToColor || yo.antiSaturn){ color.addToRGB( addToColor + yo.antiSaturn);}
	return color;
}

/* Забираем цвет colorID из текущей targetPalette палитры.
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true) или брать как есть (false) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к каждому каналу ( 0-255) типа сатурации, но нет...
@param blenType размытие переходов между цветами ( 0-1) */
CRGB ledGCfP( uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, TBlendType blenType = LINEARBLEND){
	CRGB color = ledGCfP( activePollitre, colorID, isMapped, brightness, addToColor, LINEARBLEND);
	return color;
}

void powerON(){  FastLED.setMaxPowerInMilliWatts(MAX_POWER); 	FastLED.show(); }
void powerOFF(){ FastLED.setMaxPowerInMilliWatts(0); 			FastLED.show(); }

/* Включаем / выключаем питание (!!!) ленты, 
тормозим анимацию и переходим ждущий режим (delay)  */
void powerONOFF(){
	if ( yo.ONOFF == true){ powerOFF(); } 
	else {					powerON(); 	}

	yo.ONOFF = !yo.ONOFF;
	Serial.printf( "State: %d\n", yo.ONOFF);  	
}

/* Сброс ленты в черное и обнуление LEDS_массивов диодов */
void ledOFF( int resValue){ 
	for ( int pos = 0; pos < NUM_LEDS; pos++){
		LEDS_HUE[pos] = LEDS_FEDOR[pos] = 0;
	}
	yo.lastPressed = resValue;
	fill_solid( leds, NUM_LEDS, CRGB::Black); 	
	// FastLED.show();
}

/* Включаем беленькую */
void ledUPWhite(){	
  	if ( yo.ONOFF == true){
	  	fill_solid( leds, NUM_LEDS, CRGB::White); 	
		FastLED.show();
	}
	#ifdef DEBUG_ENABLE
		Serial.printf( "\nStatic RGB = (%d.%d.%d)\n", leds[10].r, leds[10].g, leds[10].b);
	#endif
}

/* Включаем тестовое, сейчас = палитра */
void ledUP(){  
	if ( yo.ONOFF == true){
		for ( int pos = 0; pos < NUM_LEDS; pos++){ 
			// leds[pos] = pollitrR[pos*255/NUM_LEDS]; 
			// leds[pos] = ColorFromPalette( targetPalette, colorID, 255, LINEARBLEND);
			leds[pos] = ledGCfP( pos);

			#ifdef DEBUG_ENABLE
				Serial.printf( "pos [%d], (%d.%d.%d)\n", pos, leds[pos].r, leds[pos].g, leds[pos].b);
			#endif
		}	
		// for ( int pos = 0; pos < NUM_COLORS; pos++){ leds[pos] = CHSV( yoPal[pos]); }	
		FastLED.show();
	}
}

/* Моргаем кратенько черненьким, при достижении края параметров */
void ledBlink(){ powerOFF(); delay(3); powerON(); }

/* Затухаем лентой вниз до нулевого состояния 10-го диода */
void ledFadeOUT(){
	for( int i = 0; i < 20; i++){
		fadeToBlackBy(leds, NUM_LEDS, 2);
		FastLED.show();
		Serial.printf( "FadeOUT: (%d.%d.%d)", leds[10].r,  leds[10].g, leds[10].b );
		delay(10);
	}
}

void setSpeed( int value){ yo.currentSpeed = value; }

void setSaturation( int value){ 
	yo.currentSaturn  = value; 
	yo.antiSaturn = MAX_SATURATIOIN - yo.currentSaturn;
}

void setTemperature( int value){ 
	yo.currentTemp = value; 
	FastLED.setTemperature( temperList[yo.currentTemp] );
	FastLED.show();
	Serial.printf( "Temperature: #%d (%x)\n", yo.currentTemp, temperList[yo.currentTemp]);
}


void setBrightness( int value){ 
	yo.currentBrightness = value; 
	FastLED.setBrightness( yo.currentBrightness);
  	FastLED.show();
}

/* Меняем общуу срость анимации (0-...)
* @param delta +/- yo.currentSpeed.*/
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
* @param delta +/- yo.currentTemp.*/
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
* @param delta +/- yo.currentBrightness.*/
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
* @param delta +/- yo.currentSaturn.*/
void changeSaturation( int delta){
	yo.currentSaturn += delta;	
	if ( yo.currentSaturn > MAX_SATURATIOIN){ 
		yo.currentSaturn = MAX_SATURATIOIN; 
		ledBlink();
	} else if ( yo.currentSaturn < 0){ 
		yo.currentSaturn = 0;
		ledBlink();
	}
	yo.antiSaturn = MAX_SATURATIOIN - yo.currentSaturn;
	Serial.printf( "Saturation: %d ( anti: %d)\n", yo.currentSaturn, yo.antiSaturn);
}

/* Сброс параметров ленты в дефолтное состояние */
void ledReset(){
	changeBrightness(255); 
	changeSpeed( -90); 
	changeTemperature( TEMP_IND_MAX); 
	changeSaturation( 255);
}

