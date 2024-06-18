#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H
#include "Core/Base.h"
#include "Math/Vec.h"

void DrawTriangleWithoutDepthInfo(Vec2i v1, Vec2i v2, Vec2i v3, const Vec4f &color, const void *buffer, const SRendererType &type = SRendererType::SFill);
void DrawTriangleWithoutDepthInfo(Vec3i v1, Vec3i v2, Vec3i v3, const Vec4f &color, const void *buffer, const SRendererType &type = SRendererType::SFill);
void DrawTriangleLineModeWithoutDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, const Vec4f &color, const void *buffer);
void DrawTriangleFillModeWithoutDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, const Vec4f &color, const void *buffer);

void DrawTriangleWithDepthInfo(Vec2i v1, Vec2i v2, Vec2i v3, Vec4f &color, const void *buffer, const SRendererType &type = SRendererType::SFill);
void DrawTriangleWithDepthInfo(Vec2f v1, Vec2f v2, Vec2f v3, Vec4f &color, const void *buffer, const SRendererType &type = SRendererType::SFill);
void DrawTriangleWithDepthInfo(Vec3i v1, Vec3i v2, Vec3i v3, Vec4f &color, const void *buffer, const SRendererType &type = SRendererType::SFill);
void DrawTriangleWithDepthInfo(Vec3f v1, Vec3f v2, Vec3f v3, Vec4f &color, const void *buffer, const SRendererType &type = SRendererType::SFill);
void DrawTriangleFillModeWithDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, Vec4f &color, const void *buffer); // 考虑了深度信息绘制三角形
void DrawTriangleFillModeWithDepthInfo(Vec3f &v1, Vec3f &v2, Vec3f &v3, Vec4f &color, const void *buffer); // 考虑了深度信息绘制三角形
#endif                                                                                                     // DRAWTRIANGLE_H