#include <WiFi.h>
#include "pass.h"

/* Поднимаем ВайФай и подключаемся к домашней сети.
WIFI_SSID и WIFI_PASS прописываем в файле pass.h:

const char* WIFI_SSID = "";
const char* WIFI_PASS = "";
*/
void wifiConnect(){
    Serial.printf( "\nConnect to: %s\n", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      	delay(500);
      	Serial.print(".");
    }
    Serial.print("\nWiFi connected.\nIP address: ");
    Serial.println( WiFi.localIP()); 
}