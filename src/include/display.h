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
        void drawSpectrogramMock(); // fonction Mock pour le test sans sampling
    private :
        ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST);
        int specX = 0; // position courante en x pour le spectrogramme
};

#endif