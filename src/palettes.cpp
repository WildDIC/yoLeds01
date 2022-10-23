#include "config.h"
#include "palettes.h"

extern void requestSave();

CRGBPalette16 activePollitre;
pollitraZ myPal[NUM_POLLITR];
CRGB c10, c20, c21, c30, c31, c32, c40, c41, c42, c43; // набор CRGB для формирования цвета для подменый переменных к случайным палитрам

/**/
void paletteStartUP(){
	byte ind = 0; // -1? Просто, что было красиво в ++
	myPal[++ind] = { "*solid white color*"};	 myPal[ind].palette = CRGBPalette16( CRGB::White);
	myPal[++ind] = { "- 1 Random color"};	 
	myPal[++ind] = { "- 2 Random colors"}; 
	myPal[++ind] = { "- 3 Random colors"}; 
	myPal[++ind] = { "- 4 Random colors"}; 
	myPal[++ind] = { "- c2 to c3 colors"}; 

	++ind;
	yo.lastCustPal = ind;		// для вебсервера
	
	for ( int i = 0; i < 58 + 11; i++){  // ЗДЕСЯ ИНДЕКСЫ ПАЛИТР МЕНЯТЬ КОЛИЧЕСТВО РАЗНЫЕ НАДО МНОГО СИЛЬНО  + ТАКОЕ в ВЕБСЕРВЕРЕ++ ( 74)
		byte tcp[72]; //support gradient palettes with up to 18 entries
		memcpy_P(tcp, (byte*)pgm_read_dword(&(gGradientPalettes[i])), 72);
		activePollitre.loadDynamicGradientPalette(tcp);
		myPal[i+ind].palette = activePollitre;
		if ( i + ind > 11){
			myPal[i+ind].name = String( i) + ". " + palette_names[i];
		} else{
			myPal[i+ind].name = palette_names[i];
		}		
	}
	
	// if (!wrap) paletteIndex = scale8(paletteIndex, 240); //cut off blend at palette "end"
	// fastled_col = ColorFromPalette(currentPalette, paletteIndex, pbri, (paletteBlend == 3)? NOBLEND:LINEARBLEND);
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
CRGB getCol( CRGB color){
	if ( yo.againButton || color.r == 0){
		return 	CHSV( random( 1, 255), 255, random( 200, 255));
	}
	return color;	
}

/* Меням активную палитру и записываем ее в текующую активность ленты
@param byte pollitraID = Номер паллитры из myPal */
void paletteSetActive( byte pollitraID, bool force=true){
	if (  pollitraID == 2){ 
		c10 = getCol( c10);
		#ifdef WEB_ENABLE
			yo.rndStyle = "\"--gr2: "+ getHEX( c10)+ ";\"";
		#endif

		activePollitre = CRGBPalette16( c10);
	}
	else if ( pollitraID == 3){ 
		c20 = getCol( c20);	c21 = getCol( c21);
		#ifdef WEB_ENABLE
			yo.rndStyle = "\"--gr3: linear-gradient( 90deg, "+ getHEX(c20)+", "+ getHEX(c21)+", "+ getHEX(c20)+");\"";
		#endif

		activePollitre = CRGBPalette16( c20, c21);
	}
	else if ( pollitraID == 4){ 
		c30 = getCol( c30); c31 = getCol( c31); c32 = getCol( c32);
		#ifdef WEB_ENABLE
			yo.rndStyle = "\"--gr4: linear-gradient( 90deg, "+ getHEX(c30)+", "+ getHEX(c31)+", "+ getHEX(c32)+", "+ getHEX(c30)+");\"";
		#endif

		activePollitre = CRGBPalette16( c30, c31, c32);	 
	}
	else if ( pollitraID == 5){ 
		c40 = getCol( c40); c41 = getCol( c41);	c42 = getCol( c42);	c43 = getCol( c43);
		#ifdef WEB_ENABLE
			yo.rndStyle = "\"--gr5: linear-gradient( 90deg, "+ getHEX(c40)+", "+ getHEX(c41)+", "+ getHEX(c42)+", "+ getHEX(c43)+", "+ getHEX(c40)+");\"";
		#endif
		activePollitre = CRGBPalette16( c40, c41, c42, c43);	
	}
	else if ( pollitraID == 6){ 
		#ifdef WEB_ENABLE
			yo.rndStyle = "\"--gr6: linear-gradient( 90deg, "+ getHEX( yo.c2)+", "+ getHEX( yo.c3)+", "+ getHEX( yo.c2)+");\"";
		#endif

		if ( force == true){
			activePollitre = CRGBPalette16( yo.c2, yo.c3, yo.c2);
		}	
		else{
			return;
		}	
	}
	else { 
		yo.rndStyle = "false";
		activePollitre = myPal[pollitraID].palette;
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

