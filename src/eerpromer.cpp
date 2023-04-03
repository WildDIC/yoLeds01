#include <EEPROM.h>
#include "config.h"
#include "irda.h"
#include "leds.h"
#include "animeClass.h"

// #ifdef JSON_ENABLE
// #include "json_save.h"
// #endif

#define EEPROM_ADDR_START 						 100 	// зачем-то свинул на +100, не помню.
#define EEPROM_ADDR_INIT 	EEPROM_ADDR_START  + 1		// номер контрольной ячейки (byte)
#define EEPROM_ADDR_WAVEIND	EEPROM_ADDR_START  + 2		// ячейка для индекса количества waves = a.keysWeb.size() ( byte)
#define EEPROM_ADDR_WRITER 	EEPROM_ADDR_START  + 3		// записываем количество актов записей (int)
#define EEPROM_ADDR_CONFIG 	EEPROM_ADDR_START  + 10		// адрес начала записи конфига yo
#define EEPROM_ADDR_WAVES 	EEPROM_ADDR_CONFIG + 50 	// начальная запись массива waves ( +резерв под конфиг)

#define EEPROM_SAVE_TIME 	3 * 60 * 1000				// задержка на сохранение после изменения данных
#define EEPROM_WAVE_SIZE 	30							// предположительный размер/резерв сохранения настроек Вавы 
#define INIT_KEY 			50     						// ключ первого запуска. 0-254, на выбор


int eepromCurrentAddr = EEPROM_ADDR_START;				// указывает на адрес последней считанной ячейки памяти функциями фРидХХХХ, 
int eepromCurrentByte = EEPROM_ADDR_START;				// именно в туда мы будем потом, если надо (записываемые данные не совпали с сохраненными ранее),
int eepromCurrentInt  = EEPROM_ADDR_START;				// записывать проверяемые данные.

int readINT;
uint16_t read16t;
byte readBYTE;
bool readBOOL;
bool forceSave = false;
int saveCounter = 0;
byte ind;


uint16_t fRead16t()
{
	eepromCurrentInt = eepromCurrentAddr;
	EEPROM.get( eepromCurrentAddr, read16t);
	eepromCurrentAddr += 2;	
	return read16t;
}

int fReadINT()
{
	eepromCurrentInt = eepromCurrentAddr;
	EEPROM.get( eepromCurrentAddr, readINT);
	eepromCurrentAddr += 4;	
	return readINT;
}

byte fReadBYTE()
{
	eepromCurrentByte = eepromCurrentAddr;
	EEPROM.get( eepromCurrentAddr, readBYTE);
	eepromCurrentAddr += 1;	
	return readBYTE;
}

bool fReadBOOL()
{
	eepromCurrentByte = eepromCurrentAddr;
	EEPROM.get( eepromCurrentAddr, readBOOL);
	eepromCurrentAddr += 1;	
	return readBOOL;
}

void fWriteDATA( uint16_t data)	{ EEPROM.put( eepromCurrentInt,  data); ++saveCounter; }
void fWriteDATA( int data)		{ EEPROM.put( eepromCurrentInt,  data); ++saveCounter; }
void fWriteDATA( byte data)		{ EEPROM.put( eepromCurrentByte, data); ++saveCounter; }
void fWriteDATA( bool data)		{ EEPROM.put( eepromCurrentByte, data); ++saveCounter; }

void saveEEPROM( uint16_t data) { if ( fRead16t()  != data) fWriteDATA( data);}
void saveEEPROM( int data) 		{ if ( fReadINT()  != data) fWriteDATA( data);}
void saveEEPROM( byte data)		{ if ( fReadBYTE() != data) fWriteDATA( data);}
void saveEEPROM( bool data)		{ if ( fReadBOOL() != data) fWriteDATA( data);}


void eepromSaveWaveData( int waveID)
{
	waveItem w = mWaves[waveID];
	eepromCurrentAddr = EEPROM_ADDR_WAVES + ( EEPROM_WAVE_SIZE * w.indWeb);		

	saveEEPROM( waveID);
	saveEEPROM( ++w.savno);		saveEEPROM( w.indWeb);   	saveEEPROM( w.palCurrent);
	saveEEPROM( w.speed);		saveEEPROM( w.temp);		saveEEPROM( w.saturn);
	saveEEPROM( w.c1.r);		saveEEPROM( w.c1.g);		saveEEPROM( w.c1.b);
	saveEEPROM( w.c2.r);		saveEEPROM( w.c2.g);		saveEEPROM( w.c2.b);
	saveEEPROM( w.c3.r);		saveEEPROM( w.c3.g);		saveEEPROM( w.c3.b);	
	saveEEPROM( w.aux010);		saveEEPROM( w.aux100);		saveEEPROM( w.aux255);
	saveEEPROM( w.aux355);		saveEEPROM( w.aux455);				

	Serial.printf( "eepr| Saved [%d write] wave #%d, [infWeb = %d], [savNO = %d], ['", saveCounter, waveID, w.indWeb, w.savno );
	Serial.print( w.name);
	Serial.println( "'].");

	saveCounter = 0;
}


