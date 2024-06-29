#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H
#include "Core/Base.h"
#include "Math/Vec.h"
#include "Render/Texture2D.h"
void DrawTriangleWithoutDepthInfo(Vec3f *v, const Vec4f &color, const void *buffer, const SRendererType &type);
void DrawTriangleLineModeWithoutDepthInfo(Vec3f *v, const Vec4f &color, const void *buffer);
void DrawTriangleFillModeWithoutDepthInfo(Vec3f *v, const Vec4f &color, const void *buffer);

void DrawTriangleWithDepthInfo(Vec3f *v, Vec4f &color, const void *buffer, const SRendererType &type);
void DrawTriangleFillModeWithDepthInfo(Vec3f *v, Vec4f &color, const void *buffer); // 考虑了深度信息绘制三角形

void DrawTriangleFillModeWithDepthTexture(Vec3f *v, float intensity, Vec2f *texCoords, const Texture2D &texture, const void *buffer);
void DrawTriangleFillModeWithDepthTexture(Vec3f *v, float *intensity, Vec2f *texCoords, const Texture2D &texture, const void *buffer);

#endif // DRAWTRIANGLE_H