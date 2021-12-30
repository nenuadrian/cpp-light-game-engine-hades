#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "plugin.h"

class Physics : public Plugin {
public:
    Physics() : Plugin("Physics") {}
    void virtual Render();
    virtual ~Physics() {
    }

    void virtual Init(GLFWwindow* window, AssetManager* _assetManager, ThingManager* _manager, SoundManager* _soundManager) {
        this->manager = _manager;
        this->soundManager = _soundManager;
        this->assetManager = _assetManager;

       
    }

private:

};