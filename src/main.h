// #define DEBUG_ENABLE 
#define WEB_ENABLE 
#define EERPROM_ENABLE 

#ifdef DEBUG_ENABLE
#define yoBug(x) Serial.println(x)
#define yoBugF(x, y) Serial.printf(x, y)
#else
#define yoBug(x)
#define yoBugF(x, y)
#endif

#include <map>

#define DATA_PIN 13                     // Выходной Пин ленты
#define RECV_PIN 14                     // for ESP32 micrcontroller
#define NUM_LEDS 120                    // Количество диодов в ленте
#define NUM_TEMPS 51                    // Количество цветов в таблице температур
#define TOP_INDEX (NUM_LEDS / 2)        // Половина длины ленты
#define NUM_COLORS  30                  // Количество цветов в кастомной палитре
#define TEMP_IND_MAX 40                 // Максимальный используемый индекс в таблице цветов

void (*pt2Func)(); 				// Указатель на функцию для CASE

struct config{
	int currentBrightness = 255;        // Уровень яркости ( 0-255)
	int currentTemp = TEMP_IND_MAX;     // Температура ленты (0-255)
	int currentSpeed = 10;              // Скорость анимации ( задержка)
	int currentSaturn = 255;            // Сатурация цвета ( 0-255)
	int antiSaturn = 0;             	// Обратная величина сатурации ( 255-0)
	bool ONOFF = false;                 // Включено или выключено питание ленты
	int lastReceive = 0;                // ПОследнее значение с ИР приемника
	int lastPressed;					// Последнее действие для Ледов/Вэйвов для фидбека на веб-сервер
} yo;                                   // Конфиг с параметрами

struct button{
    int code;
    String name;
};

struct range{
    int code;
	int min;
	int max;
    String name;
	int *value;
};

typedef void (*pt2Funca)(void); 	// function pointer type
typedef void (*pt2static)(void); 	// function pointer type
typedef void (*pt2prewave)(void); 	// function pointer type
typedef void (*pt2setter)(int); 	// function pointer type

struct irdaItems{
    int code;					// IR code
    String name;				// Web button name
	byte typeWeb;				// 0 = None, 1 = bList, 2 = rList 
	int indForWeb;				// IND in web list 
	bool leadOFF;				// fill black and save LastPressed
	bool pt2change;				// is pt2 change ( ON/OF)
	void (*pt2Funca)(void);		// point to amination function
	void (*pt2static)(void);	// point to solo function
	void (*pt2prewave)(void);	// point to pre-wave function
	void (*pt2setter)(int);		// point to pre-wave function
	int min;					// min value for web-range
	int max;					// max value for web-range
};								// list for: IRDA - function - WEB

typedef std::map<int, irdaItems> mapIRDA;
mapIRDA mButtons; 					// list for: IRDA - function - WEB
std::map<int, irdaItems>::iterator mButtonIter;


int temperList[NUM_TEMPS] = {0xFF3300,0xFF3800,0xFF4500,0xFF4700,0xFF5200,0xFF5300,0xFF5D00,0xFF5D00,0xFF6600,0xFF6500,0xFF6F00,0xFF6D00,0xFF7600,0xFF7300,0xFF7C00,0xFF7900,
	0xFF8200,0xFF7E00,0xFF8700,0xFF8300,0xFF8D0B,0xFF8912,0xFF921D,0xFF8E21,0xFF9829,0xFF932C,0xFF9D33,0xFF9836,0xFFA23C,0xFF9D3F,0xFFA645,0xFFA148,0xFFAA4D,0xFFA54F,
	0xFFAE54,0xFFA957,0xFFB25B,0xFFAD5E,0xFFB662,0xFFB165,0xFFB969,0xFFB46B,0xFFBD6F,0xFFB872,0xFFC076,0xFFBB78,0xFFC37C,0xFFBE7E,0xFFC682,0xFFC184, 0xFFFFFF
};   								// массив с номерами цветов по верхней части таблицы Кельвина





// CRGB leds[NUM_LEDS];
// CHSV yoPalette[NUM_COLORS];
// uint8_t LEDS_HUE[NUM_LEDS];
// uint8_t LEDS_FEDOR[NUM_LEDS];

// void ShowPalette(CRGBPalette16 aPalette){
//   for ( int i = 0; i < NUM_LEDS; i++)  {
//     leds[i] =  aPalette[i];
//   }
//   FastLED.show();
//  }
//   CRGBPalette16 MyPalette;
//   //My palette #2
//   fill_gradient_RGB(MyPalette, NUM_LEDS, CRGB::Red, CRGB::Blue);
//   ShowPalette(MyPalette);

//   //My palette #3
//   fill_rainbow(MyPalette, NUM_LEDS, HUE_RED, 255 / NUM_LEDS); //full rainbow
//   ShowPalette(MyPalette);


// EEPROM.write(0, ledState);
// EEPROM.commit();
// void saveEEPROM(){
// 	EEPROM.write(0, currentBrightness);
// 	EEPROM.write(1, currentTemp);
// 	EEPROM.write(2, yo.currentSpeed);
// 	EEPROM.write(3, pt2Func);
// 	EEPROM.write(4, yo.ONOFF);
// 	EEPROM.write(5, yo.animationON);
// 	EEPROM.commit();
// }

// void flicker() {                          //-m9-FLICKER EFFECT
//   int random_bright = random(0, 255);
//   int random_delay = random(10, 100);
//   int random_bool = random(0, random_bright);
//   if (random_bool < 10) {
//     for (int i = 0 ; i < LED_COUNT; i++ ) {
//       leds[i] = CHSV(thishue, thissat, random_bright);
//     }
//     LEDS.show();
//     delay(random_delay);
//   }
// }
// void rgb_propeller() {                           //-m27-RGB PROPELLER
//   idex++;
//   int ghue = (thishue + 80) % 255;
//   int bhue = (thishue + 160) % 255;
//   int N3  = int(LED_COUNT / 3);
//   int N6  = int(LED_COUNT / 6);
//   int N12 = int(LED_COUNT / 12);
//   for (int i = 0; i < N3; i++ ) {
//     int j0 = (idex + i + LED_COUNT - N12) % LED_COUNT;
//     int j1 = (j0 + N3) % LED_COUNT;
//     int j2 = (j1 + N3) % LED_COUNT;
//     leds[j0] = CHSV(thishue, thissat, 255);
//     leds[j1] = CHSV(ghue, thissat, 255);
//     leds[j2] = CHSV(bhue, thissat, 255);
//   }
//   LEDS.show();
//   delay(thisdelay);
// }
// void kitt() {                                     //-m28-KNIGHT INDUSTIES 2000
// int TOP_INDEX = int(LED_COUNT / 2);

//   int rand = random(0, TOP_INDEX);
//   for (int i = 0; i < rand; i++ ) {
//     leds[TOP_INDEX + i] = CHSV(thishue, thissat, 255);
//     leds[TOP_INDEX - i] = CHSV(thishue, thissat, 255);
//     LEDS.show();
//     delay(thisdelay / rand);
//   }
//   for (int i = rand; i > 0; i-- ) {
//     leds[TOP_INDEX + i] = CHSV(thishue, thissat, 0);
//     leds[TOP_INDEX - i] = CHSV(thishue, thissat, 0);
//     LEDS.show();
//     delay(thisdelay / rand);
//   }
// }
