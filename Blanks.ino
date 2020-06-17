/*
 * Blank
 * 
 * Blanks are used for extending gameplay of existing games
 * or to hold new games in development by developers.
 * When in use by consumers to extend gameplay, Blanks should
 * be sterile, i.e. not be able to program Blinks with their
 * behavior, unless written over by a developer.
 * 
 * The "Blank" sketch performs demo-mode animations until
 * receiving a game to play. From this point on, the demo-mode
 * will only be seen if a game transmission fails or if the
 * battery is replaced.
 * 
 * 06.17.2020
 * by Jonathan Bobrow
 * 
 * @madewithblinks   
 * www.move38.com
 * 
 */

uint8_t sterileFlag=1;             // Make this game sterile. 

enum DemoMode {
  FADE,
  ROTATE,
  RAINBOW,
  WAVES,
  NUM_MODES
};

byte mode = 0;

Timer modeTimer;
#define MODE_DURATION 2000
  
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(mode) {
    
    case FADE:
      displayFade();
      break;
      
    case ROTATE:
      displayRotate();
      break;
    
    case RAINBOW:
      displayRainbow();
      break;
    
    case WAVES:
      displayWaves();
      break;
    
    default:
      break;
  }

  if(modeTimer.isExpired()) {

    mode = (mode + 1) % NUM_MODES;
    
    modeTimer.set( MODE_DURATION );
    
  }
}

/*
 * Fade Animation
 */
void displayFade() {
  setColor(BLUE);
  // put code here for actual fade animation
}

/*
 * Rotation Animation
 */
void displayRotate() {
  setColor(RED);
}

/*
 * Rainbow Animation
 */
void displayRainbow() {
  setColor(GREEN);
}

/*
 * Waves Animation
 */
void displayWaves() {
  setColor(ORANGE);
}
