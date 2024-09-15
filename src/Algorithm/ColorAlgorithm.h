#ifndef TONE_MAPPING_H
#define TONE_MAPPING_H
#include "Common.h"
#include "Math/MathGroup.h"
float ACES_TONEMapping(float value);
Vec3 GammaCorrection(const Vec3 &color);
float GammaCorrection(const float &color);
#endif // TONE_MAPPING_H