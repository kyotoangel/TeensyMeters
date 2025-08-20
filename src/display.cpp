#include <include/display.h>

void Display::begin() {
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("Display init ok !");
}

void Display::drawLUFSmeter(float LufsI, float LufsS, float LufsM) {
    LufsI = constrain(LufsI, -70, 0);
    LufsS = constrain(LufsS, -70, 0);
    LufsM = constrain(LufsM, -70, 0);

    auto drawBar = [&](int y, float value) {
        int xStart = 50; // position de début de la barre
        int width = 250; // largeur max
        int height = 30; // "hauteur" de la barre

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
        tft.fillRect(xStart+width+10, y, 60, height, ILI9341_BLACK);
        tft.setCursor(xStart+width+10, y+6);
        tft.setTextColor(color);
        tft.setTextSize(2);
        tft.print(value,1);
    };

    // dessiner chaque barre
    drawBar(40, LufsI);
    drawBar(100, LufsS);
    drawBar(160, LufsM);
}