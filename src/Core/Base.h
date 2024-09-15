#ifndef BASE_H
#define BASE_H
#include <memory>

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> MakeRef(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Scope<T> MakeScope(Args &&...args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
T Max(T a, T b)
{
    return (a > b) ? a : b;
}

template <typename T, typename... Args>
T Max(T first, Args... args)
{
    return Max(first, Max(args...));
}

template <typename T>
T Min(T a, T b)
{
    return (a < b) ? a : b;
}

template <typename T, typename... Args>
T Min(T first, Args... args)
{
    return Min(first, Min(args...));
}
enum PolygonMode
{
    Wire = 0,
    Fill
};

enum FaceCullMode
{
    BackFaceCull,
    FrontFaceCull
};

enum ShadingMode
{
    ForwardMode,
    DeferredMode
};

enum PipelineMode
{
    AllForwardMode,
    MixDeferredModeAndForwardMode
};

enum FrameBufferMode
{
    NormalBuffer,
    GBuffer
};
#define EPSILON 1e-5f
const int screenWidth = 500;
const int screenHeight = 500;

#endif // BASE_H