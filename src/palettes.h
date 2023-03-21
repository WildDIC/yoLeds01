#ifndef __PALETTES_H
#define __PALETTES_H

extern CRGBPalette16 activePollitre;
extern CHSVPalette16 activePollitreHSV;

void paletteStartUP();
void paletteSetActive( byte pollitraID, bool force=false);

const byte ib_jul01_gp[] PROGMEM = {
	0, 194,  1,  1,
   94,   1, 29, 18,
  132,  57,131, 28,
  255, 113,  1,  1};

// Gradient palette "es_vintage_57_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_57.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

const byte es_vintage_57_gp[] PROGMEM = {
	0,   2,  1,  1,
   23,  18,  1,  0,
   84,  69, 29,  1,
  153, 167,135, 10,
  255, 200, 190, 25};
//   255,  46, 56,  4};

const byte heatColor_my[] PROGMEM = {
	0, 		0, 		0, 		0,
	85,		136,	0, 		0,
	170,	255,	0, 		0,
	255, 	255, 	165,	0};


// Gradient palette "es_vintage_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

const byte es_vintage_01_gp[] PROGMEM = {
	0,   4,  1,  1,
   51,  16,  0,  1,
   76,  97,104,  3,
  101, 255,131, 19,
  127,  67,  9,  4,
  153,  16,  0,  1,
  229,   4,  1,  1,
  255,   4,  1,  1};


// Gradient palette "es_rivendell_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/rivendell/tn/es_rivendell_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

const byte es_rivendell_15_gp[] PROGMEM = {
	0,   1, 14,  5,
  101,  16, 36, 14,
  165,  56, 68, 30,
  242, 150,156, 99,
  255, 150,156, 99};


// Gradient palette "rgi_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/rgi/tn/rgi_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.
// Edited to be brighter

const byte rgi_15_gp[] PROGMEM = {
	0,   4,  1, 70,
   31,  55,  1, 30,
   63, 255,  4,  7,
   95,  59,  2, 29,
  127,  11,  3, 50,
  159,  39,  8, 60,
  191, 112, 19, 40,
  223,  78, 11, 39,
  255,  29,  8, 59};


// Gradient palette "retro2_16_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/retro2/tn/retro2_16.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

const byte retro2_16_gp[] PROGMEM = {
  	  0,  46,   7, 0,
	255, 188, 135, 0};


// Gradient palette "Analogous_1_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/red/tn/Analogous_1.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

const byte Analogous_1_gp[] PROGMEM = {
	0,   3,  0,255,
   63,  23,  0,255,
  127,  67,  0,255,
  191, 142,  0, 45,
  255, 255,  0,  0};


// Gradient palette "es_pinksplash_08_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_08.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

const byte es_pinksplash_08_gp[] PROGMEM = {
	0, 126, 11,255,
  127, 197,  1, 22,
  175, 210,157,172,
  221, 157,  3,112,
  255, 157,  3,112};


// Gradient palette "es_ocean_breeze_036_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_036.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

const byte es_ocean_breeze_036_gp[] PROGMEM = {
	0,   1,  6,  7,
   89,   1, 99,111,
  153, 144,209,255,
  255,   0, 73, 82};


// Gradient palette "departure_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/mjf/tn/departure.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 88 bytes of program space.

const byte departure_gp[] PROGMEM = {
	0,   8,  3,  0,
   42,  23,  7,  0,
   63,  75, 38,  6,
   84, 169, 99, 38,
  106, 213,169,119,
  116, 255,255,255,
  138, 135,255,138,
  148,  22,255, 24,
  170,   0,255,  0,
  191,   0,136,  0,
  212,   0, 55,  0,
  255,   0, 55,  0};


// Gradient palette "es_landscape_64_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_64.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

const byte es_landscape_64_gp[] PROGMEM = {
	0,   0,  0,  0,
   37,   2, 25,  1,
   76,  15,115,  5,
  127,  79,213,  1,
  128, 126,211, 47,
  130, 188,209,247,
  153, 144,182,205,
  204,  59,117,250,
  255,   1, 37,192};


// Gradient palette "es_landscape_33_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_33.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

const byte es_landscape_33_gp[] PROGMEM = {
	0,   1,  5,  0,
   19,  32, 23,  1,
   38, 161, 55,  1,
   63, 229,144,  1,
   66,  39,142, 74,
  255,   1,  4,  1};


