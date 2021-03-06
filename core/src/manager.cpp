#include "manager.h"
#include <stdexcept>
#include "physics.h"

ThingManager::ThingManager(AssetManager* assetManager, Scripts* scripts) {
    this->assetManager = assetManager;
    this->scripts = scripts;
}

entt::entity ThingManager::CreateThing(nlohmann::json json) {
    Thing* t = new Thing(this->assetManager);
    t->uuid = json["uuid"];
    t->x = json["x"];
    t->y = json["y"];
    t->z = json["z"];
    if (json.contains("script")) {
        t->script = json["script"];
    }
    return this->Add(t);
}

entt::entity ThingManager::CreateThing() {
    Thing* t = new Thing(this->assetManager);
    return this->Add(t);
}

entt::entity ThingManager::Add(Thing* t) {
    
    if (t->uuid == -1) {
        uuid++;
        t->uuid = uuid;
    }
    else {
        uuid = std::max(uuid, t->uuid + 1);
    }

    const auto entity = registry.create();
    registry.emplace<Thing*>(entity, t);
    registry.emplace<RigidBody>(entity, false);
    for (Script* s : scripts) {
        if (s->id == t->script) {
            registry.emplace<Script*>(entity, s);
            break;
        }
    }
    
    return entity;
}

void ThingManager::Render(glm::mat4 view) {
    auto registryView = registry.view<Thing*>();
    for (auto [entity, thing] : registryView.each()) {
        if (registry.any_of<Script*>(entity)) {
            auto script = registry.get<Script*>(entity);
            script->Run(entity);
        }
        thing->Render(view);
    }
}

void ThingManager::Delete(int uuid) {
    auto view = registry.view<Thing*>();
    for (auto [entity, thing] : view.each()) {
        if (thing->uuid == uuid) {
            registry.destroy(entity);
            delete thing;
            return;
        }
    }
}

Thing* ThingManager::ThingById(int uuid) {
    auto view = registry.view<Thing*>();
    for (auto [entity, thing] : view.each()) {
        if (thing->uuid == uuid) {
            return thing;
        }
    }
    throw std::invalid_argument("received an invalid UUID");
}

