#ifndef __WIFI_H
#define __WIFI_H

#include <WiFi.h>

wl_status_t wifiConnect();

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
int wifiStartUP();

void wifiCheckConnect();

#endif