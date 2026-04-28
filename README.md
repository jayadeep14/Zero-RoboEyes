# Zero RoboEyes (v1)

![RoboEyes Banner](https://img.shields.io/badge/Arduino-Library-blue.svg) 
![Version](https://img.shields.io/badge/version-1.3-green.svg)

**Zero RoboEyes** is a high-performance Arduino library for drawing smoothly animated robot eyes on OLED displays (SSD1306, SH1106, SSD1322, etc.). Using fractional easing for transitions, it breathes life into DIY robots by simulating organic movement and complex facial expressions.

## 🚀 New in v1
- **56 Distinct Emotions:** Expanded from 4 basic moods to 56, including "Cozmo-style" expressions.
- **Specialized Shape Engine:** Native rendering for complex glyphs like `HYPNOTIZED` spirals, `BARCODE_SCAN` lines, and `SYSTEM_ERROR` glitches.
- **Dynamic Eyelid Clipping:** Advanced math-based clipping for `Angry`, `Sad`, `Tired`, and `Happy` overlays.
- **Forehead Sweat:** Built-in animated sweat droplet physics for stressed or overworked states.

---
<div align="center">
  <img width="600" height="728" alt="image" src="https://github.com/user-attachments/assets/f3c04a50-61c1-48e3-8ff4-02d15b68ce3b" />
</div>

---
## 🛠 Installation

1. Open the **Arduino IDE**.
2. Navigate to **Sketch** → **Include Library** → **Manage Libraries…**
3. Search for **"Zero RoboEyes"**.
4. Click **Install**.

---

## 📖 API Reference

### 1. General & Setup
| Function | Description |
| :--- | :--- |
| `begin(w, h, fps)` | Initializes screen dimensions and sets the maximum refresh rate. |
| `update()` | **Crucial:** Call this in your `loop()`. Handles easing and frame updates. |
| `drawEyes()` | Forces an immediate redraw bypassing the framerate limiter. |
| `setDisplayColors(bg, main)` | Sets 0/1 for monochrome or 0x00/0x0F for grayscale displays. |

### 2. Face Expressions & Geometry
| Function | Description |
| :--- | :--- |
| `setMood(Mood)` | Switches between the 56 predefined moods (see table below). |
| `setPosition(Pos)` | Cardinal directions: `N`, `NE`, `E`, `SE`, `S`, `SW`, `W`, `NW`, `DEFAULT`. |
| `setSweat(bool)` | Toggles animated sweat drops on the upper screen area. |
| `setCuriosity(bool)` | When ON, eye height increases during extreme side-looks. |
| `setCyclops(bool)` | Toggles single-eye (Cyclops) mode. |

### 3. Macro Animations
| Function | Description |
| :--- | :--- |
| `setAutoblinker(on, int, var)` | Handles random blinking logic automatically. |
| `setIdleMode(on, int, var)` | Makes the robot look around randomly to simulate "life." |
| `anim_confused()` | One-shot animation: eyes shake left/right. |
| `anim_laugh()` | One-shot animation: eyes shake up/down. |

---

## 🎭 The 56 Moods List

| Category | Moods |
| :--- | :--- |
| **Directional** | `NEUTRAL`, `NORMAL_LF`, `EXTREME_LF`, `NORMAL_RT`, `EXTREME_RT`, `SIDE_GLANCE` |
| **Positive** | `HAPPY`, `GLEE`, `ADMIRATION`, `CONTENT`, `OPTIMIC`, `PLAYFUL`, `WINKING`, `COMPASSIONATE` |
| **Negative** | `ANGRY`, `FURIOUS`, `FRUSTRATED`, `ANNOYED`, `SAD_DOWN`, `WORRIED`, `POUTING` |
| **Status/Tech** | `SYSTEM_ERROR`, `LOW_BATTERY_ICON`, `DATA_STREAM`, `BARCODE_SCAN`, `SYSTEM_IDLE` |
| **Mental State** | `CONFUSED`, `STUNNED`, `HYPNOTIZED`, `FOCUSED_GOAL`, `INTRIGUED`, `SKEPTIC`, `NERVOUS` |

---

<img width="487" height="357" alt="image" src="https://github.com/user-attachments/assets/2610d075-f434-435d-921a-a4209b2b1707" />

| OLED Pin | ESP32-C3 Pin | Wire Color |
| :--- | :--- | :--- |
| **GND** | GND | Black |
| **VCC** | 3V3 | Red |
| **SCL** | GPIO 9 | Green |
| **SDA** | GPIO 8 | Green |

---

## 💻 Example Code

```cpp
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
