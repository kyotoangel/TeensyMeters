#include <include/display.h>
#include <string>

void Display::begin() {
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
}

void Display::drawLUFSmeter(float LufsI, float LufsS, float LufsM) {
    LufsI = constrain(LufsI, -70, 0);
    LufsS = constrain(LufsS, -70, 0);
    LufsM = constrain(LufsM, -70, 0);

    auto drawBar = [&](int y, float value, std::string meterName) {
        int xStart = 30; // position de début de la barre
        int width = 200; // largeur max
        int height = 10; // "hauteur" de la barre

        // calcul du remplissage de la barre en pixels
        int filled = map(value, -70, 0, 0, width);

        // couleur selon valeur
        uint16_t color = ILI9341_GREEN;
        if (value > -23) color = ILI9341_ORANGE;
        if (value > -14) color = ILI9341_RED;

        // effacer zone
        tft.fillRect(xStart, y, width, height, ILI9341_BLACK);

        // dessiner barre remplie
        tft.fillRect(xStart, y, filled, height, color);

        // afficher valeur numérique

        int xText = xStart + width - 70;

        //tft.fillRect(xText, y, 70, height, ILI9341_BLACK);
        tft.setCursor(xText, y+6);
        tft.setTextColor(color, ILI9341_BLACK);
        tft.setTextSize(2);
        tft.print(value,1);

        // afficher le type de meter

        tft.setCursor(xStart - 25, y);
        tft.setTextColor(ILI9341_CYAN);
        tft.setTextSize(2);
        tft.print(meterName.c_str());
    };

    // dessiner chaque barre
    drawBar(0, LufsI, "I");
    drawBar(35, LufsS, "S");
    drawBar(70, LufsM, "M");
}

void Display::drawSpectrogramMock() {
    int specTop = 120;  // zone spectrogramme (bas de l'écran)
    int specHeight = 120; // moitié de l'écran

    if (specX >= tft.width()) {
        specX = 0;
        tft.fillRect(0, specTop, tft.width(), specHeight, ILI9341_BLACK);
    }

    for (int f = 0; f < 50; f++) {
        int dB = random(-70, 0);
        int y = map(dB, -70, 0, specTop+specHeight-1, specTop);

        // couleur selon amplitude
        uint16_t color = tft.color565(255 + dB*3, max(0, 100+dB*2), 0);

        tft.drawPixel(specX, y, color);
    }

    specX++;
}