// Gradient palette "rainbowsherbet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/icecream/tn/rainbowsherbet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

const byte rainbowsherbet_gp[] PROGMEM = {
	0, 255, 33,  4,
   43, 255, 68, 25,
   86, 255,  7, 25,
  127, 255, 82,103,
  170, 255,255,242,
  209,  42,255, 22,
  255,  87,255, 65};


// Gradient palette "gr65_hult_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr65_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

const byte gr65_hult_gp[] PROGMEM = {
	0, 247,176,247,
   48, 255,136,255,
   89, 220, 29,226,
  160,   7, 82,178,
  216,   1,124,109,
  255,   1,124,109};


// Gradient palette "gr64_hult_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr64_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

const byte gr64_hult_gp[] PROGMEM = {
	0,   1,124,109,
   66,   1, 93, 79,
  104,  52, 65,  1,
  130, 115,127,  1,
  150,  52, 65,  1,
  201,   1, 86, 72,
  239,   0, 55, 45,
  255,   0, 55, 45};


// Gradient palette "GMT_drywet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_drywet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

const byte GMT_drywet_gp[] PROGMEM = {
	0,  47, 30,  2,
   42, 213,147, 24,
   84, 103,219, 52,
  127,   3,219,207,
  170,   1, 48,214,
  212,   1,  1,111,
  255,   1,  7, 33};


// Gradient palette "ib15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/general/tn/ib15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

const byte ib15_gp[] PROGMEM = {
	0, 113, 91,147,
   72, 157, 88, 78,
   89, 208, 85, 33,
  107, 255, 29, 11,
  141, 137, 31, 39,
  255,  59, 33, 89};


// Gradient palette "Tertiary_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/vermillion/tn/Tertiary_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

const byte Tertiary_01_gp[] PROGMEM = {
	0,   0,  1,255,
   63,   3, 68, 45,
  127,  23,255,  0,
  191, 100, 68,  1,
  255, 255,  1,  4};


// Gradient palette "lava_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/lava.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

const byte lava_gp[] PROGMEM = {
	0,   0,  0,  0,
   10,  38,  0,  0,
   46, 113,  0,  0,
   78, 142,  3,  1,
  109, 175, 17,  1,
  126, 213, 44,  2,
  154, 255, 82,  4,
  178, 255,115,  4,
  192, 255,156,  4,
  208, 255,203,  4,
  230, 255,255,  4,
  244, 255,255, 31,
  255, 255,255, 50};
//   255, 255,255,255};


// Gradient palette "fierce_ice_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/fierce-ice.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

const byte fierce_ice_gp[] PROGMEM = {
	0,   0,  0,  0,
   19,   0,  9, 45,
   89,   0, 38,255,
  149,   3,100,255,
  180,  23,199,255,
  227,  90,235,255,
  255, 130,255,255};


// Gradient palette "Colorfull_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Colorfull.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

const byte Colorfull_gp[] PROGMEM = {
	0,  10, 85,  5,
   25,  29,109, 18,
   60,  59,138, 42,
   93,  83, 99, 52,
  106, 110, 66, 64,
  109, 123, 49, 65,
  113, 139, 35, 66,
  116, 192,117, 98,
  124, 255,255,137,
  168, 100,180,155,
  255,  22,121,174};


// Gradient palette "Pink_Purple_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Pink_Purple.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

const byte Pink_Purple_gp[] PROGMEM = {
	0,  19,  2, 39,
   25,  26,  4, 45,
   51,  33,  6, 52,
   76,  68, 62,125,
  102, 118,187,240,
  109, 163,215,247,
  114, 217,244,255,
  122, 159,149,221,
  149, 113, 78,188,
  183, 128, 57,155,
  255, 146, 40,123};


// Gradient palette "Sunset_Real_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

const byte Sunset_Real_gp[] PROGMEM = {
	0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160};


// Gradient palette "Sunset_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

const byte Sunset_Yellow_gp[] PROGMEM = {
	0,  10, 62,123,
   36,  56,130,103,
   87, 153,225, 85,
  100, 199,217, 68,
  107, 255,207, 54,
  115, 247,152, 57,
  120, 239,107, 61,
  128, 247,152, 57,
  180, 255,207, 54,
  223, 255,227, 48,
  255, 255,248, 42};


