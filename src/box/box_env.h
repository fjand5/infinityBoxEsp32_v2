#ifndef BOX_ENV
#define BOX_ENV
#define NUM_OF_LAYER 3
#define LED_COUNT (12 * 4 * 6)
// #define LED_COUNT 8*4*6
#define LED_NUM_OF_SEG 24
#define LED_COUNT_ONE_SEG LED_COUNT / LED_NUM_OF_SEG
#define LED_PIN 23
#define TRANSITION_TIME 1000
#define BOX_CORE_CPU 0

#define DEFINE_DEFAULT_SPEED                                  \
    uint16_t mapSpeedDefault[MODE_COUNT] = {                  \
        0, 555, 1111, 888, 888, 888, 888, 888, 333, 111,      \
        222, 11111, 111, 1111, 1111, 333, 555, 555, 777, 555, \
        666, 444, 444, 2222, 2222, 3333, 333, 333, 111, 333,  \
        444, 444, 444, 444, 222, 111, 333, 333, 333, 333,     \
        555, 777, 777, 777, 444, 444, 555, 555, 555, 111,     \
        555, 777, 777, 777, 777, 555, 777, 57, 58, 59,        \
        60, 61, 62, 63, 64};
#endif