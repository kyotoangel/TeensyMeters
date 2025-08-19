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
        void testScreen(); // déclaration de la fonction d'exemple pour afficher un message de test
    private :
        ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST);
};

#endif