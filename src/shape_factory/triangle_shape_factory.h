#pragma once

#include <shape_factory/abstract_shape_factory.h>

namespace shape_demo
{

class TriangleShapeFactory final : public AbstractShapeFactory
{

public:

    TriangleShapeFactory();
    ~TriangleShapeFactory() override;

    Shape createShape(bool forIcon) override;

};

} // namespace shape_demo
