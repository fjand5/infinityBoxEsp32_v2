#include "box/box_controler.h"
#include "voca_render/voca_render.h"

void setup_render_layer()
{
    if (box_status == NULL)
    {
        return;
    }

    xEventGroupWaitBits(box_status, FLAG_BOX_READY, pdFALSE, pdFALSE, portMAX_DELAY);

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        vocaRender.renderSwitch(tab_name, String("en_layer_") + i, F(R"({
    "name":"Chạy"
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("en_layer_", "");
                         li = key.toInt();
                         if (value == "true")
                             box_enable(li);
                         else
                             box_disable(li);
                     });
        vocaRender.renderButton(tab_name, String("save_layer_") + i, F(R"({
    "name":"Lưu",
    "newLine":true
  })"),
                     [](String key, String value)
                     {
                         vocaStore.updateStore();
                     });
        vocaRender.renderSlider(tab_name, String("brig_layer_") + i, F(R"({
    "name":"Độ sáng",
    "min":0,
    "max":255,
    "newLine":true
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("brig_layer_", "");
                         li = key.toInt();
                         box_setBrightness(li, value.toInt());
                     });
    };
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        String tmp;
        tmp = String("color0_layer_") + i;
        vocaRender.renderColorPicker(tab_name, String("color0_layer_") + i, F(R"({
    "name":"Màu 0"
  })"),
                          [](String key, String value)
                          {
                              int li;
                              key.replace("color0_layer_", "");
                              li = key.toInt();
                              box_setColor(li, 0, value);
                          });

        tmp = String("color1_layer_") + i;
        vocaRender.renderColorPicker(tab_name, String("color1_layer_") + i, F(R"({
    "name":"Màu 1"
  })"),
                          [](String key, String value)
                          {
                              int li;
                              key.replace("color1_layer_", "");
                              li = key.toInt();
                              box_setColor(li, 1, value);
                          });

        tmp = String("color2_layer_") + i;
        vocaRender.renderColorPicker(tab_name, String("color2_layer_") + i, F(R"({
    "name":"Màu 2",
    "newLine":true
  })"),
                          [](String key, String value)
                          {
                              int li;
                              key.replace("color2_layer_", "");
                              li = key.toInt();
                              box_setColor(li, 2, value);
                          });
    };
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        String tmp;
        tmp = String("mode_layer_") + i;
        vocaRender.renderButton(tab_name, String("mode_layer_") + i + "_prev", F(R"({
    "name":"Prev"
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("mode_layer_", "");
                         key.replace("_prev", "");
                         li = key.toInt();
                         box_prevMode(li);
                     });
        vocaRender.renderButton(tab_name, String("mode_layer_") + i + "_next", F(R"({
    "name":"Next",
    "newLine":true
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("mode_layer_", "");
                         key.replace("_next", "");
                         li = key.toInt();
                         box_nextMode(li);
                     });

        vocaRender.renderSelect(tab_name, String("mode_layer_") + i, F(R"({
    "name":"Hiệu ứng",
    "options":["Static","Blink","Breath","Color Wipe","Color Wipe Inverse","Color Wipe Reverse","Color Wipe Reverse Inverse","Color Wipe Random","Random Color","Single Dynamic","Multi Dynamic","Rainbow","Rainbow Cycle","Scan","Dual Scan","Fade","Theater Chase","Theater Chase Rainbow","Running Lights","Twinkle","Twinkle Random","Twinkle Fade","Twinkle Fade Random","Sparkle","Flash Sparkle","Hyper Sparkle","Strobe","Strobe Rainbow","Multi Strobe","Blink Rainbow","Chase White","Chase Color","Chase Random","Chase Rainbow","Chase Flash","Chase Flash Random","Chase Rainbow White","Chase Blackout","Chase Blackout Rainbow","Color Sweep Random","Running Color","Running Red Blue","Running Random","Larson Scanner","Comet","Fireworks","Fireworks Random","Merry Christmas","Fire Flicker","Fire Flicker soft","Fire Flicker intense","Circus Combustus","Halloween","Bicolor Chase","Tricolor Chase","TwinkleFOX","Rain","Custom 0","Custom 1","Custom 2","Custom 3","Custom 4","Custom 5","Custom 6","Custom 7"],
    "span":{
        "xs":24,
        "sm":24,
        "md":12,
        "xl":12
    },
    "newLine":true
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("mode_layer_", "");
                         li = key.toInt();
                         box_setMode(li, value);
                     });
    };
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        String tmp;
        tmp = String("speed_layer_") + i;
        vocaRender.renderInput(tab_name, String("speed_layer_") + i, F(R"({
    "name":"Tốc độ",
    "newLine":true
  })"),
                    [](String key, String value)
                    {
                        int li;
                        key.replace("speed_layer_", "");
                        li = key.toInt();
                        box_setSpeed(li, value.toInt());
                    });
    };
};