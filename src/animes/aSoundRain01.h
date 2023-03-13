

/* Вжух-вжух радуга из цента типа странной цветомузыки */
void aSoundCheck()
{
	uint8_t rand = random8( 1, TOP_INDEX);
    for (int i = 0; i < rand; i++ ) 
	{
		leds[TOP_INDEX + i] = led.GCfP( i*3);
		leds[TOP_INDEX - i] = led.GCfP( i*3);
        delay( 100 / rand);
        FastLED.show();
	}
	
	for (int i = rand; i > 0; i-- ) 
	{
		leds[TOP_INDEX + i] = CRGB::Black;
		leds[TOP_INDEX - i] = CRGB::Black;
		FastLED.show();
        delay( 100 / rand);		
	}	
}




