#include <Arduino.h>
#include "config.h"
#include "SensorManager.h"
#include "DisplayController.h"

// Globale Instanzen
SensorManager sensor;
DisplayController display;

void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("start initialization...");

    // Initialisierung der Module
    sensor.begin();
    display.begin();

    Serial.println("System gestartet.");
}

void loop() {
    // Sensor prüfen
    sensor.update();                    // check if finger is present, update BPM if beat detected

    if (sensor.isBeatDetected()) {
        display.resetPulseAnimation();

        display.selectDisplayMode(1);   // beat deteced, but potentially not a full set of data

        if (sensor.fullSet()) {
            display.selectDisplayMode(2);  // beat detected, data set complete
            display.updateBPM(sensor.getBPM());    // transfer BPM to DisplayController

            Serial.print("BPM: ");
            Serial.println(sensor.getBPM());
        }
    }

    // Fingerprüfung → bei Verlust zurück zu Animation
    if (!sensor.isFingerPresent()) {
        display.selectDisplayMode(0);  // zurück zur Animation
        sensor.resetNoSamples();
    }

    if (sensor.isSignalLost()) {
        display.selectDisplayMode(0);  // Zurück zur Animation
        sensor.resetNoSamples();
    }

    // Display-Animation unabhängig weiterlaufen lassen
    display.update();

    // Zeitsteuerung (100 Hz)
    delay(10);
}