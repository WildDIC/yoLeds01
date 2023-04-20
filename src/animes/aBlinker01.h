// #include "waveClass.h"




/* 
		Моргалочка 

	aux010 - color change speed	
	led.aVALUE, aux100 - blink speed
	aux255 - count leds
	led.aSTATUS - timeshift for beatsin8
	
	var01 - leds light count
	color - colorID
	baza  - current activity ID
	count - baza keeper for in/out
	status- fadein/out counter/statuser

	1 - left wave
	2 - beatsin with random tshift
	3 - right wave
	4 - noise
	5 = Lake (c) wled
*/

void aBlinkerPreCum()
{
	if ( yo.AUX255 < 1) yo.AUX255 = 1;

	v.var01 = (NUM_LEDS - 1) / ( yo.AUX255 + 0) + 1; 			 	// колличество рабочих диодов

	for ( int i = 0; i < v.var01; i++) 
	{
		v.aSTATUS[i] = random8();
		v.aVALUE[i]  = yo.AUX100 + random8( 5);
		v.aFADER[i]  = ( i << 8) / v.var01;		// предрасчет таймшифта для битсина для бегущих полосок. просто, потому, что могу это сделать здесь, а не в цикле.
	}
	
	fill_solid( leds, NUM_LEDS, CRGB::Black);		
	fill_solid( v.cIN_LEDS, NUM_LEDS, CRGB::Black);		
	fill_solid( v.cOUT_LEDS, NUM_LEDS, CRGB::Black);			
}


void aBlinken02Pre()
{  
	yo.name010 = "Color speed";
	yo.name100 = "Blink speed";
	yo.name255 = "Leds distance";
	yo.isNeedUpWeb = true;
	v.status = 0;
	aBlinkerPreCum();
}

void aBllinker02anime( uint8_t base, uint8_t force){
	CRGB *ptLEDS;
	
	if      ( force == 0) ptLEDS = v.cOUT_LEDS;
	else if ( force == 1) ptLEDS = v.cIN_LEDS;	
	else	 			  ptLEDS = leds;	
	
	// base = 1;

	switch ( base)
	{
		case 1:
			for ( int i = 0; i < v.var01; i++) {	
				*( ptLEDS + i) = ( led.GCfPH( v.color, false, led.beatSin( yo.AUX100, v.aFADER[i]))); 
				// *( ptLEDS + i) = led.hsv2rgb( led.GCfPH( v.color, false, led.beatCircle( yo.AUX100, v.aFADER[i])) ); 
				// uint8_t  val 	= led.beatCircle( yo.AUX100, v.aFADER[i]);
				// CHSV col 		= led.GCfPH( v.color, false);
				// col.val 		= val; //((uint16_t)( col.val * val)) >> 8;
				// *( ptLEDS + i) 	= col; //led.hsv2rgb( col); 
				// *( ptLEDS + i) 	= led.hsv2rgb( col); 
				// *( ptLEDS + i) = led.hsv2rgb( led.GCfPH( color, false, led.beatCircle( yo.AUX100, led.aFEDOR[i]))); 
				// *( ptLEDS + i) 	= led.GCfP( v.color, false, val);
				
			}
			// Serial.println( )
			break;
		case 2:
			for ( int i = 0; i < v.var01; i++) {	
				// *( ptLEDS + i) = CHSV( color, 255, led.beatCircle( led.aVALUE[i], led.aSTATUS[i])); 
				uint8_t val 	= led.beatSin( v.aVALUE[i], v.aSTATUS[i]);
				CHSV col 		= led.GCfPH( v.color, false);
				col.val 		= val; //((uint16_t)( ( col.val * val))) >> 8;
				*( ptLEDS + i) 	= col; //led.hsv2rgb( col); 
				// *( ptLEDS + i) = led.hsv2rgb( led.GCfPH( color, false, led.beatCircle( led.aVALUE[i], led.aSTATUS[i]))); 
			}
			break;
		case 3:
			for ( int i = 0; i < v.var01; i++) {	
				// *( ptLEDS + i) = CHSV( color, 255, led.beatCircle( yo.AUX100, 255 - led.aFEDOR[i])); 
				uint8_t val 	= led.beatSin( yo.AUX100, 255 - v.aFADER[i]);
				CHSV col 		= led.GCfPH( v.color, false);
				col.val 		= val; //((uint16_t)(( col.val * val))) >> 8;
				*( ptLEDS + i) 	= col; //led.hsv2rgb( col); 
				// *( ptLEDS + i) = led.hsv2rgb( led.GCfPH( color, false, led.beatCircle( yo.AUX100, 255 - led.aFEDOR[i]))); 
			}
			break;
		case 4:
			for ( int i = 0; i < v.var01; i++) 
			{	
				uint8_t noise = inoise8( i * 150, millis() >> 2);
				noise = constrain( noise, 65, 200);
				noise = map( noise, 65, 200, 0, 255);
				// *( ptLEDS + i) = CHSV( color, 255, noise); 
				CHSV col 		= led.GCfPH( v.color, false);
				col.val 		= noise; //((uint16_t)( ( col.val * noise))) >> 8;
				*( ptLEDS + i) 	= col; //led.hsv2rgb( col); 
				// *( ptLEDS + i) = led.hsv2rgb( led.GCfPH( color, false, noise)); 
			}
			break;
		case 5: {
				uint8_t sp = 10;
				uint8_t wave1 = beatsin8(sp +2, -64,64);
				uint8_t wave2 = beatsin8(sp +1, -64,64);
				uint8_t wave3 = beatsin8(sp +2,   0,80);

				for (int i = 0; i < v.var01; i++)
				{
					int index 		= cos8(( i * 30) + wave1) / 2 + cubicwave8(( i * 50) + wave2) / 2;
					uint8_t lum 	= (index > wave3) ? index - wave3 : 0;
					// *( ptLEDS + i) = CHSV(  color, 255, lum); 
					CHSV col 		= led.GCfPH( v.color, false);
					col.val 		= lum; //((uint16_t)( ( col.val * lum))) >> 8;
					*( ptLEDS + i) 	= col; //led.hsv2rgb( col); 
					// *( ptLEDS + i) = led.hsv2rgb( led.GCfPH(  color, false, lum)); 
				} 
			}		
			break;
		case 6:{
				// fadeToBlackBy(leds, NUM_LEDS, 4);
				// leds[beatsin8(13, 0, NUM_LEDS - 1)] = ledGCfP( baza++, false);
			}
			break;
		default:
			v.baza = 1;
			break;
	}
}

