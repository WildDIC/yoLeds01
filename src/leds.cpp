#include "config.h"
#include "palettes.h"
#include "leds.h"

#define MAX_POWER 50000
#define REVERS_NUM_LEDS 255 / ( NUM_LEDS - 1)

CRGB leds[NUM_LEDS];            // Массив ленты
Ledas led;

/* Настраиваем и инициализируем FastLED ленту, кастомную палитру и уходим в черное...*/
void Ledas::startUP()
{
	// FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); 
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
	// set_max_power_in_volts_and_milliamps(5.5, 550);               // FastLED Power management set at 5V, 500mA.

	fill_solid( leds, NUM_LEDS, CRGB::Black); 	
	// ledFadeOUT();
	FastLED.delay( 5);
	FastLED.show();
}

/* Забираем цвет colorID из указанной colorPalette палитры.
@param colorPalette цветовая паллитка, если не указано - текущая, из myPal[ind].palette или имя
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true = 0-255 -> 0-NUM_LEDS) или брать как есть (false) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к каждому каналу ( 0-255) типа сатурации, но нет...
@param candle свечная мигалчка ( 0-1) значение = yo.AUX355. */
CRGB Ledas::GCfP( const struct CRGBPalette16& colorPalette, uint8_t colorID, bool isMapped, uint8_t brightness, uint8_t addToColor, bool candle)
{
	if ( isMapped == true)				{ colorID *= REVERS_NUM_LEDS; }	

	CRGB color = ColorFromPalette( colorPalette, colorID, brightness, LINEARBLEND); 

	if ( addToColor || yo.antiSaturn)	{ color.addToRGB( addToColor + yo.antiSaturn);}
	if ( yo.iscandle) 					{ color.nscale8( yo.candle); }
	return color;
}

/* Забираем цвет colorID из текущей activePollitre палитры.
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true = 0-255 -> 0-NUM_LEDS) или брать как есть (false) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к каждому каналу ( 0-255) типа сатурации, но нет...
@param candle свечная мигалчка ( 0-1) значение = yo.AUX355. */
CRGB Ledas::GCfP( uint8_t colorID, bool isMapped, uint8_t brightness, uint8_t addToColor, bool candle)
{
	CRGB color = this->GCfP( activePollitre, colorID, isMapped, brightness, addToColor, candle);
	return color;
}

/* Забираем цвет colorID из указанной colorPalette палитры.
@param colorPalette цветовая паллитка, если не указано - текущая, из myPal[ind].palette или имя
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true = 0-255 -> 0-NUM_LEDS) или брать как есть (false) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к sat ( 0-255)*/
CHSV Ledas::GCfPH( const struct CHSVPalette16& colorPalette, uint8_t colorID, bool isMapped, uint8_t brightness, uint8_t addToColor)
{
	if ( isMapped == true)				{ colorID *= REVERS_NUM_LEDS; }	
	CHSV color = ColorFromPalette( colorPalette, colorID, brightness, LINEARBLEND); 

	if ( addToColor || yo.antiSaturn)	{ color.sat = qsub8( color.sat, addToColor + yo.antiSaturn);}
	if ( yo.iscandle) 					{ color.val = ( color.val * yo.candle) >> 8; }
	if ( yo.ishifter)					{ color.hue += yo.shift; }
	return color;
}

/* Забираем цвет colorID из текущей activePollitreHSV палитры.
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true = 0-255 -> 0-NUM_LEDS) или брать как есть (false) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к sat ( 0-255)*/
CHSV Ledas::GCfPH( uint8_t colorID, bool isMapped, uint8_t brightness, uint8_t addToColor)
{
	CHSV color = this->GCfPH( activePollitreHSV, colorID, isMapped, brightness, addToColor);
	return color;
}


