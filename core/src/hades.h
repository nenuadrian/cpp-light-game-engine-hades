#pragma once

#include <vector>
#include "plugin.h"
#include "scripts.h"

class Hades {
    std::vector<Plugin*> plugins;
    Scripts* scripts;
    ~Hades();

public:
    Hades();

    void Run();
    void RegisterPlugin(Plugin* plugin);
    void InitiatePlay();
};

