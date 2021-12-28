#pragma once

#include "shader.h"
#include <glm.hpp>
#include <vector>
#include <string>


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices,
        std::vector<unsigned int> indices,
        std::vector<Texture> textures);
    void Draw(Shader* shader);
    void Draw(int shaderProgram);
    unsigned int VAO, VBO, EBO;

private:
    void setupMesh();
};


class Model
{
public:
    std::vector<Mesh> meshes;
    std::string name;
    std::string type;
    int uuid = -1;

    virtual void Draw(Shader* shader) {};
    virtual void Draw(GLuint shaderProgram) {};
};
