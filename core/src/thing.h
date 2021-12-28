#pragma once

#include <vector>
#include <string>

#include "model.h"
#include "asset-manager.h"


class Thing {
public:
    int uuid = -1;
    float x = 0;
    float y = 0;
    float z = 0;
    Shader* shader;
    Model* model;

    Thing::Thing(AssetManager* assetManager);

    bool Render(glm::mat4 view);

    ~Thing();

};
