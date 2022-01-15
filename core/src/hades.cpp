#define STB_IMAGE_IMPLEMENTATION
#define GLEW_STATIC
#define GL_CLAMP_TO_EDGE 0x812F

#include "hades.h"

#include "editor.h"
#include "physics.h"
#include "scene.h"
#include "events.h"

Hades::Hades() {
    scripts = new Scripts();
}

void Hades::InitiatePlay() {

}

void Hades::Run() {

    if (!glfwInit())
        exit(1);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Hades", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glewInit();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    EventManager* eventManager = new EventManager();

    while (!glfwWindowShouldClose(window)) {
        RegisterPlugin(new Editor());
        RegisterPlugin(new Physics());

        Scene* scene = new Scene(window, scripts);
        scene->Init(plugins, eventManager);

        while (!glfwWindowShouldClose(window) && !eventManager->breakRender) {
            glfwPollEvents();
            scene->Render();
            glfwSwapBuffers(window);
        }
        eventManager->breakRender = false;

        delete scene;

        for (Plugin* plugin : plugins) {
            delete plugin;
        }
        plugins.clear();
    }
    

    glfwTerminate();
}

void Hades::RegisterPlugin(Plugin* plugin) {
    this->plugins.push_back(plugin);
}

Hades::~Hades() {
  
}