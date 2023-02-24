#include <EEPROM.h>
#include "config.h"
#include "irda.h"
#include "leds.h"

#ifdef JSON_ENABLE
// #include "json_save.h"
#endif

#define EEPROM_ADDR_START 						 100
#define EEPROM_ADDR_INIT 	EEPROM_ADDR_START  + 1		// номер резервной ячейки (byte)
#define EEPROM_ADDR_PALIND 	EEPROM_ADDR_START  + 2		// ячейка для индекса количества паллитр ( byte)
#define EEPROM_ADDR_WRITER 	EEPROM_ADDR_START  + 3		// номер резервной ячейки (int)
#define EEPROM_ADDR_CONFIG 	EEPROM_ADDR_START  + 10
#define EEPROM_ADDR_PALLET 	EEPROM_ADDR_CONFIG + 50 	// начальная запись массива палитр ( резерв под конфиг)

#define EEPROM_SAVE_TIME 3 * 60 * 1000					// задержка на сохранение после изменения данных
#define EEPROM_WAVE_SIZE 30								// предположительный размер/резерв сохранения настроек Вавы 
#define EEPROM_SIZE EEPROM_ADDR_PALLET + ( EEPROM_WAVE_SIZE * 25)

int EEPROM_CURRENT_ADDR = EEPROM_ADDR_START;			// указывает на последне считанную ячейку памяти функциями фРидХХХХ
int EEPROM_CURRENT_BYTE = EEPROM_ADDR_START;
int EEPROM_CURRENT_INT  = EEPROM_ADDR_START;

#define INIT_KEY 50     			// ключ первого запуска. 0-254, на выбор

int readINT;
uint16_t read16t;
byte readBYTE;
bool readBOOL;
bool forceSave = false;
byte ind;


uint16_t fRead16t()
{
	EEPROM_CURRENT_INT = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, read16t);
	EEPROM_CURRENT_ADDR += 2;	
	return read16t;
}

int fReadINT()
{
	EEPROM_CURRENT_INT = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, readINT);
	EEPROM_CURRENT_ADDR += 4;	
	return readINT;
}

byte fReadBYTE()
{
	EEPROM_CURRENT_BYTE = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, readBYTE);
	EEPROM_CURRENT_ADDR += 1;	
	return readBYTE;
}

bool fReadBOOL()
{
	EEPROM_CURRENT_BYTE = EEPROM_CURRENT_ADDR;
	EEPROM.get( EEPROM_CURRENT_ADDR, readBOOL);
	EEPROM_CURRENT_ADDR += 1;	
	return readBOOL;
}



void fWriteDATA( uint16_t data)	{ EEPROM.put( EEPROM_CURRENT_INT, data); }
void fWriteDATA( int data)		{ EEPROM.put( EEPROM_CURRENT_INT, data); }
void fWriteDATA( byte data)		{ EEPROM.put( EEPROM_CURRENT_BYTE, data); }
void fWriteDATA( bool data)		{ EEPROM.put( EEPROM_CURRENT_BYTE, data); }

void saveEEPROM( uint16_t data) { if ( fRead16t()  != data){ fWriteDATA( data);}}
void saveEEPROM( int data) 		{ if ( fReadINT()  != data){ fWriteDATA( data);}}
void saveEEPROM( byte data)		{ if ( fReadBYTE() != data){ fWriteDATA( data);}}
void saveEEPROM( bool data)		{ if ( fReadBOOL() != data){ fWriteDATA( data);}}