// Gradient palette "Beech_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Beech.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 60 bytes of program space.

const byte Beech_gp[] PROGMEM = {
	0, 255,252,214,
   12, 255,252,214,
   22, 255,252,214,
   26, 190,191,115,
   28, 137,141, 52,
   28, 112,255,205,
   50,  51,246,214,
   71,  17,235,226,
   93,   2,193,199,
  120,   0,156,174,
  133,   1,101,115,
  136,   1, 59, 71,
  136,   7,131,170,
  208,   1, 90,151,
  255,   0, 56,133};


// Gradient palette "Another_Sunset_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Another_Sunset.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

const byte Another_Sunset_gp[] PROGMEM = {
	0, 110, 49, 11,
   29,  55, 34, 10,
   68,  22, 22,  9,
   68, 239,124,  8,
   97, 220,156, 27,
  124, 203,193, 61,
  178,  33, 53, 56,
  255,   0,  1, 52};





// Gradient palette "es_autumn_19_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/autumn/tn/es_autumn_19.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

const byte es_autumn_19_gp[] PROGMEM = {
	0,  26,  1,  1,
   51,  67,  4,  1,
   84, 118, 14,  1,
  104, 137,152, 52,
  112, 113, 65,  1,
  122, 133,149, 59,
  124, 137,152, 52,
  135, 113, 65,  1,
  142, 139,154, 46,
  163, 113, 13,  1,
  204,  55,  3,  1,
  249,  17,  1,  1,
  255,  17,  1,  1};


// Gradient palette "BlacK_Blue_Magenta_White_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Blue_Magenta_White.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

const byte BlacK_Blue_Magenta_White_gp[] PROGMEM = {
	0,   0,  0,  0,
   42,   0,  0, 45,
   84,   0,  0,255,
  127,  42,  0,255,
  170, 255,  0,255,
  212, 255, 55,255,
  255, 255,255,255};


// Gradient palette "BlacK_Magenta_Red_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Magenta_Red.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

const byte BlacK_Magenta_Red_gp[] PROGMEM = {
	0,   0,  0,  0,
   63,  42,  0, 45,
  127, 255,  0,255,
  191, 255,  0, 45,
  255, 255,  0,  0};


// Gradient palette "BlacK_Red_Magenta_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Red_Magenta_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

const byte BlacK_Red_Magenta_Yellow_gp[] PROGMEM = {
	0,   0,  0,  0,
   42,  42,  0,  0,
   84, 255,  0,  0,
  127, 255,  0, 45,
  170, 255,  0,255,
  212, 255, 55, 45,
  255, 255,255,  0};


// Gradient palette "Blue_Cyan_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Blue_Cyan_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

const byte Blue_Cyan_Yellow_gp[] PROGMEM = {
	0,   0,  0,255,
   63,   0, 55,255,
  127,   0,255,255,
  191,  42,255, 45,
  255, 255,255,  0};


//Custom palette by Aircoookie

const byte Orange_Teal_gp[] PROGMEM = {
	0,   0,150, 92,
   55,   0,150, 92,
  200, 255, 72,  0,
  255, 255, 72,  0};

//Custom palette by Aircoookie

const byte Tiamat_gp[] PROGMEM = {
	0,   1,  2, 14, //gc
   33,   2,  5, 35, //gc from 47, 61,126
  100,  13,135, 92, //gc from 88,242,247
  120,  43,255,193, //gc from 135,255,253
  140, 247,  7,249, //gc from 252, 69,253
  160, 193, 17,208, //gc from 231, 96,237
  180,  39,255,154, //gc from 130, 77,213
  200,   4,213,236, //gc from 57,122,248
  220,  39,252,135, //gc from 177,254,255
  240, 193,213,253, //gc from 203,239,253
  255, 255,249,255};
  
//Custom palette by Aircoookie

const byte April_Night_gp[] PROGMEM = {
    0,   1,  2, 44,
   84,   9, 11,112,
  168,  77, 19,105,
  255, 255,100,137};

const byte Orangery_gp[] PROGMEM = {
// 	0, 255, 95, 23,
//    30, 255, 82,  0,
//    60, 223, 13,  8,
//    90, 144, 44,  2,
//   120, 255,110, 17,
//   150, 255, 69,  0,
//   180, 158, 13, 11,
//   210, 241, 82, 17,
//   255, 213, 37,  4};
  0, 	54,   11, 0,
  128, 	255, 120, 0,
  255, 	255, 170, 0};