void aBlinken02(){
	v.color = led.beat8( yo.AUX010, 12);
	// far00 = far00 + 0.03 * yo.AUX100;
	// color = (uint8_t) far00;
	EVERY_N_SECONDS( 35) 
	{	
		v.count = random8( 1, 6);  // +1 becoz THIS IS RANDOM!!!

		if ( v.count != v.baza)	v.status = 1;  
	} 	
	
	//перерасчет при смене настроек с сайта
	if ( a.isChanged()) aBlinkerPreCum(); 

	// фиксики	
	if ( yo.currentSpeed < 4)
	{
		fadeToBlackBy(leds, NUM_LEDS, 1);

		uint8_t pos = inoise8( 0, millis() >> 2);
		pos = map(pos, 30, 225, 0, NUM_LEDS);  	
		leds[pos] = CRGB( yo.c1);	
	
		if ( yo.currentSpeed < 3)
		{
			pos = inoise8( 100, millis() >> 2);
			pos = map(pos, 30, 225, 0, NUM_LEDS);  	
			leds[pos] = CRGB( yo.c2);
		}
	}

	if ( yo.currentSpeed > 1 )
	{
		// Fade IN/OUT
		if ( v.status != 0)
		{
			if ( v.status >= 255)
			{
				v.status = 0;
				v.baza = v.count;
			}
			else if ( v.status >= 1) 
			{ 		/// 1 - IN, 0 - OUT
				v.status++;
				aBllinker02anime( v.baza, 0);
				aBllinker02anime( v.count, 1);			
			
				for( uint8_t i = 0; i < v.var01; i++) {
					v.cOUT_LEDS[i] = led.blend( v.cOUT_LEDS[i], v.cIN_LEDS[i], v.status);
				}
			}
		}
		else
		{
			aBllinker02anime( v.baza, 0); 
		}
		
		for ( uint8_t i = 0; i < v.var01; i++)
		{ 
			leds[i * yo.AUX255] = v.cOUT_LEDS[i];	
		}   // собсна переносим в ЛЕD из OUTLEDS попиксельно	
	}
}


