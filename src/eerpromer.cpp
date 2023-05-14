#include <EEPROM.h>
#include "config.h"
#include "animeClass.h"
#include "eeClass.h"
// #ifdef JSON_ENABLE
// #include "json_save.h"
// #endif

#define EEPROM_ADDR_START 						 100 		// зачем-то свинул на +100, не помню.
#define EEPROM_ADDR_INIT 		EEPROM_ADDR_START  + 1		// номер контрольной ячейки (byte)
#define EEPROM_ADDR_WAVEIND		EEPROM_ADDR_START  + 2		// ячейка для индекса количества waves = a.keyButton.size() ( byte)
#define EEPROM_ADDR_WRITER 		EEPROM_ADDR_START  + 3		// записываем количество актов записей (int)
#define EEPROM_ADDR_WAVESIZE 	EEPROM_ADDR_START  + 7		// записываем адрес ячейки хранения размера вавы ( byte)
#define EEPROM_ADDR_CONFIG 		EEPROM_ADDR_START  + 10		// адрес начала записи конфига yo
#define EEPROM_ADDR_WAVES 		EEPROM_ADDR_CONFIG + 80 	// начальная запись массива waves ( +резерв под конфиг)

#define EEPROM_SAVE_TIME 	3 * 60 * 1000					// задержка на сохранение после изменения данных
#define EEPROM_WAVE_SIZE 	26								// предположительный размер/резерв сохранения настроек Вавы 
#define INIT_KEY 			50     							// ключ первого запуска. 0-254, на выбор


eeClass e;

bool forceSave = false;
uint8_t waveWriteSize = 0;
// uint8_t waveSize = 0;


uint8_t getWaveSize()
{
	uint8_t res = EEPROM.read( EEPROM_ADDR_WAVESIZE);
	
	if ( res != EEPROM_WAVE_SIZE)
	{
		forceSave = true;
		Serial.printf( "eepr| Alarm! New wave size ( %d) != saved size ( %d). Need force resave...\n", EEPROM_WAVE_SIZE, res);
		
		EEPROM.write( EEPROM_ADDR_WAVESIZE, EEPROM_WAVE_SIZE);    		
		EEPROM.commit();
	}

	return res;
}


void eepromSaveWaveData( uint8_t waveID)
{
	waveItem w = mWaves[waveID];
	e.readStartHere( EEPROM_ADDR_WAVES + ( EEPROM_WAVE_SIZE * ( w.indWeb - 1)));	// минус так как IndWeb идет  еденицы

	e.saveData( waveID);		
	e.saveData( ++w.savno);	e.saveData( w.indWeb);	e.saveData( w.palCurrent);
	e.saveData( w.speed);	e.saveData( w.temp);	e.saveData( w.saturn);
	e.saveData( w.c1.r);	e.saveData( w.c1.g);	e.saveData( w.c1.b);
	e.saveData( w.c2.r);	e.saveData( w.c2.g);	e.saveData( w.c2.b);
	e.saveData( w.c3.r);	e.saveData( w.c3.g);	e.saveData( w.c3.b);	
	e.saveData( w.aux010);	e.saveData( w.aux100);	e.saveData( w.aux255);
	e.saveData( w.aux355);	e.saveData( w.aux455);				

	Serial.printf( "eepr| Saved [%2d write] wave #%3d, [infWeb = %2d], [savNO = %d], '", e.saveCounter, waveID, w.indWeb, w.savno);
	Serial.print( w.name + "'.\n");

	e.saveCounter = 0;
}


