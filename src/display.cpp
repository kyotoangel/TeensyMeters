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

void Display::testScreen(){
    tft.fillRect(20, 50, 100, 40, ILI9341_RED);
}