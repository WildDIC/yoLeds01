
/* 
		Костерок №03

*/
void aFire03pre()
{
	yo.name010 	 = "Anime type ( <> 5)";
	// yo.name100 	 = "Palette speed";
	yo.name100 	 = "Palette scale";
	yo.name355 	 = "Cooldown ticks";
	yo.nameSpeed = "Blink speed x2";

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
			{			
				v.var00 = v.aVALUE[pos] + v.color;
				
				if ( yo.AUX010 > 5)
				{
					v.count = inoise8( pos * ( yo.AUX100 >> 1), yo.now >> 3);
					v.count = constrain( v.count, 40, 215);
					v.count = map88( v.count, 39, 216);

					CHSV color	= led.GCfPH( v.count, false); 
					color.val 	= led.sin( v.var00);
					leds[pos] 	= color; 
				}
				else
				{
					// v.count = v.var00;
					leds[pos] 	= led.GCfPH( v.var00, false, led.sin( v.var00)); 
				}

				// leds[pos] 	= color; 
				// leds[pos] 	= CHSV( colorID, 255, led.sin( v.var00)); 

				if ( v.var00 == 255)
				{
					v.aSTATUS[pos] = random8( yo.AUX355 >> 1, yo.AUX255); 
				}
				break;
			}

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
