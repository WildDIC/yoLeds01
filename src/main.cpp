#include "config.h"
#include "main.h"
#include "irda.h"
#include "leds.h"
#include "palettes.h"
#include "waves.h"

#ifdef EERPROM_ENABLE 
#include "eerpromer.h"
#endif

#ifdef WEB_ENABLE
#include "wi-fi.h"
#include "webServer.h"
#else
#endif


// #include "waveClass.h"

#ifdef FPSCOUNT_ENABLE 
clock_t startFPS = clock() + 1000;
int fpsCount = 0;
#endif

#define IR_DELAY 300
clock_t startTime = clock();
clock_t startAnime = clock();

// arcsin(sin(x)).
// void loop()
// {
//     uint32_t curTime = millis();
//     uint32_t curSin = ( curTime * curSpeed * 280) / 65536; // >> 16;
//     uint8_t beatsin = (sin8( curSin)); // + 32768);
//     uint8_t scaledbeat = scale8( beatsin, 100);

//     Serial.print( curTime);
//     Serial.print( " - ");
//     Serial.print( curSin);
//     Serial.print( " - ");
//     Serial.print( beatsin);
//     Serial.print( " - ");
//     Serial.println( scaledbeat);
//     // Serial.print( " - ");
//     //Serial.println( curTime * curSpeed / 60000);

//     delay( 100);
// }
// заглушка на пустую функцию, если/пока нет вебсервеа.
void fooFunc(){}

//********************************************************************
// 						SETUP
//*********************************************************************

// void method_plus(int _arg) {
// 	Serial.printf( "From class: %d\n", minute);
// }

