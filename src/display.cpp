#include <include/display.h>
#include <string>

void Display::begin() {
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(ILI9341_BLACK);
    // variables pour drawSpectrum et drawSpectrumLines
    specTop = 140;
    specHeight = 100;
    specWidth = tft.width()-5;
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

void Display::drawSpectrumLines(float sampleRate) {
    // variables specTop, specHeight et specWidth en header !

    // tracer la grille horizontale (niveaux dB)
    for (int dB = -60; dB <= 0; dB += 20) {
        int y = map(dB, -70, 0, specTop+specHeight-1, specTop);
        tft.drawLine(0, y, specWidth, y, ILI9341_DARKGREY);
        // tft.setCursor(2, y-7);
        // tft.setTextColor(ILI9341_DARKGREY);
        // tft.setTextSize(1);
        // tft.print(dB);
    }

    // tracer la grille verticale (fréquences log)
    int freqs[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000};

    for (int f : freqs) {
        float norm = log10(f) - log10(20);
        float denom = log10(sampleRate/2) - log10(20); // représente la plage totale des fréquences de 20Hz à Nyquist (en log)
        int x = (int)(norm / denom * specWidth); // normalise entre 0 et 1 la valeur de f et la multiplie par la largeur du spectre

        tft.drawLine(x, specTop, x, specTop+specHeight, ILI9341_DARKGREY);

        tft.setCursor(x+2, specTop+specHeight-10);
        tft.setTextColor(ILI9341_DARKGREY);
        tft.setTextSize(1);

        // if (f >= 1000) {
        //     tft.print(f/1000);
        //     tft.print("k");
        // } else {
        //     tft.print(f);
        // }
    }
}

// déclaration d'une nouvelle fonction permettant de dessiner des lignes plus épaisses

void Display::drawThickLine(int x0, int y0, int x1, int y1, uint16_t color, int thickness) {
    for (int i=0; i< thickness; i++) {
        tft.drawLine(x0, y0 + i, x1, y1 + i, color);
    }
}

void Display::drawSpectrum(const float *fftBins, int nBins, float sampleRate) {

    // variables specTop, specHeight et specWidth en haut !

    // effacer zone du spectrum
    tft.fillRect(0, specTop, specWidth, specHeight, ILI9341_BLACK);

    // tracer axe abscisses (inutile avec la grille)
    tft.drawLine(0, specTop+specHeight-1, specWidth, specTop+specHeight-1, ILI9341_WHITE);

    drawSpectrumLines(sampleRate);

    // dessiner la courbe fft
    for (int i = 0; i < nBins-1; i++) {
        float f1 = (i * sampleRate / 2.0) / nBins;  // frequency bin i
        float f2 = ((i+1) * sampleRate / 2.0) / nBins; // frequency bin i+1

        int x1 = (int)((log10(f1 / 20)) / log10(sampleRate / 40) * specWidth);
        int x2 = (int)((log10(f2 / 20)) / log10(sampleRate / 40) * specWidth);

        int y1 = map(constrain(fftBins[i], -70, 0), -70, 0, specTop+specHeight-1, specTop);
        int y2 = map(constrain(fftBins[i+1], -70, 0), -70, 0, specTop+specHeight-1, specTop);

        // couleur selon amplitude

        uint16_t color = ILI9341_GREEN;
        if (fftBins[i] > -30) color = ILI9341_YELLOW;
        if (fftBins[i] > -15) color = ILI9341_RED;


        // tracer remplissage (cpu-intensive)

        tft.fillTriangle(x1, specTop+specHeight-1, x2, specTop+specHeight-1, x1, y1, color);
        tft.fillTriangle(x2, specTop+specHeight-1, x1, y1, x2, y2, color);
        
        // tracer des lignes sans remplissage avec épaisseur ajustable

        // drawThickLine(x1, y1, x2, y2, color, 5);
    }
}

void Display::drawSpectrumMock() {
    const int N = 128; // nb de bandes fft simulées
    float mock[N];
    for (int i=0; i < N; i++) {
        mock[i] = random(-70, 0); // dB aléatoires
    }
    drawSpectrum(mock,N, 48000.0f);
}