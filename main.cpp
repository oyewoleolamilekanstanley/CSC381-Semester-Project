#include <iostream>
#include <cstdio>
#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

// Vertex Shader
static const GLchar *vertexShader = "               \n\
#version 330                                        \n\
                                                    \n\
layout (location = 0) in vec3  pos;                 \n\
                                                    \n\
void main()                                         \n\
{                                                   \n\
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);   \n\
}                                                   \n\
";

// Fragment Shader
static const GLchar *fragmentShader = "             \n\
#version 330                                        \n\
                                                    \n\
out vec4 colour;                                    \n\
                                                    \n\
void main()                                         \n\
{                                                   \n\
    colour = vec4(1.0, 0.0, 0.0, 0.1);              \n\
}                                                   \n\
";

void createTriangle()
{
    GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void addShader(GLuint theProgram, const GLchar *shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);
    const GLchar *theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = (GLint)strlen(shaderCode);

    glShaderSource(theShader, 1, &shaderCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        fprintf(stderr, "Error compiling the shader '%d': '%s'\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}

void compileShader()
{
    shader = glCreateProgram();

    if (!shader)
    {
        fprintf(stderr, "Error Creating shader program");
        return;
    }

    addShader(shader, vertexShader, GL_VERTEX_SHADER);
    addShader(shader, fragmentShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        fprintf(stderr, "Error Linking program: '%s'\n", eLog);
        return;
    }

    glValidateProgram(shader);

    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        fprintf(stderr, "Error Validating program: '%s'\n", eLog);
        return;
    }

}

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Error initializing GL Framework");
        glfwTerminate();
    }

    // Setup GLFW
    // OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);

    if (!mainWindow)
    {
        fprintf(stderr, "Error creating GL window");
        glfwTerminate();
        exit(1);
    }

    // Get Buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "GLEW initialization failed: %s\n", glewGetErrorString(glewInit()));
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        exit(1);
    }

    glViewport(0, 0, bufferWidth, bufferHeight);
    createTriangle();
    compileShader();

    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwPollEvents();

        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    return 0;

}
