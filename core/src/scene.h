#include <vector>
#include "plugin.h"
#include "events.h"
#include "scripts.h"
#include <GLFW/glfw3.h>

class Scene {
    GLFWwindow* window;
public:
    std::vector<Plugin*> plugins;
    AssetManager* assetManager;
    ThingManager* manager;
    SoundManager* soundManager;
    ~Scene() {
        delete assetManager;
        delete manager;
        delete soundManager;
    }

    Scene(GLFWwindow* window, Scripts* scripts) {
        this->window = window;
        assetManager = new AssetManager();
        manager = new ThingManager(assetManager, scripts);
        soundManager = new SoundManager();

        glfwSetWindowUserPointer(window, this);

        auto func = [](GLFWwindow* w, double x, double y)
        {
            static_cast<Scene*>(glfwGetWindowUserPointer(w))->scrollCallback(w, x, y);
        };

        glfwSetScrollCallback(window, func);

        auto func2 = [](GLFWwindow* w, int button, int action, int mods)
        {
            static_cast<Scene*>(glfwGetWindowUserPointer(w))->mouseButtonCallback(w, button, action, mods);
        };

        glfwSetMouseButtonCallback(window, func2);

        auto func3 = [](GLFWwindow* w, double x, double y)
        {
            static_cast<Scene*>(glfwGetWindowUserPointer(w))->mousePosCallback(w, x, y);
        };
        glfwSetCursorPosCallback(window, func3);


        auto func4 = [](GLFWwindow* w, unsigned int c)
        {
            static_cast<Scene*>(glfwGetWindowUserPointer(w))->charCallback(w, c);
        };
        glfwSetCharCallback(window, func4);

        auto func5 = [](GLFWwindow* w, int key, int scancode, int action, int mods)
        {
            static_cast<Scene*>(glfwGetWindowUserPointer(w))->keyCallBack(w, key, scancode, action, mods);
        };
        glfwSetKeyCallback(window, func5);
    }

    void scrollCallback(GLFWwindow* w, double x, double y);
    void mousePosCallback(GLFWwindow* w, double x, double y);
    void keyCallBack(GLFWwindow* w, int key, int scancode, int action, int mods);
    void charCallback(GLFWwindow* w, unsigned int c);
    void mouseButtonCallback(GLFWwindow* w, int button, int action, int modsy);
    void Init(std::vector<Plugin*> plugins, EventManager* eventManager);
    void Render();

};

