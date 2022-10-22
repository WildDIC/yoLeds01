#include "IRrecv.h"
#include "config.h"
#include "irda.h"
#include "leds.h"

IRrecv irrecv(RECV_PIN);

decode_results results;

extern void ledOFF( int resValue);
// extern void webServerUpdate();
extern void paletteSetActive( byte pollitraID, bool force);
extern void requestSave();

/* Поднимаем ИР-сервер*/
void irdaStartUP(){
    irrecv.enableIRIn();
}

/* Скипаем до следующих данных с приемника*/
void irdaNext(){
	irrecv.resume();  // Receive the next value		
}

/* Обработка ИР приемника, через обход мапы mButtons
и сохранение в ЕЕПроМ, если код с передатчика нашелся.
Принимает входные параметры с вебсерра
@param codeFromWeb свой ИК-код, приходит от веб-кдента
@param webValue значение для установки параметров, приходит от веб-клиента*/
void irdaServer( int codeFromWeb = 0, int webValue = 0){
    uint32_t resValue = 0;

	if ( codeFromWeb){ 					// пришли данные с веб-сервера
		resValue = codeFromWeb; 		
	} 
	else if ( irrecv.decode( &results)) {
		resValue = results.value;   	// получаем значение ИР-приеника
		
		if ( resValue == ZERO_DATA){
			resValue = yo.lastReceive;
		} else {
			yo.lastReceive = resValue;			
		}
		irdaNext();		
	}	
	
	if ( resValue){		
		yoBugF( "-=>> IR receive: %d\n", resValue);
		// Serial.printf( "Code from web: %d = (%d) - [%d]\n", codeFromWeb, webValue, resValue);
		
		mbIter = mWaves.find( resValue);
		if ( mbIter != mWaves.end()){
			yoBug( "-=>> Наш выбор: ");			
			yoBugN( mbIter->second.name);			


			if ( mbIter->second.leadOFF){ 		
				yo.lastPressed	= resValue;
				ledOFF( resValue);			
			}


			if ( mbIter->second.pt2setter){ 									// сэттер или чэнджер пришел
				if ( mbIter->second.typeWeb == 0){								// changer
					mbIter->second.pt2setter( mbIter->second.min);
				}else if ( webValue){											// setter
					mbIter->second.pt2setter( webValue);
				}
			} 


			if ( mbIter->second.typeWeb == 1){	               					// если есть столбец с палитрами
				if ( mbIter->second.pollCurrent < 1) { 							// палитра, при смене активности, меняется засчет овновления селектора списка палитр. вызывается вебсервером.
					mbIter->second.pollCurrent = mbIter->second.pollDefault; 	// если текущая палитра не определена - ставим дефолтную
				}
				
				paletteSetActive( mbIter->second.pollCurrent, true);
				// setBrightness( 	mbIter->second.bright);
				setSpeed( 		mbIter->second.speed);
				setSaturation( 	mbIter->second.saturn);
				setTemperature( mbIter->second.temp);
				setAUX010( 		mbIter->second.aux010);
				setAUX100( 		mbIter->second.aux100);
				setAUX255( 		mbIter->second.aux255);
				setColors(		mbIter->second.c1, mbIter->second.c2, mbIter->second.c3, false);
				// Serial.println( "-==> Vars applied.");
				// Serial.printf("ind=%d, pol=%d, bri=%d, speed=%d, sat=%d, temp=%d, a010=%d, a100=%d, a255=%d\n", resValue, mbIter->second.pollCurrent,	mbIter->second.bright, mbIter->second.speed, mbIter->second.saturn, mbIter->second.temp, mbIter->second.aux010, mbIter->second.aux100, mbIter->second.aux255);
				// Serial.printf("ind=%d, pol=%d, bri=%d, speed=%d, sat=%d, temp=%d, a010=%d, a100=%d, a255=%d\n", yo.lastPressed, mbIter->second.pollCurrent,	yo.currentBrightness, yo.currentSpeed, yo.currentSaturn, yo.currentTemp, yo.AUX010, yo.AUX100, yo.AUX255);
			}

			if ( mbIter->second.pt2prewave){ 	mbIter->second.pt2prewave();}			
			if ( mbIter->second.pt2static){ 	mbIter->second.pt2static();}
			if ( mbIter->second.isEffect){		pt2Func = mbIter->second.pt2Funca;}
            
			#ifdef EERPROM_ENABLE
				requestSave();
				// Serial.printf( "\n -=> clock=%d, now=%d, save=%d, bool=%d\n", clock(), yo.now, yo.now + EEPROM_SAVE_TIME, yo.isNeedSaveEEPROM);
				// yo.EEPROMsaveTime = yo.now + EEPROM_SAVE_TIME;
				// yo.isNeedSaveEEPROM = true;
			#endif
			
			yo.pt2webUpdate();
		}		
	}   
}
