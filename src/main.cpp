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

#define IR_DELAY 300
clock_t startTime = clock();
clock_t startAnime = clock();

// заглушка на пустую функцию, если/пока нет вебсервеа.
void fooFunc(){}

//********************************************************************
// 						SETUP
//*********************************************************************
void setup() {
	Serial.begin(115200);
	
	irdaStartUP();
	ledsStartUP();
	paletteStartUP();
	yo.pt2webUpdate = &fooFunc;  
	yo.pt2webUnsave = &fooFunc;  

	byte ind = 0;
	/* struct irdaItems{     code;	  name; 			typeWeb	indForWeb; leadOFF; isEffect; 	pt2Funca 		pt2static		pt2prewave 		pt2setter			min		max		pollDefault*/
	mButtons[IR_TV_ON] 		=  { 0, "Power ON/OFF",			1, 	++ind, 		false, 	false,		NULL, 			&powerONOFF, 	NULL, 			NULL};
	mButtons[IR_PLAY] 		=  { 0, "White Color", 			1, 	++ind,  	true, 	true, 		NULL, 			&ledUPWhite, 	NULL, 			NULL, 				0, 		0,			1};
	mButtons[IR_FASTFF] 	=  { 0, "Pallette test", 		1, 	++ind,  	true, 	true, 		NULL, 			&ledUP, 		NULL, 			NULL,				0, 		0, 			1};
	mButtons[IR_NUM_1] 		=  { 0, "Костерок 01", 			1, 	++ind,  	true, 	true, 		&animWave02, 	NULL, 			NULL, 			NULL,				0, 		0, 			7};
	mButtons[IR_NUM_2] 		=  { 0, "Костерок 02", 			1, 	++ind,  	true, 	true, 		&animWave08, 	NULL, 			NULL, 			NULL,				0, 		0, 			7};	
	mButtons[IR_NUM_3] 		=  { 0, "Костерок 03", 			1, 	++ind,  	true, 	true, 		&animaWave13, 	NULL, 			animaWave13pre,	NULL, 				0, 		0,			6};	
	mButtons[IR_NUM_4] 		=  { 0, "8 waves", 				1, 	++ind,  	true, 	true, 		&animWave04, 	NULL, 			NULL, 			NULL, 				0, 		0,			5};
	mButtons[IR_NUM_5] 		=  { 0, "8 waves сново", 		1, 	++ind,   	true, 	true, 		&animWave09, 	NULL, 			animWave09pre, 	NULL,				0, 		0, 			4};
	mButtons[IR_NUM_6] 		=  { 0, "4 beatSins waves",		1, 	++ind,  	true, 	true, 		&animaWave10, 	NULL, 			NULL, 			NULL, 				0, 		0,			4};
	mButtons[IR_NUM_7] 		=  { 0, "Gradient (wled) 1",	1, 	++ind,  	true, 	true, 		&animaWave11, 	NULL, 			animaWave11p1,  NULL, 				0, 		0,			24};
	mButtons[IR_NUM_8] 		=  { 0, "Gradient (wled) 2",	1, 	++ind,  	true, 	true, 		&animaWave11, 	NULL, 			animaWave11p2, 	NULL, 				0, 		0,			24};
	mButtons[IR_NUM_9] 		=  { 0, "Gradient (wled) 3",	1, 	++ind,  	true, 	true, 		&animaWave11, 	NULL, 			animaWave11p3, 	NULL, 				0, 		0,			24};
	mButtons[IR_NUM_0] 		=  { 0, "Fire 2012", 			1, 	++ind,  	true, 	true, 		&animWave07, 	NULL, 			NULL, 			NULL, 				0, 		0,			4};	
	mButtons[IR_NUM_CLR] 	=  { 0, "Android (wled)",		1, 	++ind,  	true, 	true, 		&animaWave12, 	NULL, 			NULL, 			NULL, 				0, 		0,			4};
	mButtons[IR_NUM_10] 	=  { 0, "Rainbow Wave", 		1, 	++ind,   	true, 	true, 		&animWave01, 	NULL, 			NULL, 			NULL, 				0, 		0,			6};	
	mButtons[10000000] 		=  { 0, "Ползучая rainbow", 	1, 	++ind,  	true, 	true, 		&animWave05, 	NULL, 			NULL, 			NULL, 				0, 		0,			6};	
	mButtons[10000001] 		=  { 0, "Musix echo", 			1, 	++ind,  	true, 	true, 		&animWave06, 	NULL, 			NULL, 			NULL, 				0, 		0,			6};
	mButtons[10000002] 		=  { 0, "Flasher", 				1, 	++ind,  	true, 	true, 		&animWave03, 	NULL, 			NULL, 			NULL, 				0, 		0,			3};
	ind = 0;
	mButtons[10000003] 		=  { 0, "Brightness",	 		2, 	++ind,   	false, 	false, 		NULL, 			NULL, 			NULL, 			&setBrightness,		5,		255};
	mButtons[10000004] 		=  { 0, "Saturations", 			2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setSaturation, 	0,		100};
	mButtons[10000005] 		=  { 0, "Temperature", 			2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setTemperature,	0,		TEMP_IND_MAX};
	mButtons[10000006] 		=  { 0, "Speed", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setSpeed, 			2,		40};

	mButtons[IR_MENU_OK] 	=  { 0, "Leds reset",			0, 		0, 		false, 	false,		NULL, 			&ledReset, 		NULL, 			NULL};

	mButtons[IR_MENU_UP] 	=  { 0, "Brightness +", 		0, 		0,   	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeBrightness,	15};
	mButtons[IR_MENU_DN] 	=  { 0, "Brightness -", 		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeBrightness, -15};
	mButtons[IR_TVCHANL_UP] =  { 0, "Temperature +", 		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeTemperature,	1};
	mButtons[IR_TVCHANL_DN] =  { 0, "Temperature -",		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeTemperature, -1};
	mButtons[IR_VOLUME_UP] 	=  { 0, "Speed +",				0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSpeed, 		2};
	mButtons[IR_VOLUME_DN] 	=  { 0, "Speed -",				0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSpeed, 		-2};
	mButtons[IR_TVVOL_UP]  	=  { 0, "Saturation +",			0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSaturation, 	10};
	mButtons[IR_TVVOL_DN]  	=  { 0, "Saturation -",			0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSaturation, -10};

	std::map<int, irdaItems>::iterator mbIter = mButtons.begin();	

	#ifdef EERPROM_ENABLE
		eepromStartUP();		
	#endif

	#ifdef WEB_ENABLE
		int wifiStatus = wifiStartUP();
		if ( wifiStatus == WL_CONNECTED){
			Serial.println( "Поднимаем как-то WebServer.");
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
	yo.now = clock();

	if ( yo.now - startTime > IR_DELAY){
		startTime = yo.now;
		irdaServer();
	}

	if ( yo.ONOFF && pt2Func){
		if ( yo.now - startAnime > yo.currentSpeed){
			startAnime = yo.now;
			pt2Func();
		} 
	}	
	else { 
		delay( 500); 
	}  	

	#ifdef EERPROM_ENABLE
		eepromSaveHandler();
	#endif
}