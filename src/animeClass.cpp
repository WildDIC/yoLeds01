#include "animeClass.h"

extern void paletteSetActive( byte pollitraID, bool force);
extern void requestSave();


animeClass a;


bool animeClass::isID( uint8_t id)
{
	return keysAll.find( id) != keysAll.end();
}


bool animeClass::insertID( uint8_t id)
{
    // if ( this->keys.find( id) != this->keys.end()){ // ERROR
    // } else { this->keys.insert( id); }
	itKeys = keysAll.insert( id);
	if ( !itKeys.second)
	{	
		Serial.printf( "\nanim| -=> Error with ID: %d\n", id);
	}
	return !itKeys.second;
}

waveItem* animeClass::addDefault( uint8_t id)
{
	insertID( id);
	return new waveItem;
}

void animeClass::addStatic( uint8_t id, const String& name, void (*ptStatic)(), bool forWeb, uint8_t polDefault)
{
	mWaves[id] 				= *addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].name 		= name;
	mWaves[id].typeWeb 		= 1;
	mWaves[id].palDefault 	= polDefault;	
	mWaves[id].pt2static 	= ptStatic;
	
	if ( forWeb)
	{
		mWaves[id].isEffect 	= true;
		mWaves[id].leadOFF 		= true;
		mWaves[id].indWeb 		= ++indAnime;
		this->keyButton.insert( id);
	} 
}


void animeClass::addAmine( uint8_t id, const String& name, void (*ptAnime)(), bool forWeb, uint8_t polDefault, void (*ptAnimePre)())
{
	mWaves[id] 				= *addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].typeWeb 		= 1;
	mWaves[id].name 		= name;
	mWaves[id].palDefault 	= polDefault;
	mWaves[id].pt2Funca 	= ptAnime;
	mWaves[id].pt2static 	= ptAnimePre;

	if ( forWeb)
	{
		mWaves[id].leadOFF 	= true;
		mWaves[id].isEffect = true;
	 	mWaves[id].indWeb 	= ++indAnime;

		this->keyButton.insert( id);
	}
}

void animeClass::addSetter( uint8_t id, const String& name,  void (*ptSetter)(int), int min, int max, bool forWeb)
{
	mWaves[id]				= *addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].min 			= min;
	mWaves[id].max 			= max;
	mWaves[id].name 		= name;
	mWaves[id].pt2setter 	= ptSetter;
	mWaves[id].typeWeb 		= 2;	
	
	if ( forWeb)
	{
		mWaves[id].indWeb 		= ++indSetter;
		this->keyRange.insert( id);
	}
}


void animeClass::addChanger( uint8_t id, const String& name, void (*ptChanger)( int), signed char delta )
{	
	mWaves[id]	 			= *addDefault( id);
	mWaves[id].code 		= id;
	mWaves[id].name 		= name;
	mWaves[id].delta 		= delta;
	mWaves[id].pt2changer 	= ptChanger;
}


void animeClass::makeWebLists()
{
	countWaves  = keyButton.size();
	countRanges = keyRange.size();	

	vButton.resize( countWaves);
	vRanges.resize( countRanges);
	for ( auto key : keyButton)	vButton[mWaves[key].indWeb - 1] = key;  	
	for ( auto key : keyRange)	vRanges[mWaves[key].indWeb - 1] = key;  	

	// Serial.printf( "%d %d\n", key, mWaves[key].indForWeb - 1);
	// Serial.printf( "Vector size = %d\n", a.vButton.size());
	// for( auto key : a.vButton) Serial.printf( "%d \n", key );
}


void animeClass::applyWaveData( const waveItem &c)
{
	yo.loadOutside 	= false;

	yo.waveID 		= c.code;
	yo.name010 		= "AUX010";
	yo.name100 		= "AUX100";
	yo.name255 		= "AUX255";
	yo.name355 		= "AUX355";
	yo.name455 		= "AUX455";
	yo.nameSpeed	= "Speed";

	Ledas::setColors(		c.c1, 	c.c2,	 c.c3);
	Ledas::setSpeed( 		c.speed);
	Ledas::setSaturation( 	c.saturn);
	Ledas::setTemperature(  c.temp);
	Ledas::setAUX010( 		c.aux010);
	Ledas::setAUX100( 		c.aux100);
	Ledas::setAUX255( 		c.aux255);
	Ledas::setAUX355( 		c.aux355);
	Ledas::setAUX455( 		c.aux455);	
	Ledas::setShift( 		yo.shiftServ);
	Ledas::setCandle(		yo.candleServ);

	yo.loadOutside = true;

	currentNoWaves = c.indWeb - 1;
}


void animeClass::changeWave( uint8_t id, int webValue)
{
	changed  = true;			
	waveItem c = mWaves[id];

	if ( c.isEffect)
	{	 													// палитра, при смене активности, меняется засчет овновления селектора списка палитр. вызывается вебсервером.
															// если текущая палитра не определена - ставим дефолтную				
		if ( !isBetween( c.palCurrent, 1, yo.palTotal)) c.palCurrent = c.palDefault;
		applyWaveData( c);
		paletteSetActive( 	c.palCurrent, false);
		led.OFF();
	}

	#ifdef EERPROM_ENABLE
		if ( webValue != 666) requestSave();
	#endif			

	if ( c.pt2static) 			c.pt2static();	
	if ( c.isEffect){			pt2Func = c.pt2Funca;			// <==- все ради этого
								yo.pt2webUpRanges();
								yo.pt2webUpdate();}
	else if ( c.pt2setter) 		c.pt2setter(  webValue);			
	else if ( c.pt2changer) 	c.pt2changer( c.delta);
}


void animeClass::nextWave( int delta)
{
	a.currentNoWaves += delta;
	
	if ( a.currentNoWaves < 0) a.currentNoWaves = a.countWaves;
	if ( a.currentNoWaves > a.countWaves) a.currentNoWaves = 0;

	Serial.printf( "anim| Wave switch to: a.curIND = %d, size = %d, nextWave = %d \n", a.currentNoWaves, a.vButton.size(), a.vButton[a.currentNoWaves]);

	a.animeSet( a.vButton[a.currentNoWaves], 0);
}


void animeClass::animeSet( uint8_t id, int webValue)
{
	if ( id && isID( id))
	{
		Serial.printf( "anim| Wave ID: %3d. Web value: %3d.", id, webValue);
		Serial.print( " И наш выбор: '" + mWaves[id].name + "'.\n");

		changeWave( id, webValue);		
	} 	
}

