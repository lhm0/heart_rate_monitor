#include "SensorManager.h"
#include "config.h"

void SensorManager::begin() {
    Wire.begin();  // nutzt automatisch D1 (SCL) und D2 (SDA) beim D1 Mini
    Wire.setClock(400000);  // optional: 400kHz I2C für schnelleren Datentransfer

    if (!sensor.begin(Wire, I2C_SPEED_FAST)) {
        Serial.println("MAX30102 nicht gefunden.");
        while (1);
    }

    Serial.println("Sensor initialisiert. Warte auf Finger...");

    // Konfiguration wie im bewährten Beispiel
    sensor.setup();  // Default-Konfiguration (69 Samples/s)
    sensor.setPulseAmplitudeRed(0x0A);   // Red LED an (niedrig)
    sensor.setPulseAmplitudeGreen(0);    // Grün aus
    sensor.setPulseAmplitudeIR(0x0A);    // IR an (niedrig)

    beatDetected = false;
    lastBeat = 0;
    beatAvg = 0;
}

void SensorManager::update() {
    lastIR = sensor.getIR();  // 1 Sample pro Aufruf

    if (lastIR > 5000) {      // finger is present

        if (checkForBeat(lastIR)) {
        // Herzschlag erkannt
        long now = millis();
        long delta = now - lastBeat;
        lastBeat = now;

        beatsPerMinute = 60.0 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 20) {
            rates[rateSpot++] = (byte)beatsPerMinute;
            rateSpot %= RATE_SIZE;
            if (noSamples<RATE_SIZE) noSamples++;

            // Durchschnitt berechnen
            int sum = 0;
            for (byte i = 0; i < RATE_SIZE; i++) {
                sum += rates[i];
            }
            beatAvg = sum / RATE_SIZE;
        }

        beatDetected = true;
        }
    }
}

bool SensorManager::isBeatDetected() {
    if (beatDetected) {
        beatDetected = false;
        return true;
    }
    return false;
}

long SensorManager::getIR() {
    return lastIR;
}

float SensorManager::getBPM() {
    return beatAvg;
}

bool SensorManager::isFingerPresent() {
    return lastIR > 5000;
}

bool SensorManager::isSignalLost() {
    // Nur prüfen, wenn BPM bekannt
    if (beatsPerMinute < 30 || beatsPerMinute > 200) return false;

    long interval = 60.0 * 1000.0 / beatsPerMinute;
    long timeout = 1.5 * interval;

    return millis() - lastBeat > timeout;
}

bool SensorManager::fullSet() {
    return noSamples >= RATE_SIZE;
}

void SensorManager::resetNoSamples() {
    noSamples = 0;
}