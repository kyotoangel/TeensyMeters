// #include <Arduino.h>
#include <include/display.h>
#include <include/sampler.h>

// git pull origin main pour actualiser les fichiers :)

// création d'un objet global display
Display display;
Sampler sampler;

void setup() {
  Serial.begin(9600);
  //appel de la fonction d'initialisation du display
  display.begin();
  sampler.begin();
}

void loop() {
  // valeur simulées
  // float LufsI = random(-70, 1); // intégré (I)
  // float LufsS = random(-70, 1); // short-term (S)
  // float LufsM = random(-70, 1); // momentary (M)

  // display.drawLUFSmeter(LufsI, LufsS, LufsM);
  // if (sampler.available()) {
  //   const int nBands = 30; // nombre de bandes de fréquences
  //   float bands[nBands];
  //   sampler.getLogBands(bands, nBands);
  //   display.drawSpectrum(bands, nBands, AUDIO_SAMPLE_RATE_EXACT);
  // }

  if (sampler.availableRMS()) {
    float rms = sampler.getRMSdB();
    display.drawVUMeter(rms);
  }
  delay(32);
}