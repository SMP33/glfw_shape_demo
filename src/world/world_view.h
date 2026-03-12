#pragma once

#include <common/shape_demo_utils.h>

#include <memory>
#include <string>

struct GLFWwindow;

namespace shape_demo
{

class WorldModel;

/*!
 * \brief Окно для визуализации WorldModel
 */
class WorldView
{

public:

    WorldView();
    virtual ~WorldView();

    WorldView(const WorldView&) = delete;
    WorldView(WorldView&&) = delete;
    WorldView& operator=(const WorldView&) = delete;
    WorldView& operator=(WorldView&&) = delete;

    void processWindowEvents();

    bool shouldClose() const;

    void setWindowTitle(const std::string& title);

    void setWorldModel(std::shared_ptr<WorldModel> pWoldModel);
    std::shared_ptr<WorldModel> worldModel() const;

    /*!
     * \brief Преобразует мировые координаты в координаты окна
     */
    virtual Point2D mapWorldToScreen(Point2D point) const;

private:

    class PrivateData;
    std::unique_ptr<PrivateData> m_pData;

};

} // namespace shape_demo
