#include "IRrecv.h"
#include <FastLED.h>
#include "main.h"
#include "leds.h"
#include "waves.h"

#ifdef WEB_ENABLE
#include "wi-fi.h"
#include "webServer.h"
#else
#endif
// #include <EEPROM.h>

IRrecv irrecv(RECV_PIN);
decode_results results;
clock_t startTime = clock();

extern config yo;
extern CHSV yoPalette[NUM_COLORS];

//********************************************************************
// 					SETUP / LOOP
//*********************************************************************
void setup() {
	Serial.begin(115200);
	// EEPROM.begin(EEPROM_SIZE);	
	
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );  // GRB ordering is typical
	fill_solid( leds, NUM_LEDS, CRGB::Black); 
	FastLED.show();

	fill_gradient( yoPalette, 0, 
		CHSV( 0, 255, 255), NUM_COLORS, 
		CHSV( 32, 255, 255)
	);
	
	irrecv.enableIRIn();
	
	#ifdef WEB_ENABLE
		wifiConnect();
		webServerStart();
	#endif
}

void irServer( int codeFromWeb, int webValue){
	uint32_t resValue = 10;

	if (irrecv.decode(&results)) {
		resValue = results.value;   // получаем значение ИР-приеника
		
		if ( resValue == 4294967295){
			if ( clock() - startTime > 300){
				resValue = yo.lastReceive;
				startTime = clock();
			}			
		} else{
			yo.lastReceive = resValue;
			Serial.printf( "IR receive: %d\n", resValue);
			startTime = clock();
		}
		irrecv.resume();  // Receive the next value		
	}
	
	if ( codeFromWeb != 10){
		resValue = codeFromWeb;
	}

	// Serial.printf( "Code from web: %d = (%d) - [%d]\n", codeFromWeb, webValue, resValue);
	if ( resValue !=10){		
		// Serial.println( "Case");

		switch (resValue){
			case 1270235582: changeBrightness( 15); 	break;
			case 1270268222: changeBrightness(-15); 	break;
			case 1270219007: changeTemperature(  1); 	break;
			case 1270251647: changeTemperature( -1); 	break;
			case 1270235327: changeSpeed(-2); 			break;
			case 1270267967: changeSpeed( 2); 			break;
			case 551502015:  changeSaturation( 10); 	break;
			case 551534655:  changeSaturation(-10); 	break;
			case 551489775:  powerONOFF(); 				break; 					 // вкл/выкл
			case 1270278422: ledReset(); break;
			
			case 1066677700:  setBrightness( webValue); 	break;
			case 1066677701:  setSaturation( webValue); 	break;
			case 1066677702:  setTemperature( webValue); 	break;
			case 1066677703:  setSpeed( webValue); 			break;

			case 1262547214: yo.animationON = false; pt2Func = NULL; yo.lastPressed = resValue; ledUP();		break;
			case 1262530894: yo.animationON = false; pt2Func = NULL; yo.lastPressed = resValue; ledUPWhite();	break;
			
			case 1262529364: yo.animationON = true;  pt2Func = &animWave01; ledOFF( resValue); break;
			case 1262513044: yo.animationON = true;  pt2Func = &animWave02; ledOFF( resValue); break;
			case 1262545684: yo.animationON = true;  pt2Func = &animWave03; ledOFF( resValue); break;
			case 1262492644: yo.animationON = true;  pt2Func = &animWave04; ledOFF( resValue); break;
			case 1262525284: yo.animationON = true;  pt2Func = &animWave05; ledOFF( resValue); break;
			case 1262508964: yo.animationON = true;  pt2Func = &animWave06; ledOFF( resValue); break;
			case 1262541604: yo.animationON = true;  pt2Func = &animWave07; ledOFF( resValue); break;
			case 1262500804: yo.animationON = true;  pt2Func = &animWave08; ledOFF( resValue); break;
			case 1262533444: yo.animationON = true;  pt2Func = &animWave09; ledOFF( resValue); break;
		}		
	}   
}

void loop() {
	irServer( 10, 10);

	if ( yo.animationON && yo.ONOFF && pt2Func){
		pt2Func();
		delay(1);
	} else {
		delay( 500);
	}  	
}