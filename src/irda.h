#include "IRrecv.h"

IRrecv irrecv(RECV_PIN);
decode_results results;


extern void ledOFF( int resValue);
extern void eepromSave( bool forceSaveEEPROM);
extern void paletteSetActive( byte pollitraID);

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
@param codeFromWeb свой ИК-код
@param webValue значение для установки параметров*/
void irdaServer( int codeFromWeb = 0, int webValue = 0){
    uint32_t resValue = 0;

	if (irrecv.decode(&results)) {
		resValue = results.value;   // получаем значение ИР-приеника
		
		if ( resValue == 4294967295){
			resValue = yo.lastReceive;
		} else{
			yo.lastReceive = resValue;			
		}
		irdaNext();
		yoBugF( "-=>> IR receive: %d\n", resValue);
	}
	
	if ( codeFromWeb){ resValue = codeFromWeb; }

	// Serial.printf( "Code from web: %d = (%d) - [%d]\n", codeFromWeb, webValue, resValue);
	if ( resValue){		

		mbIter = mButtons.find( resValue);
		if ( mbIter != mButtons.end()){
			yoBug( "-=>> Наш выбор: ");			
			yoBugN( mbIter->second.name);			

			if ( mbIter->second.leadOFF){		ledOFF( resValue);}
			if ( mbIter->second.pollDefault){	
				if ( mbIter->second.pollCurrent < 1) { mbIter->second.pollCurrent = mbIter->second.pollDefault; }
				paletteSetActive( mbIter->second.pollCurrent);}
			if ( mbIter->second.pt2prewave){ 	mbIter->second.pt2prewave();}			
			if ( mbIter->second.pt2static){ 	mbIter->second.pt2static();}
			if ( mbIter->second.isEffect){		pt2Func = mbIter->second.pt2Funca;}
            if ( mbIter->second.pt2setter){ 	
				if ( mbIter->second.typeWeb == 0){
					mbIter->second.pt2setter( mbIter->second.min);
				}else if ( webValue){
					mbIter->second.pt2setter( webValue);
				}
			} 

			#ifdef EERPROM_ENABLE
				eepromSave( false);	
			#endif
		}		
	}   
}