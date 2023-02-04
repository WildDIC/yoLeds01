#include "config.h"
#include "main.h"
#include "pass.h"
#include "wi-fi.h"

#define WIFI_CHECK_DELAY 1000 * 30
#define WIFI_CONNECT_TIME 1000 * 15
#define WIFI_CONNECT_PRINT 250
#define WIFI_RECONNECT_TIME 1000 * 60 * 60
#define WIFI_CONNECT_TRY 5

clock_t startTimeWF = clock();
clock_t startLastDot = 0; //clock();
clock_t startCheck = 0; // - WIFI_CHECK_DELAY;
byte wifiChecks = 1;
bool wifiConnecting = false;


// wl_status_t wifiConnect(){
	// startTimeWF = clock();
	// Serial.printf( "\n[%d] Connecting to: %s\n", wifiChecks, WIFI_SSID);
    // WiFi.begin(WIFI_SSID, WIFI_PASS);	
	// wifiConnecting = true;

	// while (WiFi.status() != WL_CONNECTED) {
    //   	delay(200);
    //   	Serial.print(".");
	// 	if (  clock() > startTimeWF + WIFI_CONNECT_TIME){
	// 		Serial.print( " Break tmeout!\n"); 	
	// 		// WiFi.disconnect();
	// 		break;
	// 	}
    // }

	// // Serial.println( WiFi.getAutoReconnect());

	// if ( WiFi.status() == WL_CONNECTED){
	// 	wifiChecks = 1;
	// 	Serial.printf( "\nWiFi connected.\nIP address: ");  
    // 	Serial.println( WiFi.localIP()); 
	// } else{
	// 	Serial.printf( "WiFi connect error: %d\n", WiFi.status());
	// }
	
	// return WiFi.status();
// }


void wifiCheckConnect(){
	if ( WiFi.status() == WL_CONNECTED){
		
		if ( wifiConnecting){
			wifiConnecting = false;
			wifiChecks = 0;
			Serial.print( "\nConnection connect.\nIP address: ");
			Serial.println( WiFi.localIP()); 
		}		

		return;
	}

	if ( wifiConnecting){
		
		if ( yo.now > startLastDot){   // + WIFI_CONNECT_PRINT){
			Serial.print( '.');
			startLastDot = yo.now + WIFI_CONNECT_PRINT;
		}

		if ( yo.now > startTimeWF){
			WiFi.disconnect();
			Serial.println( "\nConnection time out error.");
			wifiConnecting = false;
		}

		return;
	}

	if ( WiFi.status() != WL_CONNECTED){	
		
		// Serial.println( WiFi.status());
		// Serial.println( yo.now);
		// Serial.println( startCheck);

		// if ( yo.now > startCheck + WIFI_CHECK_DELAY){			
		// 	Serial.println( yo.now);
		// }

			Serial.printf( "\n[%d] Connecting to: %s ", wifiChecks, WIFI_SSID);
    		WiFi.begin(WIFI_SSID, WIFI_PASS);	
			
			// startCheck = yo.now;
			startTimeWF = yo.now + WIFI_CONNECT_TIME;
			wifiChecks++;
			wifiConnecting = true;
		// }		
	}

	// if ( yo.now - startTimeWF > WIFI_CHECK_DELAY){		
	// 	if ( wifiChecks <= WIFI_CONNECT_TRY){
	// 			if ( WiFi.status() != WL_CONNECTED){
	// 				wifiConnect();
	// 				wifiChecks++;
	// 			}
	// 		// }			
	// 	}		
	// }
}


/* Поднимаем ВайФай и подключаемся к домашней сети.
WIFI_SSID и WIFI_PASS прописываем в файле pass.h 
( создаем сами, ручками, в этой же папке):

const char* WIFI_SSID = "SSIDmy2Gnetwork";
const char* WIFI_PASS = "SecretPassword";

@return int  номер статуса подключения:
    WL_NO_SSID_AVAIL    = 1
    WL_CONNECTED        = 3 - connect
    WL_CONNECT_FAILED   = 4
    WL_CONNECTION_LOST  = 5
    WL_DISCONNECTED     = 6
*/
int wifiStartUP(){
	// wifiConnect();
	wifiCheckConnect();
    // Serial.printf( "\nConnecting to: %s\n", WIFI_SSID);
    // WiFi.begin(WIFI_SSID, WIFI_PASS);
    // while (WiFi.status() != WL_CONNECTED) {
    //   	delay(250);
    //   	Serial.print(".");
    // }
    // Serial.print("\nWiFi connected.\nIP address: ");    
    // Serial.println( WiFi.localIP()); 
    // return WiFi.status();
}
