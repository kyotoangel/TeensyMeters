#include <Arduino.h>
#include <include/display.h>

// git pull origin main pour actualiser les fichiers :)

// création d'un objet global display
Display display;

void setup() {
  Serial.begin(9600);
  //appel de la fonction d'initialisation du display
  display.begin();
  display.drawSpectrumLines(48000.0f);
}

void loop() {
  // valeur simulées
  float LufsI = random(-70, 1); // intégré (I)
  float LufsS = random(-70, 1); // short-term (S)
  float LufsM = random(-70, 1); // momentary (M)

  display.drawLUFSmeter(LufsI, LufsS, LufsM);

  display.drawSpectrumMock();

  delay(500);
}