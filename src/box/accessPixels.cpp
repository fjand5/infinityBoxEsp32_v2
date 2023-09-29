#include "accessPixels.h"
FaceName stringToFaceName(String string)
{
  if (string == "FaceName_Top")
    return FaceName_Top;
  if (string == "FaceName_Bottom")
    return FaceName_Bottom;
  if (string == "FaceName_Left")
    return FaceName_Left;
  if (string == "FaceName_Right")
    return FaceName_Right;
  if (string == "FaceName_Front")
    return FaceName_Front;
  if (string == "FaceName_Back")
    return FaceName_Back;
};
SegmentName stringToSegmentName(String string)
{

  if (string == "SegmentName_Top_0")
  {
    return SegmentName_Top_0;
  }
  if (string == "SegmentName_Top_1")
  {
    return SegmentName_Top_1;
  }
  if (string == "SegmentName_Top_2")
  {
    return SegmentName_Top_2;
  }
  if (string == "SegmentName_Top_3")
  {
    return SegmentName_Top_3;
  }
  if (string == "SegmentName_Bottom_0")
  {
    return SegmentName_Bottom_0;
  }
  if (string == "SegmentName_Bottom_1")
  {
    return SegmentName_Bottom_1;
  }
  if (string == "SegmentName_Bottom_2")
  {
    return SegmentName_Bottom_2;
  }
  if (string == "SegmentName_Bottom_3")
  {
    return SegmentName_Bottom_3;
  }
  if (string == "SegmentName_Left_0")
  {
    return SegmentName_Left_0;
  }
  if (string == "SegmentName_Left_1")
  {
    return SegmentName_Left_1;
  }
  if (string == "SegmentName_Left_2")
  {
    return SegmentName_Left_2;
  }
  if (string == "SegmentName_Left_3")
  {
    return SegmentName_Left_3;
  }
  if (string == "SegmentName_Right_0")
  {
    return SegmentName_Right_0;
  }
  if (string == "SegmentName_Right_1")
  {
    return SegmentName_Right_1;
  }
  if (string == "SegmentName_Right_2")
  {
    return SegmentName_Right_2;
  }
  if (string == "SegmentName_Right_3")
  {
    return SegmentName_Right_3;
  }
  if (string == "SegmentName_Front_0")
  {
    return SegmentName_Front_0;
  }
  if (string == "SegmentName_Front_1")
  {
    return SegmentName_Front_1;
  }
  if (string == "SegmentName_Front_2")
  {
    return SegmentName_Front_2;
  }
  if (string == "SegmentName_Front_3")
  {
    return SegmentName_Front_3;
  }
  if (string == "SegmentName_Back_0")
  {
    return SegmentName_Back_0;
  }
  if (string == "SegmentName_Back_1")
  {
    return SegmentName_Back_1;
  }
  if (string == "SegmentName_Back_2")
  {
    return SegmentName_Back_2;
  }
  if (string == "SegmentName_Back_3")
  {
    return SegmentName_Back_3;
  }
};

AccessPixels::AccessPixels(/* args */)
{
}
void AccessPixels::setFaceData(FaceName faceName, FaceData faceData)
{
  switch (faceName)
  {
  case FaceName_Top:
    _faceData[0] = faceData;
    if (faceData.reverse)
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[0 + 4 - i - 1] = _faceData[0].position + i * LED_SEGMENT_COUNT;
      }
    else
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[0 + i] = _faceData[0].position + i * LED_SEGMENT_COUNT;
      }

    break;
  case FaceName_Bottom:
    _faceData[1] = faceData;
    if (faceData.reverse)
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[4 + 4 - i - 1] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    else
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[4 + i] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    break;
  case FaceName_Left:
    _faceData[2] = faceData;
    if (faceData.reverse)
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[8 + 4 - i - 1] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    else
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[8 + i] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    break;
  case FaceName_Right:
    _faceData[3] = faceData;
    if (faceData.reverse)
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[12 + 4 - i - 1] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    else
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[12 + i] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    break;
  case FaceName_Front:
    _faceData[4] = faceData;
    if (faceData.reverse)
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[16 + 4 - i - 1] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    else
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[16 + i] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    break;
  case FaceName_Back:
    _faceData[5] = faceData;
    if (faceData.reverse)
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[20 + 4 - i - 1] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    else
      for (uint16_t i = 0; i < 4; i++)
      {
        _segmentPosition[20 + i] = faceData.position + i * LED_SEGMENT_COUNT;
      }
    break;
  default:
    break;
  }
};
FaceData AccessPixels::getFaceData(FaceName faceName)
{
  switch (faceName)
  {
  case FaceName_Top:
    return _faceData[0];
    break;
  case FaceName_Bottom:
    return _faceData[1];
    break;
  case FaceName_Left:
    return _faceData[2];
    break;
  case FaceName_Right:
    return _faceData[3];
    break;
  case FaceName_Front:
    return _faceData[4];
    break;
  case FaceName_Back:
    return _faceData[5];
    break;

  default:
    break;
  }
};

