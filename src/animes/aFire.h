// #include "waveClass.h"

// void funcFire02(){
// 	fadeToBlackBy(leds, NUM_LEDS, 4);
// 	leds[beatsin8(13, 0, NUM_LEDS - 1)] = led.GCfP( w.baza++, false);
// 	FastLED.show();
// 	delay(yo.currentSpeed * 2);
// }

// waveClass initFire( uint16_t id){
// 	waveClass animeClass( id, "Fire 2024");
// 	animeClass.nSpeed = "non SPID!";
// 	animeClass.anime = &funcFire02;
// 	return animeClass;
// }



// class animeCL01:public waveClass{
// 	public:
// 		animeCL01( int i, String n, bool s = false):waveClass(i, n, s){
// 			company = n;
// 			// aux100 = 75;
// 			nSpeed = "non SPID!";
// 			anime = &animate;
// 		}		

// 	private:
// 		String company;
// };


// animeCL01 animeFire( 3212321, "Fire 2024");

// waveClass animeFire( 3212321, "Fire 2024");

// int main(){
// 	animeFire.nSpeed = "non SPID!";
// 	animeFire.anime = &animate;
// 	return 0;
// }

// waveClass initAnime(){
// 	waveClass anime( 3212321, "Fire 2024");
// 	anime.nSpeed = "non SPID!";
// 	anime.anime = &animate;
// 	return anime;
// }

// class animeCL01 : public waveClass{
// 	public:
// 		animeCL01( int i, String n, bool s = false):waveClass(i, n, s)    {
// 			company = n;
// 			// aux100 = 75;
// 		}		

// 		void pre() override{
// 			Serial.printf( "and lets the '%s' begin!\n", this->name);
// 		}
		
// 		void animate() override{
// 			// Serial.printf( "[%d]%s = %s\n", this->id, this->company, this->name);
			
// 			fadeToBlackBy(leds, NUM_LEDS, 4);
// 			leds[beatsin8(13, 0, NUM_LEDS - 1)] = ledGCfP( baza++, false);
// 			FastLED.show();
// 			delay(yo.currentSpeed * 2);
// 		}
		
// 	private:
// 		String company;
// };
// uint8_t baza = 0;



// /* 
// 		Костерок №02 

// 	var00 - active phaze ticks peaces
// 	var01 - background fader pieces

// */
// void funcFire02pre(){
// 	// yo.name010 = "Density";
// 	// yo.name100 = "In/Out ticks";
// 	// yo.name255 = "Cooldown ticks";
// 	// yo.nameSpeed = "Active phase ticks x15";

// 	for ( int ind = 0; ind < NUM_LEDS; ind++){
// 		w.aSTATUS[ind] = random8( 5);
// 		w.aVALUE[ind] = random8( 30);
// 	}
// }

// void funcFire02() {
// 	// uint8_t foundNEW = 0;

//     for (int pos = 0; pos < NUM_LEDS; pos++){	

// 		if ( led.aVALUE[pos] <= 0){
// 			led.aSTATUS[pos] +=1;

// 			switch ( led.aSTATUS[pos]){
// 				case 2:
// 					// LEDS_VALUE[pos] = beatsin88( 14, 20, 50);
// 					led.aVALUE[pos] = yo.currentSpeed * 15;
// 					nvar00 = 120 / led.aVALUE[pos];
// 					break;			
// 				case 3:
// 					led.aVALUE[pos] = yo.AUX100;
// 					nvar01 = 255 / yo.AUX100;
// 					break;
// 				case 4:
// 					led.aVALUE[pos] = yo.AUX255;
// 					leds[pos] = CRGB::Black;
// 					break;						
// 				case 6:
// 					led.aVALUE[pos] = 255;
// 					led.aSTATUS[pos] = 5;
// 					break;
// 				default:
// 					break;
// 			}
// 		}
// 		else{
// 			led.aVALUE[pos] -= 1;

// 			switch (led.aSTATUS[pos]){
// 				case 1:
// 					leds[pos] = led.GCfP( 1, false, 255 - nvar01 * led.aVALUE[pos]); 
// 					break;			
// 				case 2:
// 					leds[pos] = led.GCfP(  120 - nvar00 * led.aVALUE[pos], true);   //, random8( 230, 255));				
// 					break;			
// 				case 3:
// 					leds[pos] = led.GCfP( 120, true, nvar01 * led.aVALUE[pos]); //LEDS_VALUE[pos] /= 1.2); 
// 					break;

// 				default:
// 					break;
// 			}
// 		}
// 	}	        

//     for ( int pos01 = 0; pos01 < yo.AUX010; pos01++){
//         int pos = random8( NUM_LEDS);

// 		if ( led.aSTATUS[pos] > 4 || led.aSTATUS[pos] < 1){
// 			led.aSTATUS[pos] = 1;
// 			led.aVALUE[pos]  = yo.AUX100;
// 		}
//     }
//     FastLED.show();
// 	// delay( yo.currentSpeed);
// }


// waveClass initFire02( uint16_t id){
// 	waveClass animeClass( id, "Костерок №2");
// 	animeClass.nAUX010 = "Density";
// 	animeClass.nAUX100 = "In/Out ticks";
// 	animeClass.nAUX255 = "Cooldown ticks";
// 	animeClass.nSpeed = "Active phase ticks x15";
// 	animeClass.anime = &funcFire02;
// 	animeClass.aninePre = &funcFire02pre;
// 	return animeClass;
// }
