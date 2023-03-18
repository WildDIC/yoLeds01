// #include "waveClass.h"

/* 
		Костерок №03

	far00 - active phaze ticks peaces
	far01 - background fader pieces

*/
void aFire03pre()
{
	yo.name010 = "Density";
	// yo.name100 = "In/Out ticks x2";
	yo.name255 = "Cooldown ticks x2";
	yo.name355 = "Candle blink value";
	// yo.nameSpeed = "Active phase ticks x30";

	for ( int ind = 0; ind < NUM_LEDS; ind++)
	{
		v.aSTATUS[ind] = random8( 4);
		v.aVALUE[ind] = random8();
	}
}

void aFire03() 
{
    for (int pos = 0; pos < NUM_LEDS; pos++)
	{	
		if ( v.aVALUE[pos] <= 0)
		{
			v.aSTATUS[pos] += 1;

			switch ( v.aSTATUS[pos])
			{
				case 1: break;
				case 2:{
					v.aVALUE[pos] = yo.AUX255 << 1;
					leds[pos] = CRGB::Black;
					break;}					
				default:{
					v.aVALUE[pos] = 255;
					v.aSTATUS[pos] = 3;
					break;}
			}
		}
		else{
			v.aVALUE[pos] -= 1;

			if ( v.aSTATUS[pos] == 1)
			{
				leds[pos] = ( led.GCfPH( 255 - v.aVALUE[pos], false,  led.circle8( v.aVALUE[pos]), 0, true)); 
			}
		}
	}	        

    for ( int pos01 = 0; pos01 < yo.AUX010; pos01++)
	{
        uint8_t pos = random8( NUM_LEDS);

		if ( v.aSTATUS[pos] > 2)
		{
			v.aSTATUS[pos] = 1;
			v.aVALUE[pos]  = random8( 240, 255);
		}
    }
    // FastLED.show();
	// delay( 10);
}


