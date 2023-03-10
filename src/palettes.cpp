#include "config.h"
#include "palettes.h"

extern void requestSave();

CRGBPalette16 activePollitre;
// CHSVPalette16 activePollitreHSV;
pollitraZ myPal[NUM_POLLITR];
CRGB c10, c20, c21, c30, c31, c32, c40, c41, c42, c43; // набор CRGB для формирования цвета для подменый переменных к случайным палитрам

/**/
void paletteStartUP()
{
	byte ind = 0; // -1? Просто, что было красиво в ++
	myPal[++ind] = { "*solid white color*"};	 myPal[ind].palette = CRGBPalette16( CRGB::White);
	myPal[++ind] = { "- 1 Random color"};	 
	myPal[++ind] = { "- 2 Random colors"}; 
	myPal[++ind] = { "- 3 Random colors"}; 
	myPal[++ind] = { "- c2 color"}; 
	myPal[++ind] = { "- c2 to c3 colors"}; 
	myPal[++ind] = { "- c2 to c3 to c2 colors"}; 
	myPal[++ind] = { "- c1 to c2 to c3 colors"}; 

	++ind;
	yo.lastCustPal = ind;		// для вебсервера
	
	for ( int i = 0; i < 58 + 11; i++){  // ЗДЕСЯ ИНДЕКСЫ ПАЛИТР МЕНЯТЬ КОЛИЧЕСТВО РАЗНЫЕ НАДО МНОГО СИЛЬНО  + ТАКОЕ в ВЕБСЕРВЕРЕ++ ( 74)
		byte tcp[72]; //support gradient palettes with up to 18 entries
		memcpy_P( tcp, (byte*)pgm_read_dword(&(gGradientPalettes[i])), 72);
		activePollitre.loadDynamicGradientPalette(tcp);
		
		myPal[i+ind].palette = activePollitre;
		
		if ( i > 11 - 1)
		{
			myPal[i+ind].name = String( i - 10) + ". " + palette_names[i];
		} 
		else
		{
			myPal[i+ind].name = String( i + 1) + ". " + palette_names[i];
		}		
	}	
}


String getHEX( CRGB color){
	// long hex = ( color.r * 65536) + ( color.g * 256) * color.b;
	// return " #" + String( hex, HEX);
	// return " #" + String( color.r, HEX) + String( color.g, HEX) +String( color.b, HEX);
	return " rgb(" + String( color.r) + ","+  String( color.g) +","+String( color.b) + ")";
}

/* Генерим новый CHSV случайный цвет для "рэндомных" палитр. 
Если цвет чорный или у веб-клиента повторно нажата активность - создаем новый.

@param color CRGB текущего цвета, возвращаем его, если не требуется обновления.
@return CRGB из сгенерированного CHSV цвета, потому что, сделать нормальный цвет можно только в HSV...*/
CRGB getCol( CRGB color)
{
	if ( yo.againButton || color.r == 0)
	{
		return CHSV( random8( 1, 256), 255, random8( 200, 255));
	}
	return color;	
}

/* Меням активную палитру и записываем ее в текующую активность ленты
@param byte pollitraID = Номер паллитры из myPal */
void paletteSetActive( byte pollitraID, bool force=true)
{
	switch ( pollitraID ) 	
	{
		case 2:
			c10 = getCol( c10);
			yo.rndStyle = "\"--gr2: "+ getHEX( c10)+ ";\"";			
			activePollitre = CRGBPalette16( c10);		
			break;
		case 3:
			c20 = getCol( c20);	c21 = getCol( c21);
			yo.rndStyle = "\"--gr3: linear-gradient( 90deg, "+ getHEX(c20)+", "+ getHEX(c21)+", "+ getHEX(c20)+");\"";
			activePollitre = CRGBPalette16( c20, c21, c20);		
			break;		
		case 4:
			c30 = getCol( c30); c31 = getCol( c31); c32 = getCol( c32);
			yo.rndStyle = "\"--gr4: linear-gradient( 90deg, "+ getHEX(c30)+", "+ getHEX(c31)+", "+ getHEX(c32)+");\"";
			activePollitre = CRGBPalette16( c30, c31, c32);	 		
			break;
		case 5:
			yo.rndStyle = "\"--gr5: "+ getHEX( yo.c2) + ";\"";
			activePollitre = CRGBPalette16( yo.c2);
			break;
		case 6:
			yo.rndStyle = "\"--gr6: linear-gradient( 90deg, "+ getHEX( yo.c2)+", "+ getHEX( yo.c3)+");\"";
			activePollitre = CRGBPalette16( yo.c2, yo.c3);
			break;
		case 7:
			yo.rndStyle = "\"--gr7: linear-gradient( 90deg, "+ getHEX( yo.c2)+", "+ getHEX( yo.c3)+", "+ getHEX( yo.c2)+");\"";
			activePollitre = CRGBPalette16( yo.c2, yo.c3, yo.c2);
			break;
		case 8:
			yo.rndStyle = "\"--gr8: linear-gradient( 90deg, "+ getHEX( yo.c1)+", "+ getHEX( yo.c2)+", "+ getHEX( yo.c3)+");\"";
			activePollitre = CRGBPalette16(  yo.c1, yo.c2, yo.c3);
			break;
		default:
			yo.rndStyle = "false";
			activePollitre = myPal[pollitraID].palette;		
			break;
	}

	mWaves[yo.lastPressed].pollCurrent = pollitraID;
	yo.pollCurrent = pollitraID;
	yo.pollDefault = mWaves[yo.lastPressed].pollDefault;

	#ifdef EERPROM_ENABLE 
		requestSave();
	#endif

	#ifdef DEBUG_ENABLE
		Serial.printf( "-=> Поллитра ID: %d ( %s) for %d ( %s)\n", pollitraID, myPal[pollitraID].name, yo.lastPressed, mWaves[yo.lastPressed].name);	
	#endif
}