void eepromLoadWave()
{
	uint8_t ind 	 = EEPROM.read( EEPROM_ADDR_WAVEIND);		// читаем индекс: количкство сохраненных элементов currentPal	
	uint8_t waveSize = getWaveSize();							// читаем СОХРАНЕННУЮЮ версию вавесайза для чтения данных, если размер не совпадает с ВАВЕ_САЙЗ - форцесейв
	// Serial.printf( "-=> Before load data: ind=%d, keysWeb=%d, keysAll=%d \n", ind, a.keysWeb.size(), a.keysAll.size());

	for (int i = 0; i < ind; i++) 
	{ 		
		uint16_t waveStart  = e.readStartHere( EEPROM_ADDR_WAVES + ( waveSize * i));			// перекидываем чтение данных на аждрксс с палитрами
		uint8_t waveID 		= e.readBYTE();	
		/*
			читаем Save No, если оно равно 0, то считывается первый раз, штатный случай, 
			есть какое-то значение, то это дубль строки и переписываем ее, 
			если оно больше по номеру или пропускаем, если Савно меньше ( писали давно).
			SavNo инкрементится при записи вавы.
		*/ 
		uint16_t savno  = e.read16t();

		if ( waveID > 0 && savno >= mWaves[waveID].savno)
		{
			mWaves[waveID].savno	= savno; 		uint8_t placed 			= e.readBYTE(); mWaves[waveID].palCurrent 	= e.readBYTE();
			mWaves[waveID].speed 	= e.readBYTE(); mWaves[waveID].temp 	= e.readBYTE();	mWaves[waveID].saturn 		= e.readBYTE();
			mWaves[waveID].c1.r 	= e.readBYTE(); mWaves[waveID].c1.g 	= e.readBYTE();	mWaves[waveID].c1.b 		= e.readBYTE();
			mWaves[waveID].c2.r 	= e.readBYTE();	mWaves[waveID].c2.g 	= e.readBYTE();	mWaves[waveID].c2.b 		= e.readBYTE();
			mWaves[waveID].c3.r 	= e.readBYTE();	mWaves[waveID].c3.g 	= e.readBYTE();	mWaves[waveID].c3.b 		= e.readBYTE();
			mWaves[waveID].aux010 	= e.readBYTE();	mWaves[waveID].aux100 	= e.readBYTE();	mWaves[waveID].aux255 		= e.readBYTE(); 
			mWaves[waveID].aux355 	= e.readBYTE();	mWaves[waveID].aux455 	= e.readBYTE();

			if ( mWaves[waveID].palCurrent < 1 || mWaves[waveID].palCurrent > NUM_POLLITR) 
			{
				mWaves[waveID].palCurrent = mWaves[waveID].palDefault;
			}

			if ( placed != mWaves[waveID].indWeb) 
			{ 	
				Serial.printf( "eepr| -=> Bad 'placed', need total resave [savno=%d (%d)]. WaveID = %d, INDforWeb = %d ( %d) [", mWaves[waveID].savno, savno, waveID, mWaves[waveID].indWeb, placed);
				Serial.print( mWaves[waveID].name + "].\n");

				forceSave = true; 
			}		
			waveWriteSize = e.getCurrenRead() - waveStart;	
			// Serial.printf( "-=> LOADED [savno=%d (%d)]. WaveID = %d, INDforWeb = %d ( Addres=%d)\n", mWaves[waveID].savno, savno, waveID, mWaves[waveID].indForWeb, EEPROM_CURRENT_ADDR);
		}	
    }
}

/* Сохраняем тупо конфиг yo в ЕЕПРОМ, но не чаще, чем SAVE_DELAY*/
void eepromSaveData()
{	
	e.readStartHere( EEPROM_ADDR_CONFIG);

	e.saveData( yo.currentBri);
	e.saveData( yo.waveID);
	e.saveData( yo.ONOFF);
	e.saveData( yo.iscandle);
	e.saveData( yo.ishifter);
	e.saveData( yo.candleServ);
	e.saveData( yo.shiftServ);
	
	int writeCount = EEPROM.read( EEPROM_ADDR_WRITER);   // щёчик записей, чиста поржать над числом
	EEPROM.put( EEPROM_ADDR_WRITER, ++writeCount);		
	EEPROM.commit();

	Serial.printf( "eepr| Saved [%2d write] data [%d] times. Size of yo = %db\n", e.saveCounter, writeCount, sizeof(yo));
	e.saveCounter = 0;
}


/*Загружаем конфиг из еепромы, вэйвы ложим из ддругой процеуры*/
void eepromLoadData()
{
	e.readStartHere( EEPROM_ADDR_CONFIG);

	yo.currentBri 	= e.readBYTE();
	yo.waveID 		= e.readBYTE();	
	yo.ONOFF 		= e.readBOOL();
	yo.iscandle		= e.readBOOL();
	yo.ishifter		= e.readBOOL();
	yo.candleServ	= e.readBYTE();
	yo.shiftServ	= e.readBYTE();
}


void eepromSaveWaveIND()
{
	uint8_t size = a.keyButton.size();
	e.saveData( EEPROM_ADDR_WAVEIND, size);
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
	int eepromSize = EEPROM_ADDR_WAVES + ( EEPROM_WAVE_SIZE * ( a.countWaves + 1)); 	// считаем примерный размер памяти для сохранения конфига + ( размер волны * количество)
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
	int writeCount = EEPROM.read( EEPROM_ADDR_WRITER);
	int waveIND    = EEPROM.read( EEPROM_ADDR_WAVEIND) + 1;
	
	Serial.printf( "\neepr| Read config from EEPROM [%d times]. EEPROM used %db ( reserved %db). %d waves with size %db ( max %db). yo size = %db.\n", 
													writeCount, 		EEPROM_ADDR_WAVES + EEPROM_WAVE_SIZE * waveIND,
																						eepromSize, 		
																								waveIND, 		waveWriteSize, 	
																															EEPROM_WAVE_SIZE, 
																																			sizeof(yo));
}
