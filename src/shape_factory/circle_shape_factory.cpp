#define _USE_MATH_DEFINES

#include "circle_shape_factory.h"

#include <cmath>

namespace shape_demo
{

CircleShapeFactory::CircleShapeFactory() = default;
CircleShapeFactory::~CircleShapeFactory() = default;

Shape CircleShapeFactory::createShape(bool forIcon)
{
    Shape shape;

    // Если создаем не для иконки, то уменьшаем количество отрезков
    const auto createCircle = [](int count) -> std::vector<Point2D>
    {
        std::vector<Point2D> circle;
        circle.reserve(count);

        for (int i = 0; i < count; ++i)
        {
            const auto angle = i * 2.0 * M_PI / static_cast<double>(count);
            circle.push_back(Point2D{ static_cast<float>(std::cos(angle)), static_cast<float>(std::sin(angle)) });
        }

        return circle;
    };

    shape.contour = createCircle(forIcon ? 20 : 5 + rand() % 10);

    return shape;
}

} // namespace shape_demo