//inspired by Mark Kriegsman https://gist.github.com/kriegsman/756ea6dcae8e30845b5a
const byte C9_gp[] PROGMEM = {
	0, 184,  4,  0, //red
   60, 184,  4,  0,
   65, 144, 44,  2, //amber
  125, 144, 44,  2,
  130,   4, 96,  2, //green
  190,   4, 96,  2,
  195,   7,  7, 88, //blue
  255,   7,  7, 88};

const byte Sakura_gp[] PROGMEM = {
	0, 196, 19, 10,
   65, 255, 69, 45,
  130, 223, 45, 72,
  195, 255, 82,103,
  255, 223, 13, 17};

const byte Aurora_gp[] PROGMEM = {
	0,   1,  5, 45, //deep blue
   64,   0,200, 23,
  128,   0,255,  0, //green
  170,   0,243, 45,
  200,   0,135,  7,
  255,   1,  5, 45};//deep blue

const byte Atlantica_gp[] PROGMEM = {
	0,   0, 28,112, //#001C70
   50,  32, 96,255, //#2060FF
  100,   0,243, 45,
  150,  12, 95, 82, //#0C5F52
  200,  25,190, 95, //#19BE5F
  255,  40,170, 80};//#28AA50

  const byte C9_2_gp[] PROGMEM = {
    0,  38, 73,145,
   30,   7, 19, 51,
   56,  73, 40,230,
   86,  55, 49,182,
  112,  15,135,250,
  140, 125,122,212,
  170,  13, 55,228,
  198, 123, 65,228,
  229,   7, 19, 51,
  255,  38, 73,145};

  //C9, but brighter and with a less purple blue
  const byte C9_new_gp[] PROGMEM = {
    0,  55, 19,103,
   51,  95, 32,133,
  101, 167, 44,162,
  153, 125,182,237,
  204,  84,127,207,
  255,  19, 40,114};
  
// Gradient palette "temperature_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/arendal/tn/temperature.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 144 bytes of program space.  

const byte temperature_gp[] PROGMEM = {
	0,   1, 27,105,
   14,   1, 40,127,
   28,   1, 70,168,
   42,   1, 92,197,
   56,   1,119,221,
   70,   3,130,151,
   84,  23,156,149,
   99,  67,182,112,
  113, 121,201, 52,
  127, 142,203, 11,
  141, 224,223,  1,
  155, 252,187,  2,
  170, 247,147,  1,
  184, 237, 87,  1,
  198, 229, 43,  1,
  226, 171,  2,  2,
  240,  80,  3,  3,
  255,  80,  3,  3};

  const byte Aurora2_gp[] PROGMEM = {
	  0,  17, 177,  13,    //Greenish
	 64, 121, 242,   5,    //Greenish
	128,  25, 173, 121,    //Turquoise
	192, 250,  77, 127,    //Pink
	255, 171, 101, 221     //Purple
  };

  // Gradient palette "bhw1_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

const byte retro_clown_gp[] PROGMEM = {
	0, 227,101,  3,
  117, 194, 18, 19,
  255,  92,  8,192};

// Gradient palette "bhw1_04_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_04.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

const byte candy_gp[] PROGMEM = {
	0, 229,227,  1,
   15, 227,101,  3,
  142,  40,  1, 80,
  198,  17,  1, 79,
  255,   0,  0, 45};

// Gradient palette "bhw1_05_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_05.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

const byte toxy_reaf_gp[] PROGMEM = {
	0,   1,221, 53,
  255,  73,  3,178};

// Gradient palette "bhw1_06_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_06.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

const byte  fairy_reaf_gp[] PROGMEM = {
	0, 184,  1,128,
  160,   1,193,182,
  219, 153,227,190,
  255, 255,255,255};

// Gradient palette "bhw1_14_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_14.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

const byte semi_blue_gp[] PROGMEM = {
	0,   0,  0,  0,
   12,   1,  1,  3,
   53,   8,  1, 22,
   80,   4,  6, 89,
  119,   2, 25,216,
  145,   7, 10, 99,
  186,  15,  2, 31,
  233,   2,  1,  5,
  255,   0,  0,  0};

