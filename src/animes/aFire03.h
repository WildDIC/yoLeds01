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
		w.aSTATUS[ind] = random8( 4);
		w.aVALUE[ind] = random8();
	}
}

void aFire03() 
{
    for (int pos = 0; pos < NUM_LEDS; pos++)
	{	
		if ( w.aVALUE[pos] <= 0)
		{
			w.aSTATUS[pos] += 1;

			switch ( w.aSTATUS[pos])
			{
				case 1: break;
				case 2:{
					w.aVALUE[pos] = yo.AUX255 << 1;
					leds[pos] = CRGB::Black;
					break;}					
				default:{
					w.aVALUE[pos] = 255;
					w.aSTATUS[pos] = 3;
					break;}
			}
		}
		else{
			w.aVALUE[pos] -= 1;

			if ( w.aSTATUS[pos] == 1)
			{
				leds[pos] = led.hsv2rgb( led.GCfPH( 255 - w.aVALUE[pos], false,  led.circle8( w.aVALUE[pos]), 0, true)); 
			}
		}
	}	        

    for ( int pos01 = 0; pos01 < yo.AUX010; pos01++)
	{
        uint8_t pos = random8( NUM_LEDS);

		if ( w.aSTATUS[pos] > 2)
		{
			w.aSTATUS[pos] = 1;
			w.aVALUE[pos]  = random8( 240, 255);
		}
    }
    // FastLED.show();
	// delay( 10);
}


