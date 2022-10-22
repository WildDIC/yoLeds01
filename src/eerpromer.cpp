#include <EEPROM.h>
#include "config.h"
#include "irda.h"
#include "leds.h"

#define EEPROM_ADDR_START 						 100
#define EEPROM_ADDR_INIT 	EEPROM_ADDR_START  + 1		// номер резервной ячейки (byte)
#define EEPROM_ADDR_PALIND 	EEPROM_ADDR_START  + 2		// ячейка для индекса количества паллитр ( byte)
#define EEPROM_ADDR_WRITER 	EEPROM_ADDR_START  + 3		// номер резервной ячейки (int)
#define EEPROM_ADDR_CONFIG 	EEPROM_ADDR_START  + 10
#define EEPROM_ADDR_PALLET 	EEPROM_ADDR_CONFIG + 50 	// начальная запись массива палитр ( резерв под конфиг)

#define EEPROM_SAVE_TIME 10 * 1000						// задержка на сохранение после изменения данных
#define EEPROM_WAVE_SIZE 30								// предположительный размер/резерв сохранения настроек Вавы 
#define EEPROM_SIZE EEPROM_ADDR_PALLET + ( EEPROM_WAVE_SIZE * 25)

int EEPROM_CURRENT_ADDR = EEPROM_ADDR_START;			// указывает на последне считанную ячейку памяти функциями фРидХХХХ
int EEPROM_CURRENT_BYTE = EEPROM_ADDR_START;
int EEPROM_CURRENT_INT  = EEPROM_ADDR_START;

#define INIT_KEY 50     			// ключ первого запуска. 0-254, на выбор

int readINT;
byte readBYTE;
bool readBOOL;

byte ind;


int fReadINT(){
	EEPROM_CURRENT_INT = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, readINT);
	EEPROM_CURRENT_ADDR += 4;	
	return readINT;
}

byte fReadBYTE(){
	EEPROM_CURRENT_BYTE = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, readBYTE);
	EEPROM_CURRENT_ADDR += 1;	
	return readBYTE;
}

bool fReadBOOL(){
	EEPROM_CURRENT_BYTE = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, readBOOL);
	EEPROM_CURRENT_ADDR += 1;	
	return readBOOL;
}

void fWriteDATA( int data){  EEPROM.put( EEPROM_CURRENT_INT, data); }
void fWriteDATA( byte data){ EEPROM.put( EEPROM_CURRENT_BYTE, data); }
void fWriteDATA( bool data){ EEPROM.put( EEPROM_CURRENT_BYTE, data); }

void saveEEPROM( int data) { if ( fReadINT()  != data){ fWriteDATA( data);}}
void saveEEPROM( byte data){ if ( fReadBYTE() != data){ fWriteDATA( data);}}
void saveEEPROM( bool data){ if ( fReadBOOL() != data){ fWriteDATA( data);}}

/* Сохраняем тупо конфиг yo в ЕЕПРОМ, но не чаще, чем SAVE_DELAY
@param forceSaveEEPROM флаг того, что надо что-то срочно сохранить в ЕЕПРОМ*/
void eepromSave( bool forceSaveEEPROM = false){		
		yoBugN( "-=> Saver start");
		EEPROM_CURRENT_ADDR = EEPROM_ADDR_CONFIG;

		saveEEPROM( yo.currentBrightness);
		saveEEPROM( yo.currentTemp);
		saveEEPROM( yo.currentSpeed);
		saveEEPROM( yo.currentSaturn);
		saveEEPROM( yo.antiSaturn);
		saveEEPROM( yo.ONOFF);
		saveEEPROM( yo.lastReceive);
		saveEEPROM( yo.lastPressed);
		
		saveEEPROM( yo.c1.r); 	saveEEPROM( yo.c1.g); 	saveEEPROM( yo.c1.b);
		saveEEPROM( yo.c2.r);	saveEEPROM( yo.c2.g);	saveEEPROM( yo.c2.b);
		saveEEPROM( yo.c3.r);	saveEEPROM( yo.c3.g);	saveEEPROM( yo.c3.b);
		saveEEPROM( yo.AUX010);	saveEEPROM( yo.AUX100);	saveEEPROM( yo.AUX255);

		// Serial.printf( "Save AUX010 = %d, AUX100 = %d\n", yo.AUX010, yo.AUX100);

		ind = 0;
		mbIter = mWaves.begin();
		for (int i = 0; mbIter != mWaves.end(); mbIter++, i++) {  
			
			if ( mbIter->second.typeWeb == 1){
				
				EEPROM_CURRENT_ADDR = EEPROM_ADDR_PALLET + ( EEPROM_WAVE_SIZE * ind);		

				saveEEPROM( mbIter->first);
				saveEEPROM( mbIter->second.pollCurrent);
				saveEEPROM( mbIter->second.bright);				
				saveEEPROM( mbIter->second.speed);
				saveEEPROM( mbIter->second.aux010);
				saveEEPROM( mbIter->second.aux100);
				saveEEPROM( mbIter->second.aux255);
				saveEEPROM( mbIter->second.temp);
				saveEEPROM( mbIter->second.saturn);
				saveEEPROM( mbIter->second.c1.r);		saveEEPROM( mbIter->second.c1.g);		saveEEPROM( mbIter->second.c1.b);
				saveEEPROM( mbIter->second.c2.r);		saveEEPROM( mbIter->second.c2.g);		saveEEPROM( mbIter->second.c2.b);
				saveEEPROM( mbIter->second.c3.r);		saveEEPROM( mbIter->second.c3.g);		saveEEPROM( mbIter->second.c3.b);
				
				ind++;
		// 		// Serial.printf( "%d Save (NOT) ind = %d, ID = %d ( %d), Pal= %d ( %d).\n", EEPROM_CURRENT_ADDR, ind, palIter->first, readINT, palIter->second, readBYTE);
				// Serial.printf( "%d Save ind=%d, ID=%d Speed=%d, Bri=%d Pal=%d AUX010=%d.\n", EEPROM_CURRENT_ADDR, ind, mbIter->first, mbIter->second.speed, mbIter->second.bright, mbIter->second.pollCurrent, mbIter->second.aux010);
			}	
    	}

		EEPROM.get( EEPROM_ADDR_WRITER, readINT);
		readINT++;
		
		EEPROM.put( EEPROM_ADDR_PALIND, ind);
		EEPROM.put( EEPROM_ADDR_WRITER, readINT);
		
		EEPROM.commit();
		Serial.printf( "Saved something to EEPROM [%d]: yo = %db. ind=%d\n", readINT, sizeof(yo), ind);
		yoBugN( "-=> Saver end");
}


