#pragma once

#include <common/shape_demo_utils.h>

namespace shape_demo
{

/*!
 * \brief Интерфейс фабрики для создания фигур
 */
class AbstractShapeFactory
{

public:

    virtual ~AbstractShapeFactory() = default;

    /*!
     * \brief Создает новую фигуру
     * \param forIcon - если true, требуется эталонная фигура для иконки
     * \return
     */
    virtual Shape createShape(bool forIcon) = 0;

};

} // namespace shape_demo
