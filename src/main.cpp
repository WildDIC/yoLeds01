#include "config.h"
#include "irda.h"
#include "leds.h"
#include "palettes.h"
#include "animes/_animeCollector.h"

#ifdef EERPROM_ENABLE 
#include "eerpromer.h"
#endif

#ifdef WEB_ENABLE
#include "wi-fi.h"
#include "webServer.h"
#else
#endif

#define IR_DELAY 300
#ifdef FPSCOUNT_ENABLE 
clock_t startFPS = clock() + 1000;
int fpsCount = 0;
#endif

// заглушка на пустую функцию, если/пока нет вебсервеа.
void fooFunc(){}
void fooFunc( const String& name, uint8_t vaue){}
void fooFunc( const String& name, const String& vaue){}

//********************************************************************
// 						SETUP
//*********************************************************************
void setup() {
	yo.now = clock();
	Serial.begin(115200);
	
	irdaStartUP();
	led.startUP();
	paletteStartUP();
	yo.pt2webUpdate 	= &fooFunc;  
	yo.pt2webUnsave 	= &fooFunc;  
	yo.pt2webUpRange	= &fooFunc;  
	yo.pt2webUpRanges	= &fooFunc;  
	yo.pt2webUpColor 	= &fooFunc;

	animmeStartUP();

	#ifdef EERPROM_ENABLE
		eepromStartUP();				
	#endif

	#ifdef WEB_ENABLE
		wifiStartUP();
		webServerStartUP();
	#endif		
}


//********************************************************************
// 						LOOP 		( millis())
//*********************************************************************
void loop() 
{
	yo.now = clock();

	if ( yo.ONOFF && pt2Func)
	{		
		if ( yo.ishifter) 	yo.shift  = led.beat( yo.shiftServ);
		if ( yo.iscandle) 	yo.candle = 255 - qsub8( inoise8( millis() >> 3, millis()), yo.candleServ);

		pt2Func();			// БАТЯ всех функцийю КОРОЛЬ анимаций! ВСЕ РАДИ ЭТОГО!!!

		delay( 1);			
		FastLED.show();
	}
	else delay( 500);   	


	EVERY_N_MILLISECONDS( 250)
	{
		irdaServer( 0, 0);

	#ifdef EERPROM_ENABLE
		eepromSaveHandler();
	#endif

	#ifdef WEB_ENABLE		
		wifiCheckConnect();	
	#endif	
	}

	#ifdef FPSCOUNT_ENABLE
	fpsCount++;
	if ( yo.now >= startFPS)
	{
		Serial.printf( "fps | %d\n", fpsCount);
		startFPS = yo.now + 1000;
		fpsCount = 0;
	}
	#endif

}

