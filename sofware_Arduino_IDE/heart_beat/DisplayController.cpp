#include "DisplayController.h"
#include "config.h"
#include "heart.h"
#include "heart_s.h"

void DisplayController::begin() {
    display.init();
    display.flipScreenVertically();  // <- Dreht Display in richtige Ausrichtung
    display.clear();
    display.display();
}

void DisplayController::updateBPM(int bpm) {
    currentBPM = bpm;
}

void DisplayController::update() {
    pulseAnimationState++;
    if (pulseAnimationState > 100) pulseAnimationState = 0;

    display.clear();

    switch (displayM) {
        case 0:
            if (pulseAnimationState < 50) {
                display.drawXbm(5, 0, heart_width, heart_height, heart_bits); 
            }
            break;
        case 1:
            if (pulseAnimationState < 30) {
                display.drawXbm(5, 0, heart_width, heart_height, heart_bits); 
            }
            break;
        case 2:
            if (pulseAnimationState < 30) {
                display.drawXbm(24, 32, heart_s_width, heart_s_height, heart_s_bits);     
            } 

            display.setFont(ArialMT_Plain_10);
            String dispBPM = String(currentBPM)+" BPM";
            int pixelWidth = display.getStringWidth(dispBPM);
            int offset = (64-pixelWidth)/2;
            if (offset<0) offset=0;
            display.drawString(offset, 0, String(currentBPM)+" BPM");

            display.setFont(ArialMT_Plain_16);
            float frequ = currentBPM / 60.0;               // Umwandlung in Hz
            String frequStr = String(frequ, 3);            // Umwandlung in String mit 3 Nachkommastellen
            frequStr += " Hz";
            pixelWidth = display.getStringWidth(frequStr);
            offset = (64-pixelWidth)/2;
            if (offset<0) offset=0;
            display.drawString(offset, 12, frequStr);

            break;
    }

    display.display();
}

void DisplayController::selectDisplayMode(int mode) {
    displayM = mode;
}

int DisplayController::displayMode() {
    return displayM;
}

void DisplayController::resetPulseAnimation() {
    pulseAnimationState = 0;
}