void eepromSaveWave( bool forceSaveEEPROM = false)
{
	ind = 0;
	mbIter = mWaves.begin();

	for (int i = 0; mbIter != mWaves.end(); mbIter++, i++) 
	{  			
		if ( mbIter->second.typeWeb == 1)			// если ваве-кнопка	
		{												
			if ( mbIter->second.needSave == true || forceSaveEEPROM == true)   	// если надо сохранить там что-то, отдельно из-за ind++ 					
			{				
				EEPROM_CURRENT_ADDR = EEPROM_ADDR_PALLET + ( EEPROM_WAVE_SIZE * ind);		

				saveEEPROM( mbIter->first);
				saveEEPROM( ++mbIter->second.savno);
				saveEEPROM( mbIter->second.speed);
				saveEEPROM( mbIter->second.aux010);
				saveEEPROM( mbIter->second.aux100);
				saveEEPROM( mbIter->second.aux255);
				saveEEPROM( mbIter->second.temp);
				saveEEPROM( mbIter->second.saturn);
				saveEEPROM( mbIter->second.c1.r);		saveEEPROM( mbIter->second.c1.g);		saveEEPROM( mbIter->second.c1.b);
				saveEEPROM( mbIter->second.c2.r);		saveEEPROM( mbIter->second.c2.g);		saveEEPROM( mbIter->second.c2.b);
				saveEEPROM( mbIter->second.c3.r);		saveEEPROM( mbIter->second.c3.g);		saveEEPROM( mbIter->second.c3.b);
				
				saveEEPROM( mbIter->second.indForWeb);   // пишем реальный индекс вавы из мапы для контроля положения при считывании
				saveEEPROM( mbIter->second.pollCurrent);
				saveEEPROM( mbIter->second.bright);				

				mbIter->second.needSave = false;

				Serial.printf( "-=> %d Save [savno=%d] ind=%d, ID=%d INDforWeb=%d, Bri=%d Pal=%d AUX010=%d [", 
									EEPROM_CURRENT_ADDR, 
													mbIter->second.savno,
															ind, 
																	mbIter->first, 
																				mbIter->second.indForWeb, 
																						mbIter->second.bright, 
																								mbIter->second.pollCurrent, 
																										mbIter->second.aux010);
				Serial.print( mbIter->second.name);
				Serial.println( "].");
			}							
			ind++;
			// Serial.printf( "%d Save (NOT) ind = %d, ID = %d ( %d), Pal= %d ( %d).\n", EEPROM_CURRENT_ADDR, ind, palIter->first, readINT, palIter->second, readBYTE);
		}	
	}
	EEPROM.put( EEPROM_ADDR_PALIND, ind);		// количество записанных записей ( конец для цикла чтения при закладке)
	EEPROM.commit();
}


void eepromLoadWave()
{
	forceSave = false;
	EEPROM.get( EEPROM_ADDR_PALIND, ind);				// читаем индекс: количкство сохраненных элементов currentPal

	for (int i = 0; i < ind; i++) 
	{ 		
		EEPROM_CURRENT_ADDR = EEPROM_ADDR_PALLET + ( EEPROM_WAVE_SIZE * i);			// перекидываем чтение данных на аждрксс с палитрами
		
		int waveID 		= fReadINT();		// read irdaID		
		/*
			читаем Save No, если оно равно 0, то считывается первый раз, штатный случай, 
			есть какое-то значение, то это дубль строки и переписываем ее, 
			если оно больше по номеру или пропускаем, если Савно меньше ( писали давно).
			SavNo инкрементится при записи вавы.
		*/ 
		uint16_t savno  = fRead16t();
		
		if ( waveID > 0 && savno > mWaves[waveID].savno)
		{
			mWaves[waveID].savno    = savno;
			mWaves[waveID].speed 	= fReadBYTE();
			mWaves[waveID].aux010 	= fReadBYTE();
			mWaves[waveID].aux100 	= fReadBYTE();
			mWaves[waveID].aux255 	= fReadBYTE();
			mWaves[waveID].temp 	= fReadBYTE();
			mWaves[waveID].saturn 	= fReadBYTE();
			mWaves[waveID].c1.r 	= fReadBYTE(); 		mWaves[waveID].c1.g = fReadBYTE(); 		mWaves[waveID].c1.b = fReadBYTE();
			mWaves[waveID].c2.r 	= fReadBYTE();		mWaves[waveID].c2.g = fReadBYTE();		mWaves[waveID].c2.b = fReadBYTE();
			mWaves[waveID].c3.r 	= fReadBYTE();		mWaves[waveID].c3.g = fReadBYTE();		mWaves[waveID].c3.b = fReadBYTE();

			uint8_t placed 			= fReadBYTE();     // читаем реальный индекс вавы. записанный при сохранении волн ( переменная пока для подстаховки)
			mWaves[waveID].pollCurrent = fReadBYTE();					// read paletteID		
			mWaves[waveID].bright 	= fReadBYTE();

			if ( placed != mWaves[waveID].indForWeb) 
			{ 	
				Serial.printf( "-=> Bad 'placed', need total resave [savno=%d (%d)]. WaveID = %d, INDforWeb = %d ( %d) [", mWaves[waveID].savno, savno, waveID, mWaves[waveID].indForWeb, placed);
				Serial.print( mWaves[waveID].name);
				Serial.println( "].");

				forceSave = true; 
			}			
		}	
    }
}


