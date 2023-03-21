#ifndef __WAVES_H
#define __WAVES_H

#include "..\config.h"
#include "..\animeClass.h"
// #include "aFire.h"

#include "animesStatic.h"
#include "aBeatSIN01.h"
#include "aFire02.h"
#include "aFire03.h"
#include "aFire2012.h"
#include "aBlinker01.h"
#include "aGradient01.h"
#include "aNoisePalette01.h"
#include "aNoiseHUE01.h"
#include "aRainbow01.h"
#include "aSoundRain01.h"

#include "blured.h"
#include "twoSinsDemo.h"
#include "breathwave.h"
#include "lightings.h"
#include "jungle.h"

void animmeStartUP()
{
	a.addStatic( IR_PLAY, 	"White Power Color", 		&UPWhite, 			true);
	a.addStatic( IR_FASTFF, "Pallette static test",		&UP, 				true);
	// a.addStatic( 10212, 	"Pallette static hsv",		&UP01, 				false);
	
	a.addAmine(	IR_NUM_2, 	"Костерок v2.03",			&aFire02, 			true,	15,		&aFire02pre);
	a.addAmine(	IR_NUM_3, 	"Костерок v3.ix",			&aFire03, 			true, 	15,		&aFire03pre);	
	a.addAmine(	10000002, 	"inoise8 palette",			&aNoise, 			true, 	15, 	&aNoiseFires);
	a.addAmine(	10000012, 	"Моргалочка v2.0",			&aBlinken02, 		true, 	9, 		&aBlinken02Pre);
	a.addAmine(	IR_NUM_4, 	"VIII (IIX) beatSIN waves",	&aBeatSINAgain, 	true,	4);
	a.addAmine(	IR_NUM_5, 	"#.VI.WAVES.I.BEATSIN.#",	&aWavesBeat,  		true,	9, 		&aWavesBeatPre);
	a.addAmine(	10000011, 	"Огни Мордора ©",			&aNoise,	 		true, 	21, 	&aNoiseMordor);
	a.addAmine(	10000013, 	"inoise8 hue",		 		&aCreeping,  		true,	9, 		&aCreepingPre);
	a.addAmine(	IR_NUM_6, 	"4 beatSINs waves",			&aBeatSIN8,			true);
	a.addAmine(	IR_NUM_10,	"Rainbow Wave", 			&aRainbow, 			true);
	a.addAmine(	10000001, 	"Musix echo", 				&aSoundCheck, 		true);
	a.addAmine(	IR_NUM_0, 	"Fire 2012", 				&aFire2012,			true);
	
	a.addAmine(	10000014, 	"_blured", 					&blured,			true);
	a.addAmine(	10000015, 	"_2 sins", 					&anime2sins,		true, 	9, 		&anime2sinsPre);
	a.addAmine(	10000016, 	"_breath wave",				&beatwave,			true);
	a.addAmine(	10000017, 	"_lightings wave",			&lightings,			true);
	a.addAmine(	10000018, 	"_juungle wave",			&jungle,			true, 	9, 		&junglepre);
	
	// a.addAmine(	IR_NUM_7, 	"Gradient (wled) 1",		false, 	&aGradient, 		24, 	&aGradient01pre);
	// a.addAmine(	IR_NUM_8, 	"Gradient (wled) 2",		false, 	&aGradient, 		24, 	&aGradient02pre);
	
	a.addSetter(10000003, 	"Brightness",	 			&Ledas::setBrightness,		5,		255);		
	a.addSetter(10000004, 	"Speed", 					&Ledas::setSpeed, 			1,		10);
	a.addSetter(10000005, 	"Temperature",				&Ledas::setTemperature,		1,		TEMP_IND_MAX);
	a.addSetter(10000006, 	"Saturations",				&Ledas::setSaturation, 		0,		100);
	a.addSetter(10000007, 	"AUX010", 					&Ledas::setAUX010,			0,		10);
	a.addSetter(10000008, 	"AUX100", 					&Ledas::setAUX100,			0,		100);
	a.addSetter(10000009, 	"AUX255", 					&Ledas::setAUX255,			0,		255);
	a.addSetter(10000099, 	"AUX355", 					&Ledas::setAUX355,			0,		255);
	a.addSetter(10000100, 	"AUX455", 					&Ledas::setAUX455,			0,		255);
	
	a.addChanger(IR_MENU_UP, 	"Brightness +", 		&Ledas::changeBrightness,	5);
	a.addChanger(IR_MENU_DN, 	"Brightness -", 		&Ledas::changeBrightness, 	-5);
	a.addChanger(IR_TVCHANL_UP, "Temperature +", 		&Ledas::changeTemperature);
	a.addChanger(IR_TVCHANL_DN, "Temperature -",		&Ledas::changeTemperature, 	-1);
	a.addChanger(IR_VOLUME_UP, 	"Speed +",				&Ledas::changeSpeed);
	a.addChanger(IR_VOLUME_DN, 	"Speed -",				&Ledas::changeSpeed, 		-1);
	a.addChanger(IR_TVVOL_UP, 	"Saturation +",			&Ledas::changeSaturation, 	5);
	a.addChanger(IR_TVVOL_DN, 	"Saturation -",			&Ledas::changeSaturation, 	-5);	

	a.addStatic(IR_MENU_OK,		"Leds reset",			&Ledas::reset);	
	a.addStatic(IR_TV_ON, 		"Power ON/OFF",			&Ledas::powerONOFF);

	a.makeWebLists();
}

#endif