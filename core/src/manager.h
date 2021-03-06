#pragma once

#include <vector>
#include "thing.h"
#include "asset-manager.h"
#include "nlohmann/json.hpp"
#include <entt/entt.hpp>
#include <glm.hpp>
#include "scripts.h"

class ThingManager {
    int uuid = 0;
    AssetManager* assetManager;
    Scripts* scripts;

public:
    entt::registry registry;

    ThingManager(AssetManager* assetManager, Scripts* scripts);

    entt::entity Add(Thing* t);
    entt::entity CreateThing();
    entt::entity ThingManager::CreateThing(nlohmann::json json);
    void Render(glm::mat4 view);

    Thing* ThingById(int uuid);
    void ThingManager::Delete(int uuid);
};
