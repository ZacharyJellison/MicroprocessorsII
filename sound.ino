#include <Arduino.h>
#include <arduinoFFT.h>

#define SAMPLES 256             // Must be a power of 2
#define SAMPLING_FREQUENCY 10000 // Hz, must be less than 10000 due to ADC
#define THRESHOLD 512
#define SAMPLE_INTERVAL 100 // Interval between samples in microseconds

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];
double finalFrequency;

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

double calculateFrequency(double samples[], int numSamples) {
  int zeroCrossings = 0;

  int cross1 = 0;
  int cross2= 0;
  int waveLength = 0;

  for (int i = 1; i < numSamples; i++) {
    if ((samples[i] >= (THRESHOLD) && samples[i - 1] < (THRESHOLD)) || (samples[i] < (THRESHOLD) && samples[i - 1] >= (THRESHOLD))) {

      if(cross2 == 0 && cross1 != 0){
        cross2 = i;
        Serial.println(cross2);
      }      
      if(cross1 == 0){
        cross1 = i;
        Serial.println(cross1);
      }


      zeroCrossings++;
    }
  }

  waveLength = (cross2 - cross1) * (round(1000000 * (1.0 / SAMPLING_FREQUENCY))) * 2;

  double frequency = 1.0 / waveLength;
  return frequency;
}



void setup() {
  Serial.begin(9600);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {
  
  //SAMPLING
  for(int i=0; i<SAMPLES; i++) {
    microseconds = micros();    //Overflows after around 70 minutes!
    vReal[i] = analogRead(A0);
    vImag[i] = 0;
    while(micros() < (microseconds + sampling_period_us)){
    }
  }

  //FFT
  FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.complexToMagnitude(vReal, vImag, SAMPLES);
  double peak = FFT.majorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

  finalFrequency = calculateFrequency(vReal, SAMPLES);

  Serial.println(finalFrequency);
  delay(100);
}
