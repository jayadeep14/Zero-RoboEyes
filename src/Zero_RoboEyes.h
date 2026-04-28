/*
 * Zero RoboEyes for OLED Displays V 1.3
 * Contains all 56 distinct emotions (28 Original + 28 Cozmo Style Extensions)
 * Supports dynamic rendering of specialized glyphs (glitches, spirals, barcodes)
 * Built with fractional easing transitions and robust clipping.
 */

#ifndef _ZERO_ROBOEYES_H
#define _ZERO_ROBOEYES_H

uint8_t BGCOLOR = 0; // background and overlays
uint8_t MAINCOLOR = 1; // drawings

enum Mood {
  // ORIGINAL 28
  EXTREME_LF, NORMAL_LF, NEUTRAL, NORMAL_RT, EXTREME_RT, 
  WORRIED, SCARED, HAPPY_LF, HAPPY, GLEE, HAPPY_RT, 
  SAD_LT, SAD_DOWN, SAD_RT, SKEPTIC, FOCUSED, SQUINT, FRUSTRATED, ANNOYED, ANGRY, FURIOUS, 
  SLEEPY, SUSPICIOUS, UNIMPRESSED, SURPRISED, AWE, BLINK_LOW, BLINK_HIGH,
  
  // NEW 28 COZMO EXPRESSIONS
  COMPASSIONATE, PLAYFUL, DATA_STREAM, CURIOUS, PROBLEM_SOLVING, SIDE_GLANCE, ADMIRATION,
  SYSTEM_ERROR, CONFUSED, HYPNOTIZED, MISCHIEVOUS, FLUSTERED, STUNNED, LOW_BATTERY_ICON,
  LOW_BATTERY_EYES, DETERMINED, ONE_EYEBROW, BARCODE_SCAN, FOCUSED_GOAL, NERVOUS, INTRIGUED,
  CALM, OPTIMIC, CONTENT, QUESTION, WINKING, POUTING, SYSTEM_IDLE
};

enum CustomShape {
  SHAPE_NONE,
  SHAPE_PLAYFUL,
  SHAPE_DATA_STREAM,
  SHAPE_PROBLEM_SOLVING,
  SHAPE_ADMIRATION,
  SHAPE_SYSTEM_ERROR,
  SHAPE_CONFUSED,
  SHAPE_HYPNOTIZED,
  SHAPE_STUNNED,
  SHAPE_LOW_BATTERY_ICON,
  SHAPE_BARCODE,
  SHAPE_FOCUSED_GOAL,
  SHAPE_NERVOUS,
  SHAPE_INTRIGUED,
  SHAPE_QUESTION,
  SHAPE_POUTING,
  SHAPE_SYSTEM_IDLE
};

#define DEFAULT NEUTRAL
#define TIRED SLEEPY
#define CU SKEPTIC
#define CUE SUSPICIOUS
#define LEFT NORMAL_LF
#define RIGHT NORMAL_RT

#define ON 1
#define OFF 0

#define N 1 
#define NE 2 
#define E 3 
#define SE 4 
#define S 5 
#define SW 6 
#define W 7 
#define NW 8 


