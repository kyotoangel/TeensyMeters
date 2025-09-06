#include <include/sampler.h>

Sampler::Sampler() {
    patchCordFFT = new AudioConnection(i2s1, 0, fft1024, 0);
    patchCordRMS = new AudioConnection(i2s1, 0, rms1, 0);
}

void Sampler::begin() {
    AudioMemory(60); // nombre de blocs (1 bloc = 128 samples)

    sgtl5000_1.enable();
    sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000_1.volume(1); // volume max = 1

    fft1024.windowFunction(AudioWindowHanning1024); // lissage
}

bool Sampler::available() {
    return fft1024.available();
}

// Renvoie nBands bandes log (dans le style de l'eq eight)
void Sampler::getLogBands(float *bands, int nBands) {
    float nyquist = AUDIO_SAMPLE_RATE_EXACT / 2.0;
    float minFreq = 20.0;
    float maxFreq = nyquist;

    // calcul des bandes de fréquences
    for (int b = 0; b < nBands; b++) {
        // freq min et max de la bande b (logarithmique)
        float f1 = minFreq * pow(maxFreq/minFreq, (float)b / nBands);
        float f2 = minFreq * pow(maxFreq/minFreq, (float)(b+1) / nBands);

        int bin1 = (int)(f1 / nyquist * 512); // 512 bins (FFT1024)
        int bin2 = (int)(f2 / nyquist * 512);

        if (bin1 < 0) bin1 = 0;
        if (bin2 > 512) bin2 = 511;

        float sum = 0;
        float count = 0;

        for (int i = bin1; i <= bin2; i++){
            sum += fft1024.read(i);
            count++;
        }

        float val = (count > 0) ? sum / count : 0; // expression ternaire pour faire la moyenne
        // retourne 0 si count = 0 sinon retourne sum / count

        bands[b] = 20 * log10(val + 1e-6); // converti en dB
    }
}

bool Sampler::availableRMS(){
    return rms1.available();
}

float Sampler::getRMSdB() {
    float val = rms1.read();
    return 20*log10(val + 1e-6); // dBFS
}