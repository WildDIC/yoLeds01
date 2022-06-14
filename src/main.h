#ifndef __MAIN_H
#define __MAIN_H

#endif




/*
// ! плохой стиль - даже в C99 этого уже не требуется !
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define CYAN  0x00FFFF

// стиль, совместимый с C99, но имена констант слишком короткие
enum ColorId : unsigned
{
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF,
    CYAN = 0x00FFFF,
};

// стиль Modern C++
enum class WebColorRGB
{
    Red = 0xFF0000,
    Green = 0x00FF00,
    Blue = 0x0000FF,
    Cyan = 0x00FFFF,
};

*/


/* Platformio.ini

[env:IR Test with FastLED 01]
platform = espressif32
board = esp32dev
framework = arduino
upload_speed = 512000
monitor_speed = 115200
lib_deps = 
	fastled/FastLED@^3.5.0
	crankyoldgit/IRremoteESP8266@^2.8.2
	ottowinter/ESPAsyncWebServer-esphome@^2.1.0
*/





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
