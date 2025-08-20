#include <Arduino.h>
#include <include/display.h>

// création d'un objet global display
Display display;

void setup() {
  Serial.begin(9600);
  //appel de la fonction d'initialisation du display
  display.begin();
}

void loop() {
  // valeur simulées
  float LufsI = random(-70, 1); // intégré (I)
  float LufsS = random(-70, 1); // short-term (S)
  float LufsM = random(-70, 1); // momentary (M)

  display.drawLUFSmeter(LufsI, LufsS, LufsM);

  delay(50);
}