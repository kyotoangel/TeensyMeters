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
        void drawLUFSmeter(float LufsI, float LufsS, float LufsM); // déclaration de la fonction de dessin des barres LUFS
        // LufsI = LUFS intégrés / LufsS = LUFS short-term / LufsM = LUFS momentary
    private :
        ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST);
};

#endif