#include "config.h"
#include "main.h"
#include "irda.h"
#include "leds.h"
#include "palettes.h"
// #include "waves.h"

#include "animes/animeCollector.h"

#ifdef EERPROM_ENABLE 
#include "eerpromer.h"
#endif

#ifdef WEB_ENABLE
#include "wi-fi.h"
#include "webServer.h"
#else
#endif

#ifdef FPSCOUNT_ENABLE 
clock_t startFPS = clock() + 1000;
int fpsCount = 0;
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
	yo.now = clock();
	Serial.begin(115200);
	
	irdaStartUP();
	led.startUP();
	paletteStartUP();
	yo.pt2webUpdate = &fooFunc;  
	yo.pt2webUnsave = &fooFunc;  

	byte ind = 0;
	/* struct irdaItems{     code;	  name; 			typeWeb	indForWeb; leadOFF; isEffect; 	pt2Funca 		pt2static		pt2prewave 		pt2setter			min		max		pollDefault	bright	temp	speed	saturn	aux010	aux100	aux255 */
	mWaves[IR_TV_ON] 		=  { 0, "Power ON/OFF",			1, 	++ind, 		false, 	false,		NULL, 			&(Ledas::powerONOFF), 	NULL, 	NULL};
	mWaves[IR_PLAY] 		=  { 0, "White Power Color", 	1, 	++ind,  	true, 	true, 		NULL, 			&(Ledas::UPWhite), 	NULL, 		NULL, 				0, 		0,			1, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_FASTFF] 		=  { 0, "Pallette static test",	1, 	++ind,  	true, 	true, 		NULL, 			&(Ledas::UP), 	NULL, 			NULL,				0, 		0, 			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_2] 		=  { 0, "Костерок v2.03",		1, 	++ind,  	true, 	true, 		&aFire02, 		NULL, 			aFire02pre,		NULL,				0, 		0, 			15,			125, 	50, 	10, 	100, 	5, 		50, 	125};	
	mWaves[IR_NUM_4] 		=  { 0, "VIII / IIX beatSIN waves",1,++ind,  	true, 	true, 		&aBeatSINAgain,	NULL, 			NULL, 			NULL, 				0, 		0,			4, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_5] 		=  { 0, "#.VI.WAVES.I.BEATSIN.#",1,	++ind,   	true, 	true, 		&aWavesBeat, 	NULL, 			aWavesBeatPre, 	NULL,				0, 		0, 			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_6] 		=  { 0, "4 beatSINs waves",		1, 	++ind,  	true, 	true, 		&aBeatSIN8, 	NULL, 			NULL, 			NULL, 				0, 		0,			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000002] 		=  { 0, "inoise8 palette",		1, 	++ind,  	true, 	true, 		&aNoise, 		NULL, 			aNoiseFires,	NULL, 				0, 		0,			15,			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000000] 		=  { 0, "inoise8 hue",		 	1, 	++ind,  	true, 	true, 		&aCreeping, 	NULL, 			aCreepingPre,	NULL, 				0, 		0,			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000011] 		=  { 0, "Огни Мордора ©",		1, 	++ind,  	true, 	true, 		&aNoise,	 	NULL, 			aNoiseMordor,	NULL, 				0, 		0,			21,			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000012] 		=  { 0, "Моргалочка v2.0",		1, 	++ind,  	true, 	true, 		&aBlinken02, 	NULL, 			aBlinken02Pre,	NULL, 				0, 		0,			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_7] 		=  { 0, "Gradient (wled) 1",	1, 	++ind,  	true, 	true, 		&aGradient, 	NULL, 			aGradient01pre, NULL, 				0, 		0,			24, 		125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_8] 		=  { 0, "Gradient (wled) 2",	1, 	++ind,  	true, 	true, 		&aGradient, 	NULL, 			aGradient02pre, NULL, 				0, 		0,			24, 		125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_0] 		=  { 0, "Fire 2012", 			1, 	++ind,  	true, 	true, 		&aFire2012, 	NULL, 			NULL, 			NULL, 				0, 		0,			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_10] 		=  { 0, "Rainbow Wave", 		1, 	++ind,   	true, 	true, 		&aRainbow, 		NULL, 			NULL, 			NULL, 				0, 		0,			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[10000001] 		=  { 0, "Musix echo", 			1, 	++ind,  	true, 	true, 		&aSoundCheck, 	NULL, 			NULL, 			NULL, 				0, 		0,			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	mWaves[IR_NUM_3] 		=  { 0, "Костерок 03", 			1, 	++ind,  	true, 	true, 		&aFire03, 		NULL, 			aFire03pre,		NULL, 				0, 		0,			15,			125, 	50, 	10, 	100, 	5, 		50, 	125};	
	// mWaves[IR_NUM_1] 		=  { 0, "Костерок 01", 			1, 	++ind,  	true, 	true, 		&aFire01, 		NULL, 			NULL, 			NULL,				0, 		0, 			15,			125, 	50, 	10, 	100, 	5, 		50, 	125};
	// mWaves[IR_NUM_9] 		=  { 0, "Gradient (wled) 3",	1, 	++ind,  	true, 	true, 		&aGradient, 	NULL, 			aGradient03pre, NULL, 				0, 		0,			24, 		125, 	50, 	10, 	100, 	5, 		50, 	125};
	// mWaves[10000010] 		=  { 0, "Моргалочка",			1, 	++ind,  	true, 	true, 		&aBlinken02,	NULL, 			aBlinken02Pre,	NULL, 				0, 		0,			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	// mWaves[IR_NUM_CLR] 		=  { 0, "Android (wled)",		1, 	++ind,  	true, 	true, 		&aAndroid, 		NULL, 			NULL, 			NULL, 				0, 		0,			9, 			125, 	50, 	10, 	100, 	5, 		50, 	125};
	ind = 0;
	mWaves[10000003] 		=  { 0, "Brightness",	 		2, 	++ind,   	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setBrightness,	5,		255};		
	mWaves[10000004] 		=  { 0, "Speed", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setSpeed, 		1,		10};
	mWaves[10000005] 		=  { 0, "Temperature", 			2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setTemperature,	1,		TEMP_IND_MAX};
	mWaves[10000006] 		=  { 0, "Saturations", 			2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setSaturation, 	0,		100};
	mWaves[10000007] 		=  { 0, "AUX010", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setAUX010,		0,		10};
	mWaves[10000008] 		=  { 0, "AUX100", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setAUX100,		0,		100};
	mWaves[10000009] 		=  { 0, "AUX255", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setAUX255,		0,		255};
	mWaves[10000099] 		=  { 0, "AUX355", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setAUX355,		0,		255};
	mWaves[10000100] 		=  { 0, "AUX455", 				2, 	++ind,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::setAUX455,		0,		255};

	mWaves[IR_MENU_OK] 		=  { 0, "Leds reset",			0, 		0, 		false, 	false,		NULL, 			&Ledas::reset, 		NULL, 			NULL};

	mWaves[IR_MENU_UP] 		=  { 0, "Brightness +", 		0, 		0,   	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::changeBrightness,	5};
	mWaves[IR_MENU_DN] 		=  { 0, "Brightness -", 		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::changeBrightness, 	-5};
	mWaves[IR_TVCHANL_UP] 	=  { 0, "Temperature +", 		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::changeTemperature,	1};
	mWaves[IR_TVCHANL_DN] 	=  { 0, "Temperature -",		0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::changeTemperature, -1};
	mWaves[IR_VOLUME_UP] 	=  { 0, "Speed +",				0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::changeSpeed, 		1};
	mWaves[IR_VOLUME_DN] 	=  { 0, "Speed -",				0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::changeSpeed, 		-1};
	mWaves[IR_TVVOL_UP]  	=  { 0, "Saturation +",			0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::changeSaturation, 	5};
	mWaves[IR_TVVOL_DN]  	=  { 0, "Saturation -",			0, 		0,  	false, 	false, 		NULL, 			NULL, 			NULL, 			&Ledas::changeSaturation, -5};

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
void loop() 
{
	yo.now = clock();
	yo.beat = yo.now >> 8; // 255 = 60sec

	if ( yo.now > startTime)
	{
		startTime = yo.now + IR_DELAY;
		irdaServer( 0, 0);
	}

	if ( yo.ONOFF && pt2Func)
	{		
		if ( yo.iscandle)
		{
			yo.candle = inoise8( millis() >> 3, millis());
			yo.candle = 255 - qsub8( yo.candle, yo.AUX355);
		}

		pt2Func();

		delay( 1);			
		FastLED.show();
	}	
	else 
	{ 
		delay( 500); 
	}  	


	EVERY_N_MILLISECONDS( 250)
	{
	#ifdef EERPROM_ENABLE
		eepromSaveHandler();
	#endif

	#ifdef WEB_ENABLE		
		wifiCheckConnect();	
		// Serial.println( animeFire.nSpeed);
		// Serial.println( animeFire.anime);
	#endif	
	}

	#ifdef FPSCOUNT_ENABLE
	fpsCount++;
	if ( yo.now >= startFPS)
	{
		Serial.println( fpsCount);
		startFPS = yo.now + 1000;
		fpsCount = 0;
	}
	#endif

}


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