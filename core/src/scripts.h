#pragma once

#include <vector>
#include "thing.h"
#include <entt/entt.hpp>


class Script {
public:
    virtual void Run(entt::entity thing) {}
};

class Scripts {
    std::vector<Script*> scripts;
public:
  
    ~Scripts() {
        for (Script* s : scripts) {
            delete s;
        }
    }

    Scripts() {

    }

    void Register(Script* script);
};

