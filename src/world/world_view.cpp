#include "world/world_view.h"

#include "shape_factory/abstract_shape_factory.h"
#include "world/world_model.h"

#include <GLFW/glfw3.h>

#include <unordered_map>

namespace shape_demo
{

namespace
{
namespace world_view_cpp
{

constexpr int GL_VERSION_MAJOR{ 3 };
constexpr int GL_VERSION_MINOR{ 3 };

constexpr int WINDOW_WIDTH{ 600U };
constexpr int WINDOW_HEIGHT{ 600U };

constexpr float ICON_SCALE{ 0.05 };

std::unordered_map<GLFWwindow*, WorldView*> DescriptorToWindowMap = {};

} // namespace world_view_cpp
} // namespace

class WorldView::PrivateData
{

public:

    // Кнопка для создания фигуры
    struct Button
    {
        Shape shape;
        float xMin{ 0.0 };
        float xMax{ 0.0 };
    };

public:

    explicit PrivateData(
        WorldView* pOwner_
    );

    // Вызывается при запросе на закрытие
    static void OnCloseRequest(GLFWwindow* pWindowDescriptor);

    // Вызывается при ресайзе
    static void OnResize(GLFWwindow* pWindowDescriptor, int width, int height);

    // Отрисовка фигур
    void drawWorld() const;

    // Отрисовка кнопок
    void drawButtons();

    // Обработка пользовательского ввода
    void processUserInput();

public:

    WorldView* const pOwner;

    GLFWwindow* pWindowDescriptor{ nullptr };

    std::shared_ptr<WorldModel> pWorldModel;

    bool shouldClose{ false };

    bool leftMousePressed{ false };

    std::vector<Button> buttons;
    int currentButtonId{ -1 };
};

WorldView::PrivateData::PrivateData(
    WorldView* pOwner_
)
    : pOwner{ pOwner_ }
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, world_view_cpp::GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, world_view_cpp::GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    pWindowDescriptor = glfwCreateWindow(
        world_view_cpp::WINDOW_WIDTH,
        world_view_cpp::WINDOW_HEIGHT,
        "",
        nullptr,
        nullptr
    );

    world_view_cpp::DescriptorToWindowMap.emplace(pWindowDescriptor, pOwner);

    glfwMakeContextCurrent(pWindowDescriptor);

    glfwSetWindowCloseCallback(pWindowDescriptor, &PrivateData::OnCloseRequest);
    glfwSetFramebufferSizeCallback(pWindowDescriptor, &PrivateData::OnResize);
}

void WorldView::PrivateData::OnCloseRequest(
    GLFWwindow* pWindowDescriptor
)
{
    const auto pWindow = world_view_cpp::DescriptorToWindowMap.at(pWindowDescriptor);
    pWindow->m_pData->shouldClose = true;
}

void WorldView::PrivateData::OnResize(
    [[maybe_unused]] GLFWwindow* pWindowDescriptor,
    int width,
    int height
)
{
    glfwMakeContextCurrent(pWindowDescriptor);
    glViewport(0, 0, width, height);
}

void WorldView::PrivateData::drawWorld() const
{
    for (const auto& [id, shape] : pWorldModel->shapes())
    {
        glPushMatrix();
        const auto matrixGuard = ScopeGuard{ &glPopMatrix };

        const auto center = pOwner->mapWorldToScreen(shape.center);
        glTranslated(center.x, center.y, 0.0f);

        {
            glBegin(GL_POLYGON);
            const auto drawPoly = ScopeGuard{ &glEnd };

            glColor3b(shape.colorR, shape.colorG, shape.colorB);

            for (const auto& worldPoint : shape.contour)
            {
                const auto screenPoint = pOwner->mapWorldToScreen(worldPoint);
                glVertex3f(screenPoint.x + center.x, screenPoint.y + center.y, 0.0f);
            }
        }
    }
}