CRGB Ledas::hsv2rgb( const CHSV& hsv)
{
    CRGB rgb;
    uint16_t region, remainder, p, q, t;
    
    if (hsv.s == 0){ rgb.r = hsv.v;	rgb.g = hsv.v; rgb.b = hsv.v; 		return rgb; }
    
    region 		= hsv.h / 43;
    remainder 	= (hsv.h - (region * 43)) * 6; 
    
    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * 		 remainder)  >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;
    
    switch (region){
        case 0: 	rgb.r = hsv.v; 	rgb.g = t; 		rgb.b = p;           break;
        case 1: 	rgb.r = q; 		rgb.g = hsv.v; 	rgb.b = p;           break;
        case 2: 	rgb.r = p; 		rgb.g = hsv.v; 	rgb.b = t;           break;
        case 3: 	rgb.r = p; 		rgb.g = q; 		rgb.b = hsv.v;       break;
        case 4: 	rgb.r = t; 		rgb.g = p; 		rgb.b = hsv.v;       break;
        default:	rgb.r = hsv.v; 	rgb.g = p; 		rgb.b = q;           break;
    }    
    return rgb;
}


CHSV Ledas::rgb2hsv( const CRGB& rgb)
{
    CHSV hsv;
    uint16_t rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.v = rgbMax;
    if (hsv.v == 0){ hsv.h = 0; hsv.s = 0; 		return hsv;}

    hsv.s = 255 * ((long)(rgbMax - rgbMin)) / hsv.v;
    if (hsv.s == 0){ hsv.h = 0;					return hsv;}

    if 		(rgbMax == rgb.r)	hsv.h =   0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)   hsv.h =  85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else				        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}



void Ledas::powerON()
{  
	FastLED.setBrightness( yo.currentBri);
	FastLED.delay( 5);
	FastLED.show(); 
}

void Ledas::powerOFF()
{ 
	FastLED.setBrightness( 0);
	FastLED.delay( 5);
	FastLED.show(); 
}


/* Включаем / выключаем питание (!!!) ленты, 
тормозим анимацию и переходим ждущий режим (delay)  */
void Ledas::powerONOFF()
{
	if ( yo.ONOFF){ led.powerOFF(); } 
	else {			led.powerON(); 	}

	yo.ONOFF = !yo.ONOFF;
	Serial.printf( "set | State: %d\n", yo.ONOFF);  	
}


/* Сброс ленты в черное и обнуление LEDS_массивов диодов */
void Ledas::OFF()
{ 
	// for( uint8_t i = 0; i < 50; i++){
	// 	fadeToBlackBy( leds, NUM_LEDS, 2);
	// 	FastLED.show();
	// 	delay( 50);
	// }

	fill_solid( leds, NUM_LEDS, CRGB::Black); 	
	delay( 50);
	FastLED.show();
}


/* Моргаем кратенько черненьким, при достижении края параметров */
void Ledas::blinkLong()
{ 
	this->powerOFF(); 
	delay( 6); 
	this->powerON(); 
}

void Ledas::blinkShort()
{ 
	this->powerOFF(); 
	delay( 2); 
	this->powerON(); 
}


void Ledas::blinkPixel( uint8_t value, uint8_t max)
{
	uint8_t pos = NUM_LEDS * value / max;

	// fill_solid( leds, NUM_LEDS, CRGB::Black);

	leds[   qsub8( pos, 1)] 	= CRGB::Black;
	leds[			   pos] 	= CRGB::Red;
	leds[ ++pos % NUM_LEDS] 	= CRGB::White;

	FastLED.show();
	FastLED.delay( 8);
}


/* Затухаем лентой вниз до нулевого состояния 10-го диода */
void Ledas::fadeOUT()
{
	for( int i = 0; i < 20; i++)
	{
		fadeToBlackBy(leds, NUM_LEDS, 2);
		FastLED.show();
		Serial.printf( "FadeOUT: (%d.%d.%d)", leds[10].r,  leds[10].g, leds[10].b );
		delay(10);
	}
}


