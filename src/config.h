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

// typedef void (*pt2webUpdate)(void); 	// function pointer type
typedef void (*pt2Funca)(void); 		// function pointer type
typedef void (*pt2static)(void); 		// function pointer type
typedef void (*pt2prewave)(void); 		// function pointer type
typedef void (*pt2setter)(int); 		// function pointer type

typedef enum { ANIME_STATIC=0, ANIME_DYNAMIC=1, ANIME_SETTER=2, ANIME_CHANGER=4 } AnimeType;

struct config{
	byte currentBrightness = 255;        // Уровень яркости ( 0-255)
	byte currentTemp = TEMP_IND_MAX;     // Температура ленты (0-255)
	byte currentSpeed = 10;      	    // Скорость анимации ( задержка)
	byte currentSaturn = MAX_SATURATIOIN;// Сатурация цвета ( 0-255)
	byte antiSaturn = 0;             	// Обратная величина сатурации ( 255-0)
	bool ONOFF = false;                 // Включено или выключено питание ленты
	bool isNeedSaveEEPROM = false;
	bool againButton = 1;				// флаг нажания кнопки у веб-клиента, 0 - новая активности, 1 - повтор, для обновления случайностей в paletteSetActive
	clock_t now = 0;					// текущее время в clock()
	clock_t EEPROMsaveTime = 0;			// отодвигатель текущего времени на Х секунд, при каждом попадании в ИРСервер, для отложенной записи
	int lastReceive = 0;                // ПОследнее значение с ИР приемника
	int lastPressed;					// Последнее действие для Ледов/Вэйвов для фидбека на веб-сервер
	void (*pt2webUpdate)(void); 		// Указатель на функцию для эвента обновляльного данных с вебсервера на клиент. Подменяется с фууфанк на правильную, при поднятии вебсервера
	void (*pt2webUnsave)(void); 		// Указатель на функцию для эвента обновляльного данных с вебсервера на клиент. Подменяется с фууфанк на правильную, при поднятии вебсервера
	String rndStyle;					// строка для подмены переменных стиля случайных палитр через json на веб-клиент ( reseter)
	CRGB c1 = CRGB( 255, 0, 0);
	CRGB c2 = CRGB( 0,  255, 0);
	CRGB c3 = CRGB( 0, 0, 255);
	byte lastCustPal = 0;
	uint8_t candle = 0;
	uint8_t shift = 0;
	bool iscandle = false;
	bool ishifter = false;
	byte AUX010;
	byte AUX100;
	byte AUX255;
	byte AUX355;
	byte AUX455;
	byte pollDefault;					// ID код поллитры по-умолчанию из myPollitra[]	
	byte pollCurrent;					// ID код текущей поллитры из myPollitra[], сохраняется в ЕППРОМе
	bool loadOutside = false;			// устанавливаем данные (через сеттер) при их чтении в irda ( false) или оно пришло для устеновки извне ( true) и их надо будет сохранить 
	String name010 = "AUX010";			// AUX010 name string for web range
	String name100 = "AUX100";			// AUX100 name string for web range
	String name255 = "AUX255";			// AUX255 name string for web range
	String name355 = "AUX355";			// AUX255 name string for web range
	String name455 = "AUX455";			// AUX255 name string for web range
	String nameSpeed = "Speed";			// Speed name string for web range
};
extern config yo;						// конфиг, самое главное здесь
extern void (*pt2Func)();				// ссылка на анима-функция


// новое дописываем строго вниз ( ниже aux255), ибо собьем таблицу с определениями в main
struct waveItem{
    int code;							// IR code
    String name;						// Web button name
	byte typeWeb;						// 0 = None, 1 = bList, 2 = rList 
	byte indForWeb;						// IND in web list 
	bool leadOFF;						// fill black and save LastPressed
	bool isEffect;						// is pt2 change ( ON/OF)
	void (*pt2Funca)(void);				// point to amination function
	void (*pt2static)(void);			// point to solo function
	// void (*pt2prewave)(void);			// point to pre-wave function
	void (*pt2setter)(int);				// point to pre-wave function
	void (*pt2changer)(int);			// point to pre-wave function
	int min;							// min value for web-range
	int max;							// max value for web-range
	byte pollDefault;					// ID код поллитры по-умолчанию из myPollitra[]	
	byte bright;
	byte temp;
	byte speed;
	byte saturn;
	byte aux010;
	byte aux100;
	byte aux255;
	byte aux355;
	byte aux455;
	CRGB c1;
	CRGB c2;
	CRGB c3;
	byte pollCurrent;					// ID код текущей поллитры из myPollitra[], сохраняется в ЕППРОМе
	// bool needSaveJSON; 					// флаг необходимости что-то засейвить в этой конструкции в жосоне
	uint16_t savno; 					// количество записей вавы в память [Save No]
	uint8_t minSpeed;
	uint8_t maxSpeed;
	byte delta;							// 
	AnimeType animeType;
};										// list for: IRDA - function - WEB
typedef std::map<int, waveItem> mapWAVES;
extern mapWAVES mWaves; 							// list for: IRDA - function - WEB
extern std::map<int, waveItem>::iterator mbIter;	// итератор для этого


struct pollitraZ{
	String name;						// Имя палитры
	CRGBPalette16 palette;				// паллитра
	CHSVPalette16 paletteHSV;
};
extern pollitraZ myPal[NUM_POLLITR];	// хранилище всех палитров


struct button{  						// для вебсервера, формируем список кнопко-эментов на странице
    int code;
    String name;
};

struct range{							// для вебсервера, формируем список ранже-эментов на странице
    int code;
	int min;
	int max;
    String name;
	int *value;
};



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

// extern animeClass a;

extern int temperList[NUM_TEMPS];

int powInt(int x, int y);
int parseInt(char* chars);
bool isBetween( uint8_t number, uint8_t lowwer, uint8_t higher);

#endif