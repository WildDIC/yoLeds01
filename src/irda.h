#include "IRrecv.h"

IRrecv irrecv(RECV_PIN);
decode_results results;


extern void ledOFF( int resValue);
extern void saveEEPROM();


/* Поднимаем ИР-сервер*/
void irdaStartup(){
    irrecv.enableIRIn();
}

/* Обработка ИР приемника, через обход мапы mButtons
и сохранение в ЕЕПроМ, если код с передатчика нашелся.
Принимает входные параметры и вебсерра
@param int codeFromWeb - свой ИК-код
@param int webValue - значение для установки параметров
*/
void irdaServer( int codeFromWeb, int webValue){
    uint32_t resValue = 10;

	if (irrecv.decode(&results)) {
		resValue = results.value;   // получаем значение ИР-приеника
		
		if ( resValue == 4294967295){
			resValue = yo.lastReceive;
		} else{
			yo.lastReceive = resValue;			
		}
		irrecv.resume();  // Receive the next value		
		yoBugF( "IR receive: %d\n", resValue);
	}
	
	if ( codeFromWeb != 10){ resValue = codeFromWeb; }

	// Serial.printf( "Code from web: %d = (%d) - [%d]\n", codeFromWeb, webValue, resValue);
	if ( resValue > 0 && resValue !=10){		

		mButtonIter = mButtons.find( resValue);
		if ( mButtonIter != mButtons.end()){
			yoBug( mButtonIter->second.name);			
						
			if ( mButtonIter->second.pt2change){	pt2Func = mButtonIter->second.pt2Funca;}
			if ( mButtonIter->second.leadOFF){		ledOFF( resValue);}
			if ( mButtonIter->second.pt2prewave){ 	mButtonIter->second.pt2prewave();}			
			if ( mButtonIter->second.pt2static){ 	mButtonIter->second.pt2static();}
			if ( mButtonIter->second.pt2setter){ 	
				if ( mButtonIter->second.typeWeb == 0){
					mButtonIter->second.pt2setter( mButtonIter->second.min);
				}else{
					mButtonIter->second.pt2setter( webValue);
				}
			} 

			#ifdef EERPROM_ENABLE
				saveEEPROM();	
				yoBug( "-=>> EEPROM Saved from irDA");
			#endif
		}		
	}   
}