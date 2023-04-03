// #include "waveClass.h"



/* 
		Костерок №02 

	far00 - active phaze ticks peaces
	far01 - background fader pieces

*/
void aFire02pre()
{
	yo.name010 = "Density";
	yo.name100 = "In/Out ticks";
	yo.name255 = "Cooldown ticks";
	yo.name355 = "Candle blink value";
	yo.nameSpeed = "Active phase ticks x30";
	yo.isNeedUpWeb = true;
	
	for ( int ind = 0; ind < NUM_LEDS; ind++)
	{
		v.aSTATUS[ind] = random8( 6);
		v.aVALUE[ind] = random8( 250);
	}
}

void aFire02() 
{
	if ( a.isChanged())
	{
		v.far00 = 255. / ( yo.currentSpeed * 30);
		v.far01 = 255. / ( yo.AUX100);
	}

    for (int pos = 0; pos < NUM_LEDS; pos++)
	{	
		if ( v.aVALUE[pos] <= 0)
		{
			v.aSTATUS[pos] += 1;

			switch ( v.aSTATUS[pos])
			{
				case 2:{
					v.aVALUE[pos] = yo.currentSpeed * 30;					
					break;}				
				case 3:{
					v.aVALUE[pos] = yo.AUX100;
					break;}
				case 4:{
					v.aVALUE[pos] = yo.AUX255;
					leds[pos] = CRGB::Black;
					break;}					
				default:{
					v.aVALUE[pos] = 255;
					v.aSTATUS[pos] = 5;
					break;}
			}
		}
		else{
			v.aVALUE[pos] -= 1;

			switch ( v.aSTATUS[pos])
			{
				case 1:
					leds[pos] = ( led.GCfPH( 1, false, 255 - v.far01 * v.aVALUE[pos])); 
					break;			
				case 2:
					leds[pos] = ( led.GCfPH(  255 - v.far00 * v.aVALUE[pos], false)); 
					break;			
				case 3:
					leds[pos] = ( led.GCfPH( 255, false, v.far01 * v.aVALUE[pos]));
					break;
				default:
					break;
			}
		}
	}	        

    for ( int pos01 = 0; pos01 < yo.AUX010; pos01++)
	{
        uint8_t pos = random8( NUM_LEDS);

		if ( v.aSTATUS[pos] > 4)
		{
			v.aSTATUS[pos] = 1;
			v.aVALUE[pos]  = yo.AUX100;
		}
    }
    // FastLED.show();
	// delay( 1);
}