/* Сохраняем тупо конфиг yo в ЕЕПРОМ, но не чаще, чем SAVE_DELAY
@param forceSaveEEPROM флаг того, что надо что-то срочно сохранить в ЕЕПРОМ*/
void eepromSaveData( bool forceSaveEEPROM = false)
{		
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

		eepromSaveWave( forceSaveEEPROM);
		
		EEPROM.get( EEPROM_ADDR_WRITER, readINT);   // щёчик записей, чиста поржать над числом
		EEPROM.put( EEPROM_ADDR_WRITER, ++readINT);		
		EEPROM.commit();

		Serial.printf( "Saved something to EEPROM [%d]: yo = %db\n", readINT, sizeof(yo));
		yoBugN( "-=> Saver end");		
}


/*Загружаем конфиг из еепромы, вэйвы ложим из ддругой процеуры*/
void eepromLoadData()
{
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
}



/* Проверяем необходимость сохранения данных в ЕЕПРОМ и таймер > SAVE_DELAY*/
void eepromSaveHandler()
{
	if ( yo.isNeedSaveEEPROM == true && yo.now >= yo.EEPROMsaveTime)
	{
		yoBugN( "-=> SaveHandles");
		eepromSaveData();

#ifdef JSON_ENABLE				
		jsonSaveWave();
#endif
		yo.isNeedSaveEEPROM = false;
		yo.pt2webUnsave();
	}
}

/*Принимаем запрос на сохранение yo.isNeedSaveEEPROM.
Откладываем таймер SAVE_DELAY секунд при каждом запросе
Выставляем флаг необходимости что-то сохранить, в цикле при сохранени обнуляется*/
void requestSave()
{
	yo.EEPROMsaveTime = yo.now + EEPROM_SAVE_TIME;
	yo.isNeedSaveEEPROM = true;
	mWaves[yo.lastPressed].needSave = true;

#ifdef JSON_ENABLE
	mWaves[yo.lastPressed].needSaveJSON = true;
#endif
	// Serial.print( "-=> need save: ");
	// Serial.println( mWaves[yo.lastPressed].name);

	yoBug( "-=> need save: ");
	yoBugN( mWaves[yo.lastPressed].name);
}


/* Читаем данные из ЕЕПРОМ, если первый раз, то пишем туда дефлолтный конфиг.
После чтения, устанавливаем в ленту данные из конфига.*/
void eepromStartUP()
{
    EEPROM.begin( EEPROM_SIZE);	

	if ( EEPROM.read( EEPROM_ADDR_INIT) != INIT_KEY)  	// первый запуск		
	{ 
    	Serial.println( "\nFirst run. EEPROM initialization...");	

		EEPROM.write( EEPROM_ADDR_INIT, INIT_KEY);    	// записали ключ
    	EEPROM.write( EEPROM_ADDR_PALIND, 0);    		// записали нулевое количество индексов палитр
    	EEPROM.write( EEPROM_ADDR_WRITER, 0);    		// записали счетчик кол-ва записей
    	
		eepromSaveData( true);	
		eepromSaveWave( true);
  	}

	eepromLoadData();
	eepromLoadWave();	
	
	if ( forceSave)  // полный пересейв, если что-то пошло не так при считавынии ( ИД считанной строки не равно ИД по порядку) 
	{ 
		eepromSaveWave( true);
	}   

#ifdef JSON_ENABLE
	jsonStartUP();
	jsonLoadWave();
#endif

	EEPROM.get( EEPROM_ADDR_WRITER, readINT);
	Serial.printf( "\nRead config from EEPROM [%d times]: yo base size = %db ( writen size = %db), waves write ind = %d.\n", readINT, sizeof(yo), EEPROM_CURRENT_ADDR - 0, ind);

	if ( yo.ONOFF == true){ powerON();}

	setBrightness( yo.currentBrightness);
	irdaServer( yo.lastPressed, 0);
}