void setup() {
	yo.now = clock();
	Serial.begin(115200);
	
	irdaStartUP();
	ledsStartUP();
	paletteStartUP();
	yo.pt2webUpdate = &fooFunc;  
	yo.pt2webUnsave = &fooFunc;  

	// waveClass objCppstudio(11,11,2011); // объявление объекта и инициализвция элементов данных
    // objCppstudio.message(); // вызов функции message
    // objCppstudio.getDate(); // отобразить дату
	// objCppstudio.method = method_plus;


	byte ind = 0;
	/* struct irdaItems{     code;	  name; 			typeWeb	indForWeb; leadOFF; isEffect; 	pt2Funca 		pt2static		pt2prewave 		pt2setter			min		max		pollDefault	bright	temp	speed	saturn	aux010	aux100	aux255 */
	mWaves[IR_TV_ON] 		=  { 0, "Power ON/OFF",			1, 	++ind, 		false, 	false,		NULL, 			&powerONOFF, 	NULL, 			NULL};
	mWaves[IR_PLAY] 		=  { 0, "White Color", 			1, 	++ind,  	true, 	true, 		NULL, 			&ledUPWhite, 	NULL, 			NULL, 				0, 		0,			1, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_FASTFF] 		=  { 0, "Pallette test", 		1, 	++ind,  	true, 	true, 		NULL, 			&ledUP, 		NULL, 			NULL,				0, 		0, 			1, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_1] 		=  { 0, "Костерок 01", 			1, 	++ind,  	true, 	true, 		&animWave02, 	NULL, 			NULL, 			NULL,				0, 		0, 			8, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_2] 		=  { 0, "Костерок 02", 			1, 	++ind,  	true, 	true, 		&animWave08, 	NULL, 			animWave08pre,	NULL,				0, 		0, 			14,			125, 	50, 	10, 	100, 	5, 		50, 	125};	
	mWaves[IR_NUM_3] 		=  { 0, "Костерок 03", 			1, 	++ind,  	true, 	true, 		&animaWave13, 	NULL, 			animaWave13pre,	NULL, 				0, 		0,			8, 			125, 	50, 	10, 	100, 	5, 		50, 	125};	
	mWaves[IR_NUM_4] 		=  { 0, "8 waves", 				1, 	++ind,  	true, 	true, 		&animWave04, 	NULL, 			NULL, 			NULL, 				0, 		0,			5, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_5] 		=  { 0, "8 waves сново", 		1, 	++ind,   	true, 	true, 		&animWave09, 	NULL, 			animWave09pre, 	NULL,				0, 		0, 			4, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_6] 		=  { 0, "4 beatSins waves",		1, 	++ind,  	true, 	true, 		&animaWave10, 	NULL, 			NULL, 			NULL, 				0, 		0,			4, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000002] 		=  { 0, "inoise8 test",			1, 	++ind,  	true, 	true, 		&animWave03, 	NULL, 			animWave03fires,NULL, 				0, 		0,			3, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000011] 		=  { 0, "Огни Мордора ©",		1, 	++ind,  	true, 	true, 		&animWave03, 	NULL, 			animWave03mordor,NULL, 				0, 		0,			3, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_7] 		=  { 0, "Gradient (wled) 1",	1, 	++ind,  	true, 	true, 		&animaWave11, 	NULL, 			animaWave11p1,  NULL, 				0, 		0,			24, 		125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_8] 		=  { 0, "Gradient (wled) 2",	1, 	++ind,  	true, 	true, 		&animaWave11, 	NULL, 			animaWave11p2, 	NULL, 				0, 		0,			24, 		125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_9] 		=  { 0, "Gradient (wled) 3",	1, 	++ind,  	true, 	true, 		&animaWave11, 	NULL, 			animaWave11p3, 	NULL, 				0, 		0,			24, 		125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000010] 		=  { 0, "Моргалочка",			1, 	++ind,  	true, 	true, 		&animaWave14, 	NULL, 			NULL,			NULL, 				0, 		0,			3, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_0] 		=  { 0, "Fire 2012", 			1, 	++ind,  	true, 	true, 		&animWave07, 	NULL, 			NULL, 			NULL, 				0, 		0,			4, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	// mWaves[IR_NUM_CLR] 		=  { 0, "Android (wled)",		1, 	++ind,  	true, 	true, 		&animaWave12, 	NULL, 			NULL, 			NULL, 				0, 		0,			4, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_10] 		=  { 0, "Rainbow Wave", 		1, 	++ind,   	true, 	true, 		&animWave01, 	NULL, 			NULL, 			NULL, 				0, 		0,			7, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000000] 		=  { 0, "Ползучая rainbow", 	1, 	++ind,  	true, 	true, 		&animWave05, 	NULL, 			NULL, 			NULL, 				0, 		0,			7, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000001] 		=  { 0, "Musix echo", 			1, 	++ind,  	true, 	true, 		&animWave06, 	NULL, 			NULL, 			NULL, 				0, 		0,			7, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	ind = 0;
	mWaves[10000003] 		=  { 0, "Brightness",	 		2, 	++ind,   	false, 	false, 		NULL, 			NULL, 			NULL, 			&setBrightness,		5,		255};		
	mWaves[10000004] 		=  { 0, "Speed", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setSpeed, 			1,		10};
	mWaves[10000005] 		=  { 0, "Temperature", 			2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setTemperature,	1,		TEMP_IND_MAX};
	mWaves[10000006] 		=  { 0, "Saturations", 			2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setSaturation, 	0,		100};
	mWaves[10000007] 		=  { 0, "AUX010", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setAUX010,			0,		10};
	mWaves[10000008] 		=  { 0, "AUX100", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setAUX100,			0,		100};
	mWaves[10000009] 		=  { 0, "AUX255", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&setAUX255,			0,		255};

	mWaves[IR_MENU_OK] 		=  { 0, "Leds reset",			0, 		0, 		false, 	false,		NULL, 			&ledReset, 		NULL, 			NULL};

	mWaves[IR_MENU_UP] 		=  { 0, "Brightness +", 		0, 		0,   	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeBrightness,	15};
	mWaves[IR_MENU_DN] 		=  { 0, "Brightness -", 		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeBrightness, -15};
	mWaves[IR_TVCHANL_UP] 	=  { 0, "Temperature +", 		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeTemperature,	1};
	mWaves[IR_TVCHANL_DN] 	=  { 0, "Temperature -",		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeTemperature, -1};
	mWaves[IR_VOLUME_UP] 	=  { 0, "Speed +",				0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSpeed, 		2};
	mWaves[IR_VOLUME_DN] 	=  { 0, "Speed -",				0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSpeed, 		-2};
	mWaves[IR_TVVOL_UP]  	=  { 0, "Saturation +",			0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSaturation, 	10};
	mWaves[IR_TVVOL_DN]  	=  { 0, "Saturation -",			0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&changeSaturation, -10};

	std::map<int, waveItem>::iterator mbIter = mWaves.begin();	

	#ifdef EERPROM_ENABLE
		eepromStartUP();		
	#endif

	#ifdef WEB_ENABLE
		wifiStartUP();
		webServerStartUP();
		// if ( wifiStatus == WL_CONNECTED){
		// 	Serial.println( "Поднимаем как-то WebServer.");
		// 	webServerStartUP();
		// } else{
		// 	Serial.printf( "WiFi нетути, ( Ошибка подключения номер: %d).\nWebServera вам не будет...:(", wifiStatus);
		// }		
	#endif	
}


//********************************************************************
// 						LOOP 		( millis())
//*********************************************************************
void loop() {
	yo.now = clock();

	if ( yo.now > startTime){
		startTime = yo.now + IR_DELAY;
		irdaServer( 0, 0);
	}

	if ( yo.ONOFF && pt2Func){
		if ( yo.now > startAnime){
			startAnime = yo.now + yo.currentSpeed;
			pt2Func();
		} 
	}	
	else { 
		delay( 500); 
	}  	

	#ifdef EERPROM_ENABLE
		eepromSaveHandler();
	#endif

	#ifdef WEB_ENABLE		
		// проверка на подключенный ВФ и переконнект, если надо
		wifiCheckConnect();
	#endif

	#ifdef FPSCOUNT_ENABLE
		fpsCount++;
		if ( yo.now >= startFPS){
			Serial.println( fpsCount);
			startFPS = yo.now + 1000;
			fpsCount = 0;
		}
	#endif

	// EVERY_N_MILLISECONDS( <mseconds> ) {}
   	// EVERY_N_SECONDS( <seconds> ) {}
}