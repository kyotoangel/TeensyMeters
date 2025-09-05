#ifndef SAMPLER_H
#define SAMPLER_H

#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>

class Sampler {
    public :
    Sampler();
    void begin();
    bool available();
    void getLogBands(float *bands, int nBands);

    private :
    AudioInputI2S           i2s1;
    AudioAnalyzeFFT1024     fft1024;
    AudioConnection*        patchCord;
    AudioControlSGTL5000    sgtl5000_1;
};
#endif