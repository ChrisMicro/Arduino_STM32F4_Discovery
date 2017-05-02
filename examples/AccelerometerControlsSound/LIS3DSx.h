#include <stdint.h>

class LIS3DSx
{
  public:
    void begin();
    uint8_t getChipVersion();
    int16_t getX();
    int16_t getY();
    int16_t getZ();
    float getX_g();
    float getY_g();
    float getZ_g();
    float absolute_g();
};

