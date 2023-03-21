
/* 
		Костерок №03

*/
void aFire03pre()
{
	// yo.name010 = "Density";
	// yo.name100 = "In/Out ticks x2";
	yo.name255 = "Cooldown ticks";
	// yo.name355 = "Blured amount";
	yo.nameSpeed = "Speed x2";

	for ( int ind = 0; ind < NUM_LEDS; ind++)
	{
		v.aSTATUS[ind] = 0;
		v.aVALUE[ind] = random8();
	}
}

void aFire03() 
{
	v.color = led.beat8( yo.currentSpeed << 1, 6);

    for (int pos = 0; pos < NUM_LEDS; pos++)
	{					
		switch ( v.aSTATUS[pos])
		{
		case 0:
			v.var00 	= v.aVALUE[pos] + v.color;
			leds[pos] 	= led.GCfPH( v.var00, false, led.circle8( v.var00)); 

			if ( v.var00 == 255) v.aSTATUS[pos] = random8( yo.AUX255 >> 1, yo.AUX255); 
			break;
		
		case 1:
			v.aVALUE[pos] 	= 255 - v.color + 1;
			v.aSTATUS[pos] 	= 0;
			break;
		
		default:
			v.aSTATUS[pos] 	-= 1;
			break;		
		}
	}	        
}