// Gradient palette "bhw1_three_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_three.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

const byte pink_candy_gp[] PROGMEM = {
    0, 229, 22, 51,
   45, 242,117, 52,
   66, 255,235, 18,
   99, 249,193,  4,
  135, 106, 77,153,
  170,  39, 15,151,
  204, 121,142, 71,
  242,  57,122,190,
  255,  57,122,190};

// Gradient palette "bhw1_w00t_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_w00t.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

const byte red_reaf_gp[] PROGMEM = {
	0,   3, 13, 43,
  104,  78,141,240,
  188, 255,  0,  0,
  255,  28,  1,  1};


// Gradient palette "bhw2_23_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_23.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Red & Flash in SR
// Size: 28 bytes of program space.

const byte aqua_flash_gp[] PROGMEM = {
	0,   0,  0,  0,
   66,  57,227,233,
   96, 255,255,  8,
  124, 255,255,255,
  153, 255,255,  8,
  188,  57,227,233,
  255,   0,  0,  0};

// Gradient palette "bhw2_xc_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_xc.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// YBlue in SR
// Size: 28 bytes of program space.

const byte yelblu_hot_gp[] PROGMEM = {
	0,   4,  2,  9,
   58,  16,  0, 47,
  122,  24,  0, 16,
  158, 144,  9,  1,
  183, 179, 45,  1,
  219, 220,114,  2,
  255, 234,237,  1};

const byte PartyColors_my[] PROGMEM = {
	0,	85,	0,	171,
	17,	132,	0,	124,
	34,	181,	0,	75,
	51,	229,	0,	27,
	68,	232,	23,	0,
	85,	184,	71,	0,
	102,	171,	119,	0,
	119,	171,	171,	0,
	136,	171,	85,	0,
	153,	221,	34,	0,
	170,	242,	0,	14,
	187,	194,	0,	62,
	204,	143,	0,	113,
	221,	95,	0,	161,
	238,	47,	0,	208,
	255,	0,	7,	249};

const byte RainbowColors_my[] PROGMEM = {
	0,		255,	0,		0,
	17,		213,	42,		0,
	34,		171,	85,		0,
	51,		171,	127,	0,
	68,		171,	171,	0,
	85,		86,		213,	0,
	102,	0,		255,	0,
	119,	0,		213,	42,
	136,	0,		171,	85,
	153,	0,		86,		170,
	170,	0,		0,		255,
	187,	42,		0,		213,
	204,	85,		0,		171,
	221,	127,	0,		129,
	238,	171,	0,		85,
	255,	213,	0,		43};

const byte orangeFire_my[] PROGMEM = {
	0, 		255, 0, 	0, 
	255, 	255, 136, 	0};

const byte greenToBlue_my[] PROGMEM = {
	0, 		50, 	255, 	0, 
	127, 	0, 		50, 	255,
	255, 	50,		255, 	0};

const byte redToViolet_my[] PROGMEM = {
	0, 		255, 	0, 		0,
	127, 	127, 	0, 		255,
	255, 	255, 	0, 		0};

const byte redGreenBlue_my[] PROGMEM = {
	0, 		255, 	0, 		0,
	85,		0, 		255, 	0,
	170, 	0, 		0, 		255,
	255, 	255,	0, 		0};

const byte blueToViolet_my[] PROGMEM = {
	0, 		0, 	176, 	179,
	127, 	89, 0, 		176,
	255, 	0, 	176, 	179};

// const byte OceanColors_my[] PROGMEM = {
// 	0,		25,		25,		112,
// 	17,		0,		0,		136,
// 	34,		25,		25,		112,
// 	51,		0,		0,		128,
// 	68,		0,		0,		136,
// 	85,		0,		0,		205,
// 	102,	46,		136,	87,
// 	119,	0,		128,	128,
// 	136,	95,		158,	160,
// 	153,	0,		0,		255,
// 	170,	0,		139,	139,
// 	187,	100,	149,	237,
// 	204,	127,	255,	212,
// 	221,	46,		139,	87,
// 	238,	0,		255,	255,
// 	255,	135,	206,	250
// };




 // Gradient palette "bhw2_45_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_45.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