void eepromLoadWave()
{
	forceSave = false;
	EEPROM.get( EEPROM_ADDR_WAVEIND, ind);				// читаем индекс: количкство сохраненных элементов currentPal	
	// Serial.printf( "-=> Before load data: ind=%d, keysWeb=%d, keysAll=%d \n", ind, a.keysWeb.size(), a.keysAll.size());

	for (int i = 1; i < ind + 1; i++) 
	{ 		
		eepromCurrentAddr = EEPROM_ADDR_WAVES + ( EEPROM_WAVE_SIZE * i);			// перекидываем чтение данных на аждрксс с палитрами
		
		int waveID 		= fReadINT();		// read irdaID		
		/*
			читаем Save No, если оно равно 0, то считывается первый раз, штатный случай, 
			есть какое-то значение, то это дубль строки и переписываем ее, 
			если оно больше по номеру или пропускаем, если Савно меньше ( писали давно).
			SavNo инкрементится при записи вавы.
		*/ 
		uint16_t savno  = fRead16t();

		if ( waveID > 0 && savno >= mWaves[waveID].savno)
		{
			mWaves[waveID].savno	= savno; 			uint8_t placed 			= fReadBYTE();     	mWaves[waveID].palCurrent 	= fReadBYTE();
			mWaves[waveID].speed 	= fReadBYTE(); 		mWaves[waveID].temp 	= fReadBYTE(); 		mWaves[waveID].saturn 		= fReadBYTE();
			mWaves[waveID].c1.r 	= fReadBYTE(); 		mWaves[waveID].c1.g 	= fReadBYTE(); 		mWaves[waveID].c1.b 		= fReadBYTE();
			mWaves[waveID].c2.r 	= fReadBYTE();		mWaves[waveID].c2.g 	= fReadBYTE();		mWaves[waveID].c2.b 		= fReadBYTE();
			mWaves[waveID].c3.r 	= fReadBYTE();		mWaves[waveID].c3.g 	= fReadBYTE();		mWaves[waveID].c3.b 		= fReadBYTE();
			mWaves[waveID].aux010 	= fReadBYTE();		mWaves[waveID].aux100 	= fReadBYTE();		mWaves[waveID].aux255 		= fReadBYTE(); 
			mWaves[waveID].aux355 	= fReadBYTE();		mWaves[waveID].aux455 	= fReadBYTE();

			if ( mWaves[waveID].palCurrent < 1 || mWaves[waveID].palCurrent > NUM_POLLITR) mWaves[waveID].palCurrent = 9;
			if ( placed != mWaves[waveID].indWeb) 
			{ 	
				Serial.printf( "eepr| -=> Bad 'placed', need total resave [savno=%d (%d)]. WaveID = %d, INDforWeb = %d ( %d) [", mWaves[waveID].savno, savno, waveID, mWaves[waveID].indWeb, placed);
				Serial.print( mWaves[waveID].name);
				Serial.println( "].");

				forceSave = true; 
			}			
			// Serial.printf( "-=> LOADED [savno=%d (%d)]. WaveID = %d, INDforWeb = %d ( Addres=%d)\n", mWaves[waveID].savno, savno, waveID, mWaves[waveID].indForWeb, EEPROM_CURRENT_ADDR);
		}	
    }
}

/* Сохраняем тупо конфиг yo в ЕЕПРОМ, но не чаще, чем SAVE_DELAY*/
void eepromSaveData()
{		
	yoBugN( "-=> Saver start");
	eepromCurrentAddr = EEPROM_ADDR_CONFIG;

	saveEEPROM( yo.currentBri);
	saveEEPROM( yo.waveID);
	saveEEPROM( yo.ONOFF);
	saveEEPROM( yo.iscandle);
	saveEEPROM( yo.ishifter);
	saveEEPROM( yo.lastReceive);
	
	EEPROM.get( EEPROM_ADDR_WRITER, readINT);   // щёчик записей, чиста поржать над числом
	EEPROM.put( EEPROM_ADDR_WRITER, ++readINT);		
	EEPROM.commit();

	Serial.printf( "eepr| Saved [%d write] data [%d] times. Size of yo = %db\n", saveCounter, readINT, sizeof(yo));
	saveCounter = 0;
}


