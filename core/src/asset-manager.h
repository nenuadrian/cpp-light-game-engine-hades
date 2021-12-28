#pragma once

#include <vector>
#include <glm.hpp>
#include <string>
#include "shader.h"
#include <assimp/scene.h>           // Output data structure
#include "model.h"
#include "nlohmann/json.hpp"


class AssetManager {
    int uuid = 0;
    ~AssetManager();
public:
    std::vector<Model*> models = { };

    AssetManager();
    void InitCache();
    void Load(nlohmann::json models);
    int AddModel(Model* model);

};
