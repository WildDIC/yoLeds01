#ifndef __WAVES_H
#define __WAVES_H

/* Бегущая радужная вэйв */
void animWave01();

/* Костерок №01 */
void animWave02();

/* Моргающий градиент радуги = хуета */
void animWave03();

/* 8 волн с разной скоротью и наложением цвета */
void animWave04();

/* Ползущая радуга с проблесками беленьких диодов */
void animWave05();

/* Вжух-вжух радуга из цента типа странной цветомузыки */
void animWave06();

/* Fire 2012 */
void animWave07();

/* Костерок №02 */
void animWave08();

/*	4 wavwes + 1 beatSin*/
void animWave09pre();

/* 4 симметричные волны навстречу с наложением цвета */
void animWave09();

/*	XXX beatSin WAVES*/
void animaWave10();

/** Gradient run base function	far01 = длина полоски */
void animaWave11p1();
void animaWave11p2();
void animaWave11p3();
void animaWave11();

/** Android loading circle  */
void animaWave12();

void animaWave13pre();
void animaWave13();

#endif

    // fadeToBlackBy(leds, NUM_LEDS, 8);
    // int pos01 = beatsin16(10, 0, NUM_LEDS - 1, 0, 0);
    // int pos02 = NUM_LEDS-pos01-1;
    // int pos03 = beatsin16(10, 11, NUM_LEDS - 12, 0);
    // int pos04 = NUM_LEDS-pos03-1;


	/*
#define NUM_LEDS    60
CRGB leds[NUM_LEDS];
// #define TS01 35768
#define TS01 255
#define TS02 TS01 * 0.25
#define TS03 TS01 * 0.75
#define TS04 TS01 * 0.5

void sinTest(){
    fadeToBlackBy(leds, NUM_LEDS, 24);
    int pos01 = beatsin8(13, 0, NUM_LEDS - 1, 0, TS01);
	leds[pos01] = CRGB::Red;
    
    int pos02 = beatsin8(13, 0, NUM_LEDS - 1, 0, TS02);
	leds[pos02] = CRGB::Green;

    int pos03 = beatsin8(13, 0, NUM_LEDS - 1, 0, TS03);
	leds[pos03] = CRGB::Blue;

    int pos04 = beatsin8(13, 0, NUM_LEDS - 1, 0, TS04);
	leds[pos04] = CRGB::Yellow;

    FastLED.show();
    FastLED.delay(100);
}
void setup() {    
    FastLED.addLeds<WS2811, 5, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    sinTest();
    sinTest();sinTest();sinTest();sinTest();sinTest();sinTest();sinTest();sinTest();sinTest();sinTest();
}
void loop(){    sinTest();    }

	
	*/