void Ledas::setSpeed(  int value){ yo.currentSpeed = value; yo.pt2webUpRange( "Speed", value); 	if ( yo.loadOutside){ mWaves[yo.waveID].speed  = value;}}
void Ledas::setAUX010( int value){ yo.AUX010 = value; 		yo.pt2webUpRange( "AUX010", value); if ( yo.loadOutside){ mWaves[yo.waveID].aux010 = value;}}
void Ledas::setAUX100( int value){ yo.AUX100 = value; 		yo.pt2webUpRange( "AUX100", value); if ( yo.loadOutside){ mWaves[yo.waveID].aux100 = value;}}
void Ledas::setAUX255( int value){ yo.AUX255 = value; 		yo.pt2webUpRange( "AUX255", value); if ( yo.loadOutside){ mWaves[yo.waveID].aux255 = value;}}
void Ledas::setAUX355( int value){ yo.AUX355 = value; 		yo.pt2webUpRange( "AUX355", value); if ( yo.loadOutside){ mWaves[yo.waveID].aux355 = value;}}
void Ledas::setAUX455( int value){ yo.AUX455 = value; 		yo.pt2webUpRange( "AUX455", value); if ( yo.loadOutside){ mWaves[yo.waveID].aux455 = value;}}

void Ledas::setShift(  int value){ yo.shiftServ  = value; 	yo.pt2webUpRange( "shift",  value);}
void Ledas::setCandle( int value){ yo.candleServ = value; 	yo.pt2webUpRange( "candle", value);}


/*@param force не пишем, так как закинули цвет в мапу с веб-сервера уже*/
void Ledas::setColors(	const CRGB& c1, const CRGB& c2, const CRGB& c3)
{
	yo.c1 = c1;
	yo.c2 = c2;
	yo.c3 = c3;

	if ( yo.loadOutside)
	{
		mWaves[yo.waveID].c1 = c1;
		mWaves[yo.waveID].c2 = c2;
		mWaves[yo.waveID].c3 = c3;
	}

	yo.pt2webUpColor();
	// yo.pt2webUpColor( "vC1", "rgb("	+ String( yo.c1.r) + "," + String( yo.c1.g) + "," + String( yo.c1.b) + ")");
	// yo.pt2webUpColor( "vC2", "rgb("	+ String( yo.c2.r) + "," + String( yo.c2.g) + "," + String( yo.c2.b) + ")");
	// yo.pt2webUpColor( "vC3", "rgb("	+ String( yo.c3.r) + "," + String( yo.c3.g) + "," + String( yo.c3.b) + ")");
}


void Ledas::setSaturation( int value)
{ 
	if ( value < 0 ){ 
		value = 100;
	}
	else if (value > 100){
		value = 100;
	}

	yo.currentSaturn  = value; 
	yo.antiSaturn = MAX_SATURATIOIN - yo.currentSaturn;
	yo.pt2webUpRange( "Saturations", value);

	if ( yo.loadOutside){ mWaves[yo.waveID].saturn = value; }	
}


void Ledas::setTemperature( int value)
{ 
	if ( value < 0 ){ 
		value = TEMP_IND_MAX;
	}
	else if (value > TEMP_IND_MAX){
		value = TEMP_IND_MAX;
	}
	
	yo.currentTemp = value; 
	
	if ( yo.loadOutside){ mWaves[yo.waveID].temp = value;}
	yo.pt2webUpRange( "Temperature", value);

	FastLED.setTemperature( temperList[yo.currentTemp] );	
	FastLED.show();
	// Serial.printf( "Temperature: #%d (%x)\n", yo.currentTemp, temperList[yo.currentTemp]);
}


void Ledas::setBrightness( int value)
{ 
	if ( value < 5 ){ 
		value = 5;
	}
	yo.currentBri = value; 
	// if ( yo.loadOutside){
		// mWaves[yo.lastPressed].bright = value;
	// }
	yo.pt2webUpRange( "Brightness", value);

	FastLED.setBrightness( yo.currentBri);
  	FastLED.show();
}


