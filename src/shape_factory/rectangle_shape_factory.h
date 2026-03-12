#pragma once

#include <shape_factory/abstract_shape_factory.h>

#include <memory>

namespace shape_demo
{

class RectangleShapeFactory final : public AbstractShapeFactory
{

public:

    explicit RectangleShapeFactory(float aspectRatio);
    ~RectangleShapeFactory() override;

    Shape createShape(bool forIcon) override;

private:

    class PrivateData;
    std::unique_ptr<PrivateData> m_pData;

};

} // namespace shape_demo
