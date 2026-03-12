#include "triangle_shape_factory.h"

namespace shape_demo
{

TriangleShapeFactory::TriangleShapeFactory() = default;
TriangleShapeFactory::~TriangleShapeFactory() = default;

Shape TriangleShapeFactory::createShape(bool forIcon)
{
    Shape shape;

    // Если создаем не для иконки, то добавляем разброс для нового итема
    const auto getOffset = [](bool forIcon) -> float
    {
        return forIcon ? 0.0f : (static_cast<float>(std::rand()) / RAND_MAX - 0.5f) * 0.75;
    };

    shape.contour = std::vector<Point2D>{
        { 0.0f + getOffset(forIcon), 1.0f + getOffset(forIcon) },
        { -1.0f + getOffset(forIcon), -1.0f + getOffset(forIcon) },
        { 1.0f + getOffset(forIcon), -1.0f + getOffset(forIcon) }
    };

    return shape;
}

} // namespace shape_demo
