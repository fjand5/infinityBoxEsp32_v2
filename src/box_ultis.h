#ifndef BOX_ULTIS
#define BOX_ULTIS

#include <stdlib.h>
#include <string>
inline std::string toString(long val)
{
    char num[16];
    itoa(val, num, 10);
    return std::string(num);
}
#endif