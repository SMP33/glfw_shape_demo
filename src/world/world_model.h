#pragma once

#include <common/shape_demo_utils.h>

#include <map>
#include <memory>

namespace shape_demo
{

class AbstractShapeFactory;

/*!
 * \brief Модель, содержащая информацию о фигурах и их положении.
 * Представляет собой квадратное поле size x size
 */
class WorldModel
{

public:

    WorldModel();
    ~WorldModel();

    WorldModel(const WorldModel &) = delete;
    WorldModel(WorldModel &&) = delete;
    WorldModel& operator=(const WorldModel&) = delete;
    WorldModel& operator=(WorldModel&&) = delete;

    /*!
     * \brief Размер поля
     */
    float size() const;

    /*!
     * \brief Добавляет фабрику в список доступных
     */
    void addFactory(std::shared_ptr<AbstractShapeFactory> pFactory);

    /*!
     * \brief Список доступных фабрик
     */
    const std::vector<std::shared_ptr<AbstractShapeFactory>>& availableFactories() const;

    /*!
     * \brief Добавляет фигуру и устанавливает ей произвольные положение, масштаб и цвет
     */
    void addShape(Shape&& shape);

    /*!
     * \brief Удаление всех фигур
     */
    void clear();

    /*!
     * \brief Мап фигур по порядку добавления
     */
    const std::map<size_t, Shape>& shapes() const;

private:

    class PrivateData;
    std::unique_ptr<PrivateData> m_pData;

};

} // namespace shape_demo
