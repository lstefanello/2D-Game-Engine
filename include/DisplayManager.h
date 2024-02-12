#pragma once
#define GLEW_STATIC
//#include "imgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_opengl3.h"
#include <Globals.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace DisplayManager
{
//    extern GLuint vertex_vbo;
 //   extern GLuint instance_vbo;
    extern GLuint vao;
    extern GLuint shaderProgram;

    extern int texture_width;
    extern int texture_height;

    void Initialize();
    void CreateShaders();
    void CreateBuffers();
    void SetGLParameters();
    GLuint LoadTexture(const char* filename);

    class Texture
    {
        public:
            Texture(const char* filename);
            int width, height;
            int ID;
    };


    class Window
    {
        public:
            Window(const char* title, int off_x, int off_y, int w, int h);

            SDL_Window* window;
            SDL_GLContext context;
    };

    class Shader
    {
        public:
            Shader(const char* filepath, GLenum type);
            GLuint shader;
    };
}