void WorldView::PrivateData::drawButtons()
{
    const auto& factories = pWorldModel->availableFactories();
    auto offset = -world_view_cpp::ICON_SCALE * static_cast<float>(factories.size());

    // Если области кнопок неизвестны, вычисляем их
    const auto needToCreateButtons = buttons.size() != factories.size();
    if (needToCreateButtons)
    {
        buttons.clear();
        buttons.reserve(factories.size());
    }

    // Отрисовка иконок фабрик
    for (auto i = 0U; i < factories.size(); ++i)
    {
        const auto pFactory = factories.at(i);
        {
            glPushMatrix();
            const auto matrixGuard = ScopeGuard{ &glPopMatrix };

            glTranslated(offset, 0.0f, 0.0f);

            if (needToCreateButtons)
            {
                Button button;
                button.shape = pFactory->createShape(true);
                button.xMin = offset;
                button.xMax = offset + 2.0f * world_view_cpp::ICON_SCALE;

                buttons.emplace_back(button);
            }

            offset += 4.0f * world_view_cpp::ICON_SCALE;

            glScalef(
                world_view_cpp::ICON_SCALE,
                world_view_cpp::ICON_SCALE,
                world_view_cpp::ICON_SCALE
            );

            {
                glBegin(GL_POLYGON);
                const auto drawPolyGuard = ScopeGuard{ &glEnd };

                // Подсветка кнопки под курсором
                if (currentButtonId == i)
                {
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else
                {
                    glColor3f(0.5f, 0.5f, 0.5f);
                }

                for (const auto& point : buttons.at(i).shape.contour)
                {
                    glVertex3f(point.x, point.y + 1.0f / world_view_cpp::ICON_SCALE - 1, 0.0f);
                }
            }
        }
    }
}

void WorldView::PrivateData::processUserInput()
{
    const auto oldLeftMousePressed = leftMousePressed;
    leftMousePressed = false;
    currentButtonId = -1;

    if (!glfwGetWindowAttrib(pWindowDescriptor, GLFW_FOCUSED))
    {
        return;
    }

    // Проверка кнопок
    {
        double xPos;
        double yPos;
        glfwGetCursorPos(pWindowDescriptor, &xPos, &yPos);

        const auto x = world_view_cpp::ICON_SCALE + (static_cast<float>(xPos) / world_view_cpp::WINDOW_WIDTH) * 2.0f - 1.0f;
        const auto y = world_view_cpp::ICON_SCALE + (static_cast<float>(yPos) / world_view_cpp::WINDOW_HEIGHT) * 2.0f - 1.0f;

        if (y <= world_view_cpp::ICON_SCALE)
        {
            for (int i = 0; i < static_cast<int>(buttons.size()); ++i)
            {
                const auto& button = buttons.at(i);

                if (x >= button.xMin && x <= button.xMax)
                {
                    currentButtonId = i;
                    break;
                }
            }
        }
    }

    // Если было нажатие, а затем отпуск, и при этом выбрана кнопка, создаем соответствующую фигуру
    leftMousePressed = GLFW_PRESS == glfwGetMouseButton(pWindowDescriptor, GLFW_MOUSE_BUTTON_LEFT);
    if (oldLeftMousePressed
        && !leftMousePressed
        && -1 != currentButtonId)
    {
        auto shape = pWorldModel->availableFactories().at(currentButtonId)->createShape(false);
        pWorldModel->addShape(std::move(shape));
    }

    // Очистка сцены по R
    if (GLFW_PRESS == glfwGetKey(pWindowDescriptor, GLFW_KEY_R))
    {
        pWorldModel->clear();
    }
}

/*-----------------------------------------------------------------------------------*/

WorldView::WorldView()
    : m_pData(std::make_unique<PrivateData>(this))
{
}

WorldView::~WorldView()
{
    glfwDestroyWindow(m_pData->pWindowDescriptor);
    world_view_cpp::DescriptorToWindowMap.emplace(m_pData->pWindowDescriptor, this);
    m_pData->pWindowDescriptor = nullptr;
}

void WorldView::processWindowEvents()
{
    if (nullptr == m_pData->pWindowDescriptor)
    {
        return;
    }

    glfwMakeContextCurrent(m_pData->pWindowDescriptor);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (nullptr == m_pData->pWorldModel)
    {
        return;
    }

    m_pData->drawWorld();
    m_pData->drawButtons();

    glfwSwapBuffers(m_pData->pWindowDescriptor);

    m_pData->processUserInput();
}

bool WorldView::shouldClose() const
{
    return m_pData->shouldClose;
}

void WorldView::setWindowTitle(
    const std::string& title
)
{
    glfwSetWindowTitle(m_pData->pWindowDescriptor, title.c_str());
}

void WorldView::setWorldModel(
    std::shared_ptr<WorldModel> pWoldModel
)
{
    m_pData->pWorldModel = std::move(pWoldModel);
}

std::shared_ptr<WorldModel> WorldView::worldModel() const
{
    return m_pData->pWorldModel;
}

Point2D WorldView::mapWorldToScreen(
    Point2D point
) const
{
    return Point2D{ point.x / m_pData->pWorldModel->size(), point.y / m_pData->pWorldModel->size() };
}

} // namespace shape_demo
