#ifndef __LEDS_H
#define __LEDS_H

extern CRGB leds[NUM_LEDS];            // Массив ленты
extern uint8_t LEDS_HUE[NUM_LEDS];     // Массив для хранения ХУЕв цветов диодов (0-255)   
extern uint8_t LEDS_FEDOR[NUM_LEDS];   // Массив для хранения Яркости диодов (0-255)
extern uint8_t LEDS_STATUS[NUM_LEDS];   // Массив для хранения Яркости диодов (0-255)
extern uint8_t LEDS_VALUE[NUM_LEDS];   // Массив для хранения Яркости диодов (0-255)


/* Настраиваем и инициализируем FastLED ленту, кастомную палитру и уходим в черное...*/
void ledsStartUP();

/* Забираем цвет colorID из указанной colorPalette палитры.
@param colorPalette цветовая паллитка, если не указано - текущая, из myPal[ind].palette или имя
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true) или брать как есть (true) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к каждому каналу ( 0-255) типа сатурации, но нет...
@param blenType размытие переходов между цветами ( 0-1) */
CRGB ledGCfP( CRGBPalette16 colorPalette, uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, TBlendType blenType = LINEARBLEND);

/* Забираем цвет colorID из текущей targetPalette палитры.
@param colorID номер цвета в паллитре ( 0-255)
@param isMapped экстраполировать ли номер на всю длину палитры (true) или брать как есть (true) 
@param brightness  уйти в темненькое ( 0-255)
@param addToColor добавить к каждому каналу ( 0-255) типа сатурации, но нет...
@param blenType размытие переходов между цветами ( 0-1) */
CRGB ledGCfP( uint8_t colorID, bool isMapped = true, uint8_t brightness = 255, uint8_t addToColor = 0, TBlendType blenType = LINEARBLEND);

void powerON();
void powerOFF();

/* Включаем / выключаем питание (!!!) ленты, 
тормозим анимацию и переходим ждущий режим (delay)  */
void powerONOFF();

/* Сброс ленты в черное и обнуление LEDS_массивов диодов */
void ledOFF();

/* Включаем беленькую */
void ledUPWhite();

/* Включаем тестовое, сейчас = палитра */
void ledUP();

/* Моргаем кратенько черненьким, при достижении края параметров */
void ledBlink();

/* Затухаем лентой вниз до нулевого состояния 10-го диода */
void ledFadeOUT();

void setSpeed( 		int value);
void setAUX010(	 	int value);
void setAUX100( 	int value);
void setAUX255( 	int value);
void setSaturation( int value);
void setTemperature(int value);
void setBrightness( int value);
void setColors(	CRGB c1, CRGB c2, CRGB c3);

/* Меняем общуу срость анимации (0-...)
* @param delta +/- yo.currentSpeed.*/
void changeSpeed( int delta);

/* Меняем общуу температуру цвета ленты (0-255)
* @param delta +/- yo.currentTemp.*/
void changeTemperature( int delta);

/* Меняем общуу яркость ленты (0-255)
* @param delta +/- yo.currentBrightness.*/
void changeBrightness( int delta);

/* Меняем общуу сатурацию ленты (0-255)
* @param delta +/- yo.currentSaturn.*/
void changeSaturation( int delta);

/* Сброс параметров ленты в дефолтное состояние */
void ledReset();

CRGB ledBlend( CRGB c1, CRGB c2, uint16_t blend);

#endif

/*
 * fade out function, higher rate = quicker fade

void WS2812FX::fade_out(uint8_t rate) {
  rate = (255-rate) >> 1;
  float mappedRate = float(rate) +1.1;

  uint32_t color = SEGCOLOR(1); // target color
  int w2 = W(color);
  int r2 = R(color);
  int g2 = G(color);
  int b2 = B(color);

  for(uint16_t i = 0; i < SEGLEN; i++) {
    color = getPixelColor(i);
    int w1 = W(color);
    int r1 = R(color);
    int g1 = G(color);
    int b1 = B(color);

    int wdelta = (w2 - w1) / mappedRate;
    int rdelta = (r2 - r1) / mappedRate;
    int gdelta = (g2 - g1) / mappedRate;
    int bdelta = (b2 - b1) / mappedRate;

    // if fade isn't complete, make sure delta is at least 1 (fixes rounding issues)
    wdelta += (w2 == w1) ? 0 : (w2 > w1) ? 1 : -1;
    rdelta += (r2 == r1) ? 0 : (r2 > r1) ? 1 : -1;
    gdelta += (g2 == g1) ? 0 : (g2 > g1) ? 1 : -1;
    bdelta += (b2 == b1) ? 0 : (b2 > b1) ? 1 : -1;

    setPixelColor(i, r1 + rdelta, g1 + gdelta, b1 + bdelta, w1 + wdelta);
  }
}

*/