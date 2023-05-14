#include "animeClass.h"
#include "animeCollector.h"

#include "animes\animesStatic.h"
#include "animes\aBeatSIN01.h"
#include "animes\aFire02.h"
#include "animes\aFire03.h"
#include "animes\aFire2012.h"
#include "animes\aBlinker01.h"
#include "animes\aGradient01.h"
#include "animes\aNoisePalette01.h"
#include "animes\aNoiseHUE01.h"
#include "animes\aRainbow01.h"
#include "animes\aSoundRain01.h"

#include "animes\blured.h"
#include "animes\twoSinsDemo.h"
#include "animes\breathwave.h"
#include "animes\lightings.h"
#include "animes\jungle.h"

void animePresets()
{
	/* Костерок 2.03*/
	mWaves[A_FIRE02].speed  = 8;
	mWaves[A_FIRE02].aux010 = 7;
	mWaves[A_FIRE02].aux100 = 70;
	mWaves[A_FIRE02].aux255 = 180;
	mWaves[A_FIRE02].aux355 = 180;

	/* Костерок 3.9*/
	mWaves[A_FIRE03].speed  = 5;
	mWaves[A_FIRE03].aux010 = 8;
	mWaves[A_FIRE03].aux100 = 14;
	mWaves[A_FIRE03].aux255 = 12;
	mWaves[A_FIRE03].aux355 = 130;

	/* inoise palette*/
	mWaves[A_NOISEPLT].speed  = 5;
	mWaves[A_NOISEPLT].aux010 = 3;
	mWaves[A_NOISEPLT].aux100 = 20;
	mWaves[A_NOISEPLT].aux255 = 20;
	mWaves[A_NOISEPLT].aux355 = 54;

	/* blinker*/
	mWaves[A_BLINKER].speed  = 5;
	mWaves[A_BLINKER].aux010 = 5;
	mWaves[A_BLINKER].aux100 = 20;
	mWaves[A_BLINKER].aux255 = 13;

	/* hell fire*/
	mWaves[A_NOISEMRD].speed  = 4;
	mWaves[A_NOISEMRD].aux010 = 3;
	mWaves[A_NOISEMRD].aux100 = 10;
	mWaves[A_NOISEMRD].aux255 = 10;
	mWaves[A_NOISEMRD].aux355 = 60;

	/* 6 waves*/
	mWaves[A_BSIN6].speed  = 6;
	mWaves[A_BSIN6].saturn = 50;
}

void animmeStartUP()
{
	a.addStatic( A_WPOWER, 	"White Power Color", 		&UPWhite, 			true);
	a.addStatic( A_PLTTEST, "Pallette static test",		&UP, 				true);
	// a.addStatic( 10212, 	"Pallette static hsv",		&UP01, 				false);	
	a.addAmine(	A_FIRE02, 	"Костерок v2.03",			&aFire02, 			true,	15,		&aFire02pre);
	a.addAmine(	A_FIRE03, 	"Костерок v3.ix",			&aFire03, 			true, 	15,		&aFire03pre);	
	a.addAmine(	A_NOISEPLT,	"inoise8 palette",			&aNoise, 			true, 	20, 	&aNoiseFires);
	a.addAmine(	A_BLINKER, 	"Моргалочка v2.0",			&aBlinken02, 		true, 	9, 		&aBlinken02Pre);
	a.addAmine(	A_BSIN8, 	"VIII (IIX) beatSIN waves",	&aBeatSINAgain, 	true,	9);
	a.addAmine(	A_BSIN6, 	"#.VI.WAVES.I.BEATSIN.#",	&aWavesBeat,  		true,	15, 	&aWavesBeatPre);
	a.addAmine(	A_NOISEMRD,	"Огни Мордора ©",			&aNoise,	 		true, 	21, 	&aNoiseMordor);
	a.addAmine(	A_NOISEHUE,	"inoise8 hue",		 		&aCreeping,  		true,	9, 		&aCreepingPre);
	a.addAmine(	A_BSIN4, 	"4 beatSINs waves",			&aBeatSIN8,			true);
	a.addAmine(	A_RAINBOW,	"Rainbow Wave", 			&aRainbow, 			true);
	a.addAmine(	A_MUSIC, 	"Musix echo", 				&aSoundCheck, 		true);
	a.addAmine(	A_FIRE21, 	"Fire 2012", 				&aFire2012,			true);
	
	a.addAmine(	A_BLURED, 	"_blured", 					&blured,			true);
	a.addAmine(	A_SIN2, 	"_2 sins", 					&anime2sins,		true, 	9, 		&anime2sinsPre);
	a.addAmine(	A_BREATH, 	"_breath wave",				&beatwave,			true);
	a.addAmine(	A_LIGHTING,	"_lightings wave",			&lightings,			true);
	a.addAmine(	A_JUNGLE, 	"_juungle wave",			&jungle,			true, 	9, 		&junglepre);
	
	// a.addAmine(	IR_NUM_7, 	"Gradient (wled) 1",		false, 	&aGradient, 		24, 	&aGradient01pre);
	// a.addAmine(	IR_NUM_8, 	"Gradient (wled) 2",		false, 	&aGradient, 		24, 	&aGradient02pre);
	
	a.addSetter( A_BRIGHT, 	"Brightness",	 			&led.setBrightness,		5,		255);		
	a.addSetter( A_SPEED, 	"Speed", 					&led.setSpeed, 			1,		10);
	a.addSetter( A_TEMPER, 	"Temperature",				&led.setTemperature,	1,		TEMP_IND_MAX, false);
	a.addSetter( A_SATUR, 	"Saturations",				&led.setSaturation, 	0,		100, false);
	a.addSetter( A_AUX010, 	"AUX010", 					&led.setAUX010,			0,		10);
	a.addSetter( A_AUX100, 	"AUX100", 					&led.setAUX100,			0,		100);
	a.addSetter( A_AUX255, 	"AUX255", 					&led.setAUX255,			0,		255);
	a.addSetter( A_AUX355, 	"AUX355", 					&led.setAUX355,			0,		255);
	a.addSetter( A_AUX455, 	"AUX455", 					&led.setAUX455,			0,		255);
	a.addSetter( A_SHIFT, 	"shift", 					&led.setShift,			0,		20,  false);
	a.addSetter( A_CANDLE, 	"candle", 					&led.setCandle,			0,		255, false);
	
	a.addChanger( A_BRIGHT_P, 	"Brightness +", 		&led.changeBrightness,	 5);
	a.addChanger( A_BRIGHT_M, 	"Brightness -", 		&led.changeBrightness, 	-5);
	a.addChanger( A_TEMP_P, 	"Temperature +", 		&led.changeTemperature);
	a.addChanger( A_TEMP_M, 	"Temperature -",		&led.changeTemperature, -1);
	a.addChanger( A_SPEED_P, 	"Speed +",				&led.changeSpeed);
	a.addChanger( A_SPEED_M, 	"Speed -",				&led.changeSpeed, 		-1);
	a.addChanger( A_SATUR_P, 	"Saturation +",			&led.changeSaturation, 	 5);
	a.addChanger( A_SATUR_M, 	"Saturation -",			&led.changeSaturation, 	-5);

	a.addChanger( A_WAVE_P,		"wave +",				&a.nextWave, 	    +1);	
	a.addChanger( A_WAVE_M,		"wave -",				&a.nextWave, 	    -1);	

	a.addStatic( A_RESET,		"Leds reset",			&led.reset);	
	a.addStatic( A_POWER, 		"Power ON/OFF",			&led.powerONOFF);


	animePresets();

	a.makeWebLists();
}