void AccessPixels::setSegmentColors(SegmentName segmentName, ICRGB *colors)
{
  switch (segmentName)
  {
  case SegmentName_Top_0:
    if (_faceData[0].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[0], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[0], colors[i]);
      }
    break;
  case SegmentName_Top_1:
    if (_faceData[0].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[1], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[1], colors[i]);
      }
    break;
  case SegmentName_Top_2:
    if (_faceData[0].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[2], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[2], colors[i]);
      }
    break;
  case SegmentName_Top_3:
    if (_faceData[0].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[3], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[3], colors[i]);
      }
    break;
  case SegmentName_Bottom_0:
    if (_faceData[1].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[4], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[4], colors[i]);
      }
    break;
  case SegmentName_Bottom_1:
    if (_faceData[1].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[5], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[5], colors[i]);
      }
    break;
  case SegmentName_Bottom_2:
    if (_faceData[1].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[6], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[6], colors[i]);
      }
    break;
  case SegmentName_Bottom_3:
    if (_faceData[1].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[7], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[7], colors[i]);
      }
    break;
  case SegmentName_Left_0:
    if (_faceData[2].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[8], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[8], colors[i]);
      }
    break;
  case SegmentName_Left_1:
    if (_faceData[2].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[9], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[9], colors[i]);
      }
    break;
  case SegmentName_Left_2:

    if (_faceData[2].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[10], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[10], colors[i]);
      }
    break;
  case SegmentName_Left_3:

    if (_faceData[2].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[11], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[11], colors[i]);
      }
    break;
  case SegmentName_Right_0:

    if (_faceData[3].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[12], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[12], colors[i]);
      }
    break;
  case SegmentName_Right_1:

    if (_faceData[3].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[13], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[13], colors[i]);
      }
    break;
  case SegmentName_Right_2:

    if (_faceData[3].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[14], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[14], colors[i]);
      }
    break;
  case SegmentName_Right_3:

    if (_faceData[3].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[15], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[15], colors[i]);
      }
    break;
  case SegmentName_Front_0:

    if (_faceData[4].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[16], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[16], colors[i]);
      }
    break;
  case SegmentName_Front_1:
    if (_faceData[4].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[17], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[17], colors[i]);
      }
    break;
  case SegmentName_Front_2:
    if (_faceData[4].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[18], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[18], colors[i]);
      }
    break;
  case SegmentName_Front_3:
    if (_faceData[4].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[19], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[19], colors[i]);
      }
    break;
  case SegmentName_Back_0:
    if (_faceData[5].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[20], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[20], colors[i]);
      }
    break;
  case SegmentName_Back_1:
    if (_faceData[5].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[21], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[21], colors[i]);
      }
    break;
  case SegmentName_Back_2:
    if (_faceData[5].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[22], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[22], colors[i]);
      }
    break;
  case SegmentName_Back_3:
    if (_faceData[5].reverse)
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[23], colors[LED_SEGMENT_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        setColor(i + _segmentPosition[23], colors[i]);
      }
    break;

  default:
    break;
  }
};
uint16_t AccessPixels::getSegmentPosition(SegmentName segmentName)
{
  switch (segmentName)
  {
  case SegmentName_Top_0:
    return _segmentPosition[0];
    break;
  case SegmentName_Top_1:
    return _segmentPosition[1];

    break;
  case SegmentName_Top_2:
    return _segmentPosition[2];

    break;
  case SegmentName_Top_3:
    return _segmentPosition[3];

    break;
  case SegmentName_Bottom_0:
    return _segmentPosition[4];

    break;
  case SegmentName_Bottom_1:
    return _segmentPosition[5];

    break;
  case SegmentName_Bottom_2:
    return _segmentPosition[6];

    break;
  case SegmentName_Bottom_3:
    return _segmentPosition[7];

    break;
  case SegmentName_Left_0:
    return _segmentPosition[8];

    break;
  case SegmentName_Left_1:
    return _segmentPosition[9];

    break;
  case SegmentName_Left_2:
    return _segmentPosition[10];

    break;
  case SegmentName_Left_3:
    return _segmentPosition[11];

    break;
  case SegmentName_Right_0:
    return _segmentPosition[12];

    break;
  case SegmentName_Right_1:
    return _segmentPosition[13];

    break;
  case SegmentName_Right_2:
    return _segmentPosition[14];

    break;
  case SegmentName_Right_3:
    return _segmentPosition[15];

    break;
  case SegmentName_Front_0:
    return _segmentPosition[16];

    break;
  case SegmentName_Front_1:
    return _segmentPosition[17];

    break;
  case SegmentName_Front_2:
    return _segmentPosition[18];

    break;
  case SegmentName_Front_3:
    return _segmentPosition[19];

    break;
  case SegmentName_Back_0:
    return _segmentPosition[20];

    break;
  case SegmentName_Back_1:
    return _segmentPosition[21];

    break;
  case SegmentName_Back_2:
    return _segmentPosition[22];

    break;
  case SegmentName_Back_3:
    return _segmentPosition[23];

    break;

  default:
    break;
  }
};

