#include "world/world_model.h"
#include "world/world_view.h"
#include "world/rotated_world_view.h"
#include "shape_factory/triangle_shape_factory.h"
#include "shape_factory/rectangle_shape_factory.h"
#include "shape_factory/circle_shape_factory.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

int main(
    [[maybe_unused]] int argc,
    [[maybe_unused]] char* argv[]
)
{

    if (!glfwInit())
    {
        std::cerr << "Ошибка инициализации GLFW" << std::endl;
        return -1;
    }

    std::vector<std::unique_ptr<shape_demo::WorldView>> windows;
    windows.reserve(2);

    {
        const auto pWorldModel = std::make_shared<shape_demo::WorldModel>();
        pWorldModel->addFactory(std::make_shared<shape_demo::TriangleShapeFactory>());
        pWorldModel->addFactory(std::make_shared<shape_demo::RectangleShapeFactory>(1.0f));
        pWorldModel->addFactory(std::make_shared<shape_demo::RectangleShapeFactory>(0.5f));
        pWorldModel->addFactory(std::make_shared<shape_demo::CircleShapeFactory>());

        {
            auto pDirectWindow = std::make_unique<shape_demo::WorldView>();
            pDirectWindow->setWorldModel(pWorldModel);
            pDirectWindow->setWindowTitle("Прямой вид");
            windows.emplace_back(std::move(pDirectWindow));
        }

        {
            auto pRotatedWindow = std::make_unique<shape_demo::RotatedWorldView>();
            pRotatedWindow->setWorldModel(pWorldModel);
            pRotatedWindow->setWindowTitle("Вид с поворотом");
            windows.emplace_back(std::move(pRotatedWindow));
        }
    }

    // Цикл обработки событий
    while (true)
    {
        if (windows.empty())
        {
            break;
        }

        for (const auto& pUniqueWindow : windows)
        {
            pUniqueWindow->processWindowEvents();
        }

        // Удаление окон, для которых было запрошено закрытие
        windows.erase(
            std::remove_if(
                std::begin(windows),
                std::end(windows),
                [](const auto& pUniqueWindow)
                {
                    return pUniqueWindow->shouldClose();
                }
            ),
            std::end(windows)
        );

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
