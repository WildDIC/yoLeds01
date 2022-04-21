#include <EEPROM.h>

#define EEPROM_SIZE 200

#define EEPROM_ADDR_START 						 0
#define EEPROM_ADDR_INIT 	EEPROM_ADDR_START  + 1		// номер резервной ячейки
#define EEPROM_ADDR_WRITER 	EEPROM_ADDR_START  + 2		// номер резервной ячейки
#define EEPROM_ADDR_PALIND 	EEPROM_ADDR_START  + 3		// ячейка для индекса количества паллитр
#define EEPROM_ADDR_CONFIG 	EEPROM_ADDR_START  + 10
#define EEPROM_ADDR_PALLET 	EEPROM_ADDR_CONFIG + 40 	// начальная запись массива палитр

#define INIT_KEY 50     			// ключ первого запуска. 0-254, на выбор
#define SAVE_DELAY 1000 * 60		// время в миллисекундах на задержку записи в EPPROM

clock_t saveTime = clock();
extern config yo;
int readINT;
byte readBYTE;
byte ind;


/* Сохраняем тупо конфиг yo в ЕЕПРОМ, но не чаще, чем SAVE_DELAY
@param forceSaveEEPROM флаг того, что надо что-то срочно сохранить в ЕЕПРОМ*/
void eepromSave( bool forceSaveEEPROM = false){
		ind = 0;
		EEPROM.get( EEPROM_ADDR_CONFIG +  0, readINT);  if ( readINT  != yo.currentBrightness){ 	EEPROM.put( EEPROM_ADDR_CONFIG +  0, yo.currentBrightness);}
		EEPROM.get( EEPROM_ADDR_CONFIG +  4, readINT);  if ( readINT  != yo.currentTemp){ 			EEPROM.put( EEPROM_ADDR_CONFIG +  4, yo.currentTemp);}
		EEPROM.get( EEPROM_ADDR_CONFIG +  8, readINT);  if ( readINT  != yo.currentSpeed){ 			EEPROM.put( EEPROM_ADDR_CONFIG +  8, yo.currentSpeed);}
		EEPROM.get( EEPROM_ADDR_CONFIG + 12, readINT);  if ( readINT  != yo.currentSaturn){ 		EEPROM.put( EEPROM_ADDR_CONFIG + 12, yo.currentSaturn);}
		EEPROM.get( EEPROM_ADDR_CONFIG + 16, readINT);  if ( readINT  != yo.antiSaturn){ 			EEPROM.put( EEPROM_ADDR_CONFIG + 16, yo.antiSaturn);}
		EEPROM.get( EEPROM_ADDR_CONFIG + 20, readBYTE); if ( readBYTE != yo.ONOFF){ 				EEPROM.put( EEPROM_ADDR_CONFIG + 20, yo.ONOFF);}
		EEPROM.get( EEPROM_ADDR_CONFIG + 21, readINT);  if ( readINT  != yo.lastReceive){ 			EEPROM.put( EEPROM_ADDR_CONFIG + 21, yo.lastReceive);}
		EEPROM.get( EEPROM_ADDR_CONFIG + 25, readINT);  if ( readINT  != yo.lastPressed){ 			EEPROM.put( EEPROM_ADDR_CONFIG + 25, yo.lastPressed);}

		palIter = currentPal.begin();
		for (int i = 0; palIter != currentPal.end(); palIter++, i++) {  
			byte addrIND = EEPROM_ADDR_PALLET + 0 + ( i * 5);
			byte addrPal = EEPROM_ADDR_PALLET + 4 + ( i * 5);

			EEPROM.get( addrIND, readINT);
			EEPROM.get( addrPal, readBYTE);
			
			if ( palIter->first !=0 ){			
				if ( palIter->first != readINT){ 	EEPROM.put( EEPROM_ADDR_PALLET + 0 + ind * 5, palIter->first); }
				if ( palIter->second != readBYTE){	EEPROM.put( EEPROM_ADDR_PALLET + 4 + ind * 5, palIter->second);}
				ind++;
				// Serial.printf( " Save (NOT) palID ( %d) ID = %d ( %d), Pal= %d ( %d).\n", ind, palIter->first, savedINT, palIter->second, savedBYTE);
			}			
    	}

		EEPROM.get( EEPROM_ADDR_WRITER, readBYTE);
		readBYTE++;
		
		EEPROM.put( EEPROM_ADDR_PALIND, ind);
		EEPROM.put( EEPROM_ADDR_WRITER, readBYTE);
		
		EEPROM.commit();
		Serial.printf( "Saved something to EEPROM [%d]: yo = %db, int = %d.\n", readBYTE, sizeof(yo), sizeof(readINT));
}


/* Проверяем необходимость сохранения данных в ЕЕПРОМ и таймер > SAVE_DELAY*/
void eepromSaveHandler(){
	if ( isNeedSaveEEPROM && clock() - saveTime > SAVE_DELAY){
		saveTime = clock();
		isNeedSaveEEPROM = false;
		eepromSave();		
	}
}

/* Читаем данные из ЕЕПРОМ, если первый раз, то пишем туда дефлолтный конфиг.
После чтения, устанавливаем в ленту данные из конфига.*/
void eepromStartUP(){
    EEPROM.begin( EEPROM_SIZE);	
	if ( EEPROM.read( EEPROM_ADDR_INIT) != INIT_KEY) { // первый запуск		
    	Serial.println( "\nFirst run. EEPROM initialization...");	

		EEPROM.write( EEPROM_ADDR_INIT, INIT_KEY);    	// записали ключ
    	EEPROM.write( EEPROM_ADDR_PALIND, 0);    		// записали нулевое количество индексов палитр
    	EEPROM.write( EEPROM_ADDR_WRITER, 0);    		// записали счетчик кол-ва записей
    	
		eepromSave(  true);	
  	}

	EEPROM.get( EEPROM_ADDR_CONFIG +  0, yo.currentBrightness);
	EEPROM.get( EEPROM_ADDR_CONFIG +  4, yo.currentTemp);
	EEPROM.get( EEPROM_ADDR_CONFIG +  8, yo.currentSpeed);
	EEPROM.get( EEPROM_ADDR_CONFIG + 12, yo.currentSaturn);
	EEPROM.get( EEPROM_ADDR_CONFIG + 16, yo.antiSaturn);
	EEPROM.get( EEPROM_ADDR_CONFIG + 20, yo.ONOFF);
	EEPROM.get( EEPROM_ADDR_CONFIG + 21, yo.lastReceive);
	EEPROM.get( EEPROM_ADDR_CONFIG + 25, yo.lastPressed);

	ind = 0;
	EEPROM.get( EEPROM_ADDR_PALIND, ind);
	EEPROM.get( EEPROM_ADDR_WRITER, readBYTE);

	Serial.printf( "\nRead config from EEPROM [%d]: yo = %db, ind = %d.\n", readBYTE, sizeof(yo), ind);

	if ( yo.ONOFF == true){ powerON();}
	setBrightness( yo.currentBrightness);

	for (int i = EEPROM_ADDR_PALLET; i < EEPROM_ADDR_PALLET + ( ind * 5); i+=5) {  // выводим их
		EEPROM.get( i, 		readINT);		// read irdaID
		EEPROM.get( i + 4,  readBYTE);		// read paletteID
		
		if ( readBYTE != 255){
			currentPal[readINT] = readBYTE;
			mButtons[readINT].pollCurrent = readBYTE;
		}	
		// Serial.printf( "Read ( %d) ID = %d, Pal= %d.\n", i, butID, palID);
    }

	irdaServer( yo.lastPressed, 10);
}
