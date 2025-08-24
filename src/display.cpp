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

void Display::drawSpectrum(const float *fftBins, int nBins) {
    int specTop = 60;
    int specHeight = 150;
    int specWidth = tft.width();

    // effacer zone du spectrum
    tft.fillRect(0, specTop, specWidth, specHeight, ILI9341_BLACK);

    // tracer axe abscisses
    tft.drawLine(0, specTop+specHeight-1, specWidth, specTop+specHeight-1, ILI9341_WHITE);

    // dessiner la courbe fft
    for (int i = 0; i < nBins-1; i++) {
        int x1 = map(i, 0, nBins-1, 0, specWidth-1);
        int y1 = map(constrain(fftBins[i], -70, 0), -70, 0, specTop+specHeight-1, specTop);

        int x2 = map(i+1, 0, nBins-1, 0, specWidth-1);
        int y2 = map(constrain(fftBins[i+1], -70, 0), -70, 0, specTop+specHeight-1, specTop);

        tft.drawLine(x1, y1, x2, y2, ILI9341_GREEN);
    }
}

void Display::drawSpectrumMock() {
    const int N = 64; // nb de bandes fft simulées
    float mock[N];
    for (int i=0; i < N; i++) {
        mock[i] = random(-70, 0); // dB aléatoires
    }
    drawSpectrum(mock,N);
}