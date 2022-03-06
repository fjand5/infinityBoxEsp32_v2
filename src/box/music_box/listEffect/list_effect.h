#include <WS2812FX.h>
void overflowBeginInit(WS2812FX *leds);
uint16_t overflowBeginHandler(WS2812FX *leds);
void overflowBeginOnBeat(WS2812FX *leds, double val, double freq);

void overflowMidInit(WS2812FX *leds);
void overflowMidOnBeat(WS2812FX *leds, double val, double freq);
uint16_t overflowMidHandler(WS2812FX *leds);

void starBeatInit(WS2812FX *leds);
void starBeatOnBeat(WS2812FX *leds, double val, double freq);
uint16_t starBeatHandler(WS2812FX *leds);



