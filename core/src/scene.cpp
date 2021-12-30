#include "scene.h"
#include <glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "opengl.h"

glm::mat4 view = glm::lookAt(
    glm::vec3(0, 50, 50), // Camera is at (4,3,3), in World Space
    glm::vec3(0, 0, 0), // and looks at the origin
    glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);

glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 1000.0f);

void Scene::scrollCallback(GLFWwindow* w, double x, double y) {
    for (Plugin* plugin : plugins) {
        plugin->scrollCallback(w, x, y);
    }
    view = glm::translate(view, glm::vec3(0, 0, y));
}

void Scene::mouseButtonCallback(GLFWwindow* w, int button, int action, int modsy) {
    for (Plugin* plugin : plugins) {
        plugin->mouseButtonCallback(w, button, action, modsy);
    }
}

void Scene::charCallback(GLFWwindow* w, unsigned int c) {
    for (Plugin* plugin : plugins) {
        plugin->charCallback(w, c);
    }
}

void Scene::keyCallBack(GLFWwindow* w, int key, int scancode, int action, int mods) {
    for (Plugin* plugin : plugins) {
        plugin->keyCallBack(w, key, scancode, action, mods);
    }
}

void Scene::mousePosCallback(GLFWwindow* w, double x, double y) {
    for (Plugin* plugin : plugins) {
        plugin->mousePosCallback(w, x, y);
    }
}

void Scene::Init(std::vector<Plugin*> plugins, EventManager* eventManager) {
    this->plugins = plugins;
    
    assetManager->InitCache();
    for (Plugin* plugin : plugins) {
        plugin->Init(window, eventManager, assetManager, manager, soundManager);
    }

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);
}

void Scene::Render() {
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LESS));

    GL_CHECK(glClearColor(114, 144, 154, 0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    manager->Render(projection * view);

    for (Plugin* plugin : plugins) {
        plugin->Render();
    }

}