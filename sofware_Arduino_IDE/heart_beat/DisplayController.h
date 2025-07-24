#pragma once
#include <SSD1306Wire.h>

class DisplayController {
public:
    void begin();
    void update();
    void updateBPM(int bpm);
    void selectDisplayMode(int mode);
    int displayMode();
    void resetPulseAnimation();

private:
    SSD1306Wire display = SSD1306Wire(0x3C, D2, D1, GEOMETRY_64_48);  // ← Größe explizit gesetzt!

    int currentBPM = 0;
    int displayM = 0;
    int pulseAnimationState = 0;
    unsigned long lastPulseUpdate = 0;
};