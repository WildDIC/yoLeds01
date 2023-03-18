#include "config.h"
#include "palettes.h"
#include "leds.h"

extern void requestSave();

CRGBPalette16 activePollitre;
CHSVPalette16 activePollitreHSV;
pollitraZ myPal[NUM_POLLITR];
CRGB c10, c20, c21, c30, c31, c32, c40, c41, c42, c43; // набор CRGB для формирования цвета для подменый переменных к случайным палитрам

void rgb2hsvpalette( uint8_t ind) //, CRGBPalette16 rgbpalette = activePollitre)
{
	for (uint8_t i = 0; i < 16; i++)
		{				
			myPal[ind].paletteHSV[i] = led.rgb2hsv( activePollitre[i]);

			// CHSV h = led.rgb2hsv( activePollitre[i]);
			// CRGB c = led.hsv2rgb( myPal[ind].paletteHSV[i]);
			// // CRGB f;
			// // hsv2rgb_rainbow( myPal[ind].paletteHSV[i], f);

			// Serial.printf( "%d. %d. o[%d, %d, %d] m[%d, %d, %d] f[%d, %d, %d ] h[%d, %d, %d]\n", 
			// 	ind, i, 
			// 	activePollitre[i].r, activePollitre[i].g, activePollitre[i].b, 
			// 	c.r, c.g, c.b, 
			// 	// f.r, f.g, f.b, 
			// 	h.h, h.s, h.v,
			// 	myPal[ind].paletteHSV[i].h, myPal[ind].paletteHSV[i].s, myPal[ind].paletteHSV[i].v);
		}
}

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

		rgb2hsvpalette( i+ind);		
		// rgb2hsvpalette( i+ind, &activePollitre);		
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
		return CHSV( random8(), 255, random8( 200, 255));
	}
	return color;	
}

/* Меням активную палитру и записываем ее в текующую активность ленты
@param byte pollitraID = Номер паллитры из myPal */
void paletteSetActive( byte pollitraID, bool force)
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

	if ( pollitraID <= 8)
	{
		rgb2hsvpalette( pollitraID);
	}

	activePollitreHSV = myPal[pollitraID].paletteHSV;

	mWaves[yo.lastPressed].pollCurrent = pollitraID;
	yo.pollCurrent = pollitraID;
	yo.pollDefault = mWaves[yo.lastPressed].pollDefault;

	#ifdef EERPROM_ENABLE 
		if ( force) requestSave();
	#endif

	#ifdef DEBUG_ENABLE
		Serial.printf( "-=> Поллитра ID: %d ( %s) for %d ( %s)\n", pollitraID, myPal[pollitraID].name, yo.lastPressed, mWaves[yo.lastPressed].name);	
	#endif
}


// CRGB hsv2rgb( CHSV in)
// {
//     double      hh, p, q, t, ff;
//     long        i;
//     CRGB        out;

//     if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
//         out.r = in.v;
//         out.g = in.v;
//         out.b = in.v;
//         return out;
//     }
//     hh = in.h;
//     if(hh >= 360.0) hh = 0.0;
//     hh /= 60.0;
//     i = (long)hh;
//     ff = hh - i;
//     p = in.v * (1.0 - in.s);
//     q = in.v * (1.0 - (in.s * ff));
//     t = in.v * (1.0 - (in.s * (1.0 - ff)));

//     switch(i) {
//     case 0:
//         out.r = in.v;
//         out.g = t;
//         out.b = p;
//         break;
//     case 1:
//         out.r = q;
//         out.g = in.v;
//         out.b = p;
//         break;
//     case 2:
//         out.r = p;
//         out.g = in.v;
//         out.b = t;
//         break;

//     case 3:
//         out.r = p;
//         out.g = q;
//         out.b = in.v;
//         break;
//     case 4:
//         out.r = t;
//         out.g = p;
//         out.b = in.v;
//         break;
//     case 5:
//     default:
//         out.r = in.v;
//         out.g = p;
//         out.b = q;
//         break;
//     }
//     return out;     
// }

  /**
      * @desc Convert hsv object to rgb
      * @param hsv - hsv color object
    */
    ;

    // CRGB hsvToRgb( CHSV hsv) {
    //   float h = hsv.h / 255;
    //   float s = hsv.s / 255;
    //   float v = hsv.v / 2255;
      
	//   float i = floor(h);
    //   float f = h - i;
    //   float p = v * (1 - s);
    //   float q = v * (1 - f * s);
    //   float t = v * (1 - (1 - f) * s);
    //   float mod = i % 6;
      
	//   var r = [v, q, p, p, t, v][mod];
    //   var g = [t, v, v, q, p, p][mod];
    //   var b = [p, p, t, v, v, q][mod];
      
	//   return {
    //     map( r * 255),
    //     map( g * 255),
    //     map( b * 255)
    //   };
    // }

    /**
      * @desc Convert rgb object to hsv
      * @param rgb - rgb object
    */
    ;

    // CHSV rgbToHsv( CRGB rgb) {
    //   var r = rgb.r / 255;
    //   var g = rgb.g / 255;
    //   var b = rgb.b / 255;
    //   var max = Math.max(r, g, b);
    //   var min = Math.min(r, g, b);
    //   var delta = max - min;
    //   var hue = 0;
    //   var value = max;
    //   var saturation = max === 0 ? 0 : delta / max;

    //   switch (max) {
    //     case min:
    //       hue = 0; // achromatic

    //       break;

    //     case r:
    //       hue = (g - b) / delta + (g < b ? 6 : 0);
    //       break;

    //     case g:
    //       hue = (b - r) / delta + 2;
    //       break;

    //     case b:
    //       hue = (r - g) / delta + 4;
    //       break;
    //   }

    //   return {
    //     h: hue * 60 % 360,
    //     s: clamp(saturation * 100, 0, 100),
    //     v: clamp(value * 100, 0, 100)
    //   };
    // } 

	
// CHSV rgb2hsv( CRGB in)
// {
//     CHSV        out;
//     double      min, max, delta;

//     min = in.r < in.g ? in.r : in.g;
//     min = min  < in.b ? min  : in.b;

//     max = in.r > in.g ? in.r : in.g;
//     max = max  > in.b ? max  : in.b;

//     out.v = max;                                // v
//     delta = max - min;
//     if (delta < 0.00001)
//     {
//         out.s = 0;
//         out.h = 0; // undefined, maybe nan?
//         return out;
//     }
//     if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
//         out.s = (delta / max) * 255;                  // s
//     } else {
//         // if max is 0, then r = g = b = 0              
//         // s = 0, h is undefined
//         out.s = 0.0;
//         out.h = NAN;                            // its now undefined
//         return out;
//     }
//     if( in.r >= max )                           // > is bogus, just keeps compilor happy
//     	out.h = 0   + 43 * ( in.g - in.b ) / delta;        // between yellow & magenta
//     else 
//     if( in.g >= max )
//         out.h =  85 + 43 * ( in.b - in.r ) / delta;  // between cyan & yellow
//     else
//         out.h = 171 + 43 * ( in.r - in.g ) / delta;  // between magenta & cyan

//     // out.h *= ( 60.0 * 0.7111);                              // degrees

//     if( out.h < 0.0 )
//         out.h += 256.0;

//     return out;
// }


