#pragma once
#include "FreeRTOS.h"
#include "driver/i2s.h"
#include "arduinoFFT.h"

#define SAMPLES 128
#define BAND 16
#define SAMPLES_MAX_FREQ 16000
#define MAX_INTENSITY 2511122.00
class Microphone
{
private:
  double vReal[SAMPLES];
  double vImag[SAMPLES];
  double micGain = 50.0;
  double takeBeat = 50.0;

public:
  Microphone(/* args */);

  double mapf(double x, double in_min, double in_max, double out_min, double out_max);
  int32_t getMIC_RAW();
  double calcData();
  double handleMicrophone(void (*onChangeMax)(double val, double freq) = NULL);
  void setMicGain(double gain);
  double getMicGain();
  void setTakeBeat(double beat);
  double getTakeBeat();
  void begin();
  ~Microphone();
};
extern Microphone microphone;
