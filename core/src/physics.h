#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "plugin.h"
#include "btBulletDynamicsCommon.h"

struct RigidBody {
    bool test;
};

class Physics : public Plugin {
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btSequentialImpulseConstraintSolver* solver;
    btBroadphaseInterface* overlappingPairCache;
    btCollisionDispatcher* dispatcher;
    btDefaultCollisionConfiguration* collisionConfiguration;
    bool initialized = false;

public:
    Physics() : Plugin("Physics") {
    }
    void virtual Render();
    virtual ~Physics();

    void virtual Init(GLFWwindow* window, EventManager* _eventManager, AssetManager* _assetManager, ThingManager* _manager, SoundManager* _soundManager) {
        this->eventManager = _eventManager;
        this->manager = _manager;
        this->soundManager = _soundManager;
        this->assetManager = _assetManager;

        Setup();
    }

private:
    void Setup();
};