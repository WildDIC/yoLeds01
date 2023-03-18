// #include "waveClass.h"




/* 8 волн с разной скоротью и наложением цвета */
void aBeatSINAgain()
{
	fadeToBlackBy(leds, NUM_LEDS, 4);
    for (int i = 4; i < 12; i++) 
	{
      	leds[beatsin8( i + yo.currentSpeed, 0, NUM_LEDS - 1)] |= led.GCfP( v.baza +=32, false);  	// ЖДОБАВИТЬСАТУРАЦИИИИИИИИИИИИИИИИИИИИИИИИИИИИ
    }																							// себе в жопу добавь свою сатурацию страную!!!
	FastLED.delay( 1);
	// FastLED.show();
}




/*
			3*2 wavwes + 1 beatSin
*/
void aWavesBeatPre(){
	v.count = 3;
	v.var00 = NUM_LEDS / v.count;

	for ( int ind = 0; ind < v.count; ind++)
	{
		v.aVALUE[ind] = random8( 255);
	}
}
/* 6 симметричные волны навстречу с наложением цвета */
void aWavesBeat() 
{
 	if ( ++v.baza > NUM_LEDS) { v.baza = 0; }
    fadeToBlackBy(leds, NUM_LEDS, 4);

    for ( int ind = 0; ind < v.count; ind++)
	{
        int pos = ( v.baza + ind * v.var00) % NUM_LEDS;

        leds[pos] 			  |= led.GCfP( v.aVALUE[ind]++, false, 255, 20);
        leds[NUM_LEDS - pos]  |= led.GCfP( v.aVALUE[ind]++, false, 255, 20);
    }
	leds[beatsin8( 12, 0, NUM_LEDS - 1)] |=  led.GCfP( myPal[9].palette, led.beat( 5), false);
     
    // FastLED.show();        
  	delay( yo.currentSpeed * 2);
}


/*
		XXX beatSin WAVES
*/
void aBeatSIN8()
{
	v.baza++;
    fadeToBlackBy(leds, NUM_LEDS, 8);

	for ( uint8_t i = 1; i < 9; i++)	
	{
		v.color = 255 * i / 8;
		leds[beatsin8( 10 + i, 0, NUM_LEDS - 1, 0, v.color)] = led.GCfP( v.baza + v.color);
	}	

    // FastLED.show();
	delay( yo.currentSpeed * 2);
}

