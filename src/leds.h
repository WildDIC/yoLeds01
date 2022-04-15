#define MAX_POWER 50000

CRGB leds[NUM_LEDS];            // Массив ленты
CHSV *yoPal; 			    	// Активная поллитра из массива поллитр: myPal
uint8_t LEDS_HUE[NUM_LEDS];     // Массив для хранения ХУЕв цветов диодов (0-255)   
uint8_t LEDS_FEDOR[NUM_LEDS];   // Массив для хранения Яркости диодов (0-255)

struct pollitra{
    String name;				// Имя палитры
	CHSV pollitra[NUM_COLORS];	// Массив поллитровых собсна цветов
};

pollitra myPal[NUM_POLLITR];

/* Настраиваем и инициализируем FastLED ленту, кастомную палитру и уходим в черное...*/
void ledsStartUP(){
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); 
	fill_solid( leds, NUM_LEDS, CRGB::Black); 	
	// ledFadeOUT();
	FastLED.show();

	byte ind = 0; // -1? Просто, что было красиво в ++
	myPal[++ind] = { "*solid white"};	 fill_solid(    myPal[ind].pollitra, NUM_COLORS, CHSV( 0, 0, 255));
	myPal[++ind] = { "random 1 color"};	 
	myPal[++ind] = { "random 2 colors"}; 
	myPal[++ind] = { "random 3 colors"}; 
	myPal[++ind] = { "random 4 colors"}; 
	myPal[++ind] = { "full raindow"};	 fill_gradient( myPal[ind].pollitra, NUM_COLORS, CHSV( 0, 255, 255), CHSV( 255, 255, 255), FORWARD_HUES );
	myPal[++ind] = { "orange fire"};	 fill_gradient( myPal[ind].pollitra, NUM_COLORS, CHSV( 7, 255, 255),  CHSV( 35, 255, 255), FORWARD_HUES );
	myPal[++ind] = { "green to blue"};	 fill_gradient( myPal[ind].pollitra, NUM_COLORS, CHSV( 75, 255, 255), CHSV( 160, 255, 255), FORWARD_HUES );
	

	// uint8_t paletteIndex = i;
  	// if (mapping && SEGLEN > 1) paletteIndex = (i*255)/(SEGLEN -1);
  	// if (!wrap) paletteIndex = scale8(paletteIndex, 240); //cut off blend at palette "end"
  	// CRGB fastled_col;
	// fastled_col = ColorFromPalette(currentPalette, paletteIndex, pbri, (paletteBlend == 3)? NOBLEND:LINEARBLEND);
}

/* Меням активную палитру и записываем ее в текующую активность ленты
@param byte pollitraID = Номер паллитры из myPal */
void ledSetPollitre( byte pollitraID){
	if ( 	  myPal[pollitraID].name == "random 1 color"){ 	fill_solid(    myPal[pollitraID].pollitra, NUM_COLORS, CHSV(random8(), 255, random8(128, 255)));}
	else if ( myPal[pollitraID].name == "random 2 colors"){ fill_gradient( myPal[pollitraID].pollitra, NUM_COLORS, CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));}
	else if ( myPal[pollitraID].name == "random 3 colors"){ fill_gradient( myPal[pollitraID].pollitra, NUM_COLORS, CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));}
	else if ( myPal[pollitraID].name == "random 4 colors"){ fill_gradient( myPal[pollitraID].pollitra, NUM_COLORS, CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), 	CHSV(random8(), 255, random8(128, 255)));}

	yoPal = myPal[pollitraID].pollitra;
	mButtons[yo.lastPressed].pollCurrent = pollitraID;
	// Serial.printf( "Поллитра ID: %d ( %s) for %d ( %s)\n", pollitraID, myPal[pollitraID].name, yo.lastPressed, mButtons[yo.lastPressed].name);
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
}

/* Включаем тестовое, сейчас = палитра */
void ledUP(){  
	if ( yo.ONOFF == true){
		for ( int pos = 0; pos < NUM_LEDS; pos++){ leds[pos] = CHSV( yoPal[pos*255/NUM_LEDS]); }	
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
	yo.antiSaturn = 255 - yo.currentSaturn;
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

/* Сброс параметров ленты в дефолтное состояние */
void ledReset(){
	changeBrightness(255); 
	changeSpeed( -90); 
	changeTemperature( TEMP_IND_MAX); 
	changeSaturation( 255);
}

