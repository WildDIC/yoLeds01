#include <FastLED.h>
#include "main.h"
#include "irda.h"
#include "leds.h"
#include "waves.h"

#ifdef EERPROM_ENABLE 
#include "eerpromer.h"
#endif

#ifdef WEB_ENABLE
#include "wi-fi.h"
#include "webServer.h"
#else
#endif

#define IR_DELAY 100
clock_t startTime = clock();
clock_t startAnime = clock();


//********************************************************************
// 						SETUP
//*********************************************************************
void setup() {
	Serial.begin(115200);
	
	irdaStartUP();
	ledsStartUP();
	paletteStartUP();
	
	byte ind = 0;
	/* struct irdaItems{     code;	  name; 		typeWeb	indForWeb; leadOFF; isEffect; 	pt2Funca 		pt2static		pt2prewave 		pt2setter			min		max		pollDefault*/
	mButtons[551489775] =   { 0, "Power ON/OFF",		1, 	++ind, 		false, 	false,		NULL, 			&powerONOFF, 	NULL, 			NULL};
	mButtons[1262530894] =  { 0, "White Color", 		1, 	++ind,  	true, 	true, 		NULL, 			&ledUPWhite, 	NULL, 			NULL, 				0, 		0,			1};
	mButtons[1262547214] =  { 0, "Pallette test", 		1, 	++ind,  	true, 	true, 		NULL, 			&ledUP, 		NULL, 			NULL,				0, 		0, 			1};
	mButtons[1262513044] =  { 0, "Костерок 01", 		1, 	++ind,  	true, 	true, 		&animWave02, 	NULL, 			NULL, 			NULL,				0, 		0, 			7};
	mButtons[1262500804] =  { 0, "Костерок 02", 		1, 	++ind,  	true, 	true, 		&animWave08, 	NULL, 			NULL, 			NULL,				0, 		0, 			7};
	mButtons[1262541604] =  { 0, "Fire 2012", 			1, 	++ind,  	true, 	true, 		&animWave07, 	NULL, 			NULL, 			NULL, 				0, 		0,			4};
	mButtons[1262492644] =  { 0, "8 waves", 			1, 	++ind,  	true, 	true, 		&animWave04, 	NULL, 			NULL, 			NULL, 				0, 		0,			5};
	mButtons[1262533444] =  { 0, "8 waves сново", 		1, 	++ind,   	true, 	true, 		&animWave09, 	NULL, 			animWave09pre, 	NULL,				0, 		0, 			4};
	mButtons[1262529364] =  { 0, "Rainbow Wave", 		1, 	++ind,   	true, 	true, 		&animWave01, 	NULL, 			NULL, 			NULL, 				0, 		0,			6};
	mButtons[1262525284] =  { 0, "Ползучая rainbow", 	1, 	++ind,  	true, 	true, 		&animWave05, 	NULL, 			NULL, 			NULL, 				0, 		0,			6};
	mButtons[1262508964] =  { 0, "Musix echo", 			1, 	++ind,  	true, 	true, 		&animWave06, 	NULL, 			NULL, 			NULL, 				0, 		0,			6};
	mButtons[1262545684] =  { 0, "Flasher", 			1, 	++ind,  	true, 	true, 		&animWave03, 	NULL, 			NULL, 			NULL, 				0, 		0,			3};
	mButtons[1262545666] =  { 0, "4 beatSins waves",	1, 	++ind,  	true, 	true, 		&animaWave10, 	NULL, 			NULL, 			NULL, 				0, 		0,			4};
	ind = 0;
	mButtons[1066677700] =  { 0, "Brightness",	 		2, 	++ind,   	false, 	false, 		NULL, 			NULL, 			NULL, 			&setBrightness,		5,		255};
	mButtons[1066677701] =  { 0, "Saturations", 		2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setSaturation, 	0,		100};
	mButtons[1066677702] =  { 0, "Temperature", 		2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setTemperature,	0,		TEMP_IND_MAX};
	mButtons[1066677703] =  { 0, "Speed", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setSpeed, 			0,		40};

	mButtons[1270278422] =  { 0, "Leds reset",			0, 		0, 		false, 	false,		NULL, 			&ledReset, 		NULL, 			NULL};

	mButtons[1270235582] =  { 0, "Brightness +", 		0, 		0,   	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeBrightness,	15};
	mButtons[1270268222] =  { 0, "Brightness -", 		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeBrightness, -15};
	mButtons[1270219007] =  { 0, "Temperature +", 		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeTemperature,	1};
	mButtons[1270251647] =  { 0, "Temperature -",		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeTemperature, -1};
	mButtons[1270267967] =  { 0, "Speed +",				0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSpeed, 		2};
	mButtons[1270235327] =  { 0, "Speed -",				0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSpeed, 		-2};
	mButtons[551502015]  =  { 0, "Saturation +",		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSaturation, 	10};
	mButtons[551534655]  =  { 0, "Saturation -",		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSaturation, -10};

	std::map<int, irdaItems>::iterator mbIter = mButtons.begin();	

	#ifdef EERPROM_ENABLE
		eepromStartUP();		
	#endif

	#ifdef WEB_ENABLE
		int wifiStatus = wifiStartUP();
		if ( wifiStatus == WL_CONNECTED){
			Serial.println( "Поднимаем как-то WebServer...");
			webServerStartUP();
		} else{
			Serial.printf( "WiFi нетути, ( Ошибка подключения номер: %d).\nWebServera вам не будет...:(", wifiStatus);
		}		
	#endif	
}

//********************************************************************
// 						LOOP 		( millis())
//*********************************************************************
void loop() {
	if ( clock() - startTime > IR_DELAY){
		startTime = clock();
		irdaServer();
	}

	if ( yo.ONOFF && pt2Func){
		if ( clock() - startAnime > yo.currentSpeed){
			startAnime = clock();
			pt2Func();
			// delay( yo.currentSpeed);
			// Serial.println( yo.currentSpeed);
		} 
	}	
	else { 
		delay( 500); 
	}  	
}