/*Загружаем конфиг из еепромы, вэйвы ложим из ддругой процеуры*/
void eepromLoadData()
{
	eepromCurrentAddr 	= EEPROM_ADDR_CONFIG;

	yo.currentBri 	= fReadBYTE();
	yo.waveID 		= fReadINT();	
	yo.ONOFF 		= fReadBOOL();
	yo.iscandle		= fReadBOOL();
	yo.ishifter		= fReadBOOL();
	yo.lastReceive 	= fReadINT();
}


void eepromSaveWaveIND()
{
	uint8_t size = a.keyButton.size();
	EEPROM.get( EEPROM_ADDR_WAVEIND, ind);							
	
	if ( ind != size)
	{
		EEPROM.put( EEPROM_ADDR_WAVEIND, size);		
	}	
}


void eepromSaveWave()
{
	for ( auto keys : a.forSave)
	{
		eepromSaveWaveData( keys);
	}

	a.forSave.clear();
	eepromSaveWaveIND();
	EEPROM.commit();
}


void eepromForceSaveWave()
{
	Serial.println( "eepr| -=> Force saving wavedata...");

	for ( auto keys : a.keyButton) 
	{  			
		eepromSaveWaveData( keys);
	}
	
	forceSave = false;
	eepromSaveWaveIND();
	EEPROM.commit();
}




/* Проверяем необходимость сохранения данных в ЕЕПРОМ и таймер > SAVE_DELAY*/
void eepromSaveHandler()
{
	if ( yo.isNeedSaveEEPROM && yo.now >= yo.EEPROMsaveTime)
	{
		yoBugN( "-=> SaveHandles");
		eepromSaveData();
		eepromSaveWave();

		yo.isNeedSaveEEPROM = false;
		yo.pt2webUnsave();
	}
}

/*Принимаем запрос на сохранение yo.isNeedSaveEEPROM.
Откладываем таймер SAVE_DELAY секунд при каждом запросе
Добавляем waveID в set a.forSave, в цикле, при сохранени, сет очищается*/
void requestSave()
{
	yo.EEPROMsaveTime 	= yo.now + EEPROM_SAVE_TIME;
	a.forSave.insert( yo.waveID);

	if ( !yo.isNeedSaveEEPROM)
	{
		yo.isNeedSaveEEPROM = true;
		yo.pt2webUnsave();
	}
	// Serial.print( "-=> need save: ");
	// Serial.println( mWaves[yo.lastPressed].name);
	// Serial.printf( "a.forSave set size: %d.\n", a.forSave.size());
}

/* Читаем данные из ЕЕПРОМ, если первый раз, то пишем туда дефлолтный конфиг.
После чтения, устанавливаем в ленту данные из конфига.*/
void eepromStartUP()
{	
	int eepromSize = EEPROM_ADDR_WAVES + ( EEPROM_WAVE_SIZE * ( a.countWaves + 2)); 	// считаем примерный размер памяти для сохранения конфига + ( размер волны * количество)
    EEPROM.begin( eepromSize);							// резервируем память под всякое

	if ( EEPROM.read( EEPROM_ADDR_INIT) != INIT_KEY)  	// первый запуск, если не нашли "резевный" ключь в тут		
	{ 
    	Serial.println( "\neepr| First run. EEPROM initialization...");	

		EEPROM.write( EEPROM_ADDR_INIT, INIT_KEY);    	// записали ключ
    	EEPROM.write( EEPROM_ADDR_WAVEIND, 0);    		// записали нулевое количество волнов ( ind = 0)
    	EEPROM.write( EEPROM_ADDR_WRITER, 0);    		// записали счетчик кол-ва записей
    	
		eepromSaveData();								// сохраняем конфиг
		eepromForceSaveWave();							// делаем первый "форсажный" сейв волн в еепрому
  	}

	eepromLoadData();
	eepromLoadWave();	
	
	if ( forceSave) eepromForceSaveWave(); 				// полный пересейв, если что-то пошло не так при считавынии ( ИД считанной строки не равно ИД по порядку), 
														// скорее всего не совпали ИД строк при считывании с тем, в каком положенни они были при записи в прошлый раз.
	EEPROM.get( EEPROM_ADDR_WRITER, readINT);
	EEPROM.get( EEPROM_ADDR_WAVEIND, ind);
	
	Serial.printf( "\neepr| Read config from EEPROM [%d times]. EEPROM: used = %db, reserved = %db. waves ind = %d. yo size = %db. \n", readINT, eepromCurrentAddr - 0, eepromSize, ind, sizeof(yo));
	
	if ( yo.ONOFF == true) led.powerON();

	led.setBrightness( yo.currentBri);
	irdaServer( yo.waveID, 666);					// 666 что бы не было запроса на сохранение после ресета 
}