uint8_t Ledas::valueChange( uint8_t value, int delta, uint8_t min, uint8_t max)
{
	int out = value;  // int что бы перекрыть сложение/вычитаение
	out = (int)out + delta;

	if ( out < min) out = min;
	if ( out > max) out = max;
	
	// led.blinkShort();
	led.blinkPixel( value, max);	
	
	return out;
}

/* Меняем общуу срость анимации (0-...)
* @param delta +/- yo.currentSpeed.*/
void Ledas::changeSpeed( int delta)
{
	uint8_t value = led.valueChange( yo.currentSpeed, delta, 1, 50);
	led.setSpeed( value);

	Serial.printf( "chng| Speed [%d]: %d\n", delta, yo.currentSpeed);
}


/* Меняем общуу температуру цвета ленты (0-255)
* @param delta +/- yo.currentTemp.*/
void Ledas::changeTemperature( int delta)
{
	uint8_t value = led.valueChange( yo.currentTemp, delta, 0, TEMP_IND_MAX);

	if ( yo.currentTemp > TEMP_IND_MAX)
	{ 
		temperList[yo.currentTemp] = 0xFFFFFF;
	} 

	led.setTemperature( value);

	Serial.printf( "chng| Temperature [%d]: #%d (%x)\n", delta, yo.currentTemp, temperList[yo.currentTemp]);
}


/* Меняем общуу яркость ленты (0-255)
* @param delta +/- yo.currentBrightness.*/
void Ledas::changeBrightness( int delta)
{  
  	Serial.printf( "chng| Brightness [%d]: %d -> ", delta, yo.currentBri);  	

	uint8_t value = led.valueChange( FastLED.getBrightness(), delta, 5);
	led.setBrightness( value);

	Serial.printf( "%d.\n", yo.currentBri);  	
}


/* Меняем общуу сатурацию ленты (0-255)
* @param delta +/- yo.currentSaturn.*/
void Ledas::changeSaturation( int delta)
{
	uint8_t value = led.valueChange( yo.currentSaturn, delta, 0, MAX_SATURATIOIN);
	led.setSaturation( value);

	yo.antiSaturn = MAX_SATURATIOIN - yo.currentSaturn;

	Serial.printf( "chng| Saturation [%d]: %d ( anti: %d)\n", delta, yo.currentSaturn, yo.antiSaturn);
}


/* Сброс параметров ленты в дефолтное состояние */
void Ledas::reset()
{
	yo.loadOutside = true;	
	led.setBrightness(128); 
	led.setSpeed( 5);
	led.setTemperature( TEMP_IND_MAX); 
	led.setSaturation( 100);	
	yo.loadOutside = false;
}



CRGB Ledas::blend( const CRGB& c1, const CRGB& c2, uint16_t blend) 
{
  if ( blend == 0)  return c1;
  if ( blend == 255) return c2;

  uint32_t r3 = (( c2.r * blend) + ( c1.r * ( 255 - blend))) >> 8;
  uint32_t g3 = (( c2.g * blend) + ( c1.g * ( 255 - blend))) >> 8;
  uint32_t b3 = (( c2.b * blend) + ( c1.b * ( 255 - blend))) >> 8;

  return CRGB(r3, g3, b3);
}


/*
returns [0, highest-1] for a time period with x8'scale' and x'speed':
bpm ( highest = 256):	
	1 = 64.0 sec	11 = 5.81 sec
	2 = 32.0 sec	12 = 5.33 sec
	3 = 21.0 sec	13 = 4.92 sec
	4 = 16.0 sec	14 = 4.57 sec
	5 = 12.8 sec	15 = 4.27 sec
	6 = 10.6 sec	16 = 4.00 sec
	7 = 9.14 sec	17 = 3.76 sec
	8 = 8.00 sec	18 = 3.56 sec
	9 = 7.10 sec	19 = 3.37 sec
	10 = 6.4 sec	20 = 3.20 sec
timeScale:	
	..., 7 = x0.5, 8 = x1, 9 = x2, ...
*/
uint8_t Ledas::beat8( uint8_t bpm, uint8_t timeScale, uint16_t highest)
{
	return (( millis() * bpm) >> timeScale) % highest;
}


