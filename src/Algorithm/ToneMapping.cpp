#include "ToneMapping.h"
#include "Math/MathUtils.h"
float ACES_TONEMapping(float value)
{
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    value = (value * (a * value + b)) / (value * (c * value + d) + e);
    return Clamp(value, 0.0f, 1.0f);
}