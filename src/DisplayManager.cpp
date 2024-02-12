#include <DisplayManager.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace DisplayManager
{
    GLuint vertex_vbo;
    GLuint instance_vbo;
    GLuint vao;
    GLuint shaderProgram;
    GLuint posAttrib;

    int texture_width;
    int texture_height;

    void Initialize()
    {
        //SDL_SetHint(SDL_HINT_VIDEODRIVER, "wayland,x11");
        SDL_Init(SDL_INIT_EVERYTHING);
//        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetSwapInterval(1);

        CreateShaders();
        CreateBuffers();
        SetGLParameters();
    }

    void CreateShaders()
    {
        Shader vertex("../shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
        Shader fragment("../shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
 
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertex.shader);
        glAttachShader(shaderProgram, fragment.shader);
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);

        glDeleteShader(vertex.shader);
        glDeleteShader(fragment.shader);
    }
    
    void CreateBuffers()
    {
        GLuint vertex_vbo;
        GLuint instance_vbo;
        unsigned int ebo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vertex_vbo);
        glGenBuffers(1, &instance_vbo);
        glGenBuffers(1, &ebo);

        GLfloat vertices[] = 
        {
            0.5f,  0.5f,  // top right
            0.5f, -0.5f,  // bottom right
           -0.5f, -0.5f,  // bottom left
           -0.5f,  0.5f   // top left
        };


        unsigned int index[] =
        {
            0, 1, 3,
            1, 2, 3
        };

 
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); 

        glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[13 * Globals::MAX_ENTITIES]), nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)0); 
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(3*sizeof(float))); 
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(5*sizeof(float)));
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(9*sizeof(float)));

        glVertexAttribDivisor(0, 0); 
        glVertexAttribDivisor(1, 1); 
        glVertexAttribDivisor(2, 1); 
        glVertexAttribDivisor(3, 1); 
        glVertexAttribDivisor(4, 1); 

        glBindVertexArray(0);

/*        unsigned int fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, &fbo);

        unsigned int fbo_texture;
        glGenTextures(1, &fbo_texture);
        glBindTexture(GL_TEXTURE_2D, fbo_texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);

        glTexImage2D(
          GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, Globals::SCREEN_WIDTH, SCREEN_HEIGHT, 0,
          GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
        );

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, fbo_texture, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &fbo);*/
    }

    void SetGLParameters()
    {
        glViewport(0, 0, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_MULTISAMPLE);
    }

    Texture::Texture(const char* filename)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



        int t_width, t_height, nrChannels;
        unsigned char *data = stbi_load(filename, &t_width, &t_height, &nrChannels, 0); //load the texture

        width = t_width;
        height = t_height;

        texture_width = t_width;
        texture_height = t_height;

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        ID = texture;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    Window::Window(const char* title, int off_x, int off_y, int w, int h)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
        context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, context);

        glewExperimental = GL_TRUE;
        glewInit();


/*        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io; ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init("#version 330 core");*/
    }

    DisplayManager::Shader::Shader(const char* filepath, GLenum type)
    {
        std::ifstream file;
        std::stringstream shader_stream;
        std::string code;

        file.open(filepath);
        shader_stream << file.rdbuf();
        file.close();

        code = shader_stream.str();
        const char* c_code = code.c_str();

        if (type == GL_VERTEX_SHADER)
        {
            shader = glCreateShader(GL_VERTEX_SHADER);
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            shader = glCreateShader(GL_FRAGMENT_SHADER);
        }

        glShaderSource(shader, 1, &c_code, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }  
    }
}