void AccessPixels::setFaceColors(FaceName faceName, ICRGB *colors)
{
  switch (faceName)
  {
  case FaceName_Top:
    if (_faceData[0].reverse)
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[0].position, colors[LED_FACE_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[0].position, colors[i]);
      }
    break;
  case FaceName_Bottom:
    if (_faceData[1].reverse)
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[1].position, colors[LED_FACE_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[1].position, colors[i]);
      }
    break;
  case FaceName_Left:
    if (_faceData[2].reverse)
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[2].position, colors[LED_FACE_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[2].position, colors[i]);
      }
    break;
  case FaceName_Right:
    if (_faceData[3].reverse)
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[3].position, colors[LED_FACE_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[3].position, colors[i]);
      }
    break;
  case FaceName_Front:
    if (_faceData[4].reverse)
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[4].position, colors[LED_FACE_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[4].position, colors[i]);
      }
    break;
  case FaceName_Back:
    if (_faceData[5].reverse)
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[5].position, colors[LED_FACE_COUNT - 1 - i]);
      }
    else
      for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
      {
        setColor(i + _faceData[5].position, colors[i]);
      }
    break;

  default:
    break;
  }
};
void AccessPixels::setHalfFaceColors(FaceName faceName, ICRGB *colors)
{
  switch (faceName)
  {
  case FaceName_Top:
    if (_faceData[0].reverse)
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[0].position, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[0].position + LED_HALFFACE_COUNT, colors[i]);
      }
    }
    else
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[0].position, colors[i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[0].position + LED_HALFFACE_COUNT, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
    }
    break;
  case FaceName_Bottom:
    if (_faceData[1].reverse)
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[1].position, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[1].position + LED_HALFFACE_COUNT, colors[i]);
      }
    }
    else
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[1].position, colors[i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[1].position + LED_HALFFACE_COUNT, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
    }
    break;
  case FaceName_Left:
    if (_faceData[2].reverse)
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[2].position, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[2].position + LED_HALFFACE_COUNT, colors[i]);
      }
    }
    else
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[2].position, colors[i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[2].position + LED_HALFFACE_COUNT, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
    }
    break;
  case FaceName_Right:
    if (_faceData[3].reverse)
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[3].position, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[3].position + LED_HALFFACE_COUNT, colors[i]);
      }
    }
    else
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[3].position, colors[i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[3].position + LED_HALFFACE_COUNT, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
    }
    break;
  case FaceName_Front:
    if (_faceData[4].reverse)
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[4].position, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[4].position + LED_HALFFACE_COUNT, colors[i]);
      }
    }
    else
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[4].position, colors[i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[4].position + LED_HALFFACE_COUNT, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
    }
    break;
  case FaceName_Back:
    if (_faceData[5].reverse)
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[5].position, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[5].position + LED_HALFFACE_COUNT, colors[i]);
      }
    }
    else
    {
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[5].position, colors[i]);
      }
      for (uint16_t i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        setColor(i + _faceData[5].position + LED_HALFFACE_COUNT, colors[LED_HALFFACE_COUNT - 1 - i]);
      }
    }
    break;

  default:
    break;
  }
};
void AccessPixels::setColor(int16_t index, ICRGB color)
{
  ICRGB *lastColor = getPixels() + index;
  *lastColor = (*lastColor) + color;
  lastColor->i = color.i;
};

AccessPixels::~AccessPixels()
{
}
