#include <EEPROM.h>

#define EEPROM_SIZE 200
#define INIT_ADDR EEPROM_SIZE - 1	// номер резервной ячейки
#define INIT_KEY 50     			// ключ первого запуска. 0-254, на выбор
#define SAVE_DELAY 1000 * 30		// время в миллисекундах на задержку записи в EPPROM

clock_t saveTime = clock();
extern config yo;

/* Сохраняем тупо конфиг yo в ЕЕПРОМ, но не чаще, чем SAVE_DELAY
@param forceSaveEEPROM флаг того, что надо что-то срочно сохранить в ЕЕПРОМ*/
void eepromSave( bool forceSaveEEPROM = false){
	if ( forceSaveEEPROM == true || clock() - saveTime > SAVE_DELAY){
		saveTime = clock();

		EEPROM.put( 0, yo);
		EEPROM.commit();

		yoBugN( "-=>> EEPROM Saved something");
	}
}


void eepromRead(){
}

/* Читаем данные из ЕЕПРОМ, если первый раз, то пишем туда дефлолтный конфиг.
После чтения, устанавливаем в ленту данные из конфига.*/
void eepromStartUP(){
    EEPROM.begin(EEPROM_SIZE);	
	if (EEPROM.read(INIT_ADDR) != INIT_KEY) { // первый запуск		
    	EEPROM.write(INIT_ADDR, INIT_KEY);    // записали ключ
		Serial.println( "\nFirst run. EEPROM initialization...");	
    	eepromSave(  true);
  	}

	EEPROM.get(0, yo);
	Serial.println( "\nRead config from EEPROM.");

	if ( yo.ONOFF == true){ powerON();}
	setBrightness( yo.currentBrightness);
	irdaServer( yo.lastPressed, 10);
}
