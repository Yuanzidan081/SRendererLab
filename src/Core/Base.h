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
#endif // BASE_H