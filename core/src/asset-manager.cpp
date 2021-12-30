#include "asset-manager.h"
#include "model_complex.h"
#include "model_basic.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>

AssetManager::AssetManager() {
    if (!std::filesystem::exists("assets")) {
        std::filesystem::create_directory("assets");
        std::filesystem::create_directory("assets/sounds");
        std::filesystem::create_directory("assets/models");
    }
}

void AssetManager::InitCache() {
    auto model = new ModelComplex("C:\\Users\\Adrian\\Desktop\\Backpack_v2_L3.123c453282d0-e9c5-46f0-8e0c-2cdc6188c9c1\\12305_backpack_v2_l3.obj");
    AddModel(model);
    AddModel(new ModelBasic());
}

int AssetManager::AddModel(Model* model) {
    uuid++;
    if (model->uuid == -1) {
        model->uuid = uuid;
    }
    uuid = std::max(uuid, model->uuid + 1);
    this->models.push_back(model);
    return uuid;
}

void AssetManager::Load(nlohmann::json models) {
    for (auto jsonT : models) {
        Model* model;
        if (jsonT["type"] == "basic") {
            model = new ModelBasic();

        }
        else {
            std::string path = jsonT["path"];
            model = new ModelComplex(path.c_str());
        }
        model->uuid = jsonT["uuid"];
        this->AddModel(model);
    }
}

AssetManager::~AssetManager() {
    for (Model* model : models) {
        delete model;
    }
}