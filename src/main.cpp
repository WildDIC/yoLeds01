#include "IRrecv.h"
#include <FastLED.h>
#include "waves.h"
// #include <EEPROM.h>

IRrecv irrecv(RECV_PIN);
decode_results results;
void (*pt2Func)();
clock_t startTime = clock();

extern config yo;
extern CHSV yoPalette[NUM_COLORS];


//********************************************************************
// 					SETUP / LOOP
//*********************************************************************
void setup() {
	// EEPROM.begin(EEPROM_SIZE);	
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );  // GRB ordering is typical
	
	fill_gradient( yoPalette, 0, 
		CHSV( 0, 255, 255), NUM_COLORS, 
		CHSV( 32, 255, 255)
	);

	Serial.begin(115200);
	irrecv.enableIRIn();
}

void loop() {
	if (irrecv.decode(&results)) {
		uint32_t resValue = results.value;   // получаем значение ИР-приеника
		
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
	//    Serial.println((uint32_t) (results.value & 0xFFFFFFFF), HEX); // print the second part of the message
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
			case 1270278422: changeBrightness(255); changeSpeed( -90); changeTemperature( TEMP_IND_MAX); changeSaturation( 255); break;
			
			case 1262547214: yo.animationON = false; pt2Func = NULL; ledUP(); 		break;
			case 1262530894: yo.animationON = false; pt2Func = NULL; ledUPWhite();	break;
			
			case 1262529364: yo.animationON = true;  pt2Func = &animWave01; ledOFF(); break;
			case 1262513044: yo.animationON = true;  pt2Func = &animWave02; ledOFF(); break;
			case 1262545684: yo.animationON = true;  pt2Func = &animWave03; ledOFF(); break;
			case 1262492644: yo.animationON = true;  pt2Func = &animWave04; ledOFF(); break;
			case 1262525284: yo.animationON = true;  pt2Func = &animWave05; ledOFF(); break;
			case 1262508964: yo.animationON = true;  pt2Func = &animWave06; ledOFF(); break;
			case 1262541604: yo.animationON = true;  pt2Func = &animWave07; ledOFF(); break;
			case 1262500804: yo.animationON = true;  pt2Func = &animWave08; ledOFF(); break;
			case 1262533444: yo.animationON = true;  pt2Func = &animWave09; ledOFF(); break;
		}
		irrecv.resume();  // Receive the next value
	}    

	if ( yo.animationON && yo.ONOFF){
		pt2Func();
		delay(1);
	} else {
		delay(300);
	}  	
}