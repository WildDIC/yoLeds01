
/* Включаем беленькую */
void UPWhite()
{	
	if ( yo.ONOFF)
	{
		for ( int pos = 0; pos < NUM_LEDS; pos++)
		{ 
			leds[pos] = led.GCfP( pos, true);
		}	
		delay( 5);
		FastLED.show();
	}

  	// if ( yo.ONOFF)
	// {
	//   	fill_solid( leds, NUM_LEDS, CRGB::White); 	
	// 	FastLED.delay( 5);
	// 	FastLED.show();
	// }
	// #ifdef DEBUG_ENABLE
	// 	Serial.printf( "\nStatic RGB = (%d.%d.%d)\n", leds[10].r, leds[10].g, leds[10].b);
	// #endif
}


/* Включаем тестовое, сейчас = палитра */
void UP()
{  
	if ( yo.ONOFF)
	{
		for ( int pos = 0; pos < NUM_LEDS; pos++)
		{ 
			leds[pos] = led.GCfPH( pos, true);

			#ifdef DEBUG_ENABLE
				Serial.printf( "pos [%d], (%d.%d.%d)\n", pos, leds[pos].r, leds[pos].g, leds[pos].b);
			#endif
		}	
		delay( 5);
		FastLED.show();
	}
}


void UP01()
{  
	if ( yo.ONOFF)
	{
		for ( int pos = 0; pos < NUM_LEDS; pos++)
		{ 
			leds[pos] = led.GCfPH( pos, true);
		}	
		delay( 5);
		FastLED.show();
	}
}
