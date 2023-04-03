#include "animeClass.h"

extern void paletteSetActive( byte pollitraID, bool force);
extern void requestSave();


animeClass a;
// waveItem c; 								// копия данных в оперативной работе вытащенная из откуда-то ( мапы м вавами или из  сейвника)

bool animeClass::isInID( int id)
{
    // if ( this->keys.find( id) != this->keys.end()){ // ERROR
    // } else { this->keys.insert( id); }
	itKeys = keysAll.insert( id);
	if ( !itKeys.second){	
		Serial.printf( "\nanim| -=> Error with ID: %d\n", id);
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
	mWaves[id].palDefault 	= polDefault;	
	mWaves[id].pt2static 	= ptStatic;
	
	if ( forWeb)
	{
		mWaves[id].isEffect 	= true;
		mWaves[id].leadOFF 		= true;
		mWaves[id].indWeb 	= ++a.indAnime;
		this->keyButton.insert( id);
	} 
}


void animeClass::addAmine( int id, const String& name, void (*ptAnime)(), bool forWeb, uint8_t polDefault, void (*ptAnimePre)())
{
	mWaves[id] 				= *a.addDefault( id);
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
	 	mWaves[id].indWeb 	= ++a.indAnime;

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
	mWaves[id].indWeb 		= ++a.indSetter;
	mWaves[id].pt2setter 	= ptSetter;
	
	this->keyRange.insert( id);
}


void animeClass::addChanger( int id, const String& name, void (*ptChanger)( int), signed char delta )
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

	a.vButton.resize( countWaves);
	a.vRanges.resize( countRanges);
	for ( auto key : keyButton)	a.vButton[mWaves[key].indWeb - 1] = key;  	
	for ( auto key : keyRange)	a.vRanges[mWaves[key].indWeb - 1] = key;  	

	// Serial.printf( "%d %d\n", key, mWaves[key].indForWeb - 1);
	// Serial.printf( "Vector size = %d\n", a.vButton.size());
	// for( auto key : a.vButton) Serial.printf( "%d \n", key );
}


// void animeClass::applyWaveData()
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

	led.setColors(		c.c1, 	c.c2,	 c.c3);
	// setBrightness( 	mbIter->second.bright);
	led.setSpeed( 		c.speed);
	led.setSaturation( 	c.saturn);
	led.setTemperature( c.temp);
	led.setAUX010( 		c.aux010);
	led.setAUX100( 		c.aux100);
	led.setAUX255( 		c.aux255);
	led.setAUX355( 		c.aux355);
	led.setAUX455( 		c.aux455);
	// paletteSetActive( 	mbIter->second.pollCurrent, false);
	// led.OFF();
	
	// Serial.println( "-==> Vars applied.");
	// Serial.printf("ind=%d, pol=%d, bri=%d, speed=%d, sat=%d, temp=%d, a010=%d, a100=%d, a255=%d\n", resValue, mbIter->second.pollCurrent,	mbIter->second.bright, mbIter->second.speed, mbIter->second.saturn, mbIter->second.temp, mbIter->second.aux010, mbIter->second.aux100, mbIter->second.aux255);
	// Serial.printf("ind=%d, pol=%d, bri=%d, speed=%d, sat=%d, temp=%d, a010=%d, a100=%d, a255=%d\n", yo.lastPressed, mbIter->second.pollCurrent,	yo.currentBrightness, yo.currentSpeed, yo.currentSaturn, yo.currentTemp, yo.AUX010, yo.AUX100, yo.AUX255);
	yo.loadOutside = true;

	a.currentNoWaves = c.indWeb - 1;
}


void animeClass::changeWave( int resValue, int webValue)
{
	a.changed  = true;			
	waveItem c = mWaves[resValue];

	if ( c.isEffect)
	{	 													// палитра, при смене активности, меняется засчет овновления селектора списка палитр. вызывается вебсервером.
															// если текущая палитра не определена - ставим дефолтную				
		if ( !isBetween( c.palCurrent, 1, yo.palTotal)) c.palCurrent = c.palDefault;
		a.applyWaveData( c);
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

	irdaServer( a.vButton[a.currentNoWaves], 0);
}