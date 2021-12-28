#pragma once


#include "model.h"


class ModelBasic : public Model
{
public:

    ModelBasic() {
        name = "primitive";
        type = "basic";
        vertices = new float[] {
            -0.5f, 0.7f, 0.0f,
                -0.5f, -0.7f, 0.0f,
                0.5f, -0.7f, 0.0f,

                0.5f, -0.7f, 0.0f,
                0.5f, 0.7f, 0.0f,
                -0.5f, 0.7f, 0.0f
        };
    };

private:
    float* vertices;
};
