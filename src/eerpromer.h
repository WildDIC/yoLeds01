#include <EEPROM.h>

#define EEPROM_SIZE 100
#define INIT_ADDR 61  // номер резервной ячейки
#define INIT_KEY 50     // ключ первого запуска. 0-254, на выбор

extern config yo;


void saveEEPROM(){
	EEPROM.put( 0, yo);
	EEPROM.commit();
}

void readErrprom(){

}

void onLoadInit(){
    EEPROM.begin(EEPROM_SIZE);	
	if (EEPROM.read(INIT_ADDR) != INIT_KEY) { // первый запуск
		Serial.println( "First run. EEPROM initialization...");
    	EEPROM.write(INIT_ADDR, INIT_KEY);    // записали ключ		
    	saveEEPROM();
  	}
	EEPROM.get(0, yo);
    
    // Serial.println( yo.lastPressed);
	// Serial.println( yo.currentSpeed);
	// Serial.println( yo.currentBrightness);
}
