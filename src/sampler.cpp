#include <include/sampler.h>

Sampler::Sampler() {
    patchCord = new AudioConnection(i2s1, 0, fft1024, 0);
}

void Sampler::begin() {
    AudioMemory(12); // nombre de blocs (1 bloc = 128 samples)

    sgtl5000_1.enable();
    sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000_1.volume(0.5); // volume max = 1

    fft1024.windowFunction(AudioWindowHanning1024); // lissage
}

bool Sampler::available() {
    return fft1024.available();
}

// Renvoie nBands bandes log (dans le style de l'eq eight)
void Sampler::getLogBands(float *bands, int nBands) {
    
}