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

waveItem* animeClass::addDefault( int id)
{
	a.isInID( id);
	return new waveItem;
}

void animeClass::addStatic( int id, const String& name, void (*ptStatic)(), bool forWeb, uint8_t polDefault)
{
	mWaves[id] 				= *a.addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].name 		= name;
	mWaves[id].typeWeb 		= 1;
	mWaves[id].pollDefault 	= polDefault;	
	mWaves[id].pt2static 	= ptStatic;
	
	if ( forWeb)
	{
		mWaves[id].isEffect 	= true;
		mWaves[id].leadOFF 		= true;
		mWaves[id].indForWeb 	= ++a.indAnime;
		this->keyButton.insert( id);
	} 
}


void animeClass::addAmine( int id, const String& name, void (*ptAnime)(), bool forWeb, uint8_t polDefault, void (*ptAnimePre)())
{
	mWaves[id] 				= *a.addDefault( id);
	mWaves[id].typeWeb 		= 1;
	mWaves[id].name 		= name;
	mWaves[id].pollDefault 	= polDefault;
	mWaves[id].pt2Funca 	= ptAnime;
	mWaves[id].pt2static 	= ptAnimePre;

	if ( forWeb)
	{
		mWaves[id].leadOFF 		= true;
		mWaves[id].isEffect 	= true;
	 	mWaves[id].indForWeb 	= ++a.indAnime;
		this->keyButton.insert( id);
	}
}

void animeClass::addSetter( int id, const String& name,  void (*ptSetter)(int), int min, int max)
{
	mWaves[id]				= *a.addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].min 			= min;
	mWaves[id].max 			= max;
	mWaves[id].name 		= name;
	mWaves[id].typeWeb 		= 2;
	mWaves[id].indForWeb 	= ++a.indSetter;
	mWaves[id].pt2setter 	= ptSetter;
	
	this->keyRange.insert( id);
}


void animeClass::addChanger( int id, const String& name, void (*ptChanger)( int), byte delta )
{	
	mWaves[id]	 			= *a.addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].name 		= name;
	mWaves[id].delta 		= delta;
	mWaves[id].pt2changer 	= ptChanger;
}


void animeClass::makeWebLists()
{
	countWaves = keyButton.size();
	countRanges = keyRange.size();	
}
