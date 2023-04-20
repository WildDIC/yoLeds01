#ifndef __CONFIG_H
#define __CONFIG_H

#include <FastLED.h>
#include <map>

#define WEB_ENABLE 
#define EERPROM_ENABLE 
// #define JSON_ENABLE
// #define FPSCOUNT_ENABLE
// #define DEBUG_ENABLE 

#ifdef DEBUG_ENABLE
#define yoBug(x) Serial.print(x)
#define yoBugN(x) Serial.println(x)
#define yoBugF(x, y) Serial.printf(x, y)
#else
#define yoBug(x)
#define yoBugN(x)
#define yoBugF(x, y)
#endif

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define BETWEEN(a,b,n) ((a<n)&&(n<bb))


#define MAX_SATURATIOIN 100
// #define LED_PIN     5
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN 13                     // Выходной Пин ленты
#define RECV_PIN 14                     // for ESP32 micrcontroller
#define NUM_LEDS 120                    // Количество диодов в ленте

#define NUM_TEMPS 51                    // Количество цветов в таблице температур
#define TOP_INDEX (NUM_LEDS / 2)        // Половина длины ленты
#define NUM_COLORS  255                 // Количество цветов в кастомной палитре
#define NUM_POLLITR  80                 // Количество кастомных поллитров
#define TEMP_IND_MAX 50                 // Максимальный используемый индекс в таблице цветов
#define GRADIENT_PALETTE_COUNT 58

// typedef enum { ANIME_STATIC=0, ANIME_DYNAMIC=1, ANIME_SETTER=2, ANIME_CHANGER=4 } AnimeType;

struct config{
	int waveID;							// Последнее действие для Ледов/Вэйвов для фидбека на веб-сервер
	int lastReceive = 0;                // ПОследнее значение с ИР приемника

	void (*pt2webUpdate)(void); 		// Указатель на функцию для эвента обновляльного данных с вебсервера на клиент. Подменяется с фууфанк на правильную, при поднятии вебсервера
	void (*pt2webUpRanges)(void); 		// Указатель на функцию для эвента обновляльного данных с вебсервера на клиент. Подменяется с фууфанк на правильную, при поднятии вебсервера
	void (*pt2webUnsave)(void); 		// Указатель на функцию для эвента обновляльного данных с вебсервера на клиент. Подменяется с фууфанк на правильную, при поднятии вебсервера
	void (*pt2webUpRange)( const String&, uint8_t); 		// Указатель на функцию для эвента обновляльного данных с вебсервера на клиент. Подменяется с фууфанк на правильную, при поднятии вебсервера
	void (*pt2webUpColor)( void);	// Указатель на функцию для эвента обновляльного данных с вебсервера на клиент. Подменяется с фууфанк на правильную, при поднятии вебсервера

	clock_t now 		= 0;				// текущее время в clock()
	clock_t EEPROMsaveTime = 0;			// отодвигатель текущего времени на Х секунд, при каждом попадании в ИРСервер, для отложенной записи
	uint8_t candle 		= 0;
	uint8_t shift 		= 0;
	uint8_t candleServ 	= 0;
	uint8_t shiftServ 	= 0;
	bool againButton 	= true;			// флаг нажания кнопки у веб-клиента, 0 - новая активности, 1 - повтор, для обновления случайностей в paletteSetActive
	bool ONOFF 			= false;        // Включено или выключено питание ленты
	bool iscandle 		= false;
	bool ishifter 		= false;
	bool loadOutside 	= false;		// устанавливаем данные (через сеттер) при их чтении в irda ( false) или оно пришло для устеновки извне ( true) и их надо будет сохранить 
	bool isNeedSaveEEPROM = false;
	bool isNeedUpWeb	= false;
	String rndStyle;					// строка для подмены переменных стиля случайных палитр через json на веб-клиент ( reseter)
	String name010 = "AUX010";			// AUX010 name string for web range
	String name100 = "AUX100";			// AUX100 name string for web range
	String name255 = "AUX255";			// AUX255 name string for web range
	String name355 = "AUX355";			// AUX355 name string for web range
	String name455 = "AUX455";			// AUX455 name string for web range
	String nameSpeed = "Speed";			// Speed name string for web range
	byte currentBri = 255;      		// Уровень яркости ( 0-255)
	byte currentTemp = TEMP_IND_MAX;    // Температура ленты (0-255)
	byte currentSpeed = 10;      	    // Скорость анимации ( задержка)
	byte currentSaturn = MAX_SATURATIOIN;// Сатурация цвета ( 0-255)
	byte antiSaturn = 0;             	// Обратная величина сатурации ( 255-0)
	byte AUX010;
	byte AUX100;
	byte AUX255;
	byte AUX355;
	byte AUX455;
	byte palDefault;					// ID код поллитры по-умолчанию из myPollitra[]	
	byte palCurrent;					// ID код текущей поллитры из myPollitra[], сохраняется в ЕППРОМе
	byte palRandom 	= 0;					// количество самодельных ( рэндомных + колоро-палитровых) самодельных палитр
	byte palTotal 	= 0;					// количество палитр из верхней части списка палитр ( после самосборных до "ВЛЕД-овских")
	byte palCust 	= 0;					// общее количество палитр
	CRGB c1 = CRGB( 255, 0, 0);
	CRGB c2 = CRGB( 0,  255, 0);
	CRGB c3 = CRGB( 0, 0, 255);
};
extern config yo;						// конфиг, самое главное здесь
extern void (*pt2Func)();				// ссылка на анима-функция


