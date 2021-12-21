#pragma once
#include "Arduino.h"
#include "v_box.h"
#define BOX_THREAD(func,param)  xTaskCreatePinnedToCore(\
        func,      \
        "THREAD_LAYERS",    \
        4096,         \ 
        (void *)param, \
        2,              \
        NULL,           \
        BOX_CORE_CPU);  
#define SPLIT_SEGMENT_TYPE_VERTEX 0
#define SPLIT_SEGMENT_TYPE_FACE 1
uint32_t stringToColor(String val)
{
    // #ffaabb
    val.toLowerCase();
    if (!val.startsWith("#") || val.length() != 7)
        val = "#ff0000";
    uint32_t color;
    String redStr = val.substring(1, 3);
    String greenStr = val.substring(3, 5);
    String blueStr = val.substring(5);
    int redInt = strtol(redStr.c_str(), NULL, 16);
    int greenInt = strtol(greenStr.c_str(), NULL, 16);
    int blueInt = strtol(blueStr.c_str(), NULL, 16);
    color = ((uint32_t)redInt << 16) | ((uint32_t)greenInt << 8) | blueInt;
    return color;
}
void setLayerMode(VBox *layer, uint8_t mode)
{
    for (int i = 0; i < layer->getNumSegments(); i++)
    {
        layer->setMode(i, mode);
    }
}
void setLayerBrightness(VBox *layer, uint8_t brig)
{
    layer->setBrightness(brig);
}
void setLayerColor(VBox *layer, uint8_t index, uint32_t color)
{
    for (int i = 0; i < layer->getNumSegments(); i++)
    {
        layer->setColorByIndex(index, color);
    }
}
void splitSegment(VBox *layer, int type = SPLIT_SEGMENT_TYPE_VERTEX)
{
    int mode, color, speed;
    mode = layer->getMode();
    color = layer->getColor();
    speed = layer->getSpeed();
    if (type == SPLIT_SEGMENT_TYPE_VERTEX)
    {
        int tmp;
        uint8_t opt, index = 0;
        uint16_t offset = 0;
        tmp = getValue("seg_font_1", "15").toInt();
        opt = getValue("seg_font_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_top_4", "16").toInt();
        opt = getValue("seg_top_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_font_2", "14").toInt();
        opt = getValue("seg_font_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_left_2", "1").toInt();
        opt = getValue("seg_left_2_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_font_3", "13").toInt();
        opt = getValue("seg_font_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_bottom_3", "9").toInt();
        opt = getValue("seg_bottom_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_font_4", "12").toInt();
        opt = getValue("seg_font_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_right_1", "23").toInt();
        opt = getValue("seg_right_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_back_1", "4").toInt();
        opt = getValue("seg_back_1_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_left_4", "3").toInt();
        opt = getValue("seg_left_4_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_back_2", "5").toInt();
        opt = getValue("seg_back_2_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_top_2", "18").toInt();
        opt = getValue("seg_top_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_back_3", "6").toInt();
        opt = getValue("seg_back_3_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_right_3", "21").toInt();
        opt = getValue("seg_right_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_back_4", "7").toInt();
        opt = getValue("seg_back_4_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_bottom_1", "11").toInt();
        opt = getValue("seg_bottom_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_top_3", "17").toInt();
        opt = getValue("seg_top_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_left_3", "2").toInt();
        opt = getValue("seg_left_3_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_top_1", "19").toInt();
        opt = getValue("seg_top_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_right_4", "20").toInt();
        opt = getValue("seg_right_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_bottom_4", "8").toInt();
        opt = getValue("seg_bottom_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_left_1", "0").toInt();
        opt = getValue("seg_left_1_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = getValue("seg_bottom_2", "10").toInt();
        opt = getValue("seg_bottom_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = getValue("seg_right_2", "22").toInt();
        opt = getValue("seg_right_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
    }
}