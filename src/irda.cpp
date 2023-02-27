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

/*мапа нескольких кодов пультов на один код действия
	int codeNew = int codeOld*/ 
keyMaps keyCodes;

/* Поднимаем ИР-сервер*/
void irdaStartUP()
{	
	keyCodes = {
		// {127026699, IR_TV_ON},	
		// {127026699, IR_TVVOL_UP	},
		// {127026699, IR_TVVOL_DN},	
		// {127026699, IR_TVCHANL_UP},	
		// {127026699, IR_TVCHANL_DN},	
		// {127026699, IR_VOLUME_UP},
		// {127026699, IR_VOLUME_DN},	
		{551485695, IR_MENU_UP},	
		{551518335, IR_MENU_DN},	
		// {127026699, IR_MENU_DN},	
		// {127026699, IR_MENU_LEFT},	
		// {127026699, IR_MENU_RIGHT},	
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
	else if ( irrecv.decode( &results)) 
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

	if ( keyCodes[resValue]){	resValue = keyCodes[resValue]; }
	
	if ( resValue)
	{		
		yoBugF( "-=>> IR receive: %d\n", resValue);
		// Serial.printf( "Code from web: %d = (%d) - [%d]\n", codeFromWeb, webValue, resValue);
		
		mbIter = mWaves.find( resValue);
		if ( mbIter != mWaves.end())
		{
			yoBug( "-=>> Наш выбор: ");			
			yoBugN( mbIter->second.name);			

			if ( mbIter->second.pt2setter){ 									// сэттер или чэнджер пришел
				// yo.loadOutside = true;

				if ( mbIter->second.typeWeb == 0){								// changer
					mbIter->second.pt2setter( mbIter->second.min);
				}
				else if ( webValue){											// setter
					mbIter->second.pt2setter( webValue);
				}
			} 

			if ( mbIter->second.isEffect){	               						// если это эффект и надо применить цвета, палитры и прочее
				if ( mbIter->second.pollCurrent < 1) { 							// палитра, при смене активности, меняется засчет овновления селектора списка палитр. вызывается вебсервером.
					mbIter->second.pollCurrent = mbIter->second.pollDefault; 	// если текущая палитра не определена - ставим дефолтную
				}
				
				yo.loadOutside 	= false;
				yo.lastPressed 	= resValue;
				yo.name010 		= "AUX010";
				yo.name100 		= "AUX100";
				yo.name255 		= "AUX255";
				yo.nameSpeed	= "Speed";
				setColors(		mbIter->second.c1, mbIter->second.c2, mbIter->second.c3);
				// setBrightness( 	mbIter->second.bright);
				setSpeed( 		mbIter->second.speed);
				setSaturation( 	mbIter->second.saturn);
				setTemperature( mbIter->second.temp);
				setAUX010( 		mbIter->second.aux010);
				setAUX100( 		mbIter->second.aux100);
				setAUX255( 		mbIter->second.aux255);
				paletteSetActive( mbIter->second.pollCurrent, true);
				ledOFF();
				// Serial.println( "-==> Vars applied.");
				// Serial.printf("ind=%d, pol=%d, bri=%d, speed=%d, sat=%d, temp=%d, a010=%d, a100=%d, a255=%d\n", resValue, mbIter->second.pollCurrent,	mbIter->second.bright, mbIter->second.speed, mbIter->second.saturn, mbIter->second.temp, mbIter->second.aux010, mbIter->second.aux100, mbIter->second.aux255);
				// Serial.printf("ind=%d, pol=%d, bri=%d, speed=%d, sat=%d, temp=%d, a010=%d, a100=%d, a255=%d\n", yo.lastPressed, mbIter->second.pollCurrent,	yo.currentBrightness, yo.currentSpeed, yo.currentSaturn, yo.currentTemp, yo.AUX010, yo.AUX100, yo.AUX255);
				yo.loadOutside = true;
			}

			if ( mbIter->second.pt2prewave){ 	mbIter->second.pt2prewave();}			
			if ( mbIter->second.pt2static){ 	mbIter->second.pt2static();}
			if ( mbIter->second.isEffect){		pt2Func = mbIter->second.pt2Funca;}
            
			#ifdef EERPROM_ENABLE
				requestSave();
			#endif
			
			yo.pt2webUpdate();
		}		
	}   
}
