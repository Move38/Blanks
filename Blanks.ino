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
  NUM_MODES
};

byte mode;

Timer modeTimer;
#define MODE_DURATION 6000

byte bri[6];
  
void setup() {
  // put your setup code here, to run once:
  modeTimer.set( MODE_DURATION );
  mode = FADE;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // handle button presses
  if( buttonPressed() ) {
    modeTimer.set(0);
  }
  
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
  Color col;
  byte bri;
  byte bla= map(sin8_C(bri), 0, 255, 127, 255);
  // rise RED
  if( modeTimer.getRemaining() > (MODE_DURATION * 5) / 6  ) {
    col = RED;
    bri = 255 * (MODE_DURATION - modeTimer.getRemaining()) / (MODE_DURATION / 6);
  }
  
  // fall RED
  else if( modeTimer.getRemaining() <= (MODE_DURATION * 5) / 6 &&
           modeTimer.getRemaining() > (MODE_DURATION * 4) / 6 ) {
    col = RED;
    bri = 255 - (255 * (( MODE_DURATION * 5 ) / 6 - modeTimer.getRemaining()) / (MODE_DURATION / 6));
  }

  // rise GREEN
  else if( modeTimer.getRemaining() <= (MODE_DURATION * 4) / 6 &&
           modeTimer.getRemaining() > (MODE_DURATION * 3) / 6 ) {
    col = GREEN;
    bri = (255 * (( MODE_DURATION * 4 ) / 6 - modeTimer.getRemaining()) / (MODE_DURATION / 6));
  }

  // fall GREEN
  else if( modeTimer.getRemaining() <= (MODE_DURATION * 3) / 6 &&
           modeTimer.getRemaining() > (MODE_DURATION * 2) / 6 ) {
    col = GREEN;
    bri = 255 - (255 * (( MODE_DURATION * 3 ) / 6 - modeTimer.getRemaining()) / (MODE_DURATION / 6));
  }

  // rise BLUE
  else if( modeTimer.getRemaining() <= (MODE_DURATION * 2) / 6 &&
           modeTimer.getRemaining() > (MODE_DURATION * 1) / 6 ) {
    col = BLUE;
    bri = (255 * (( MODE_DURATION * 2 ) / 6 - modeTimer.getRemaining()) / (MODE_DURATION / 6));
  }

  // fall BLUE
  else if( modeTimer.getRemaining() <= (MODE_DURATION * 1) / 6 &&
           modeTimer.getRemaining() > (MODE_DURATION * 0) / 6 ) {
    col = BLUE;
    bri = 255 - (255 * (( MODE_DURATION * 1 ) / 6 - modeTimer.getRemaining()) / (MODE_DURATION / 6));
  }
  
  setColor(dim(col,bri));
}

/*
 * Rotation Animation
 */
void displayRotate() {
  // rotate white around
  setColor(OFF);
  FOREACH_FACE(f) {
    if ((millis() / 100) % 6 == f) {
      bri[f] = 255;
    }
    if ( bri[f] >= 5 ) {
      bri[f] -= 5;
    }
    setColorOnFace(dim(WHITE, bri[f]), f);
  }
}

/*
 * Rainbow Animation
 */
void displayRainbow() {
  FOREACH_FACE(f) {
    setColorOnFace(makeColorHSB((millis()/10 + (5-f)*21) % 255, 255, 255), f);
  }
}

/*
 * Waves Animation
 */
void displayWaves() {
  setColor(ORANGE);
}
