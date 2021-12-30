#pragma once

#include <vector>
#include "plugin.h"

class Hades {
    std::vector<Plugin*> plugins;
    ~Hades();

public:
    Hades();

    void Run();
    void RegisterPlugin(Plugin* plugin);
    void InitiatePlay();
};

