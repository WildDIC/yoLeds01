#include <EEPROM.h>

#define EEPROM_SIZE 100
#define INIT_ADDR 61  // номер резервной ячейки
#define INIT_KEY 50     // ключ первого запуска. 0-254, на выбор

extern config yo;
// extern void irServer( int codeFromWeb, int webValue);

/* Сохраняем тупо конфиг yo в ЕЕПРОМ*/
void eepromSave(){
	EEPROM.put( 0, yo);
	EEPROM.commit();
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
    	eepromSave();
  	}
	EEPROM.get(0, yo);
	Serial.println( "\nRead config from EEPROM.");

	if ( yo.ONOFF == true){ powerON();}
	setBrightness( yo.currentBrightness);
	irdaServer( yo.lastPressed, 10);
    
    // Serial.println( yo.lastPressed);
	// Serial.println( yo.currentSpeed);
	// Serial.println( yo.currentBrightness);
}