/* Проверяем необходимость сохранения данных в ЕЕПРОМ и таймер > SAVE_DELAY*/
void eepromSaveHandler(){
	if ( yo.isNeedSaveEEPROM == true && yo.now >= yo.EEPROMsaveTime){
		yoBugN( "-=> SaveHandles");
		eepromSave();		
		yo.pt2webUnsave();
		yo.isNeedSaveEEPROM = false;
	}
}

/*Принимаем запрос на сохранение yo.isNeedSaveEEPROM.
Откладываем таймер SAVE_DELAY секунд при каждом запросе*/
void requestSave(){
	yo.EEPROMsaveTime = yo.now + EEPROM_SAVE_TIME;
	yo.isNeedSaveEEPROM = true;
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

	EEPROM_CURRENT_ADDR 	= EEPROM_ADDR_CONFIG;
	yo.currentBrightness 	= fReadBYTE();
	yo.currentTemp 			= fReadBYTE();
	yo.currentSpeed 		= fReadBYTE();
	yo.currentSaturn		= fReadBYTE();
	yo.antiSaturn 			= fReadBYTE();
	yo.ONOFF 				= fReadBOOL();
	yo.lastReceive 			= fReadINT();
	yo.lastPressed 			= fReadINT();

	yo.c1.r = fReadBYTE(); 		yo.c1.g = fReadBYTE(); 		yo.c1.b = fReadBYTE();
	yo.c2.r = fReadBYTE();		yo.c2.g = fReadBYTE();		yo.c2.b = fReadBYTE();
	yo.c3.r = fReadBYTE();		yo.c3.g = fReadBYTE();		yo.c3.b = fReadBYTE();
	yo.AUX010 = fReadBYTE();	yo.AUX100 = fReadBYTE();	yo.AUX255 = fReadBYTE();


	EEPROM.get( EEPROM_ADDR_PALIND, ind);				// читаем индекс: количкство сохраненных элементов currentPal

	for (int i = 0; i < ind; i++) { 

		EEPROM_CURRENT_ADDR = EEPROM_ADDR_PALLET + ( EEPROM_WAVE_SIZE * i);			// перекидываем чтение данных на аждрксс с палитрами

		fReadINT();		// read irdaID
		fReadBYTE();	// read paletteID
		
		int waveID = readINT;
		
		if ( readBYTE != 255 && waveID > 0){

			mWaves[waveID].pollCurrent = readBYTE;
			mWaves[waveID].bright 	= fReadBYTE();
			mWaves[waveID].speed 	= fReadBYTE();
			mWaves[waveID].aux010 	= fReadBYTE();
			mWaves[waveID].aux100 	= fReadBYTE();
			mWaves[waveID].aux255 	= fReadBYTE();
			mWaves[waveID].temp 	= fReadBYTE();
			mWaves[waveID].saturn 	= fReadBYTE();
			mWaves[waveID].c1.r 	= fReadBYTE(); 		mWaves[waveID].c1.g = fReadBYTE(); 		mWaves[waveID].c1.b = fReadBYTE();
			mWaves[waveID].c2.r 	= fReadBYTE();		mWaves[waveID].c2.g = fReadBYTE();		mWaves[waveID].c2.b = fReadBYTE();
			mWaves[waveID].c3.r 	= fReadBYTE();		mWaves[waveID].c3.g = fReadBYTE();		mWaves[waveID].c3.b = fReadBYTE();
			// mWaves[waveID].temp = TEMP_IND_MAX;
			// mWaves[waveID].saturn = 100;
		}	
		else{
			mWaves[waveID].pollCurrent = mWaves[waveID].pollDefault; 		// default vars
			mWaves[waveID].bright = 125;
			mWaves[waveID].temp = TEMP_IND_MAX;
			mWaves[waveID].saturn = 100;
			mWaves[waveID].speed = 10;
			mWaves[waveID].aux010 = 5;
			mWaves[waveID].aux100 = 50;
			mWaves[waveID].aux255 = 128;
		}
		// Serial.printf( "id=%d, aux010=%d, speed=%d, bri=%d, polcur=%d\n", waveID, mWaves[waveID].aux010, mWaves[waveID].speed, mWaves[waveID].bright, mWaves[waveID].pollCurrent);
    }

	EEPROM.get( EEPROM_ADDR_WRITER, readINT);
	Serial.printf( "\nRead config from EEPROM [%d times]: yo base size = %db ( writen size = %db), pollitres write ind = %d.\n", readINT, sizeof(yo), EEPROM_CURRENT_ADDR - 0, ind);
	// Serial.printf( "Read AUX010 = %d, AUX100 = %d\n", yo.AUX010, yo.AUX100);

	if ( yo.ONOFF == true){ powerON();}
	setBrightness( yo.currentBrightness);
	irdaServer( yo.lastPressed, 0);
}
