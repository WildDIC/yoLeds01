#include "IRrecv.h"
#include "config.h"
#include "irda.h"
#include "animeClass.h"

IRrecv irrecv(RECV_PIN);

decode_results results;


/*мапа нескольких кодов пультов на один код действия
	int codeNew = int codeOld*/ 
keyMaps keyCodes;

/* Поднимаем ИР-сервер*/
void irdaStartUP()
{	
	keyCodes = {
		{1268261342, IR_TV_ON},	
		// {1261884204, IR_TV_ON},	
		// {127026699, IR_TVVOL_UP	},
		// {127026699, IR_TVVOL_DN},	
		// {127026699, IR_TVCHANL_UP},	
		// {127026699, IR_TVCHANL_DN},	
		// {127026699, IR_VOLUME_UP},
		// {127026699, IR_VOLUME_DN},	
		{551485695, IR_MENU_UP},	
		{551518335, IR_MENU_DN},	
		// {127026699, IR_MENU_DN},	
		
		{1240493167, IR_MENU_LEFT},	
		{1118950049, IR_MENU_LEFT},	
		{1864947811, IR_MENU_LEFT},	
		{481457630, IR_MENU_LEFT},	
		{1576443506, IR_MENU_LEFT},	
		{1274544202, IR_MENU_LEFT},	
		{184755576, IR_MENU_LEFT},	

		{449300946, IR_MENU_RIGHT},	
		{1302542546, IR_MENU_RIGHT},	
		{528721466, IR_MENU_RIGHT},	
		{1374020412, IR_MENU_RIGHT},	
		{1274544330, IR_MENU_RIGHT},	
		{873323003, IR_MENU_RIGHT},	
		// {127026699, IR_MENU_OK},

		// {127026699, IR_BACK},	
		// {127026699, IR_FORWARD},
		// {127026699, IR_PAUSE},	
		// {127026699, IR_REWIND},		
		// {127026699, IR_PLAY},	
		// {127026699, IR_STOP},		
		// {127026699, IR_FASTFF},		

		// {127026699, IR_NUM_0},	
		// {127026699, IR_NUM_1},		
		// {127026699, IR_NUM_2},		
		// {127026699, IR_NUM_3},		
		// {127026699, IR_NUM_4},		
		// {127026699, IR_NUM_5},		
		// {127026699, IR_NUM_6},		
		// {127026699, IR_NUM_7},		
		// {127026699, IR_NUM_8},		
		// {127026699, IR_NUM_9},		
		// {127026699, IR_NUM_10},		
		// {127026699, IR_NUM_CLR},	
	};

	// keyCodes[551485695] = IR_MENU_UP;

    irrecv.enableIRIn();
}

/* Скипаем до следующих данных с приемника*/
void irdaNext()
{
	irrecv.resume();  // Receive the next value		
}


int getIRcode()
{
	int resValue = 0;

	if ( irrecv.decode( &results)) 
	{
		resValue = results.value;   	// получаем значение ИР-приеника
		if ( resValue == ZERO_DATA)
		{
			resValue = yo.lastReceive;
		} 
		else 
		{
			yo.lastReceive = resValue;			
		}
		irdaNext();		
	}
	return resValue;
}

/* Обработка ИР приемника, через обход мапы mButtons
и сохранение в ЕЕПроМ, если код с передатчика нашелся.
Принимает входные параметры с вебсерра
@param codeFromWeb свой ИК-код, приходит от веб-кдента
@param webValue значение для установки параметров, приходит от веб-клиента*/
void irdaServer( int codeFromWeb = 0, int webValue = 0)
{
    uint32_t resValue = 0;

	if ( codeFromWeb){ 					// пришли данные с веб-сервера
		resValue = codeFromWeb; 		
	} 
	else{
		resValue = getIRcode();
	}		
	
	if ( resValue)
	{		
		Serial.printf( "irda| Code from web [%d]. webValue: %d. resValue #%d.", codeFromWeb, webValue, resValue);
		
		if ( keyCodes[resValue])						// ищем много-к-одному в списке ИР кодов пришедшее
		{	
			resValue = keyCodes[resValue]; 
			Serial.printf( " -=> [%d].", resValue);
		}

		if ( a.isID( resValue))
		{
			Serial.print( " И наш выбор: '" + mWaves[resValue].name + "'.\n");
			a.changeWave( resValue, webValue);		
		} 	
		else
		{
			Serial.print( "\n");
		}
	}   
}
