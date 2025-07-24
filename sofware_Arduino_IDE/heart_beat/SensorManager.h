#pragma once

#include <Wire.h>
#include <MAX30105.h>
#include "heartRate.h"

class SensorManager {
public:
    void begin();
    void update();                  // check, if finger is present. If beat detected, update beatsPerMinute und beatDetected
    bool isBeatDetected();
    long getIR();
    float getBPM();
    bool isFingerPresent();
    bool isSignalLost();
    void resetNoSamples();
    bool fullSet();                 // returns true, if a full set of measurements has been acquired

private:
    MAX30105 sensor;
    long lastIR = 0;
    bool beatDetected = false;


    // Herzfrequenz-Analyse
    const static int RATE_SIZE = 5;
    byte rates[RATE_SIZE];
    byte rateSpot = 0;
    byte noSamples = 0;
    long lastBeat = 0;
    float beatsPerMinute = 0;
    float beatAvg = 0;
};