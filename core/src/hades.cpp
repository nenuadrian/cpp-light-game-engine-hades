#define STB_IMAGE_IMPLEMENTATION
#define GLEW_STATIC
#define GL_CLAMP_TO_EDGE 0x812F

#include "hades.h"

#include "editor.h"
#include "scene.h"

Hades::Hades() {
    RegisterPlugin(new Editor());
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

    Scene* scene = new Scene(window);
    scene->Init(plugins);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        scene->Render();
        glfwSwapBuffers(window);
    }
   
    for (Plugin* plugin : plugins) {
        delete plugin;
    }

    glfwTerminate();
}

void Hades::RegisterPlugin(Plugin* plugin) {
    this->plugins.push_back(plugin);
}

Hades::~Hades() {
  
}