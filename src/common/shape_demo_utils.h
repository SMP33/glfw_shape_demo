#pragma once

#include <vector>

namespace shape_demo
{

/*!
 * \brief Вызывает функтор в деструкторе
 */
template <class Callable>
struct ScopeGuard
{
    ScopeGuard(
        Callable&& guard_
    )
        : guard{ std::move(guard_) }
    {
    }

    ~ScopeGuard()
    {
        guard();
    }

    Callable const guard;
};

/*!
 * \brief Точка на плоскости
 */
struct Point2D
{
    float x{ 0.0f };
    float y{ 0.0f };
};

/*!
 * \brief Фигура
 */
struct Shape
{
    Point2D center;

    /// Точки контура, заданные относительно центра
    std::vector<Point2D> contour;

    int colorR{ 0 };
    int colorG{ 0 };
    int colorB{ 0 };
};

} // namespace shape_demo
