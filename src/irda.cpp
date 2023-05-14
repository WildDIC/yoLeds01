#include "IRrecv.h"
#include "config.h"
#include "irda.h"
#include "animeCollector.h"

#define ZERO_DATA 		0xFFFFFFFF

#define IR_TV_ON		1268261342
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
#define IR_PLAY			1262530894
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
int lastReceive;

/*мапа нескольких кодов пультов на один код действия
	int codeNew = int codeOld*/ 
keyMaps keyCodes;

/* Поднимаем ИР-сервер*/
void irdaStartUP()
{	
	keyCodes = {
		{IR_TV_ON, 		A_POWER},	

		{551485695, 	A_BRIGHT_P},	
		{IR_MENU_UP, 	A_BRIGHT_P},	

		{551518335, 	A_BRIGHT_M},	
		{IR_MENU_DN, 	A_BRIGHT_M},	
		
		{1240493167, 	A_WAVE_M},	
		{1118950049, 	A_WAVE_M},	
		{1864947811, 	A_WAVE_M},	
		{481457630, 	A_WAVE_M},	
		{1576443506, 	A_WAVE_M},	
		{1274544202, 	A_WAVE_M},	
		{184755576, 	A_WAVE_M},	
		{IR_MENU_LEFT, 	A_WAVE_M},	

		{449300946, 	A_WAVE_P},	
		{1302542546, 	A_WAVE_P},	
		{528721466, 	A_WAVE_P},	
		{1374020412, 	A_WAVE_P},	
		{1274544330, 	A_WAVE_P},	
		{873323003, 	A_WAVE_P},	
		{IR_MENU_RIGHT,	A_WAVE_P},	
	};

    irrecv.enableIRIn();
}

/* Скипаем до следующих данных с приемника*/
void irdaNext()
{
	irrecv.resume();  // Receive the next value		
}


uint8_t irdaCheckIRcode()
{
	if ( irrecv.decode( &results)) 
	{
		static int resValue;   							// получаем значение ИР-приеника
		resValue = results.value;
		Serial.printf( "irda| Received code is: %10d.", resValue);

		irdaNext();	

		if ( resValue == ZERO_DATA)
		{
			resValue = lastReceive;
		} 

		if ( keyCodes[resValue])						// ищем много-к-одному в списке ИР кодов пришедшее
		{	
			lastReceive = resValue;
			
			static uint8_t waveID;
			waveID = keyCodes[resValue]; 
			Serial.printf( " -=> Wave ID: %3d.", waveID);
			Serial.print( " Looks like '" + mWaves[waveID].name + "'.\n");

			return waveID;
		}
		else Serial.print ( " Not wave found id here...\n");
	}

	return 0;
}