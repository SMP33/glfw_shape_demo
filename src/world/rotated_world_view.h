#pragma once

#include <world/world_view.h>

namespace shape_demo
{

/*!
 * \brief Окно для визуализации WorldModel с поворотом при отображении
 */
class RotatedWorldView final: public WorldView
{

public:

    RotatedWorldView();
    ~RotatedWorldView() override;

    Point2D mapWorldToScreen(Point2D point) const override;
};

} // namespace shape_demo