// новое дописываем строго вниз ( ниже aux255), ибо собьем таблицу с определениями в main
struct waveItem{
    int code = 0;							// IR code
    String name;						// Web button name
	byte typeWeb = 0;						// 0 = None, 1 = bList, 2 = rList 
	byte indWeb = 0;						// IND in web list 
	bool leadOFF = false;						// fill black and save LastPressed
	bool isEffect = false;						// is pt2 change ( ON/OF)
	void (*pt2Funca)(void) = nullptr;				// point to amination function
	void (*pt2static)(void) = nullptr;			// point to solo function
	void (*pt2setter)(int) = nullptr;				// point to pre-wave function
	void (*pt2changer)(int) = nullptr;			// point to pre-wave function
	int min = 0;							// min value for web-range
	int max = 255;							// max value for web-range
	byte palDefault = 9;					// ID код поллитры по-умолчанию из myPollitra[]	
	byte bright = 128;
	byte temp = TEMP_IND_MAX;
	byte speed = 5;
	byte saturn = 100;
	byte aux010 = 5;
	byte aux100 = 50;
	byte aux255 = 128;
	byte aux355 = 128;
	byte aux455 = 128;
	CRGB c1 = CRGB{ 255, 0, 0};
	CRGB c2 = CRGB( 0, 255, 0);
	CRGB c3 = CRGB{ 0, 0, 255};
	byte palCurrent = 9;					// ID код текущей поллитры из myPollitra[], сохраняется в ЕППРОМе
	uint16_t savno = 0; 					// количество записей вавы в память [Save No]
	// uint8_t minSpeed;
	// uint8_t maxSpeed;
	signed char delta = 1;							// 
	// AnimeType animeType;
};										// list for: IRDA - function - WEB
typedef std::map<int, waveItem> mapWAVES;
extern mapWAVES mWaves; 							// list for: IRDA - function - WEB
extern std::map<int, waveItem>::iterator mbIter;	// итератор для этого
// extern waveItem c;

struct pollitraZ{
	String name;						// Имя палитры
	CRGBPalette16 palette;				// паллитра
	CHSVPalette16 paletteHSV;
};
extern pollitraZ myPal[NUM_POLLITR];	// хранилище всех палитров


class varStorage
{
	private:
		/* data */
	public:
		int status 		= 0;
		int count 		= 0;

		uint8_t color 	= 0;
		uint8_t ind 	= 0;
		uint8_t baza 	= 0;     

		uint8_t var00 	= 0;
		uint8_t var01 	= 0;
		uint8_t var02 	= 0;
		uint8_t var03 	= 0;

		float far00 	= 0.0;
		float far01 	= 0.0;

		uint8_t aVALUE[NUM_LEDS];
		uint8_t aSTATUS[NUM_LEDS];
		uint8_t aFADER[NUM_LEDS];

		CRGB cIN_LEDS[NUM_LEDS];
		CRGB cOUT_LEDS[NUM_LEDS];

		// CHSV hIN_LEDS[NUM_LEDS];
		// CHSV hOUT_LEDS[NUM_LEDS];
};
extern varStorage v;
extern int temperList[NUM_TEMPS];

int powInt(int x, int y);
int parseInt(char* chars);
bool isBetween( uint8_t number, uint8_t lowwer, uint8_t higher);

// CRGB& CRGB::operator=(const CHSV& rhs) = delete;


inline void hsv2rgb_rainbow( const CHSV& hsv, CRGB& rgb) 
{
    uint16_t region, remainder, p, q, t;
    
    if (hsv.s == 0) {	rgb.r = hsv.v;	rgb.g = hsv.v;	rgb.b = hsv.v;		return;}
    
    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 
    
    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * 		 remainder)  >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;
    
    switch (region) {
        case 0:		rgb.r = hsv.v; 	rgb.g = t; 		rgb.b = p;		break;
        case 1:		rgb.r = q; 		rgb.g = hsv.v; 	rgb.b = p;    	break;
        case 2: 	rgb.r = p; 		rgb.g = hsv.v; 	rgb.b = t;    	break;
        case 3:		rgb.r = p; 		rgb.g = q; 		rgb.b = hsv.v;  break;
        case 4: 	rgb.r = t; 		rgb.g = p; 		rgb.b = hsv.v;  break;
        default:	rgb.r = hsv.v; 	rgb.g = p; 		rgb.b = q;   	break;
    }
	// Serial.println( "New");
}


#endif