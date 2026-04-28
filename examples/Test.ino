#include <Adafruit_SSD1306.h>
#include <Zero_RoboEyes.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RoboEyes<Adafruit_SSD1306> roboEyes(display);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  // Start eyes at 128x32 resolution, 100 FPS
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
  
  // Enable "Life-like" behaviors
  roboEyes.setAutoblinker(true, 3, 2); // Blink every 3-5s
  roboEyes.setIdleMode(true, 4, 2);    // Look around every 4-6s
  
  roboEyes.setMood(HAPPY);
}

void loop() {
  // Always call update to process animations
  roboEyes.update();
}
