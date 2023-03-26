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

String PALL_HOLDER = ":root{\n" ;;

/**/
void paletteStartUP()
{	
	uint8_t ind 	= 1;	

	palStorage paletteStorage[] = {
		// { ind++, "*empty zero line*"},
		{ ind++, "*solid white color*"},
		{ ind++, "- 1 Random color"},	 
		{ ind++, "- 2 Random colors"}, 
		{ ind++, "- 3 Random colors"}, 
		{ ind++, "- c2 color"}, 
		{ ind++, "- c2 to c3 colors"}, 
		{ ind++, "- c2 to c3 to c2 colors"}, 
		{ ind++, "- c1 to c2 to c3 colors"},

		{ ind++, "RainbowColors", 	RainbowColors_my},			// 05 - 
		{ ind++, "Temperature",		temperature_gp},               //54-41 Temperature
		{ ind++, "PartyColors",		PartyColors_my},

		{ ind++, "- green to blue",	greenToBlue_my},
		{ ind++, "- red to violet",	redToViolet_my},
		{ ind++, "- blue to violet",blueToViolet_my},

		{ ind++, "Light of my fire",lightFie_my},				  // Light of my fire
		{ ind++, "Swamp fire",		retro2_16_gp},                 //17-04 Swamp fire
		{ ind++, "Orangery fire",	Orangery_gp},                  //47-34 Orangery
		{ ind++, "Hell fire",		orangeFire_my},				  // Hell fire
		{ ind++, "Sakura",			Sakura_gp},                    //49-36 Sakura

		{ ind++, "Pastel",			Sunset_Yellow_gp},             //20-07 Pastel
		{ ind++, "Fire",			lava_gp},                      //35-22 Fire
		{ ind++, "HeatColors",		heatColor_my},
		{ ind++, "Icefire",			fierce_ice_gp},                //36-23 Icefire
		{ ind++, "Grintage",		es_vintage_57_gp},             //32-19 Grintage
		{ ind++, "Yelblu Hot",		yelblu_hot_gp},                //64-51 Yelblu Hot
		{ ind++, "Magred",			BlacK_Magenta_Red_gp},         //41-28 Magred

		{ ind++, "Analogous",		Analogous_1_gp},               //18-05 Analogous
		{ ind++, "Orange & Teal",	Orange_Teal_gp},               //44-31 Orange & Teal	
		{ ind++, "Toxy Reaf",		toxy_reaf_gp},                 //58-45 Toxy Reaf
		{ ind++, "Drywet",			GMT_drywet_gp},                //30-17 Drywet
		{ ind++, "Yelblu",			Blue_Cyan_Yellow_gp},          //43-30 Yelblu
		{ ind++, "Tertiary",		Tertiary_01_gp},               //34-21 Tertiary
		{ ind++, "Atlantica",		Atlantica_gp},                 //51-38 Atlantica
		{ ind++, "Retro Clown",		retro_clown_gp},               //56-43 Retro Clown
		{ ind++, "Red Flash",		red_flash_gp},                 //66-53 Red Flash

		{ ind++, "Пастила",			deepForest_my},
		{ ind++, "Strange Fire",	candy2_gp},                     //70-57 Candy2
		{ ind++, "Lite Cactus",		lite_light_gp},                //65-52 Lite Light
		{ ind++, "Sunset",			Sunset_Real_gp},               //13-00 Sunset
		{ ind++, "Rivendell",		es_rivendell_15_gp},           //14-01 Rivendell
		{ ind++, "Breeze",			es_ocean_breeze_036_gp},       //15-02 Breeze
		{ ind++, "Red & Blue",		rgi_15_gp},                    //16-03 Red & Blue
		{ ind++, "Splash",			es_pinksplash_08_gp},          //19-06 Splash
		{ ind++, "Sunset 2",		Another_Sunset_gp},            //21-08 Sunset2
		{ ind++, "Beech",			Beech_gp},                     //22-09 Beech
		{ ind++, "Vintage",			es_vintage_01_gp},             //23-10 Vintage
		{ ind++, "Departure",		departure_gp},                 //24-11 Departure
		{ ind++, "Landscape",		es_landscape_64_gp},           //25-12 Landscape
		{ ind++, "Beach",			es_landscape_33_gp},           //26-13 Beach
		{ ind++, "Sherbet",			rainbowsherbet_gp},            //27-14 Sherbet
		{ ind++, "Hult",			gr65_hult_gp},                 //28-15 Hult
		{ ind++, "Hult 64",			gr64_hult_gp},                 //29-16 Hult64
		{ ind++, "Jul",				ib_jul01_gp},                  //31-18 Jul
		{ ind++, "Rewhi",			ib15_gp},                      //33-20 Rewhi
		{ ind++, "Cyane",			Colorfull_gp},                 //37-24 Cyane
		{ ind++, "Light Pink",		Pink_Purple_gp},               //38-25 Light Pink
		{ ind++, "Autumn",			es_autumn_19_gp},              //39-26 Autumn
		{ ind++, "Magenta",			BlacK_Blue_Magenta_White_gp},  //40-27 Magenta
		{ ind++, "Yelmag",			BlacK_Red_Magenta_Yellow_gp},  //42-29 Yelmag
		{ ind++, "Tiamat",			Tiamat_gp},                    //45-32 Tiamat
		{ ind++, "April Night",		April_Night_gp},               //46-33 April Night
		{ ind++, "C9",				C9_gp},                        //48-35 C9
		{ ind++, "Aurora",			Aurora_gp},                    //50-37 Aurora
		{ ind++, "C9 2",			C9_2_gp},                      //52-39 C9 2
		{ ind++, "C9 New",			C9_new_gp},                    //53-40 C9 New
		{ ind++, "Aurora 2",		Aurora2_gp},                   //55-42 Aurora 2
		{ ind++, "Candy",			candy_gp},                     //57-44 Candy
		{ ind++, "Fairy Reaf",		fairy_reaf_gp},                //59-46 Fairy Reaf
		{ ind++, "Semi Blue",		semi_blue_gp},                 //60-47 Semi Blue
		{ ind++, "Pink Candy",		pink_candy_gp},                //61-48 Pink Candy
		{ ind++, "Red Reaf",		red_reaf_gp},                  //62-49 Red Reaf
		{ ind++, "Aqua Flash",		aqua_flash_gp},                //63-50 Aqua Flash
		{ ind++, "Blink Red",		blink_red_gp},                 //67-54 Blink Red
		{ ind++, "Red Shift",		red_shift_gp},                 //68-55 Red Shift
		{ ind++, "Red Tide",		red_tide_gp},                  //69-56 Red Tide
		{ ind++, "RainbowStripeColors",RainbowStripeColors_my},
		{ ind++, "File Colors",	ForestColors_my}
	};

	yo.palRandom	= 8;
	yo.palCust 		= 11 + yo.palRandom;		// для вебсервера
	yo.palTotal 	= ind;

	PALL_HOLDER += "\t\t\t--gr0: #181E28;\n";
	PALL_HOLDER += "\t\t\t--gr1: #181E28;\n";
	PALL_HOLDER += "\t\t\t--gr2: #181E28;\n";
	PALL_HOLDER += "\t\t\t--gr3: linear-gradient( 90deg, #181E28, #ff0000);\n";
	PALL_HOLDER += "\t\t\t--gr4: linear-gradient( 90deg, #181E28, #ff0000, #00ff00);\n";
	PALL_HOLDER += "\t\t\t--gr5: linear-gradient( 90deg, #181E28, #ff0000, #00ff00, #0000ff);\n";
	PALL_HOLDER += "\t\t\t--gr6: #181E28;\n";
	PALL_HOLDER += "\t\t\t--gr7: linear-gradient( 90deg, #181E28, #ff0000);\n";
	PALL_HOLDER += "\t\t\t--gr8: linear-gradient( 90deg, #181E28, #ff0000, #0000ff);\n";

	for ( auto pal : paletteStorage)
	{
		uint8_t ind = pal.ind;

		if ( pal.name)  		// ифы что бы номерочки ставить разные в нпазваниях палитр в селекторе на сайте.
		{
			if 		( ind <= yo.palRandom) 	myPal[ind].name = pal.name;
			else if ( ind <=  yo.palCust) 	myPal[ind].name = String( ind - yo.palRandom) + ". " + pal.name;
			else							myPal[ind].name = String( ind - yo.palCust  ) + ". " + pal.name;
		}
		
		if ( pal.pals)
		{
			byte tcp[72]; //support gradient palettes with up to 18 entries
			memcpy_P( tcp, ( byte*) pgm_read_dword( &( pal.pals)), 72);	
			activePollitre.loadDynamicGradientPalette( tcp);
			
			myPal[ind].palette = activePollitre;		

			rgb2hsvpalette( ind);	
			
			PALL_HOLDER += "\t\t\t--gr"+ String( ind) +": linear-gradient( 90deg, ";
			for ( byte i = 0; i < sizeof( tcp); i += 4)
			{
				String coma = ( tcp[i] == 255) ? "%" : "%,";

				PALL_HOLDER += "rgb(" + String( tcp[i+1]) + "," 
									  + String( tcp[i+2]) + "," 
									  + String( tcp[i+3]) + ") "
									  + String( tcp[i] * 100 / 255) + coma;   // сдвигать >> 8 не надо, проценты получаются кривые малость 100 - 99
				
				if ( tcp[i]== 255) break;
			}
			PALL_HOLDER += ");\n";
		}
	}
	PALL_HOLDER += "\t\t}";
}


