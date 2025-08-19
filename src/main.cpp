#include <Arduino.h>
#include <display.cpp>

// création d'un objet global display
Display display;

void setup() {
  Serial.begin(9600);

  //appel de la fonction d'initialisation du display

  display.begin();

}

void loop() {
  //test: afficher rectangle rouge
  display.testScreen();
  delay(2000);
}