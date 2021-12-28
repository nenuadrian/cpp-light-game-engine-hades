#include "thing.h"
#include "shader.h"
#include "opengl.h"

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags



// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 vertex;\n"
"layout (location = 1) in vec3 norml;\n"
"layout (location = 2) in vec2 uvIn;\n"
"out vec2 TexCoord;\n"
"uniform mat4 MVP;\n"
"void main()\n"
"{\n"
"   gl_Position = MVP * vec4(vertex, 1.0);\n"
"   TexCoord = uvIn; \n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"uniform sampler2D texture_diffuse;\n"
"uniform sampler2D texture_specular;\n"
"void main()\n"
"{\n"
"   FragColor = mix(texture(texture_diffuse, TexCoord), texture(texture_specular, TexCoord), 0.2);\n"
"}\n\0";


Thing::Thing(AssetManager* assetManager) {
    model = assetManager->models[0];

    GL_CHECK(shader = new Shader());
    GL_CHECK(shader->Load(vertexShaderSource, fragmentShaderSource));
    GL_CHECK(glUseProgram(shader->ID));
    GL_CHECK(glUniform1i(glGetUniformLocation(shader->ID, std::string("texture_diffuse").c_str()), 0));
    GL_CHECK(glUniform1i(glGetUniformLocation(shader->ID, std::string("texture_specular").c_str()), 1));
    GL_CHECK(glUseProgram(0));
}

bool Thing::Render(glm::mat4 view) {
    // Tell OpenGL which Shader Program we want to use
    GL_CHECK(glUseProgram(shader->ID));

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    Model = glm::translate(Model, glm::vec3(x, y, z));
    glm::mat4 mvp = view * Model;

    // Outputs the matrices into the Vertex Shader
    GL_CHECK({
        GLuint modelLoc = glGetUniformLocation(shader->ID, "MVP");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mvp));
    });
    this->model->Draw(shader);
  
    GL_CHECK(glUseProgram(0));

    return true;
}

Thing::~Thing() {
    // Delete all the objects we've created
    if (shader != nullptr) {
        glDeleteProgram(shader->ID);
    }
}