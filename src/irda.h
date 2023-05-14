#ifndef __IRDA_H
#define __IRDA_H

// мапа нескольких кодов пультов на один код действия
using keyMaps = std::map<unsigned int, int>;

extern keyMaps keyCodes;

/* Поднимаем ИР-сервер*/
void irdaStartUP();

uint8_t irdaCheckIRcode();

#endif