#pragma once

#include <shape_factory/abstract_shape_factory.h>

namespace shape_demo
{

class CircleShapeFactory final : public AbstractShapeFactory
{

public:

    CircleShapeFactory();
    ~CircleShapeFactory() override;

    Shape createShape(bool forIcon) override;

};

} // namespace shape_demo
