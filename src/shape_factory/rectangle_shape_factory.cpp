#include "rectangle_shape_factory.h"

namespace shape_demo
{

class RectangleShapeFactory::PrivateData
{

public:

    float aspectRatio{};
    bool rotate{ true };

};

RectangleShapeFactory::RectangleShapeFactory(
    float aspectRatio
)
    : m_pData{ std::make_unique<PrivateData>() }
{
    m_pData->aspectRatio = aspectRatio;
}

RectangleShapeFactory::~RectangleShapeFactory() = default;

Shape RectangleShapeFactory::createShape(
    bool forIcon
)
{
    Shape shape;

    auto w =  1.0f;
    auto h = m_pData->aspectRatio;

    // Если создаем не для иконки, то поворачиваем каждый новый итем
    if (!forIcon)
    {
        m_pData->rotate = !m_pData->rotate;
        if (m_pData->rotate)
        {
            std::swap(w, h);
        }
    }

    shape.contour = std::vector<Point2D>{
        { -w, -h },
        { w, -h },
        { w, h },
        { -w, h }
    };

    return shape;
}

} // namespace shape_demo
