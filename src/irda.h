#include "IRrecv.h"
#define ZERO_DATA 		0xFFFFFFFF

#define IR_TV_ON		551489775
#define IR_TVVOL_UP		551502015
#define IR_TVVOL_DN		551534655
#define IR_TVCHANL_UP	1270219007
#define IR_TVCHANL_DN	1270251647	
#define IR_VOLUME_UP	1270235327
#define IR_VOLUME_DN	1270267967
#define IR_MENU_UP		1270235582
#define IR_MENU_DN		1270268222
#define IR_MENU_LEFT	1270227422
#define IR_MENU_RIGHT	1270260062
#define IR_MENU_OK		1270278422

#define IR_BACK			1262518654
#define IR_FORWARD		1262486014
#define IR_PAUSE		1262520694
#define IR_REWIND		1262488054
#define IR_PLAY			321321321
#define IR_STOP			1262514574
#define IR_FASTFF		1262547214

#define IR_NUM_0		1262517124
#define IR_NUM_1		1262529364
#define IR_NUM_2		1262513044
#define IR_NUM_3		1262545684
#define IR_NUM_4		1262492644
#define IR_NUM_5		1262525284
#define IR_NUM_6		1262508964
#define IR_NUM_7		1262541604
#define IR_NUM_8		1262500804
#define IR_NUM_9		1262533444
#define IR_NUM_10		1270262102
#define IR_NUM_CLR		1270266437

IRrecv irrecv(RECV_PIN);
decode_results results;

extern void ledOFF( int resValue);
// extern void webServerUpdate();
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

	yoBugF( "-=>> IR receive: %d\n", resValue);
	
	if ( resValue){		
		// Serial.printf( "Code from web: %d = (%d) - [%d]\n", codeFromWeb, webValue, resValue);
		
		mbIter = mButtons.find( resValue);
		if ( mbIter != mButtons.end()){
			yoBug( "-=>> Наш выбор: ");			
			yoBugN( mbIter->second.name);			

			if ( mbIter->second.leadOFF){		ledOFF( resValue);}
			// if ( mbIter->second.pollDefault && webValue == 1){	               // если есть столбец с палитрами и на сервере нажали новую кнопку - меняем палитру.
			if ( mbIter->second.pollDefault ){	               // если есть столбец с палитрами и на сервере нажали новую кнопку - меняем палитру.
				if ( mbIter->second.pollCurrent < 1) { 							// палитра, при смене активности, меняется засчет овновления селектора списка палитр. вызывается вебсервером.
					mbIter->second.pollCurrent = mbIter->second.pollDefault; 	// если текущая палитра не определена - ставим дефолтную
				}
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
				yo.isNeedSaveEEPROM = true;
			#endif
			
			yo.pt2webUpdate();
		}		
	}   
}