const byte lite_light_gp[] PROGMEM = {
    0, 192, 50,207,
   25, 192, 50,207,
   51, 133, 50,207,
   76,  87, 50,207,
  102,  59, 61,207,
  127,  37, 73,207,
  153,  37, 97,207,
  178,  37,127,207,
  204,  37,166,172,
  229,  37,213,140,
  255,  37,213,140};


// Gradient palette "bhw2_22_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_22.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Pink Plasma in SR
// Size: 20 bytes of program space.

const byte red_flash_gp[] PROGMEM = {
    0, 247,199, 87,
   53, 247,199, 87,
  107, 242,156, 75,
  119, 234,119, 65,
  132, 213, 88, 66,
  145, 194, 62, 67,
  158, 142, 33, 84,
  202,  98, 13,105,
  247,  34, 10, 35,
  251,   5,  9,  5,
  255,   5,  9,  5};



// Gradient palette "bhw3_40_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_40.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

const byte blink_red_gp[] PROGMEM = {
    0,  23,  4, 32,
   63,  98, 31, 52,
  127, 224,138, 24,
  191,   7, 55,164,
  255,  23,  4, 32};


// Gradient palette "bhw3_52_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_52.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Yellow2Blue in SR
// Size: 28 bytes of program space.

const byte red_shift_gp[] PROGMEM = {
    0, 206,149,133,
   40, 190,  8, 61,
   76,  45,  7, 85,
  101,   9, 18,130,
  140,   7,162,138,
  188, 153,219,194,
  229,   7,162,138,
  255,   7,162,138};


// Gradient palette "bhw4_097_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw4/tn/bhw4_097.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Yellow2Red in SR
// Size: 44 bytes of program space.

const byte red_tide_gp[] PROGMEM = {
    0,  43,  3,153,
   63, 100,  4,103,
  127, 188,  5, 66,
  191, 161, 11,115,
  255, 135, 20,182};



// Gradient palette "bhw4_017_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw4/tn/bhw4_017.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

const byte candy2_gp[] PROGMEM = {
    0,  21,  3, 56,
   25,  21,  3, 56,
   51,  29, 10, 95,
   76,  39, 21,145,
  102,  40, 33,156,
  127,  43, 47,170,
  153,  58, 73,184,
  178,  77,105,197,
  204, 109,141,210,
  229, 146,184,223,
  255, 146,184,223};

const byte RainbowStripeColors_my[] PROGMEM = {
    0,  75,  1,221,
   30, 252, 73,255,
   48, 169,  0,242,
  119,   0,149,242,
  170,  43,  0,242,
  206, 252, 73,255,
  232,  78, 12,214,
  255,   0,149,242};

const byte deepForest_my[] PROGMEM = {
    0,   0,255,255,
  127, 255,  0,255,
  191, 255,255,  0,
  255, 255,255,255};


const byte ForestColors_my[] PROGMEM = {
    0, 113, 91,147,
   72, 157, 88, 78,
   89, 208, 85, 33,
  107, 255, 29, 11,
  141, 137, 31, 39,
  255,  59, 33, 89};


const byte lightFie_my[] PROGMEM = {
	0, 			255, 95, 0,
	// 127, 	255, 94, 0,
	// 255, 	255, 195, 0};
	255, 		255, 195, 0};



const String palette_names[70] = {
	// "Default","* Random Cycle","* Color 1","* Colors 1&2","* Color Gradient","* Colors Only","Party","Cloud","Lava","Ocean",
	// "Forest","Rainbow","Rainbow Bands",
	"RainbowColors", "Temperature", "PartyColors", "- green to blue", "- red to violet", "- blue to violet", 			/// 11 palitres
	"Light of my fire", "Swamp fire",  "Orangery fire", "Hell fire", "Sakura",
	
	"Pastel", 	
	"Fire", "HeatColors", "Icefire", "Grintage", "Yelblu Hot", "Magred", 
	 "Analogous", "Orange & Teal", "Toxy Reaf", "Drywet", "Yelblu", "Tertiary", "Atlantica", "Retro Clown",

	"Sunset","Rivendell","Breeze","Red & Blue","Splash",							//   58 palitres
	"Sunset 2","Beech","Vintage","Departure","Landscape","Beach","Sherbet","Hult","Hult 64",
	"Jul","Rewhi","Cyane","Light Pink","Autumn", "Magenta","Yelmag","Tiamat","April Night", "C9",
	"Aurora","C9 2","C9 New","Aurora 2","Candy","Fairy Reaf",
	"Semi Blue","Pink Candy","Red Reaf","Aqua Flash","Lite Light","Red Flash","Blink Red","Red Shift","Red Tide", "Candy2", 
	"RainbowStripeColors", "Deep forest", "ForestColors"};

