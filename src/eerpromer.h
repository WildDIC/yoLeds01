#include <EEPROM.h>

#define EEPROM_ADDR_START 						 100
#define EEPROM_ADDR_INIT 	EEPROM_ADDR_START  + 1		// номер резервной ячейки (byte)
#define EEPROM_ADDR_PALIND 	EEPROM_ADDR_START  + 2		// ячейка для индекса количества паллитр ( byte)
#define EEPROM_ADDR_WRITER 	EEPROM_ADDR_START  + 3		// номер резервной ячейки (int)
#define EEPROM_ADDR_CONFIG 	EEPROM_ADDR_START  + 10
#define EEPROM_ADDR_PALLET 	EEPROM_ADDR_CONFIG + 200 	// начальная запись массива палитр

#define EEPROM_SIZE EEPROM_ADDR_PALLET + 200

int EEPROM_CURRENT_ADDR = EEPROM_ADDR_START;
int EEPROM_CURRENT_BYTE = EEPROM_ADDR_START;
int EEPROM_CURRENT_INT  = EEPROM_ADDR_START;

#define INIT_KEY 50     			// ключ первого запуска. 0-254, на выбор
#define SAVE_DELAY 1000 * 60		// время в миллисекундах на задержку записи в EPPROM

clock_t saveTime = clock();
extern config yo;
int readINT;
byte readBYTE;
byte ind;

void fReadINT(){
	EEPROM_CURRENT_INT = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, readINT);
	EEPROM_CURRENT_ADDR += 4;	
}

void fReadBYTE(){
	EEPROM_CURRENT_BYTE = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, readBYTE);
	EEPROM_CURRENT_ADDR += 1;	
}

void fWriteDATA( int data){  EEPROM.put( EEPROM_CURRENT_INT, data); }
void fWriteDATA( byte data){ EEPROM.put( EEPROM_CURRENT_BYTE, data); }
void fWriteDATA( bool data){ EEPROM.put( EEPROM_CURRENT_BYTE, data); }

void tryToSaveEEPROM( int data){ fReadINT();	if ( readINT  != data){ fWriteDATA( data);}}
void tryToSaveEEPROM( byte data){fReadBYTE();	if ( readBYTE != data){ fWriteDATA( data);}}
void tryToSaveEEPROM( bool data){fReadBYTE();	if ( readBYTE != data){ fWriteDATA( data);}}

/* Сохраняем тупо конфиг yo в ЕЕПРОМ, но не чаще, чем SAVE_DELAY
@param forceSaveEEPROM флаг того, что надо что-то срочно сохранить в ЕЕПРОМ*/
void eepromSave( bool forceSaveEEPROM = false){
		EEPROM_CURRENT_ADDR = EEPROM_ADDR_CONFIG;
		tryToSaveEEPROM( yo.currentBrightness);
		tryToSaveEEPROM( yo.currentTemp);
		tryToSaveEEPROM( yo.currentSpeed);
		tryToSaveEEPROM( yo.currentSaturn);
		tryToSaveEEPROM( yo.antiSaturn);
		tryToSaveEEPROM( yo.ONOFF);
		tryToSaveEEPROM( yo.lastReceive);
		tryToSaveEEPROM( yo.lastPressed);
		
		tryToSaveEEPROM( yo.c1.r);
		tryToSaveEEPROM( yo.c1.g);
		tryToSaveEEPROM( yo.c1.b);
		tryToSaveEEPROM( yo.c2.r);
		tryToSaveEEPROM( yo.c2.g);
		tryToSaveEEPROM( yo.c2.b);
		tryToSaveEEPROM( yo.c3.r);
		tryToSaveEEPROM( yo.c3.g);
		tryToSaveEEPROM( yo.c3.b);

		ind = 0;
		palIter = currentPal.begin();
		EEPROM_CURRENT_ADDR = EEPROM_ADDR_PALLET;		
		for (int i = 0; palIter != currentPal.end(); palIter++, i++) {  
			fReadINT();
			fReadBYTE();
			
			if ( palIter->first != 0){
				if ( palIter->first  != readINT){  fWriteDATA( palIter->first); }
				if ( palIter->second != readBYTE){ fWriteDATA( palIter->second);}
				ind++;
				// Serial.printf( "%d Save (NOT) ind = %d, ID = %d ( %d), Pal= %d ( %d).\n", EEPROM_CURRENT_ADDR, ind, palIter->first, readINT, palIter->second, readBYTE);
			}			
    	}

		EEPROM.get( EEPROM_ADDR_WRITER, readINT);
		readINT++;
		
		EEPROM.put( EEPROM_ADDR_PALIND, ind);
		EEPROM.put( EEPROM_ADDR_WRITER, readINT);
		
		EEPROM.commit();
		Serial.printf( "Saved something to EEPROM [%d]: yo = %db. ind=%d\n", readINT, sizeof(yo), ind);
}


/* Проверяем необходимость сохранения данных в ЕЕПРОМ и таймер > SAVE_DELAY*/
void eepromSaveHandler(){
	if ( yo.isNeedSaveEEPROM && yo.now - saveTime > SAVE_DELAY){
		saveTime = yo.now;
		yo.isNeedSaveEEPROM = false;
		eepromSave();		
		yo.pt2webUnsave();
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

	EEPROM_CURRENT_ADDR = EEPROM_ADDR_CONFIG;
	fReadINT();  yo.currentBrightness 	= readINT;
	fReadINT();  yo.currentTemp 		= readINT;
	fReadINT();  yo.currentSpeed 		= readINT;
	fReadINT();  yo.currentSaturn 		= readINT;
	fReadINT();  yo.antiSaturn 			= readINT;
	fReadBYTE(); yo.ONOFF 				= readBYTE;
	fReadINT();  yo.lastReceive 		= readINT;
	fReadINT();  yo.lastPressed 		= readINT;

	fReadBYTE(); yo.c1.r = readBYTE;
	fReadBYTE(); yo.c1.g = readBYTE;
	fReadBYTE(); yo.c1.b = readBYTE;
	fReadBYTE(); yo.c2.r = readBYTE;
	fReadBYTE(); yo.c2.g = readBYTE;
	fReadBYTE(); yo.c2.b = readBYTE;
	fReadBYTE(); yo.c3.r = readBYTE;
	fReadBYTE(); yo.c3.g = readBYTE;
	fReadBYTE(); yo.c3.b = readBYTE;

	EEPROM.get( EEPROM_ADDR_PALIND, ind);
	for (int i = EEPROM_ADDR_PALLET; i < EEPROM_ADDR_PALLET + ( ind * 5); i+=5) {  // выводим их

		EEPROM.get( i, 		readINT);		// read irdaID
		EEPROM.get( i + 4,  readBYTE);		// read paletteID
		
		if ( readBYTE != 255 && readINT > 0){
			currentPal[readINT] = readBYTE;
			mButtons[readINT].pollCurrent = readBYTE;
		}	
		// Serial.printf( "%d Read ( %d) ID = %d, Pal= %d.\n", ind, i, readINT, readBYTE);
    }

	EEPROM.get( EEPROM_ADDR_WRITER, readINT);
	Serial.printf( "\nRead config from EEPROM [%d times]: yo base size = %db ( writen size = %db), pollitres write ind = %d.\n", readINT, sizeof(yo), EEPROM_CURRENT_ADDR - 0, ind);

	if ( yo.ONOFF == true){ powerON();}
	setBrightness( yo.currentBrightness);
	irdaServer( yo.lastPressed, 10);
}
