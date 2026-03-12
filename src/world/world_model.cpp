#include "world/world_model.h"

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <ctime>
#include <vector>

namespace shape_demo
{

namespace
{
namespace world_model_cpp
{

constexpr auto MAX_OFFSET{ 100.0f };

constexpr auto MAX_SCALE{ 25.0f };
constexpr auto MIN_SCALE{ 5.0f };

constexpr auto MAX_ITEM_COUNT{ 10 };

} // namespace world_model_cpp
} // namespace

class WorldModel::PrivateData
{

public:

    std::vector<std::shared_ptr<AbstractShapeFactory>> factories;

    size_t nextShapeId{ 1U };

    // Фигуры в порядке добавления
    std::map<size_t, Shape> shapes;

};

/*-----------------------------------------------------------------------------------*/

WorldModel::WorldModel()
    : m_pData(std::make_unique<PrivateData>())
{
    srand(time(0));
}

WorldModel::~WorldModel() = default;

float WorldModel::size() const
{
    return world_model_cpp::MAX_OFFSET;
}

void WorldModel::addFactory(
    std::shared_ptr<AbstractShapeFactory> pFactory
)
{
    m_pData->factories.emplace_back(std::move(pFactory));
}

const std::vector<std::shared_ptr<AbstractShapeFactory>>& WorldModel::availableFactories() const
{
    return m_pData->factories;
}

void WorldModel::addShape(
    Shape&& shape
)
{
    // При добавлении устанавливаем случайные параметры: положение, масштаб, цвет

    const auto getOffset = []
    {
        return world_model_cpp::MAX_OFFSET * static_cast<float>(std::rand()) / RAND_MAX - world_model_cpp::MAX_OFFSET * 0.5f;
    };

    shape.center.x = getOffset();
    shape.center.y = getOffset();

    const auto scale = world_model_cpp::MIN_SCALE + world_model_cpp::MAX_SCALE * static_cast<float>(std::rand()) / RAND_MAX;

    for (auto& point : shape.contour)
    {
        point.x *= scale;
        point.y *= scale;
    }

    shape.colorR = std::rand() % 255;
    shape.colorG = std::rand() % 255;
    shape.colorB = std::rand() % 255;

    m_pData->shapes.emplace(++m_pData->nextShapeId, std::move(shape));

    if (m_pData->shapes.size() > world_model_cpp::MAX_ITEM_COUNT)
    {
        m_pData->shapes.erase(m_pData->shapes.begin());
    }
}

void WorldModel::clear()
{
    m_pData->shapes.clear();
}

const std::map<size_t, Shape>& WorldModel::shapes() const
{
    return m_pData->shapes;
}

} // namespace shape_demo
