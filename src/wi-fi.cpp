#include "config.h"
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


void wifiCheckConnect(){
	if ( WiFi.status() == WL_CONNECTED){		
		if ( wifiConnecting){
			wifiConnecting = false;
			wifiChecks = 0;
			Serial.print( "\nwifi| Connection connect.\nIP address: ");
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
			Serial.println( "\nwifi| Connection time out error.");
			wifiConnecting = false;
		}
		return;
	}

	if ( WiFi.status() != WL_CONNECTED){	
		
		WiFi.begin(WIFI_SSID, WIFI_PASS);	
		
		startTimeWF = yo.now + WIFI_CONNECT_TIME;
		wifiChecks++;
		wifiConnecting = true;

		Serial.printf( "\nwifi| [%d] Connecting to: %s ", wifiChecks, WIFI_SSID);
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
	wifiCheckConnect();
}