template<typename AdafruitDisplay>
class RoboEyes
{
public:

AdafruitDisplay *display;

int screenWidth = 128;
int screenHeight = 32;
int frameInterval = 20;
unsigned long fpsTimer = 0;

bool curious = 0;
bool cyclops = 0;
bool eyeL_open = 1; 
bool eyeR_open = 1;
bool blinkL = false;
bool blinkR = false;

int eyeLwidthDefault = 36;
int eyeLheightDefault = 36;
int eyeRwidthDefault = 36;
int eyeRheightDefault = 36;
int spaceBetweenDefault = 10;

byte eyeLborderRadiusDefault = 8;
byte eyeRborderRadiusDefault = 8;
byte eyeLborderRadiusNext = 8;
byte eyeRborderRadiusNext = 8;
float eyeLborderRadiusCurrent = 8;
float eyeRborderRadiusCurrent = 8;

int eyeLxDefault = ((screenWidth)-(eyeLwidthDefault+spaceBetweenDefault+eyeRwidthDefault))/2;
int eyeLyDefault = ((screenHeight-eyeLheightDefault)/2);
int eyeRxDefault = eyeLxDefault+eyeLwidthDefault+spaceBetweenDefault;
int eyeRyDefault = eyeLyDefault;

float eyeLxCurrent = eyeLxDefault;
float eyeLyCurrent = eyeLyDefault;
float eyeRxCurrent = eyeRxDefault;
float eyeRyCurrent = eyeRyDefault;

float eyeLwidthCurrent = eyeLwidthDefault;
float eyeLheightCurrent = 1; 
float eyeRwidthCurrent = eyeRwidthDefault;
float eyeRheightCurrent = 1; 

float eyelidsAngryLCurrent = 0, eyelidsAngryRCurrent = 0;
float eyelidsSadLCurrent = 0, eyelidsSadRCurrent = 0;
float eyelidsTiredLCurrent = 0, eyelidsTiredRCurrent = 0;
float eyelidsHappyLCurrent = 0, eyelidsHappyRCurrent = 0;

int eyeLxNext = eyeLxDefault;
int eyeLyNext = eyeLyDefault;
int eyeRyNext = eyeRyDefault;
int spaceBetweenNext = spaceBetweenDefault;
int eyeLwidthNext = eyeLwidthDefault;
int eyeLheightNext = eyeLheightDefault;
int eyeRwidthNext = eyeRwidthDefault;
int eyeRheightNext = eyeRheightDefault;

int eyelidsAngryLNext = 0, eyelidsAngryRNext = 0;
int eyelidsSadLNext = 0, eyelidsSadRNext = 0;
int eyelidsTiredLNext = 0, eyelidsTiredRNext = 0;
int eyelidsHappyLNext = 0, eyelidsHappyRNext = 0;

int eyeLheightOffset = 0;
int eyeRheightOffset = 0;

CustomShape customShapeNext = SHAPE_NONE;
CustomShape customShapeCurrent = SHAPE_NONE;
bool drawBlushCurrent = false;
bool drawBlushNext = false;

bool hFlicker = 0;
bool hFlickerAlternate = 0;
byte hFlickerAmplitude = 2;

bool vFlicker = 0;
bool vFlickerAlternate = 0;
byte vFlickerAmplitude = 10;

bool autoblinker = 0;
int blinkInterval = 1;
int blinkIntervalVariation = 4;
unsigned long blinktimer = 0;

bool idle = 0;
int idleInterval = 1;
int idleIntervalVariation = 3;
unsigned long idleAnimationTimer = 0;

bool mode = 0;
int modeInterval = 1;
int modeIntervalVariation = 3;
unsigned long modeAnimationTimer = 0;

bool confusedAnim = 0;
unsigned long confusedAnimationTimer = 0;
int confusedAnimationDuration = 500;
bool confusedToggle = 1;

bool laugh = 0;
unsigned long laughAnimationTimer = 0;
int laughAnimationDuration = 500;
bool laughToggle = 1;

bool sweat = 0;
byte sweatBorderradius = 3;

int sweat1XPosInitial = 2, sweat1XPos;
float sweat1YPos = 2, sweat1YPosMax, sweat1Height = 2, sweat1Width = 1;
int sweat2XPosInitial = 2, sweat2XPos;
float sweat2YPos = 2, sweat2YPosMax, sweat2Height = 2, sweat2Width = 1;
int sweat3XPosInitial = 2, sweat3XPos;
float sweat3YPos = 2, sweat3YPosMax, sweat3Height = 2, sweat3Width = 1;


RoboEyes(AdafruitDisplay &disp) : display(&disp) {};

void begin(int width, int height, byte frameRate) {
	screenWidth = width;
	screenHeight = height;
    
    eyeLheightCurrent = 1;
    eyeRheightCurrent = 1;
    eyeL_open = 1;
    eyeR_open = 1;
    
    eyeLxDefault = ((screenWidth)-(eyeLwidthDefault+spaceBetweenDefault+eyeRwidthDefault))/2;
    eyeLyDefault = ((screenHeight-eyeLheightDefault)/2);
    eyeRxDefault = eyeLxDefault+eyeLwidthDefault+spaceBetweenDefault;
    eyeRyDefault = eyeLyDefault;
    
    eyeLxCurrent = eyeLxDefault;
    eyeLyCurrent = eyeLyDefault;
    eyeRxCurrent = eyeRxDefault;
    eyeRyCurrent = eyeRyDefault;

    display->clearDisplay();
    display->display();
    setFramerate(frameRate);
}

void update(){
  if(millis()-fpsTimer >= frameInterval){
    drawEyes();
    fpsTimer = millis();
  }
}

void setFramerate(byte fps){
  frameInterval = 1000/fps;
}

void setDisplayColors(uint8_t background, uint8_t main) {
  BGCOLOR = background;
  MAINCOLOR = main;
}

void setWidth(byte leftEye, byte rightEye) {
  eyeLwidthNext = leftEye;
  eyeRwidthNext = rightEye;
  eyeLwidthDefault = leftEye;
  eyeRwidthDefault = rightEye;
  eyeLxDefault = ((screenWidth)-(eyeLwidthDefault+spaceBetweenDefault+eyeRwidthDefault))/2;
  eyeRxDefault = eyeLxDefault+eyeLwidthDefault+spaceBetweenDefault;
  eyeLxNext = eyeLxDefault;
}

void setHeight(byte leftEye, byte rightEye) {
  eyeLheightNext = leftEye;
  eyeRheightNext = rightEye;
  eyeLheightDefault = leftEye;
  eyeRheightDefault = rightEye;
  eyeLyDefault = ((screenHeight-eyeLheightDefault)/2);
  eyeRyDefault = eyeLyDefault;
  eyeLyNext = eyeLyDefault;
  eyeRyNext = eyeRyDefault;
}

void setBorderradius(byte leftEye, byte rightEye) {
  eyeLborderRadiusNext = leftEye;
  eyeRborderRadiusNext = rightEye;
  eyeLborderRadiusDefault = leftEye;
  eyeRborderRadiusDefault = rightEye;
}

void setSpacebetween(int space) {
  spaceBetweenNext = space;
  spaceBetweenDefault = space;
  eyeRxDefault = eyeLxDefault+eyeLwidthDefault+spaceBetweenDefault;
}

void setMood(Mood mood) {
    eyeLxNext = eyeLxDefault;
    eyeLyNext = eyeLyDefault;
    eyeRyNext = eyeRyDefault;
    spaceBetweenNext = spaceBetweenDefault;
    
    eyeLwidthNext = eyeLwidthDefault;
    eyeRwidthNext = eyeRwidthDefault;
    eyeLheightNext = eyeLheightDefault;
    eyeRheightNext = eyeRheightDefault;

    eyelidsAngryLNext = 0; eyelidsAngryRNext = 0;
    eyelidsSadLNext = 0; eyelidsSadRNext = 0;
    eyelidsTiredLNext = 0; eyelidsTiredRNext = 0;
    eyelidsHappyLNext = 0; eyelidsHappyRNext = 0;
    
    drawBlushNext = false;
    
    CustomShape targetShape = SHAPE_NONE;
    int mvX = 15;

    switch(mood) {
      // ORIGINAL 28 EMOTIONS
      case EXTREME_LF:
        eyeLxNext -= mvX * 2;
        eyeLwidthNext = eyeLwidthDefault * 0.7;
        eyeRwidthNext = eyeRwidthDefault * 0.9;
        break;
      case NORMAL_LF: eyeLxNext -= mvX; break;
      case NEUTRAL: break;
      case NORMAL_RT: eyeLxNext += mvX; break;
      case EXTREME_RT:
        eyeLxNext += mvX * 2;
        eyeLwidthNext = eyeLwidthDefault * 0.9;
        eyeRwidthNext = eyeRwidthDefault * 0.7;
        break;
      case WORRIED:
        eyelidsSadLNext = eyeLheightDefault * 0.4;
        eyelidsSadRNext = eyeRheightDefault * 0.4;
        break;
      case SCARED:
        eyeLwidthNext = eyeLwidthDefault * 0.8;
        eyeRwidthNext = eyeRwidthDefault * 0.8;
        eyeLheightNext = eyeLheightDefault * 0.8;
        eyeRheightNext = eyeRheightDefault * 0.8;
        eyeLxNext += 3; spaceBetweenNext -= 6;
        break;
      case HAPPY_LF:
        eyeLxNext -= mvX; eyelidsHappyLNext = eyeLheightDefault * 0.4; eyelidsHappyRNext = eyeRheightDefault * 0.4;
        break;
      case HAPPY:
        eyelidsHappyLNext = eyeLheightDefault * 0.4; eyelidsHappyRNext = eyeRheightDefault * 0.4; break;
      case GLEE:
        eyelidsHappyLNext = eyeLheightDefault * 0.55; eyelidsHappyRNext = eyeRheightDefault * 0.55;
        eyeLxNext -= 2; spaceBetweenNext += 4; break;
      case HAPPY_RT:
        eyeLxNext += mvX; eyelidsHappyLNext = eyeLheightDefault * 0.4; eyelidsHappyRNext = eyeRheightDefault * 0.4;
        break;
      case SAD_LT:
        eyeLxNext -= mvX; eyelidsSadLNext = eyeLheightDefault * 0.4; eyelidsSadRNext = eyeRheightDefault * 0.4; break;
      case SAD_DOWN:
        eyelidsSadLNext = eyeLheightDefault * 0.4; eyelidsSadRNext = eyeRheightDefault * 0.4; eyeLyNext += 6; break;
      case SAD_RT:
        eyeLxNext += mvX; eyelidsSadLNext = eyeLheightDefault * 0.4; eyelidsSadRNext = eyeRheightDefault * 0.4; break;
      case SKEPTIC:
        eyelidsTiredLNext = eyeLheightDefault * 0.1; eyelidsTiredRNext = eyeRheightDefault * 0.4;
        eyelidsHappyRNext = eyeRheightDefault * 0.2; break;
      case FOCUSED:
        eyelidsTiredLNext = eyeLheightDefault * 0.3; eyelidsTiredRNext = eyeRheightDefault * 0.3;
        eyelidsHappyLNext = eyeLheightDefault * 0.2; eyelidsHappyRNext = eyeRheightDefault * 0.2; break;
      case SQUINT:
        eyelidsTiredLNext = eyeLheightDefault * 0.4; eyelidsTiredRNext = eyeRheightDefault * 0.4;
        eyelidsHappyLNext = eyeLheightDefault * 0.4; eyelidsHappyRNext = eyeRheightDefault * 0.4;
        eyeLwidthNext = eyeLwidthDefault * 0.8; eyeRwidthNext = eyeRwidthDefault * 0.8; break;
      case FRUSTRATED:
        eyeLwidthNext = eyeLwidthDefault * 0.8; eyeRwidthNext = eyeRwidthDefault * 0.8;
        eyeLheightNext = eyeLheightDefault * 0.8; eyeRheightNext = eyeRheightDefault * 0.8;
        eyelidsAngryLNext = eyeLheightDefault * 0.4; eyelidsAngryRNext = eyeRheightDefault * 0.4; break;
      case ANNOYED:
        eyelidsTiredLNext = eyeLheightDefault * 0.4; eyelidsTiredRNext = eyeRheightDefault * 0.4; break;
      case ANGRY:
        eyelidsAngryLNext = eyeLheightDefault * 0.5; eyelidsAngryRNext = eyeRheightDefault * 0.5;
        eyeLxNext += 3; spaceBetweenNext -= 6; eyeLyNext += 2; break;
      case FURIOUS:
        eyelidsAngryLNext = eyeLheightDefault * 0.7; eyelidsAngryRNext = eyeRheightDefault * 0.7;
        eyeLwidthNext = eyeLwidthDefault * 0.9; eyeRwidthNext = eyeRwidthDefault * 0.9;
        eyeLxNext += 6; spaceBetweenNext -= 12; eyeLyNext += 4; break;
      case SLEEPY:
        eyelidsTiredLNext = eyeLheightDefault * 0.6; eyelidsTiredRNext = eyeRheightDefault * 0.6;
        eyelidsHappyLNext = eyeLheightDefault * 0.1; eyelidsHappyRNext = eyeRheightDefault * 0.1;
        eyeLyNext += 5; break;
      case SUSPICIOUS:
        eyelidsTiredLNext = eyeLheightDefault * 0.1; eyelidsTiredRNext = eyeRheightDefault * 0.5;
        eyelidsHappyRNext = eyeRheightDefault * 0.3; break;
      case UNIMPRESSED:
        eyelidsTiredLNext = eyeLheightDefault * 0.5; eyelidsTiredRNext = eyeRheightDefault * 0.5; eyeLyNext += 5; break;
      case SURPRISED:
        eyeLheightNext = eyeLheightDefault * 1.2; eyeRheightNext = eyeRheightDefault * 1.2;
        eyeLwidthNext = eyeLwidthDefault * 1.1; eyeRwidthNext = eyeRwidthDefault * 1.1; eyeLyNext -= 4; break;
      case AWE:
        eyeLheightNext = eyeLheightDefault * 1.35; eyeRheightNext = eyeRheightDefault * 1.35;
        eyeLwidthNext = eyeLwidthDefault * 1.25; eyeRwidthNext = eyeRwidthDefault * 1.25;
        eyeLyNext -= 6; eyeLxNext -= 4; spaceBetweenNext += 8; break;
      case BLINK_LOW:
        eyeLheightNext = 2; eyeRheightNext = 2; eyeLyNext += eyeLheightDefault / 2; break;
      case BLINK_HIGH:
        eyeLheightNext = 2; eyeRheightNext = 2; eyeLyNext -= eyeLheightDefault / 4; break;
        
      // THE NEW 28 COZMO EXPRESSIONS
      case COMPASSIONATE: 
        eyelidsSadLNext = eyeLheightDefault * 0.5; eyelidsSadRNext = eyeRheightDefault * 0.5; eyeLyNext -= 4; break;
      case PLAYFUL: targetShape = SHAPE_PLAYFUL; break;
      case DATA_STREAM: targetShape = SHAPE_DATA_STREAM; break;
      case CURIOUS:
        eyeLheightNext = eyeLheightDefault * 1.1; eyeRheightNext = eyeRheightDefault * 1.1; break;
      case PROBLEM_SOLVING: targetShape = SHAPE_PROBLEM_SOLVING; break;
      case SIDE_GLANCE:
        eyeLxNext += 20; eyeLwidthNext = eyeLwidthDefault * 0.6; eyeRwidthNext = eyeRwidthDefault * 0.6; break;
      case ADMIRATION: targetShape = SHAPE_ADMIRATION; break;
      case SYSTEM_ERROR: targetShape = SHAPE_SYSTEM_ERROR; break;
      case CONFUSED: targetShape = SHAPE_CONFUSED; break;
      case HYPNOTIZED: targetShape = SHAPE_HYPNOTIZED; break;
      case MISCHIEVOUS:
        eyelidsAngryLNext = eyeLheightDefault * 0.8; eyelidsAngryRNext = eyeRheightDefault * 0.8;
        eyeLheightNext = eyeLheightDefault * 0.9; eyeRheightNext = eyeRheightDefault * 0.9;
        eyeLwidthNext = eyeLwidthDefault * 0.8; eyeRwidthNext = eyeRwidthDefault * 0.8; break;
      case FLUSTERED:
        eyelidsSadLNext = eyeLheightDefault * 0.4; eyelidsSadRNext = eyeRheightDefault * 0.4; drawBlushNext = true; break;
      case STUNNED: targetShape = SHAPE_STUNNED; break;
      case LOW_BATTERY_ICON: targetShape = SHAPE_LOW_BATTERY_ICON; break;
      case LOW_BATTERY_EYES:
        eyeLheightNext = eyeLheightDefault * 0.2; eyeRheightNext = eyeRheightDefault * 0.2; eyeLyNext += eyeLheightDefault * 0.6; break;
      case DETERMINED: 
        eyelidsAngryLNext = eyeLheightDefault * 0.3; eyelidsAngryRNext = eyeRheightDefault * 0.3;
        eyelidsTiredLNext = eyeLheightDefault * 0.2; eyelidsTiredRNext = eyeRheightDefault * 0.2; break;
      case ONE_EYEBROW:
        eyelidsAngryLNext = eyeLheightDefault * 0.5;
        eyeRheightNext = eyeRheightDefault * 1.2; eyeRyNext -= 5; break;
      case BARCODE_SCAN: targetShape = SHAPE_BARCODE; break;
      case FOCUSED_GOAL: targetShape = SHAPE_FOCUSED_GOAL; break;
      case NERVOUS: targetShape = SHAPE_NERVOUS; break;
      case INTRIGUED: targetShape = SHAPE_INTRIGUED; break;
      case CALM: 
        eyeLheightNext = 4; eyeRheightNext = 4;
        eyeLwidthNext = screenWidth / 2 - 10; eyeRwidthNext = screenWidth / 2 - 10;
        spaceBetweenNext = 4; eyeLxNext = 8; break;
      case OPTIMIC: 
        eyeLheightNext = eyeLheightDefault * 0.8; eyeRheightNext = eyeRheightDefault * 0.8; break;
      case CONTENT:
        eyeLwidthNext = eyeLwidthDefault * 0.9; eyeRwidthNext = eyeRwidthDefault * 0.9;
        eyelidsHappyLNext = eyeLheightDefault * 0.2; eyelidsHappyRNext = eyeRheightDefault * 0.2; break;
      case QUESTION: targetShape = SHAPE_QUESTION; break;
      case WINKING:
        eyelidsHappyLNext = eyeLheightDefault * 0.3; eyeRheightNext = 4; eyeLyNext += eyeRheightDefault / 2; break;
      case POUTING: targetShape = SHAPE_POUTING; break;
      case SYSTEM_IDLE: targetShape = SHAPE_SYSTEM_IDLE; break;
    }

    if (targetShape != customShapeCurrent && !blinkL && !blinkR) { // Snap transition with a forced blink!
        customShapeNext = targetShape;
        blink();
    } else {
        customShapeNext = targetShape;
    }
}

int getScreenConstraint_X(){
  return screenWidth-eyeLwidthCurrent-spaceBetweenDefault-eyeRwidthCurrent;
} 

int getScreenConstraint_Y(){
 return screenHeight-eyeLheightDefault;
}

void setPosition(unsigned char position) {
    switch (position) {
    case N:  eyeLxNext = getScreenConstraint_X()/2; eyeLyNext = 0; break;
    case NE: eyeLxNext = getScreenConstraint_X(); eyeLyNext = 0; break;
    case E:  eyeLxNext = getScreenConstraint_X(); eyeLyNext = getScreenConstraint_Y()/2; break;
    case SE: eyeLxNext = getScreenConstraint_X(); eyeLyNext = getScreenConstraint_Y(); break;
    case S:  eyeLxNext = getScreenConstraint_X()/2; eyeLyNext = getScreenConstraint_Y(); break;
    case SW: eyeLxNext = 0; eyeLyNext = getScreenConstraint_Y(); break;
    case W:  eyeLxNext = 0; eyeLyNext = getScreenConstraint_Y()/2; break;
    case NW: eyeLxNext = 0; eyeLyNext = 0; break;
    default: eyeLxNext = getScreenConstraint_X()/2; eyeLyNext = getScreenConstraint_Y()/2; break;
    }
}

void setAutoblinker(bool active, int interval, int variation){
  autoblinker = active; blinkInterval = interval; blinkIntervalVariation = variation;
}
void setAutoblinker(bool active){ autoblinker = active; }

void setIdleMode(bool active, int interval, int variation){
  idle = active; idleInterval = interval; idleIntervalVariation = variation;
}
void setMode(bool active, int interval, int variation){
  mode = active; modeInterval = interval; modeIntervalVariation = variation;
}
void setIdleMode(bool active) { idle = active; }
void setMode(bool active) { mode = active; }

void setCuriosity(bool curiousBit) { curious = curiousBit; }
void setCyclops(bool cyclopsBit) { cyclops = cyclopsBit; }

void setHFlicker (bool flickerBit, byte Amplitude) {
  hFlicker = flickerBit; hFlickerAmplitude = Amplitude;
}
void setHFlicker (bool flickerBit) { hFlicker = flickerBit; }

void setVFlicker (bool flickerBit, byte Amplitude) {
  vFlicker = flickerBit; vFlickerAmplitude = Amplitude;
}
void setVFlicker (bool flickerBit) { vFlicker = flickerBit; }

void setSweat (bool sweatBit) { sweat = sweatBit; }

void close() { eyeL_open = 0; eyeR_open = 0; }
void open() { eyeL_open = 1; eyeR_open = 1; }
void blink() { blinkL = true; blinkR = true; }
void anim_blink() { blink(); }

void close(bool l, bool r) {
  if (l) eyeL_open = 0;
  if (r) eyeR_open = 0;
}
void open(bool l, bool r) {
  if (l) eyeL_open = 1;
  if (r) eyeR_open = 1;
}
void blink(bool l, bool r) {
  if (l) blinkL = true;
  if (r) blinkR = true;
}

void anim_confused() { confusedAnim = 1; }
void anim_laugh() { laugh = 1; }

void drawCustomShape(int lX, int lY, int lW, int lH, int rX, int rY, int rW, int rH) {
    if (customShapeCurrent == SHAPE_PLAYFUL) {
        display->drawRoundRect(lX, lY, lW, lH, lW/2, MAINCOLOR);
        display->fillRect(lX, lY+lH/2, lW, lH/2+1, BGCOLOR); 
        display->drawRoundRect(lX+2, lY+2, lW-4, lH-4, (lW-4)/2, MAINCOLOR);
        display->fillRect(lX+2, lY+lH/2, lW-4, lH/2+1, BGCOLOR);
        if(!cyclops) {
            display->drawRoundRect(rX, rY, rW, rH, rW/2, MAINCOLOR);
            display->fillRect(rX, rY+rH/2, rW, rH/2+1, BGCOLOR);
            display->drawRoundRect(rX+2, rY+2, rW-4, rH-4, (rW-4)/2, MAINCOLOR);
            display->fillRect(rX+2, rY+rH/2, rW-4, rH/2+1, BGCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_DATA_STREAM) {
        for(int x = lX; x < lX+lW; x+=4) {
            for(int y = lY; y < lY+lH; y+= random(4, 9)) display->drawLine(x, y, x, y+2, MAINCOLOR);
        }
        if(!cyclops) {
            for(int x = rX; x < rX+rW; x+=4) {
                for(int y = rY; y < rY+rH; y+= random(4, 9)) display->drawLine(x, y, x, y+2, MAINCOLOR);
            }
        }
    }
    else if (customShapeCurrent == SHAPE_PROBLEM_SOLVING) {
        display->drawRect(lX, lY, lW, lH, MAINCOLOR);
        display->drawRect(lX+4, lY+4, lW-8, lH-8, MAINCOLOR);
        display->drawRect(lX+8, lY+8, lW-16, lH-16, MAINCOLOR);
        if(!cyclops) {
            display->drawRect(rX, rY, rW, rH, MAINCOLOR);
            display->drawRect(rX+4, rY+4, rW-8, rH-8, MAINCOLOR);
            display->drawRect(rX+8, rY+8, rW-16, rH-16, MAINCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_ADMIRATION) {
        int cLx = lX + lW/2, cLy = lY + lH/2;
        display->fillTriangle(cLx, lY, cLx+4, cLy, cLx-4, cLy, MAINCOLOR);
        display->fillTriangle(cLx, lY+lH, cLx+4, cLy, cLx-4, cLy, MAINCOLOR);
        display->fillTriangle(lX, cLy, cLx, cLy-4, cLx, cLy+4, MAINCOLOR);
        display->fillTriangle(lX+lW, cLy, cLx, cLy-4, cLx, cLy+4, MAINCOLOR);
        if(!cyclops) {
            int cRx = rX + rW/2, cRy = rY + rH/2;
            display->fillTriangle(cRx, rY, cRx+4, cRy, cRx-4, cRy, MAINCOLOR);
            display->fillTriangle(cRx, rY+rH, cRx+4, cRy, cRx-4, cRy, MAINCOLOR);
            display->fillTriangle(rX, cRy, cRx, cRy-4, cRx, cRy+4, MAINCOLOR);
            display->fillTriangle(rX+rW, cRy, cRx, cRy-4, cRx, cRy+4, MAINCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_SYSTEM_ERROR) {
        for(int x = lX; x < (cyclops ? lX+lW : rX+rW); x+=5) {
             for(int y = lY; y < lY+lH; y+=5) {
                  if(random(3)==0) display->fillRect(x, y, 4, 4, MAINCOLOR);
             }
        }
    }
    else if (customShapeCurrent == SHAPE_CONFUSED) {
        int r = min(lW, lH)/2;
        display->drawCircle(lX+lW/2, lY+lH/2, r, MAINCOLOR);
        display->drawCircle(lX+lW/2, lY+lH/2, r-1, MAINCOLOR);
        display->drawCircle(lX+lW/2, lY+lH/2, r-2, MAINCOLOR);
        if(!cyclops) {
            display->drawCircle(rX+rW/2, rY+rH/2, r, MAINCOLOR);
            display->drawCircle(rX+rW/2, rY+rH/2, r-1, MAINCOLOR);
            display->drawCircle(rX+rW/2, rY+rH/2, r-2, MAINCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_HYPNOTIZED) {
        for(float a = 0; a < 6*PI; a+=0.5) {
            float rad = a * 1.5;
            display->fillCircle(lX+lW/2 + rad*cos(a), lY+lH/2 + rad*sin(a), 2, MAINCOLOR);
            if(!cyclops) display->fillCircle(rX+rW/2 + rad*cos(a), rY+rH/2 + rad*sin(a), 2, MAINCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_POUTING) {
        for(float a = 0; a < 4*PI; a+=0.5) {
            float rad = a * 1.2;
            display->fillCircle(lX+lW/2 + rad*cos(a), lY+lH/2 + rad*sin(a), 1, MAINCOLOR);
            if(!cyclops) display->fillCircle(rX+rW/2 + rad*cos(a), rY+rH/2 + rad*sin(a), 1, MAINCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_STUNNED) {
        for(int i = -1; i <= 1; i++) {
           display->drawLine(lX, lY+i, lX+lW, lY+lH+i, MAINCOLOR);
           display->drawLine(lX+lW, lY+i, lX, lY+lH+i, MAINCOLOR);
           if(!cyclops) {
               display->drawLine(rX, rY+i, rX+rW, rY+rH+i, MAINCOLOR);
               display->drawLine(rX+rW, rY+i, rX, rY+rH+i, MAINCOLOR);
           }
        }
    }
    else if (customShapeCurrent == SHAPE_LOW_BATTERY_ICON) {
        int bW = 60, bH = 20;
        int bX = (screenWidth - bW)/2;
        int bY = screenHeight - bH - 2;
        display->drawRect(bX, bY, bW, bH, MAINCOLOR);
        display->drawRect(bX+1, bY+1, bW-2, bH-2, MAINCOLOR);
        display->fillRect(bX+bW, bY+bH/2-4, 4, 8, MAINCOLOR); 
        display->fillRect(bX+4, bY+4, 8, bH-8, MAINCOLOR);
    }
    else if (customShapeCurrent == SHAPE_BARCODE) {
        for(int x = lX; x < (cyclops ? lX+lW : rX+rW); x+= random(2, 6)) {
            display->fillRect(x, lY, random(1, 4), lH, MAINCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_FOCUSED_GOAL) {
        for(int y = lY; y < lY+lH; y+= 3) {
            display->fillRect(lX, y, (cyclops ? lW*2 : rX+rW-lX), 1, MAINCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_NERVOUS) {
        int w = cyclops ? lW : rX+rW - lX;
        for(int y = lY; y < lY+lH; y+= 4) {
            for(int x = lX; x < lX+w; x+=6) {
                if((x+y)%3 == 0) display->fillRect(x, y, 4, 3, MAINCOLOR);
            }
        }
    }
    else if (customShapeCurrent == SHAPE_INTRIGUED) {
        for(int i=-2; i<=2; i++) display->drawLine(lX+lW, lY+i, lX, lY+lH+i, MAINCOLOR);
        if(!cyclops) {
            display->drawRoundRect(rX, rY, rW, rH, rW/2, MAINCOLOR);
            display->fillRect(rX, rY, rW/2+2, rH, BGCOLOR); 
        }
    }
    else if (customShapeCurrent == SHAPE_QUESTION) {
        display->fillRoundRect(lX, lY+lH/2, lW, lH/2, 4, MAINCOLOR);
        if(!cyclops) {
            display->fillRoundRect(rX, rY, rW, rH/2, rW/2, MAINCOLOR);
            display->fillRect(rX, rY+rH/4, rW/2+2, rH/4+2, BGCOLOR);
            display->fillRect(rX+rW/2, rY+rH/2, rW/8, rH/4, MAINCOLOR);
            display->fillRect(rX+rW/2, rY+rH - 4, rW/8, 4, MAINCOLOR);
        }
    }
    else if (customShapeCurrent == SHAPE_SYSTEM_IDLE) {
        int cy = lY + lH/2;
        for(int x = 10; x < screenWidth-10; x += 6) {
            display->fillRect(x, cy-1, 3, 3, MAINCOLOR);
        }
    }
}


void drawEyes() {
  if(curious) {
    if(eyeLxNext <= 10) eyeLheightOffset = 8;
    else if(eyeLxNext >= (getScreenConstraint_X()-10) && cyclops) eyeLheightOffset = 8;
    else eyeLheightOffset = 0;
    if(eyeLxNext + eyeLwidthNext + spaceBetweenNext >= screenWidth - eyeRwidthCurrent - 10) eyeRheightOffset = 8;
    else eyeRheightOffset = 0;
  } else {
    eyeLheightOffset = 0; eyeRheightOffset = 0;
  }

  int targetLHeight, targetRHeight;

  if (blinkL) {
    targetLHeight = 1;
    if (eyeLheightCurrent <= 2.2f + eyeLheightOffset) {
        blinkL = false;
        if(customShapeCurrent != customShapeNext) customShapeCurrent = customShapeNext;
    }
  } else if (!eyeL_open) {
    targetLHeight = 1;
    if(customShapeCurrent != customShapeNext) customShapeCurrent = customShapeNext;
  } else {
    targetLHeight = eyeLheightNext + eyeLheightOffset;
  }

  if (blinkR) {
    targetRHeight = 1;
    if (eyeRheightCurrent <= 2.2f + eyeRheightOffset) blinkR = false;
  } else if (!eyeR_open) {
    targetRHeight = 1;
  } else {
    targetRHeight = eyeRheightNext + eyeRheightOffset;
  }

  float ease = 0.35f;

  eyeLxCurrent += (eyeLxNext - eyeLxCurrent) * ease;
  eyeLyCurrent += (eyeLyNext - eyeLyCurrent) * ease;
  int realRxNext = eyeLxNext + eyeLwidthNext + spaceBetweenNext;
  int realRyNext = eyeRyNext;
  eyeRxCurrent += (realRxNext - eyeRxCurrent) * ease;
  eyeRyCurrent += (realRyNext - eyeRyCurrent) * ease;

  eyeLwidthCurrent += (eyeLwidthNext - eyeLwidthCurrent) * ease;
  eyeLheightCurrent += (targetLHeight - eyeLheightCurrent) * ease;
  eyeRwidthCurrent += (eyeRwidthNext - eyeRwidthCurrent) * ease;
  eyeRheightCurrent += (targetRHeight - eyeRheightCurrent) * ease;
  
  float drawLy = eyeLyCurrent + (eyeLheightDefault - eyeLheightCurrent)/2 - eyeLheightOffset/2;
  float drawRy = eyeRyCurrent + (eyeRheightDefault - eyeRheightCurrent)/2 - eyeRheightOffset/2;

  eyeLborderRadiusCurrent += (eyeLborderRadiusNext - eyeLborderRadiusCurrent) * ease;
  eyeRborderRadiusCurrent += (eyeRborderRadiusNext - eyeRborderRadiusCurrent) * ease;

  eyelidsAngryLCurrent += (eyelidsAngryLNext - eyelidsAngryLCurrent) * ease;
  eyelidsAngryRCurrent += (eyelidsAngryRNext - eyelidsAngryRCurrent) * ease;
  eyelidsSadLCurrent += (eyelidsSadLNext - eyelidsSadLCurrent) * ease;
  eyelidsSadRCurrent += (eyelidsSadRNext - eyelidsSadRCurrent) * ease;
  eyelidsTiredLCurrent += (eyelidsTiredLNext - eyelidsTiredLCurrent) * ease;
  eyelidsTiredRCurrent += (eyelidsTiredRNext - eyelidsTiredRCurrent) * ease;
  eyelidsHappyLCurrent += (eyelidsHappyLNext - eyelidsHappyLCurrent) * ease;
  eyelidsHappyRCurrent += (eyelidsHappyRNext - eyelidsHappyRCurrent) * ease;
  drawBlushCurrent = drawBlushNext; // instant toggle for overlay

  if(autoblinker){
    if(millis() >= blinktimer){
      blink();
      blinktimer = millis()+(blinkInterval*1000)+(random(blinkIntervalVariation)*1000);
    }
  }

  if(laugh){
    if(laughToggle){
      setVFlicker(1, 5); laughAnimationTimer = millis(); laughToggle = 0;
    } else if(millis() >= laughAnimationTimer+laughAnimationDuration){
      setVFlicker(0, 0); laughToggle = 1; laugh=0; 
    }
  }

  if(confusedAnim){
    if(confusedToggle){
      setHFlicker(1, 20); confusedAnimationTimer = millis(); confusedToggle = 0;
    } else if(millis() >= confusedAnimationTimer+confusedAnimationDuration){
      setHFlicker(0, 0); confusedToggle = 1; confusedAnim=0; 
    }
  }

  if(idle){
    if(millis() >= idleAnimationTimer){
      eyeLxNext = random(getScreenConstraint_X());
      eyeLyNext = random(getScreenConstraint_Y());
      idleAnimationTimer = millis()+(idleInterval*1000)+(random(idleIntervalVariation)*1000);
    }
  }
  
  if(mode){
    if(millis() >= modeAnimationTimer){
      eyeLyNext = random((getScreenConstraint_Y()/2)+5);
      modeAnimationTimer = millis()+(modeInterval*500)+(random(modeIntervalVariation)*500);
    }
  }

  float drawLx = eyeLxCurrent;
  float drawRx = eyeRxCurrent;

  if(hFlicker) {
    if(hFlickerAlternate) { drawLx += hFlickerAmplitude; drawRx += hFlickerAmplitude; }
    else { drawLx -= hFlickerAmplitude; drawRx -= hFlickerAmplitude; }
    hFlickerAlternate = !hFlickerAlternate;
  }

  if(vFlicker) {
    if(vFlickerAlternate) { drawLy += vFlickerAmplitude; drawRy += vFlickerAmplitude; }
    else { drawLy -= vFlickerAmplitude; drawRy -= vFlickerAmplitude; }
    vFlickerAlternate = !vFlickerAlternate;
  }

  display->clearDisplay();

  int lX = (int)drawLx; int lY = (int)drawLy;
  int lW = (int)eyeLwidthCurrent; int lH = (int)eyeLheightCurrent;
  int rX = (int)drawRx; int rY = (int)drawRy;
  int rW = (int)eyeRwidthCurrent; int rH = (int)eyeRheightCurrent;

  if (customShapeCurrent != SHAPE_NONE) {
      drawCustomShape(lX, lY, lW, lH, rX, rY, rW, rH);
  } else {
      display->fillRoundRect(lX, lY, lW, lH, (int)eyeLborderRadiusCurrent, MAINCOLOR);
      if (!cyclops){
        display->fillRoundRect(rX, rY, rW, rH, (int)eyeRborderRadiusCurrent, MAINCOLOR);
      }

      if(!cyclops) {
          if((int)eyelidsTiredLCurrent > 0) display->fillRect(lX - 1, lY - 1, lW + 2, (int)eyelidsTiredLCurrent + 1, BGCOLOR);
          if((int)eyelidsTiredRCurrent > 0) display->fillRect(rX - 1, rY - 1, rW + 2, (int)eyelidsTiredRCurrent + 1, BGCOLOR);
      } else {
          if((int)eyelidsTiredLCurrent > 0) display->fillRect(lX - 1, lY - 1, lW/2 + 1, (int)eyelidsTiredLCurrent + 1, BGCOLOR);
          if((int)eyelidsTiredRCurrent > 0) display->fillRect(lX + lW/2, lY - 1, lW/2 + 2, (int)eyelidsTiredRCurrent + 1, BGCOLOR);
      }

      if(!cyclops) {
          if((int)eyelidsSadLCurrent > 0) {
            display->fillTriangle(lX, lY-1, lX+lW, lY-1, lX, lY+(int)eyelidsSadLCurrent-1, BGCOLOR);
          }
          if((int)eyelidsSadRCurrent > 0) {
            display->fillTriangle(rX, rY-1, rX+rW, rY-1, rX+rW, rY+(int)eyelidsSadRCurrent-1, BGCOLOR);
          }
      } else {
          if((int)eyelidsSadLCurrent > 0) {
            display->fillTriangle(lX, lY-1, lX+lW/2, lY-1, lX, lY+(int)eyelidsSadLCurrent-1, BGCOLOR);
          }
          if((int)eyelidsSadRCurrent > 0) {
            display->fillTriangle(lX+lW, lY-1, lX+lW/2, lY-1, lX+lW, lY+(int)eyelidsSadRCurrent-1, BGCOLOR);
          }
      }

      if(!cyclops) {
          if((int)eyelidsAngryLCurrent > 0) {
            display->fillTriangle(lX, lY-1, lX+lW, lY-1, lX+lW, lY+(int)eyelidsAngryLCurrent-1, BGCOLOR);
          }
          if((int)eyelidsAngryRCurrent > 0) {
            display->fillTriangle(rX, rY-1, rX+rW, rY-1, rX, rY+(int)eyelidsAngryRCurrent-1, BGCOLOR);
          }
      } else {
          if((int)eyelidsAngryLCurrent > 0) {
            display->fillTriangle(lX, lY-1, lX+lW/2, lY-1, lX+lW/2, lY+(int)eyelidsAngryLCurrent-1, BGCOLOR);
          }
          if((int)eyelidsAngryRCurrent > 0) {
            display->fillTriangle(lX+lW, lY-1, lX+lW/2, lY-1, lX+lW/2, lY+(int)eyelidsAngryRCurrent-1, BGCOLOR);
          }
      }

      if(!cyclops) {
          if((int)eyelidsHappyLCurrent > 0) {
            display->fillRect(lX - 1, lY + lH - (int)eyelidsHappyLCurrent, lW + 2, (int)eyelidsHappyLCurrent + 1, BGCOLOR);
          }
          if((int)eyelidsHappyRCurrent > 0) {
            display->fillRect(rX - 1, rY + rH - (int)eyelidsHappyRCurrent, rW + 2, (int)eyelidsHappyRCurrent + 1, BGCOLOR);
          }
      } else {
          if((int)eyelidsHappyLCurrent > 0) {
            display->fillRect(lX - 1, lY + lH - (int)eyelidsHappyLCurrent, lW/2 + 1, (int)eyelidsHappyLCurrent + 1, BGCOLOR);
          }
          if((int)eyelidsHappyRCurrent > 0) {
            display->fillRect(lX + lW/2, lY + lH - (int)eyelidsHappyRCurrent, lW/2 + 2, (int)eyelidsHappyRCurrent + 1, BGCOLOR);
          }
      }
      
      if(drawBlushCurrent) {
        for(int x = lX; x < lX+lW; x+=4) {
             for(int y = lY+lH+2; y < lY+lH+6; y+=3) { if(random(2)==0) display->fillRect(x, y, 2, 2, MAINCOLOR); }
        }
        for(int x = rX; x < rX+rW; x+=4) {
             for(int y = rY+rH+2; y < rY+rH+6; y+=3) { if(random(2)==0) display->fillRect(x, y, 2, 2, MAINCOLOR); }
        }
      }
  }

  if (sweat){
    if(sweat1YPos <= sweat1YPosMax){sweat1YPos+=0.5;}
    else {sweat1XPosInitial = random(30); sweat1YPos = 2; sweat1YPosMax = (random(10)+10); sweat1Width = 1; sweat1Height = 2;}
    if(sweat1YPos <= sweat1YPosMax/2){sweat1Width+=0.5; sweat1Height+=0.5;}
    else {sweat1Width-=0.1; sweat1Height-=0.5;}
    sweat1XPos = sweat1XPosInitial-(sweat1Width/2);
    display->fillRoundRect(sweat1XPos, sweat1YPos, sweat1Width, sweat1Height, sweatBorderradius, MAINCOLOR);

    if(sweat2YPos <= sweat2YPosMax){sweat2YPos+=0.5;}
    else {sweat2XPosInitial = random((screenWidth-60))+30; sweat2YPos = 2; sweat2YPosMax = (random(10)+10); sweat2Width = 1; sweat2Height = 2;}
    if(sweat2YPos <= sweat2YPosMax/2){sweat2Width+=0.5; sweat2Height+=0.5;}
    else {sweat2Width-=0.1; sweat2Height-=0.5;}
    sweat2XPos = sweat2XPosInitial-(sweat2Width/2);
    display->fillRoundRect(sweat2XPos, sweat2YPos, sweat2Width, sweat2Height, sweatBorderradius, MAINCOLOR);

    if(sweat3YPos <= sweat3YPosMax){sweat3YPos+=0.5;}
    else {sweat3XPosInitial = (screenWidth-30)+(random(30)); sweat3YPos = 2; sweat3YPosMax = (random(10)+10); sweat3Width = 1; sweat3Height = 2;}
    if(sweat3YPos <= sweat3YPosMax/2){sweat3Width+=0.5; sweat3Height+=0.5;}
    else {sweat3Width-=0.1; sweat3Height-=0.5;}
    sweat3XPos = sweat3XPosInitial-(sweat3Width/2);
    display->fillRoundRect(sweat3XPos, sweat3YPos, sweat3Width, sweat3Height, sweatBorderradius, MAINCOLOR);
  }

  display->display();
}

}; 

#endif
