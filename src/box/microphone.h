#pragma once
#include "FreeRTOS.h"
#include "driver/i2s.h"
#include "arduinoFFT.h"
#include "web/web.h"
#include "pref/pref.h"
#define PREF_MICROPHONE_NAME "__microphone"

#define SAMPLES 128
#define BAND 16
#define SAMPLES_MAX_FREQ 16000
#define MAX_INTENSITY 2511122.00
class Microphone : private Pref
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
  double handleMicrophone(void (*onChangeMax)(void *param, double val, double freq), void *param);
  void setMicGain(double gain);
  double getMicGain();
  void setTakeBeat(double beat);
  double getTakeBeat();
  void begin();

  void setRoute();
  ~Microphone();
};
extern Microphone microphone;
