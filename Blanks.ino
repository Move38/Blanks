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

enum DemoMode {
  FADE,
  ROTATE,
  RAINBOW,
  NUM_MODES
};

byte mode;

Timer fadeTimer;
#define FADE_DURATION 6000

byte bri[6];


bool hasNeighbor[6];
uint32_t attachTime[6];

byte rotateDuration;
uint32_t buttonPressTime;
byte rotateFace = 0;
Timer rotateTimer;
  
void setup() {
  // put your setup code here, to run once:
  mode = ROTATE;
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
        
    default:
      break;
  }

}

/*
 * Fade Animation
 */
void displayFade() {
  Color col;
  byte bri;
  byte bla= map(sin8_C(bri), 0, 255, 127, 255);

  if(fadeTimer.isExpired()) {
    
    fadeTimer.set( FADE_DURATION );    

  }

  // rise RED
  if( fadeTimer.getRemaining() > (FADE_DURATION * 5) / 6  ) {
    col = RED;
    bri = 255 * (FADE_DURATION - fadeTimer.getRemaining()) / (FADE_DURATION / 6);
  }
  
  // fall RED
  else if( fadeTimer.getRemaining() <= (FADE_DURATION * 5) / 6 &&
           fadeTimer.getRemaining() > (FADE_DURATION * 4) / 6 ) {
    col = RED;
    bri = 255 - (255 * (( FADE_DURATION * 5 ) / 6 - fadeTimer.getRemaining()) / (FADE_DURATION / 6));
  }

  // rise GREEN
  else if( fadeTimer.getRemaining() <= (FADE_DURATION * 4) / 6 &&
           fadeTimer.getRemaining() > (FADE_DURATION * 3) / 6 ) {
    col = GREEN;
    bri = (255 * (( FADE_DURATION * 4 ) / 6 - fadeTimer.getRemaining()) / (FADE_DURATION / 6));
  }

  // fall GREEN
  else if( fadeTimer.getRemaining() <= (FADE_DURATION * 3) / 6 &&
           fadeTimer.getRemaining() > (FADE_DURATION * 2) / 6 ) {
    col = GREEN;
    bri = 255 - (255 * (( FADE_DURATION * 3 ) / 6 - fadeTimer.getRemaining()) / (FADE_DURATION / 6));
  }

  // rise BLUE
  else if( fadeTimer.getRemaining() <= (FADE_DURATION * 2) / 6 &&
           fadeTimer.getRemaining() > (FADE_DURATION * 1) / 6 ) {
    col = BLUE;
    bri = (255 * (( FADE_DURATION * 2 ) / 6 - fadeTimer.getRemaining()) / (FADE_DURATION / 6));
  }

  // fall BLUE
  else if( fadeTimer.getRemaining() <= (FADE_DURATION * 1) / 6 &&
           fadeTimer.getRemaining() > (FADE_DURATION * 0) / 6 ) {
    col = BLUE;
    bri = 255 - (255 * (( FADE_DURATION * 1 ) / 6 - fadeTimer.getRemaining()) / (FADE_DURATION / 6));
  }
  
  setColor(dim(col,bri));
}

/*
 * Rotation Animation
 */
void displayRotate() {
  // rotate white around
  uint32_t durationHeld = 0;
  
  // handle button presses
  if( buttonPressed() ) {
    buttonPressTime = millis();
    rotateTimer.set(0);
  }
  if( buttonDown() ) {
    durationHeld = millis() - buttonPressTime;
  
    // range for duration held alone is 0-3000, together 0-6000
    if(isAlone()) {
      rotateDuration = 75 - map(durationHeld, 0, 3000, 0, 70);
    }
    else {
      rotateDuration = 75 - map(durationHeld, 0, 6000, 0, 70);      
    }
  
    if (rotateTimer.isExpired()) {
        rotateFace = (rotateFace + 1) % 6;
        byte startBri = 255 - map(rotateDuration, 5, 75, 0, 155); 
        bri[rotateFace] = startBri;
        rotateTimer.set(rotateDuration);
    }
    
    FOREACH_FACE(f) {
      if ( bri[f] >= 5 ) {
        bri[f] -= 5;
      }
      setColorOnFace(dim(WHITE, bri[f]), f);
    }
  }
  else {
    setColor(dim(WHITE, 127));
  }  


  // animate on neighbor attach
  FOREACH_FACE(f) {
    if(!isValueReceivedOnFaceExpired(f)) {
      if(!hasNeighbor[f]) {
        attachTime[f] = millis();
      }
      hasNeighbor[f] = true;
    }
    else {
      hasNeighbor[f] = false;
    }

    uint32_t timeSinceAttach = millis() - attachTime[f];
    if( timeSinceAttach < 300 ) {
      byte briAttach = 227 - map(timeSinceAttach, 0, 300, 0, 100);
      setColorOnFace(dim(WHITE, briAttach), f);    
    }
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