/*
returns [0, highest-1] for a time period with the given 'scale':
timeScale ( highest = 256):
	8 = 64 sec
	7 = 32 sec
	6 = 16 sec
	5 = 8 sec
	4 = 4 sec
	3 = 2 sec
	2 = 1 sec
	1 = 0.5/1 sec
*/
uint8_t Ledas::beat( uint8_t timeScale, uint16_t highest)
{
	return ( millis() >> timeScale) % highest;
}


/*
	Псево sin(), выдает [0, 255, 0] с замедлением на вершинах
	@param ind index [0. 255]
	@return full circle [0, 255, 0]
*/
uint8_t Ledas::sin( uint8_t ind)
{
	uint8_t out;
    if( ind & 0x80) ind = 255 - ind;
        
    if ( ind < 64)
	{
        ind = ind << 1;
        out  = ( ind * ind) >> 7;
    }
	else
	{
        ind = ( 128 - ind) << 1;
        out = 255 - (( ind * ind) >> 7);  // (( in * in) / 255) * 2 = ( scale8( in, in))
    }
    
	return out;
}


/*
	In/Out triwave circle:
	@param ind index [0, 255]
	@return in-out full circle [0, 255, 0]
*/
uint8_t Ledas::saw(uint8_t ind)
{
    if( ind & 0x80) ind = 255 - ind;

    return ind << 1;
}


/*
	In/Out circle: like triwave, but with custom period		
	@param ind circle index [0, highest]
	@param highest highest circe lenght 
	@param timeShift timeshift 
	@return [0, highest/2, highest] = [0, highest, 0]
*/
uint8_t Ledas::sawHigh( uint8_t ind, uint8_t highest, uint8_t timeShift)
{
	// uint8_t htotal = highest >> 1;
	ind = ( ind + timeShift) % highest;			// % <=- сильно под вопросом

	if ( ind > ( highest >> 1)){
		ind = highest - ind;
	}
	// uint8_t result = ind * ( 255 / ( htotal));
	// return result;
	return ind << 1;
} 



uint8_t Ledas::beatSaw( uint8_t bpm, uint8_t timeShift, uint8_t timeScale)
{	
	uint8_t result;
	result = this->beat8( bpm, timeScale);  	// [0-255]
	result = this->saw( result + timeShift);	// [0-255-0]
	return result;
}



uint8_t Ledas::beatSawHi( uint8_t bpm, uint16_t highest, uint8_t timeShift, uint8_t timeScale)
{	
	uint8_t result;
	result = this->beat8( bpm, timeScale, highest);  		// [0-high]
	result = this->sawHigh( result, highest, timeShift);	// [0-high-0]
	return result;
}


/*
	In/Out circle: like triwave, but with custom period		
	@param ind circle index
	@param highest total circe lenght 
	@param ts timeshift ( highest/2 = +255 )
	@return [0, highest/2, highest] = [0, 255, 0]
*/
uint8_t Ledas::sinHigh( uint8_t ind, uint8_t highest, uint8_t ts)
{
	// uint8_t htotal = total >> 1;
	// ind = ( ts + ind) % total;			// % <=- сильно под вопросом
	// if ( ind > htotal){ ind = total - ind; }
	// uint8_t result = ind * ( 255 / ( htotal));

	uint8_t result = highest == 255 ? ind : ( ind << 8) / highest;
	result = result + ts;
	result = this->sin( result);
	return result;
} 



