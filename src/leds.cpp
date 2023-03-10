#include "config.h"
#include "palettes.h"

#define MAX_POWER 50000
#define REVERS_NUM_LEDS 255 / ( NUM_LEDS - 1)

CRGB leds[NUM_LEDS];            // Массив ленты
uint8_t LEDS_HUE[NUM_LEDS];     // Массив для хранения ХУЕв цветов диодов (0-255)   
uint8_t LEDS_STATUS[NUM_LEDS];     // Массив для хранения ХУЕв цветов диодов (0-255)   
uint8_t LEDS_VALUE[NUM_LEDS];     // Массив для хранения ХУЕв цветов диодов (0-255)   
uint8_t LEDS_FEDOR[NUM_LEDS];   // Массив для хранения Яркости диодов (0-255)

/* Настраиваем и инициализируем FastLED ленту, кастомную палитру и уходим в черное...*/
void ledsStartUP()
{
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); 
	fill_solid( leds, NUM_LEDS, CRGB::Black); 	
	// ledFadeOUT();
	FastLED.show();
}

/* Забираем цвет colorID из указанной colorPalette палитры.
@param colorPalette цветовая паллитка, если не указано - текущая, из myPal[ind].palette или имя
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true = 0-255 -> 0-NUM_LEDS) или брать как есть (false) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к каждому каналу ( 0-255) типа сатурации, но нет...
@param candle свечная мигалчка ( 0-1) значение = yo.AUX355. */
CRGB ledGCfP( CRGBPalette16 colorPalette, uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false)
{
	if ( isMapped == true)				{ colorID *= REVERS_NUM_LEDS; }	

	CRGB color = ColorFromPalette( colorPalette, colorID, brightness, NOBLEND); 

	if ( addToColor || yo.antiSaturn)	{ color.addToRGB( addToColor + yo.antiSaturn);}
	if ( candle && yo.iscandle) 		{ color.nscale8( yo.candle); }
	return color;
}

/* Забираем цвет colorID из текущей activePollitre палитры.
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true = 0-255 -> 0-NUM_LEDS) или брать как есть (false) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к каждому каналу ( 0-255) типа сатурации, но нет...
@param candle свечная мигалчка ( 0-1) значение = yo.AUX355. */
CRGB ledGCfP( uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, bool candle = false)
{
	CRGB color = ledGCfP( activePollitre, colorID, isMapped, brightness, addToColor, candle);
	return color;
}

void powerON()
{  
	FastLED.setBrightness( yo.currentBrightness);
	FastLED.delay( 5);
	FastLED.show(); 
}

void powerOFF()
{ 
	FastLED.setBrightness( 0);
	FastLED.delay( 5);
	FastLED.show(); 
}


/* Включаем / выключаем питание (!!!) ленты, 
тормозим анимацию и переходим ждущий режим (delay)  */
void powerONOFF()
{
	if ( yo.ONOFF){ powerOFF(); } 
	else {			powerON(); 	}

	yo.ONOFF = !yo.ONOFF;
	Serial.printf( "State: %d\n", yo.ONOFF);  	
}


/* Сброс ленты в черное и обнуление LEDS_массивов диодов */
void ledOFF()
{ 
	for ( int pos = 0; pos < NUM_LEDS; pos++){
		LEDS_HUE[pos] = LEDS_FEDOR[pos] = 0;
	}
	// for( uint8_t i = 0; i < 50; i++){
	// 	fadeToBlackBy( leds, NUM_LEDS, 2);
	// 	FastLED.show();
	// 	delay( 50);
	// }

	fill_solid( leds, NUM_LEDS, CRGB::Black); 	
	FastLED.delay( 5);
	FastLED.show();
}


/* Включаем беленькую */
void ledUPWhite()
{	
  	if ( yo.ONOFF)
	{
	  	fill_solid( leds, NUM_LEDS, CRGB::White); 	
		FastLED.delay( 5);
		FastLED.show();
	}
	#ifdef DEBUG_ENABLE
		Serial.printf( "\nStatic RGB = (%d.%d.%d)\n", leds[10].r, leds[10].g, leds[10].b);
	#endif
}


/* Включаем тестовое, сейчас = палитра */
void ledUP()
{  
	if ( yo.ONOFF)
	{
		for ( int pos = 0; pos < NUM_LEDS; pos++)
		{ 
			// leds[pos] = pollitrR[pos*255/NUM_LEDS]; 
			// leds[pos] = ColorFromPalette( targetPalette, colorID, 255, LINEARBLEND);
			// leds[pos] = ledGCfP( pos);
			leds[pos] = ledGCfP( pos, true);

			#ifdef DEBUG_ENABLE
				Serial.printf( "pos [%d], (%d.%d.%d)\n", pos, leds[pos].r, leds[pos].g, leds[pos].b);
			#endif
		}	
		// for ( int pos = 0; pos < NUM_COLORS; pos++){ leds[pos] = CHSV( yoPal[pos]); }	
		FastLED.show();
		FastLED.delay( 5);
	}
}


