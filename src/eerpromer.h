#include <EEPROM.h>

#define EEPROM_SIZE 100
#define INIT_ADDR 61  // номер резервной ячейки
#define INIT_KEY 50     // ключ первого запуска. 0-254, на выбор

extern config yo;
extern void irServer( int codeFromWeb, int webValue);

void saveEEPROM(){
	EEPROM.put( 0, yo);
	EEPROM.commit();
}

void readErrprom(){

}

void onLoadInit(){
    EEPROM.begin(EEPROM_SIZE);	
	if (EEPROM.read(INIT_ADDR) != INIT_KEY) { // первый запуск		
    	EEPROM.write(INIT_ADDR, INIT_KEY);    // записали ключ
		Serial.println( "First run. EEPROM initialization...");		
    	saveEEPROM();
  	}
	EEPROM.get(0, yo);

	if ( yo.ONOFF == true){ powerON();}
	setBrightness( yo.currentBrightness);
	irdaServer( yo.lastPressed, 10);
    
    // Serial.println( yo.lastPressed);
	// Serial.println( yo.currentSpeed);
	// Serial.println( yo.currentBrightness);
}
