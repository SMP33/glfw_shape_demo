#define _USE_MATH_DEFINES

#include "world/rotated_world_view.h"

#include <cmath>

namespace shape_demo
{

RotatedWorldView::RotatedWorldView() = default;
RotatedWorldView::~RotatedWorldView() = default;

Point2D RotatedWorldView::mapWorldToScreen(Point2D point) const
{
    Point2D rotatedPoint;

    const auto s = std::sin(-M_PI_4);
    const auto c = std::cos(-M_PI_4);

    rotatedPoint.x = static_cast<float>(point.x * c - point.y * s);
    rotatedPoint.y = static_cast<float>(point.x * s + point.y * c);

    return WorldView::mapWorldToScreen(rotatedPoint);
}



} // namespace shape_demo