String getHEX( const CRGB& color){
	// long hex = ( color.r * 65536) + ( color.g * 256) * color.b;
	// return " #" + String( hex, HEX);
	// return " #" + String( color.r, HEX) + String( color.g, HEX) +String( color.b, HEX);
	return " rgb(" + String( color.r) + "," +  String( color.g) + "," + String( color.b) + ")";
}

/* Генерим новый CHSV случайный цвет для "рэндомных" палитр. 
Если цвет чорный или у веб-клиента повторно нажата активность - создаем новый.

@param color CRGB текущего цвета, возвращаем его, если не требуется обновления.
@return CRGB из сгенерированного CHSV цвета, потому что, сделать нормальный цвет можно только в HSV...*/
CRGB getCol( const CRGB& color)
{
	if ( yo.againButton || color.r == 0)
	{
		return CHSV( random8(), random8( 200, 255), random8( 200, 255));
	}
	return color;	
}

/* Меням активную палитру и записываем ее в текующую активность ленты
@param pollitraID = Номер паллитры из myPal
@param force необходимость запросить сохранение после выбора палитры, 
скорее всего надо, когда палитру меняем из веба, а не из ИРДы */
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

	mWaves[yo.waveID].palCurrent = pollitraID;
	yo.palCurrent = pollitraID;
	yo.palDefault = mWaves[yo.waveID].palDefault;

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
//     if( in.r >= max )                           // > is bogus, just keepaletteStorage compilor happy
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


