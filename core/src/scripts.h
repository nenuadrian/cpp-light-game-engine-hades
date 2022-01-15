#pragma once

#include <vector>
#include "thing.h"
#include <entt/entt.hpp>


class Script {
public:
    std::string id;

    Script(std::string _id) {
        id = _id;
    };

    virtual void Run(entt::entity thing) {}
    virtual ~Script() {}
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

