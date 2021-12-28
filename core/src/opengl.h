#ifndef OPENGL_UTILS

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#define OPENGL_UTILS

static void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        //const GLubyte* msg = glErrorString(err);
        printf("OpenGL error %08x, at %s:%i - for %s \n", err, fname, line, stmt);
        abort();
    }
}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif

#endif