/* Моргаем кратенько черненьким, при достижении края параметров */
void ledBlink(){ powerOFF(); delay(3); powerON(); }


/* Затухаем лентой вниз до нулевого состояния 10-го диода */
void ledFadeOUT()
{
	for( int i = 0; i < 20; i++)
	{
		fadeToBlackBy(leds, NUM_LEDS, 2);
		FastLED.show();
		Serial.printf( "FadeOUT: (%d.%d.%d)", leds[10].r,  leds[10].g, leds[10].b );
		delay(10);
	}
}


void setSpeed(  int value){ yo.currentSpeed = value; if ( yo.loadOutside){ mWaves[yo.lastPressed].speed  = value;}}
void setAUX010( int value){ yo.AUX010 = value; 		 if ( yo.loadOutside){ mWaves[yo.lastPressed].aux010 = value;}}
void setAUX100( int value){ yo.AUX100 = value; 		 if ( yo.loadOutside){ mWaves[yo.lastPressed].aux100 = value;}}
void setAUX255( int value){ yo.AUX255 = value; 		 if ( yo.loadOutside){ mWaves[yo.lastPressed].aux255 = value;}}
void setAUX355( int value){ yo.AUX355 = value; 		 if ( yo.loadOutside){ mWaves[yo.lastPressed].aux355 = value;}}
void setAUX455( int value){ yo.AUX455 = value; 		 if ( yo.loadOutside){ mWaves[yo.lastPressed].aux455 = value;}}


/*@param force не пишем, так как закинули цвет в мапу с веб-сервера уже*/
void setColors(	CRGB c1, CRGB c2, CRGB c3)
{
	yo.c1 = c1;
	yo.c2 = c2;
	yo.c3 = c3;

	if ( yo.loadOutside)
	{
		mWaves[yo.lastPressed].c1 = c1;
		mWaves[yo.lastPressed].c2 = c2;
		mWaves[yo.lastPressed].c3 = c3;
	}
}


void setSaturation( int value)
{ 
	if ( value < 0 ){ 
		value = 100;
	}
	else if (value > 100){
		value = 100;
	}

	yo.currentSaturn  = value; 
	yo.antiSaturn = MAX_SATURATIOIN - yo.currentSaturn;
	
	if ( yo.loadOutside){ mWaves[yo.lastPressed].saturn = value; }	
}


void setTemperature( int value)
{ 
	if ( value < 0 ){ 
		value = TEMP_IND_MAX;
	}
	else if (value > TEMP_IND_MAX){
		value = TEMP_IND_MAX;
	}
	
	yo.currentTemp = value; 
	
	if ( yo.loadOutside){ mWaves[yo.lastPressed].temp = value;}
	
	FastLED.setTemperature( temperList[yo.currentTemp] );	
	FastLED.show();
	// Serial.printf( "Temperature: #%d (%x)\n", yo.currentTemp, temperList[yo.currentTemp]);
}


void setBrightness( int value)
{ 
	if ( value < 5 ){ 
		value = 5;
	}
	yo.currentBrightness = value; 
	// if ( yo.loadOutside){
		// mWaves[yo.lastPressed].bright = value;
	// }
	FastLED.setBrightness( yo.currentBrightness);
  	FastLED.show();
}


/* Меняем общуу срость анимации (0-...)
* @param delta +/- yo.currentSpeed.*/
void changeSpeed( int delta)
{
	yo.currentSpeed += delta;
	if ( yo.currentSpeed > 50)
	{ 
		yo.currentSpeed = 50; 
		ledBlink();
	} else if ( yo.currentSpeed < 2)
	{ 
		yo.currentSpeed = 2;
		ledBlink();
	}
	Serial.printf( "Speed: %d\n", yo.currentSpeed);
}


/* Меняем общуу температуру цвета ленты (0-255)
* @param delta +/- yo.currentTemp.*/
void changeTemperature( int delta)
{
	yo.currentTemp += delta;
	if ( yo.currentTemp > TEMP_IND_MAX)
	{ 
		yo.currentTemp = TEMP_IND_MAX; 
		temperList[yo.currentTemp] = 0xFFFFFF;
		ledBlink();
	} 
	else if ( yo.currentTemp < 0)
	{ 
		yo.currentTemp = 0; 
		ledBlink();
	}  
	
	FastLED.setTemperature( temperList[yo.currentTemp] );
	FastLED.show();
	Serial.printf( "Temperature: #%d (%x)\n", yo.currentTemp, temperList[yo.currentTemp]);
}