/* 
Такой как beatSin8, только без sin и попроще с таймерами, выдает bpm( 0-255) циклов в минуту.
@param bpm ожидаемый примерный BPM
@param timeShift [0, 255] сдвигаем ответ 
@param timeScale ( 1-Х ) множитель БПМ для ledBeat8()
@return [0, 255, 0] in BPM from [0, 255] + timeshift
*/
uint8_t Ledas::beatSin( accum88 bpm, uint8_t timeShift, uint8_t timeScale)
{
    uint8_t beat 	= this->beat8( bpm, timeScale);
    uint8_t result 	= this->sin( beat + timeShift);
    return result;
}

/* 
Такой как beatSin8, только без sin и попроще с таймерами, выдает bpm ( 0-highest) циклов в минуту.
@param bpm ожидаемый примерный BPM
@param highest [0, 255] верхнее выдаваемое значение 
@param timeShift [0, 255] сдвигаем ответ 
@param timeScale ( 1-Х ) множитель БПМ для ledBeat8()
@return [0, 255, 0] in BPM from [0, hightest] + timeshift
*/
uint8_t Ledas::beatSinHi( accum88 bpm, uint8_t highest, uint8_t timeShift, uint8_t timeScale)
{
    uint8_t beat  	= this->beatSin( bpm, timeShift, timeScale);
    uint8_t result 	= scale8( beat, highest);
    return result;
}

/* 
Такой как beatSin8, только без sin и попроще с таймерами, выдает bpm ( lowest-highest) циклов в минуту.
@param bpm ожидаемый примерный BPM
@param lowest [0, 255] нижнее выдаваемое значение 
@param highest [0, 255] верхнее выдаваемое значение 
@param timeShift [0, 255] сдвигаем ответ 
@param timeScale ( 1-Х ) множитель БПМ для ledBeat8()
@return [0, 255, 0] in BPM from [lowest, highest] + timeshift 
*/
uint8_t Ledas::beatSinHiLo( accum88 bpm, uint8_t lowest, uint8_t highest, uint8_t timeShift, uint8_t timeScale)
{
	uint8_t beat 	= this->beatSinHi( bpm, ( highest - lowest), timeShift, timeScale);
    uint8_t result 	= lowest + beat;
    return result;
}

// Contact(const Contact& other) = delete;

// Contact(const Contact& other) = delete;
// Contact& operator=(const Contact& other) = delete;
// pixelTypes.h:172
/// allow assignment from HSV color
// inline CRGB& CRGB::operator= (const CHSV& rhs)  __attribute__((always_inline))
// {
//     hsv2rgb( rhs, *this);	
// 	return *this;
// }


// /// allow assignment from H, S, and V
// inline CRGB& setHSV (uint8_t hue, uint8_t sat, uint8_t val) __attribute__((always_inline))
// {
// 	hsv2rgb_rainbow( CHSV(hue, sat, val), *this);
// 	return *this;
// }

// /// allow assignment from just a Hue, saturation and value automatically at max.
// inline CRGB& setHue (uint8_t hue) __attribute__((always_inline))
// {
// 	hsv2rgb_rainbow( CHSV(hue, 255, 255), *this);
// 	return *this;
// }


// CRGB hsv2rgb_01( CHSV rhs)
// {
// 	Serial.println( "Error");
// 	return CRGB( 0,0,0);
// }


// {
//     CRGB h = hsv2rgb_01( rhs);
//     return h;
// }

//     /// allow assignment from HSV color
// inline CRGB& operator= (const CHSV& rhs) __attribute__((always_inline))
// {
//     hsv2rgb_rainbow( rhs, *this);
//     return *this;
// }





// CRGB& operator= (const CHSV& rhs) 
// {
//     // lhs += rhs;
// 	// hsv2rgb_01( rhs, *this);
//     return CRGB(255,255,255);
// }


// CRGB CRGB operator= (const CHSV& rhs) __attribute__((always_inline))
// {
//         // hsv2rgb_01( rhs, *this);
//         return CRGB(rhs);
// }

// struct CRGB {
// 	inline CRGB& operator= (const CHSV& rhs) __attribute__((always_inline))
//     {
//         hsv2rgb_01( rhs, *this);
//         return *this;
//     }
// }