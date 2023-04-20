
/* 
		Бегущая радужная вэйв 
*/
void aRainbow()
{
	uint8_t len = yo.AUX100;
	uint8_t ind = 0;
	uint8_t bri = 255;
	uint8_t pix = led.beatSinHiLo( yo.AUX355, len, NUM_LEDS);
	v.color = led.beat( 4);

	// fadeToBlackBy(leds, NUM_LEDS, 1);
	// leds[ledCircle8( yo.currentSpeed << 2, NUM_LEDS)] = ledGCfP( baza++, false);

	for ( uint8_t i = 0; i < NUM_LEDS; i++)
	{
		if ( isBetween( i, pix - len, pix))
		{
			bri = led.sinHigh( ind++, len, yo.AUX255);
			// leds[i] = CHSV( color, 255, bri);			

			// leds[i] = ledGCfP( i, true, ledHCircle( ind, len));
			// leds[i] =  ledGCfP( myPal[10].palette, i);
			// leds[i] = ledBlend( ledGCfP( myPal[10].palette, i), leds[i], 64); //  CRGB( 255, 0, 0);
		}
		else
		{
			bri = 255;
			// leds[i] = CRGB::Black;
			// leds[i] = CHSV( v.color, 255, 255);		
		}
		
		leds[i] = ( CHSV( v.color, 255, bri));
		// leds[i] = ledGCfP( myPal[10].palette, color, false, bri);
	}
	// Serial.printf( "Color = %d, pix = %d\n", color, pix);
	// delay( 5);
	// fadeToBlackBy(leds, NUM_LEDS, 3);
	// leds[ledCircle8( yo.currentSpeed << 2, NUM_LEDS)] = ledGCfP( baza++, false);
	// leds[beatsin8( yo.currentSpeed << 2, 0, NUM_LEDS - 1)] = ledGCfP( baza++, false);
}


