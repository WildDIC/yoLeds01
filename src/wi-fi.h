#include <WiFi.h>
#include "pass.h"

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
    Serial.printf( "\nConnecting to: %s\n", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      	delay(250);
      	Serial.print(".");
    }
    Serial.print("\nWiFi connected.\nIP address: ");    
    Serial.println( WiFi.localIP()); 
    return WiFi.status();
}