// Single array of defined cpt-city color palettes.
// This will let us programmatically choose one based on
// a number, rather than having to activate each explicitly
// by name every time.
const byte* const gGradientPalettes[] PROGMEM = {
	// + 11
  	RainbowColors_my,			// 05 - 
	temperature_gp,               //54-41 Temperature
	PartyColors_my,

	greenToBlue_my,
	redToViolet_my,
	blueToViolet_my,

	lightFie_my,				  // Light of my fire
	retro2_16_gp,                 //17-04 Swamp fire
	Orangery_gp,                  //47-34 Orangery
	orangeFire_my,				  // Hell fire
	Sakura_gp,                    //49-36 Sakura

	Sunset_Yellow_gp,             //20-07 Pastel
	lava_gp,                      //35-22 Fire
	heatColor_my,
	fierce_ice_gp,                //36-23 Icefire
	es_vintage_57_gp,             //32-19 Grintage
	yelblu_hot_gp,                //64-51 Yelblu Hot
	BlacK_Magenta_Red_gp,         //41-28 Magred
	
	Analogous_1_gp,               //18-05 Analogous
	Orange_Teal_gp,               //44-31 Orange & Teal	
	toxy_reaf_gp,                 //58-45 Toxy Reaf
	GMT_drywet_gp,                //30-17 Drywet
	Blue_Cyan_Yellow_gp,          //43-30 Yelblu
	Tertiary_01_gp,               //34-21 Tertiary
	Atlantica_gp,                 //51-38 Atlantica
	retro_clown_gp,               //56-43 Retro Clown

	Sunset_Real_gp,               //13-00 Sunset
	es_rivendell_15_gp,           //14-01 Rivendell
	es_ocean_breeze_036_gp,       //15-02 Breeze
	rgi_15_gp,                    //16-03 Red & Blue
	es_pinksplash_08_gp,          //19-06 Splash
	Another_Sunset_gp,            //21-08 Sunset2
	Beech_gp,                     //22-09 Beech
	es_vintage_01_gp,             //23-10 Vintage
	departure_gp,                 //24-11 Departure
	es_landscape_64_gp,           //25-12 Landscape
	es_landscape_33_gp,           //26-13 Beach
	rainbowsherbet_gp,            //27-14 Sherbet
	gr65_hult_gp,                 //28-15 Hult
	gr64_hult_gp,                 //29-16 Hult64
	ib_jul01_gp,                  //31-18 Jul
	ib15_gp,                      //33-20 Rewhi
	Colorfull_gp,                 //37-24 Cyane
	Pink_Purple_gp,               //38-25 Light Pink
	es_autumn_19_gp,              //39-26 Autumn
	BlacK_Blue_Magenta_White_gp,  //40-27 Magenta
	BlacK_Red_Magenta_Yellow_gp,  //42-29 Yelmag
	Tiamat_gp,                    //45-32 Tiamat
	April_Night_gp,               //46-33 April Night
	C9_gp,                        //48-35 C9
	Aurora_gp,                    //50-37 Aurora
	C9_2_gp,                      //52-39 C9 2
	C9_new_gp,                    //53-40 C9 New
	Aurora2_gp,                   //55-42 Aurora 2
	candy_gp,                     //57-44 Candy
	fairy_reaf_gp,                //59-46 Fairy Reaf
	semi_blue_gp,                 //60-47 Semi Blue
	pink_candy_gp,                //61-48 Pink Candy
	red_reaf_gp,                  //62-49 Red Reaf
	aqua_flash_gp,                //63-50 Aqua Flash
	lite_light_gp,                //65-52 Lite Light
	red_flash_gp,                 //66-53 Red Flash
	blink_red_gp,                 //67-54 Blink Red
	red_shift_gp,                 //68-55 Red Shift
	red_tide_gp,                  //69-56 Red Tide
	candy2_gp,                     //70-57 Candy2
	RainbowStripeColors_my,
	deepForest_my,
	ForestColors_my
};

#endif