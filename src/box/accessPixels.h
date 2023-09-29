#include <Arduino.h>
#include "env.h"
#include "pixel.h"
#define SET_ALL_FACE_COLORS(colors)       \
  setFaceColors(FaceName_Top, colors);    \
  setFaceColors(FaceName_Bottom, colors); \
  setFaceColors(FaceName_Left, colors);   \
  setFaceColors(FaceName_Right, colors);  \
  setFaceColors(FaceName_Front, colors);  \
  setFaceColors(FaceName_Back, colors);
#define SET_ALL_HALFFACE_COLORS(colors)       \
  setHalfFaceColors(FaceName_Top, colors);    \
  setHalfFaceColors(FaceName_Bottom, colors); \
  setHalfFaceColors(FaceName_Left, colors);   \
  setHalfFaceColors(FaceName_Right, colors);  \
  setHalfFaceColors(FaceName_Front, colors);  \
  setHalfFaceColors(FaceName_Back, colors);
#define SET_ALL_SEGMENT_COLORS(colors)\
  setSegmentColors(SegmentName_Top_0,colors);\
  setSegmentColors(SegmentName_Top_1,colors);\
  setSegmentColors(SegmentName_Top_2,colors);\
  setSegmentColors(SegmentName_Top_3,colors);\
  setSegmentColors(SegmentName_Bottom_0,colors);\
  setSegmentColors(SegmentName_Bottom_1,colors);\
  setSegmentColors(SegmentName_Bottom_2,colors);\
  setSegmentColors(SegmentName_Bottom_3,colors);\
  setSegmentColors(SegmentName_Left_0,colors);\
  setSegmentColors(SegmentName_Left_1,colors);\
  setSegmentColors(SegmentName_Left_2,colors);\
  setSegmentColors(SegmentName_Left_3,colors);\
  setSegmentColors(SegmentName_Right_0,colors);\
  setSegmentColors(SegmentName_Right_1,colors);\
  setSegmentColors(SegmentName_Right_2,colors);\
  setSegmentColors(SegmentName_Right_3,colors);\
  setSegmentColors(SegmentName_Front_0,colors);\
  setSegmentColors(SegmentName_Front_1,colors);\
  setSegmentColors(SegmentName_Front_2,colors);\
  setSegmentColors(SegmentName_Front_3,colors);\
  setSegmentColors(SegmentName_Back_0,colors);\
  setSegmentColors(SegmentName_Back_1,colors);\
  setSegmentColors(SegmentName_Back_2,colors);\
  setSegmentColors(SegmentName_Back_3,colors);
typedef enum
{
  FaceName_Top,
  FaceName_Bottom,
  FaceName_Left,
  FaceName_Right,
  FaceName_Front,
  FaceName_Back,
} FaceName;
FaceName stringToFaceName(String string);
typedef struct
{
  uint16_t position;
  bool reverse;
} FaceData;
typedef enum
{
  SegmentName_Top_0,
  SegmentName_Top_1,
  SegmentName_Top_2,
  SegmentName_Top_3,
  SegmentName_Bottom_0,
  SegmentName_Bottom_1,
  SegmentName_Bottom_2,
  SegmentName_Bottom_3,
  SegmentName_Left_0,
  SegmentName_Left_1,
  SegmentName_Left_2,
  SegmentName_Left_3,
  SegmentName_Right_0,
  SegmentName_Right_1,
  SegmentName_Right_2,
  SegmentName_Right_3,
  SegmentName_Front_0,
  SegmentName_Front_1,
  SegmentName_Front_2,
  SegmentName_Front_3,
  SegmentName_Back_0,
  SegmentName_Back_1,
  SegmentName_Back_2,
  SegmentName_Back_3,
} SegmentName;
SegmentName stringToSegmentName(String string);

class AccessPixels
{
private:
  /*
  Vị trí bắt đầu của 6 mặt,
  thứ tự là trên, dưới, trái, phải, trước, sau.
  */
  FaceData _faceData[6];

  /*
  Vị trí bắt đầu của 24 đoạn led, thứ tự là:
  trên, dưới, trái, phải, trước, sau.
  Mỗi 4 đoạn được sếp theo thứ tự ngược chiều kim đồng hồ trên mỗi mặt.
 */
  uint16_t _segmentPosition[24];

public:
  AccessPixels(/* args */);
  ~AccessPixels();
  void setFaceColors(FaceName faceName, ICRGB *colors);
  void setHalfFaceColors(FaceName faceName, ICRGB *colors);
  void setFaceData(FaceName faceName, FaceData faceData);
  FaceData getFaceData(FaceName faceName);

  void setSegmentColors(SegmentName segmentName, ICRGB *colors);
  uint16_t getSegmentPosition(SegmentName segmentName);

  void setColor(int16_t index, ICRGB color);

  // SegmentPosition được suy ra từ Face nên không cần thiết.
  // void setSegmentPosition(SegmentName segmentName, uint16_t position);
  virtual ICRGB *getPixels() = 0;
};