/* Меняем общуу яркость ленты (0-255)
* @param delta +/- yo.currentBrightness.*/
void changeBrightness( int delta)
{  
  	yo.currentBrightness = FastLED.getBrightness() + delta;
  	if ( yo.currentBrightness > 255)
	{
    	yo.currentBrightness = 255;
		ledBlink();
  	}
	else if ( yo.currentBrightness <= 5)
	{
	    yo.currentBrightness = 5;
		ledBlink();
  	}  
  	Serial.printf( "Brightness: %d. \n", yo.currentBrightness);  	
  	FastLED.setBrightness( yo.currentBrightness);
  	FastLED.show();
}


/* Меняем общуу сатурацию ленты (0-255)
* @param delta +/- yo.currentSaturn.*/
void changeSaturation( int delta)
{
	yo.currentSaturn += delta;	
	if ( yo.currentSaturn > MAX_SATURATIOIN)
	{ 
		yo.currentSaturn = MAX_SATURATIOIN; 
		ledBlink();
	} 
	else if ( yo.currentSaturn < 0)
	{ 
		yo.currentSaturn = 0;
		ledBlink();
	}
	yo.antiSaturn = MAX_SATURATIOIN - yo.currentSaturn;
	Serial.printf( "Saturation: %d ( anti: %d)\n", yo.currentSaturn, yo.antiSaturn);
}


/* Сброс параметров ленты в дефолтное состояние */
void ledReset()
{
	setBrightness(128); 
	// changeSpeed( -90); 
	setSpeed( 5);
	changeTemperature( TEMP_IND_MAX); 
	changeSaturation( 100);
}


CRGB ledBlend( CRGB c1, CRGB c2, uint16_t blend) 
{
  if( blend == 0)  return c1;
  if(blend == 255) return c2;

  uint32_t r3 = (( c2.r * blend) + ( c1.r * ( 255 - blend))) >> 8;
  uint32_t g3 = (( c2.g * blend) + ( c1.g * ( 255 - blend))) >> 8;
  uint32_t b3 = (( c2.b * blend) + ( c1.b * ( 255 - blend))) >> 8;

  return CRGB(r3, g3, b3);
}


/*
returns 0-255 for a time period with x8'scale' and x'speed':
speed:	
	1 = 65.363ms	11 = 5.936ms
	2 = 32.642ms	12 = 5.447ms
	3 = 21.762ms	13 = 5.026ms
	4 = 16.324ms	14 = 4.665ms
	5 = 13.060ms	15 = 4.356ms
	6 = 10.882ms	16 = 4.082ms
	7 = 9.327ms		17 = 3.845ms
	8 = 8.163ms		18 = 3.631ms
	9 = 7.257ms		19 = 3.440ms
	10 = 6.530ms	20 = 3.267ms
scale:	
	..., 7 = x0.5, 8 = x1, 9 = x2, ...
*/
uint8_t ledBeat8( uint8_t speed = 16, uint8_t scale = 8)
{
	return ( millis() * speed) >> scale;
}


/*
returns 0-255 for a time period with the given 'scale':
scale:
	8 = 65.363ms
	7 = 32.663ms
	6 = 16.350ms
	5 = 8.178ms
	4 = 4.080ms
	3 = 2.048ms
	2 = 1.024ms
	1 = 512/1.024
*/
uint8_t ledBeat( uint8_t scale = 4)
{
	return millis() >> scale;
}

/*
	In/Out circle:
		0-128-255 = 0-255-0
*/
uint8_t ledCir8(uint8_t in)
{
    if( in & 0x80) 
	{
        in = 255 - in;
    }
    uint8_t out = in << 1;
    return out;
}


uint8_t ledCircle( accum88 beats_per_minute, uint8_t timeShift = 0, uint32_t timeScale = 8)
{
    uint8_t beat 	= ledBeat8( beats_per_minute, timeScale);
    uint8_t result 	= ledCir8( beat + timeShift);
    return result;
}


uint8_t ledCircle8( accum88 beats_per_minute, uint8_t highest = 255, uint8_t timeShift = 0, uint32_t timeScale = 8)
{
    uint8_t beat  	= ledCircle( beats_per_minute, timeShift, timeScale);
    uint8_t result 	= scale8( beat, highest);
    return result;
}


uint8_t ledCircle88( accum88 beats_per_minute, uint8_t lowest = 0, uint8_t highest = 255, uint8_t timeShift = 0, uint32_t timeScale = 8)
{
	uint8_t beat 	=  ledCircle8( beats_per_minute, ( highest - lowest), timeShift, timeScale);
    uint8_t result 	= lowest + beat;
    return result;
}