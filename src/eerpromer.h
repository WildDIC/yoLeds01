#ifndef __EEPROM_H
#define __EEPROM_H
// #include <EEPROM.h>
// #include "config.h"

/* Сохраняем тупо конфиг yo в ЕЕПРОМ, но не чаще, чем SAVE_DELAY
@param forceSaveEEPROM флаг того, что надо что-то срочно сохранить в ЕЕПРОМ*/
void eepromSave( bool forceSaveEEPROM);

/* Проверяем необходимость сохранения данных в ЕЕПРОМ и таймер > SAVE_DELAY*/
void eepromSaveHandler();

/* Читаем данные из ЕЕПРОМ, если первый раз, то пишем туда дефлолтный конфиг.
После чтения, устанавливаем в ленту данные из конфига.*/
void eepromStartUP();

/*Сообщаем о желании что-то сохранить после внесенных изменений с сайта или с пульта.
Производится с откладываемой задержкой в EEPROM_SAVE_TIME секунд*/
void requestSave();

#endif