

CRGBPalette16 currentPalette01;                                 // Use palettes instead of direct CHSV or CRGB assignments
CRGBPalette16 targetPalette01;                                  // Also support smooth palette transitioning
TBlendType    currentBlending01;                                // NOBLEND or LINEARBLEND


// Routine specific variables
uint8_t    numdots =   4;                                     // Number of dots in use.
uint8_t   thisfade =   2;                                     // How long should the trails be. Very low value = longer trails.
uint8_t   thisdiff =  16;                                     // Incremental change in hue between each dot.
uint8_t    thishue01 =   0;                                     // Starting hue.
uint8_t     curhue =   0;                                     // The current hue
uint8_t    thissat = 255;                                     // Saturation of the colour.
uint8_t thisbright = 255;                                     // How bright should the LED/display be.
uint8_t   thisbeat =   5;                                     // Higher = faster movement.


void ChangeMe01() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 30;                // IMPORTANT!!! Change '30' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: numdots = 1; thisbeat = 20; thisdiff = 16; thisfade = 2; thishue01 = 0; break;                  // You can change values here, one at a time , or altogether.
      case 10: numdots = 4; thisbeat = 10; thisdiff = 16; thisfade = 8; thishue01 = 128; break;
      case 20: numdots = 8; thisbeat =  3; thisdiff =  0; thisfade = 8; thishue01=random8(); break;           // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 30: break;
    }
  }
  
} // ChangeMe()
  


void junglepre() {
  currentPalette01  = CRGBPalette16(CRGB::Black);
  targetPalette01   = RainbowColors_p;
  currentBlending01 = LINEARBLEND;  

} // setup()

void juggle_pal() {                                           // Several colored dots, weaving in and out of sync with each other
  
  curhue = thishue;                                           // Reset the hue values.
  fadeToBlackBy(leds, NUM_LEDS, thisfade);
  
  for( int i = 0; i < numdots; i++) {
    leds[beatsin16(thisbeat+i+numdots,0,NUM_LEDS)] += ColorFromPalette(currentPalette01, curhue , thisbright, currentBlending01);    // Munge the values and pick a colour from the palette
    curhue += thisdiff;
  }
  
} // juggle_pal()



  
void jungle() {

  EVERY_N_MILLISECONDS(100) {                                 // AWESOME palette blending capability provided as required.
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette01, maxChanges);   
  }
 
  ChangeMe01();
  juggle_pal();
//   FastLED.show();                         // Power managed display of LED's.
  
} // loop()


