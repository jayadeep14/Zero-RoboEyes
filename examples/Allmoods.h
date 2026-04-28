#include <Adafruit_SSD1306.h>
#include "Zero_RoboEyes.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RoboEyes<Adafruit_SSD1306> roboEyes(display); 

// Array containing all 56 moods
Mood allEmotions[] = {
  // Original 28
  EXTREME_LF, NORMAL_LF, NEUTRAL, NORMAL_RT, EXTREME_RT, 
  WORRIED, SCARED, HAPPY_LF, HAPPY, GLEE, HAPPY_RT, 
  SAD_LT, SAD_DOWN, SAD_RT, SKEPTIC, FOCUSED, SQUINT, FRUSTRATED, ANNOYED, ANGRY, FURIOUS, 
  SLEEPY, SUSPICIOUS, UNIMPRESSED, SURPRISED, AWE, BLINK_LOW, BLINK_HIGH,
  
  // New 28 Cozmo Expressions
  COMPASSIONATE, PLAYFUL, DATA_STREAM, CURIOUS, PROBLEM_SOLVING, SIDE_GLANCE, ADMIRATION,
  SYSTEM_ERROR, CONFUSED, HYPNOTIZED, MISCHIEVOUS, FLUSTERED, STUNNED, LOW_BATTERY_ICON,
  LOW_BATTERY_EYES, DETERMINED, ONE_EYEBROW, BARCODE_SCAN, FOCUSED_GOAL, NERVOUS, INTRIGUED,
  CALM, OPTIMIC, CONTENT, QUESTION, WINKING, POUTING, SYSTEM_IDLE
};

int totalEmotions = sizeof(allEmotions) / sizeof(allEmotions[0]);
int currentIndex = 0;
unsigned long lastChangeTime = 0;

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100); 
  roboEyes.setAutoblinker(true, 3, 2); // Random autoblinking every 3-5 seconds
}

void loop() {
  // Cycle to the next emotion every 4 seconds to test them all out
  if (millis() - lastChangeTime > 4000) {
    Mood currentMood = allEmotions[currentIndex];
    roboEyes.setMood(currentMood);
    
    // Print index so you know which one is playing on screen
    Serial.print("Playing Emotion ID: ");
    Serial.println(currentIndex);
    
    currentIndex++;
    if (currentIndex >= totalEmotions) {
      currentIndex = 0;
    }
    lastChangeTime = millis();
  }

  // Handle serial inputs 
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int selectedMood = input.toInt(); // allow typing '0' to '55' into serial
    if(selectedMood >= 0 && selectedMood < totalEmotions) {
      currentIndex = selectedMood;
      roboEyes.setMood((Mood)currentIndex);
      Serial.print("Manual Selection - Emotion ID: ");
      Serial.println(currentIndex);
      lastChangeTime = millis();
    }
  }

  roboEyes.update();
}
