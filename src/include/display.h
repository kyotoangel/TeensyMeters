#ifndef DISPLAY_H
#define DISPLAY_H

#include <ILI9341_t3n.h>
#include <SPI.h>

// pins de la teensy reliés à l'écran

#define TFT_CS   10   // Chip Select TFT
#define TFT_DC    3   // Data/Command
#define TFT_RST   2   // Reset

// déclaration de la classe pour gérer l'écran

class Display {
    public : 
        void begin(); // déclaration de la fonction d'initialisation
        void drawLUFSmeter(float LufsI, float LufsS, float LufsM);
        // LufsI = LUFS intégrés / LufsS = LUFS short-term / LufsM = LUFS momentary
        void drawSpectrum(const float *fftBins, int nBins, float sampleRate);
        void drawSpectrumMock(); // mock = a des fins de tests, valeurs aléatoires.
        void drawSpectrumLines(float sampleRate); // dessin des lignes verticales et horizontales (dB / Hz)
        void drawThickLine(int x0, int y0, int x1, int y1, uint16_t color, int thickness);
    private :
        ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST);
        int specX = 0; // position courante en x pour le spectrogramme

        // variables pour drawSpectrum et drawSpectrumLines
        int specTop;
        int specHeight;
        int specWidth;
};

#endif