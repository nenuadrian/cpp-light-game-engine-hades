#pragma once
#include <string>
#include "manager.h"
#include "asset-manager.h"
#include "sound.h"
#include <GLFW/glfw3.h>

class Plugin {
protected:
    std::string name;
    ThingManager* manager;
    SoundManager* soundManager;
    AssetManager* assetManager;

public:
    Plugin(std::string name) {
        this->name = name;
    }

    virtual ~Plugin() {}
    void virtual Init(GLFWwindow* window, AssetManager* _assetManager, ThingManager* _manager, SoundManager* _soundManager) {
        this->manager = _manager;
        this->soundManager = _soundManager;
        this->assetManager = _assetManager;
    }

    void virtual scrollCallback(GLFWwindow* w, double x, double y) {}
    void virtual mouseButtonCallback(GLFWwindow* w, int button, int action, int modsy) {}
    void virtual mousePosCallback(GLFWwindow* w, double x, double y) {}
    void virtual keyCallBack(GLFWwindow* w, int key, int scancode, int action, int mods) {}
    void virtual charCallback(GLFWwindow* w, unsigned int c) {}
    void virtual Render() {};
};

