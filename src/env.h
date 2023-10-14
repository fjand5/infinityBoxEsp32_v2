
#define LED_BUTTON_PIN 19
#define BUTTON_PIN 4
#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_8_BIT 8
#define LEDC_BASE_FREQ 5000
#define BUTTON_TICK_LOOP 50 //ms
#define BUTTON_LONG_LONG_CLICK_TIME 3500 //ms nhấn giữ trên 3s là kích hoạt longlongclick
#define BUTTON_LONG_CLICK_TIME 2000 //ms nhấn giữ trên 3s là kích hoạt longclick
#define BUTTON_CLICK_TIME 100 //ms nhấn giữ trên 0.1s là kích hoạt click

#define LED_PIN 23
#define LED_SEGMENT_COUNT 18 // Số lượng led trên mỗi đoạn
#define LED_HALF_SEGMENT_COUNT 9 // Số lượng led trên mỗi nửa đoạn
#define LED_FACE_COUNT 72    // Số lượng led trên mỗi mặt
#define LED_HALFFACE_COUNT LED_FACE_COUNT/2    // Số lượng led trên mỗi mặt
#define LED_FACES 6          // Số mặt của hộp
#define LED_SEGMENTS 24      // Số đoạn

#define LED_COUNT LED_SEGMENT_COUNT *LED_SEGMENTS