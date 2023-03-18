#include "animeClass.h"

animeClass a;

bool animeClass::isInID( int id)
{
    // if ( this->keys.find( id) != this->keys.end()){ // ERROR
    // } else { this->keys.insert( id); }
	itKeys = keysAll.insert( id);
	if ( !itKeys.second){	
		Serial.printf( "\n-=> Error with ID: %d\n", id);
	}
	return !itKeys.second;
}

waveItem animeClass::addDefault( int id)
{
	a.isInID( id);

	waveItem wave;
	
	wave.typeWeb 		= 0;						// 0 = None, 1 = bList, 2 = rList 
	wave.indForWeb		= 0;
	wave.leadOFF 		= false;						// fill black and save LastPressed
	wave.isEffect 		= false;						// is pt2 change ( ON/OF)
	wave.delta 			= 0;							// min value for web-range
	wave.min 			= 0;							// min value for web-range
	wave.max			= 255;							// max value for web-range
	wave.bright			= 128;
	wave.temp 			= TEMP_IND_MAX;
	wave.speed 			= 5;
	wave.saturn 		= 100;
	wave.minSpeed		= 1;
	wave.maxSpeed		= 10;
	wave.c1 			= CRGB{ 255, 0, 0};
	wave.c2 			= CRGB{ 0, 255, 0};
	wave.c3 			= CRGB{ 0, 0, 255};
	wave.savno 			= 0; 					// количество записей вавы в память [Save No]
	wave.pt2setter 		= nullptr;
	wave.pt2static 		= nullptr;
	wave.pt2Funca 		= nullptr;
	// wave.pt2prewave 	= nullptr;
	wave.pt2changer 	= nullptr;
	wave.pollDefault 	= 9;					// ID код поллитры по-умолчанию из myPollitra[]	
	wave.aux010			= 5;
	wave.aux100			= 50;
	wave.aux255			= 128;
	wave.aux355			= 128;
	wave.aux455			= 128;

	return wave;
}

void animeClass::addStatic( int id, String name, void (*ptStatic)(), bool forWeb, uint8_t polDefault)
{
	mWaves[id] 				= a.addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].name 		= name;
	mWaves[id].typeWeb 		= 1;
	mWaves[id].animeType	= ANIME_STATIC;
	mWaves[id].pollDefault 	= polDefault;	
	mWaves[id].pt2static 	= ptStatic;
	
	if ( forWeb)
	{
		mWaves[id].isEffect 	= true;
		mWaves[id].leadOFF 		= true;
		mWaves[id].indForWeb 	= ++a.indAnime;
		this->keysWeb.insert( id);
	} 

	// Serial.printf( "-=> STATIC Wave ID (%d) = %d\n", id, mWaves[id].indForWeb);
}

/*
Добавляем "сеттер", добавляется на страницу в виде рэнджа, вызывается из веба, при изменениии рэнджа с передацей значения в функцию.
@param id Unical ID. irDA code даже лучше будет
@param name Animation name for web ( Here - Nah)
@param ptSetter указатель на функцию "сеттер" = &staticFuuctionName
@param min мин
@param max  макс		
*/
void animeClass::addSetter( int id, String name,  void (*ptSetter)(int), int min, int max)
{
	mWaves[id]				= a.addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].min 			= min;
	mWaves[id].max 			= max;
	mWaves[id].name 		= name;
	mWaves[id].typeWeb 		= 2;
	mWaves[id].animeType	= ANIME_SETTER;
	mWaves[id].indForWeb 	= ++a.indSetter;
	mWaves[id].pt2setter 	= ptSetter;
}

/*
@param id Unical ID. irDA code даже лучше будет
@param name Animation name for web ( Here - Nah)
@param ptAnime указатель на функию аминации, выполняется в цикле loop = &staticFuuctionName
@param forWeb публиковать на сайте ( будет в виде кнопки вызова анимации), позиция в странице зависит от порядка при добавлении
@param polDefault ИД политры по-умолчанию для анимации, берется из таблицы myPal из palettes.cpp ( 9 - радуга)
@param ptAnimePre указатель на функция "пре", выполнится один раз перед первым запуском функции с анимацией = &staticFuuctionName
*/
void animeClass::addAmine( int id, String name, void (*ptAnime)(), bool forWeb, uint8_t polDefault, void (*ptAnimePre)())
{
	mWaves[id] 				= a.addDefault( id);
	mWaves[id].typeWeb 		= 1;
	mWaves[id].animeType	= ANIME_DYNAMIC;
	mWaves[id].name 		= name;
	mWaves[id].pollDefault 	= polDefault;
	mWaves[id].pt2Funca 	= ptAnime;
	mWaves[id].pt2static 	= ptAnimePre;

	if ( forWeb)
	{
		mWaves[id].leadOFF 		= true;
		mWaves[id].isEffect 	= true;
	 	mWaves[id].indForWeb 	= ++a.indAnime;
		this->keysWeb.insert( id);
	}

	// Serial.printf( "-=> Wave ID (%d) = %d\n", id, mWaves[id].indForWeb);
}

/*
Добавляем "Чэнджер", для тыканья с пульта ИД и вызова функций
	с передачей +/-дельты в нее. Не для веба.

@param id Unical ID. irDA code даже лучше будет. Доп коды в таблице keyCodes в irda.cpp
@param name Animation name ( Here - Nah), просто для понимания, что это такое.
@param ptChanger pointer to changer function = &staticFuuctionName
@param delta +/- add/sub, передаем это значение в функцию		
*/
void animeClass::addChanger( int id, String name, void (*ptChanger)( int), byte delta )
{	
	mWaves[id]	 			= a.addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].name 		= name;
	mWaves[id].delta 		= delta;
	mWaves[id].pt2changer 	= ptChanger;
	mWaves[id].animeType	= ANIME_CHANGER;
}


