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
        60, 61, 62, 63, 64}

#define COLOR_COUNT 15
#define DEFINE_DEFAULT_COLOR(num)                \
    uint32_t listColors[COLOR_COUNT][num] = { \
        {0x0f2557, 0xee7879, 0xf3a51a},     \
        {0xff6700, 0x191970, 0xe0e722},     \
        {0x3e090d, 0xc75f5f, 0x89feff},     \
        {0x800000, 0xf3a51a, 0x8b4513},     \
        {0x191970, 0x800000, 0xfffafa},     \
        {0x8b008b, 0x7fff00, 0xff4500},     \
        {0x4b0082, 0x800000, 0xff69b4},     \
        {0x8b4513, 0xe0e722, 0x006400},     \
        {0xff00ff, 0x9932cc, 0xff00a0},     \
        {0xfe00fe, 0xdefe47, 0x00b3fe},     \
        {0x65dc98, 0x8d8980, 0x222035},     \
        {0xff2a6d, 0xd1f7ff, 0x05d9e8},     \
        {0xfff69f, 0xd0902f, 0xa15501},     \
        {0xb0acb0, 0x85ebd9, 0x2f404d},     \
        {0xff577d, 0xffccdc, 0x0a9cf5},     \
    }

#endif