#include <Arduino.h>
#include <arduinoFFT.h>

const uint16_t samples = 256; //This value MUST ALWAYS be a power of 2
const double samplingFrequency = 5000;
const uint8_t amplitude = 100;

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[samples];
double vImag[samples];
double peakFrequency;

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency);

void setup() {
  Serial.begin(9600);
  sampling_period_us = round(1000000 * (1.0 / samplingFrequency));
}

void loop() {
  
  //SAMPLING
  for(int i=0; i<samples; i++) {
    microseconds = micros();    //Overflows after around 70 minutes!
    vReal[i] = analogRead(A0);
    vImag[i] = 0;
    while(micros() < (microseconds + sampling_period_us)){
    }
  }

  //FFT
  FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);	/* Weigh data */
  FFT.compute(FFTDirection::Forward); /* Compute FFT */
  FFT.complexToMagnitude(); /* Compute magnitudes */
  double peakFrequency = FFT.majorPeak(vReal, samples, samplingFrequency);

  Serial.println("Peak Frequency: ");
  Serial.println(peakFrequency);
  delay(2000);
}
