#include <GLAD/glad.h>		// Должно идти первым
#include <GLFW/glfw3.h>
#include <iostream>
#include "crt_debug.h"
#include "callbacks.h"
#include "Resources/res_manager.h"

#include "glm/gtc/type_ptr.hpp"

extern "C" { // Чтобы выбиралась не "Intel(R) HD Graphics 4000" (OpenGL 4.0), а "GeForce GT 630M" (OpenGL 4.6)
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; // Не проверялось
}

void render(GLFWwindow* pWindow, string sExeFileName);

int Terminate(string buf) {
    std::cerr << buf << std::endl;
    glfwTerminate();
    system("pause");
    return -1;
}

int main(int argv, char** argc) {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(int(g_fCenterX*2), int(g_fCenterY*2), "OpenGL Experiments", nullptr, nullptr);
    if (!pWindow)
        return Terminate("Window don't create!");

    glfwSetCursorPosCallback(pWindow, OnCursorPos);
    glfwSetWindowSizeCallback(pWindow, OnWndSize);
    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetMouseButtonCallback(pWindow, OnMouse);
    glfwSetKeyCallback(pWindow, OnKey);
    glfwMakeContextCurrent(pWindow); // Make the window's context current

    glfwSetCursorPos(pWindow, g_fCenterX, g_fCenterY);

    if (!gladLoadGL())
        return Terminate("Can't load GLAD!");
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl << std::endl;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    try {
        render(pWindow, argc[0]);
    } catch (string msg) { 
        Terminate(msg.c_str());
    }

    glfwTerminate();
    return 0;
}

void render(GLFWwindow* pWindow, string sExeFileName) {
    CResourceManager res(sExeFileName);
    auto pObjectShader = res.ShaderProgramF("def_shader", "default.vert",    "default.frag");
    auto pGridShader   = res.ShaderProgramF("grd_shader", "line_color.vert", "def_color.frag");
    auto pBkgShader    = res.ShaderProgramF("bkg_shader", "def_color.vert",  "def_color.frag");
    auto pTexture = res.Texture2D("wall", "wall.png");

    InitGrid();
    grid.Scale({ 10.0f, 1.0, 10.0f });
    cube.Position({0.0f, 1.0f, 0.0f});

    CVertexArraysObject vao(GL_ARRAY_BUFFER, 1);
    vao.Bind(cube, cube.GetBytesCount(), GL_STATIC_DRAW);
    vao.Attribute(GL_FLOAT, 3, GL_FALSE, 5*sizeof(GLfloat));
    vao.Attribute(GL_FLOAT, 3, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));

    CVertexArraysObject vao_grid(GL_ARRAY_BUFFER, 2);
    vao_grid.Bind(grid, grid.GetBytesCount(), GL_FLOAT, 3, GL_STATIC_DRAW);

    CVertexArraysObject vao_bkg(GL_ARRAY_BUFFER, 2);
    vao_bkg.Bind(vBackground, sizeof(vBackground), GL_STATIC_DRAW);
    vao_bkg.Attribute(GL_FLOAT, 3, GL_FALSE, 6*sizeof(GLfloat));
    vao_bkg.Attribute(GL_FLOAT, 3, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));

    // Проекционная матрица : 45 deg; поле обзора, 4:3 соотношение сторон, диапазон : 0.1 юнит <-> 100 юнитов
    glm::mat4 Projection = glm::perspective(g_camera.Zoom, g_fCenterX / g_fCenterY, 0.1f, 1000.0f);
    //glm::mat Projection = glm::ortho(0.0f, g_fCenterX*2, 0.0f, g_fCenterY*2, -1000.0f, 1000.0f);

    pObjectShader->Activate();
    pObjectShader->Set("Texture", 0);
    pObjectShader->Set("projection", glm::value_ptr(Projection));

    pGridShader->Activate();
    pGridShader->Set("projection", glm::value_ptr(Projection));
    pGridShader->Set("model", glm::value_ptr(grid.GetModelMatrix()));

    glEnable(GL_LINE_SMOOTH);
    while (!glfwWindowShouldClose(pWindow)) {
        const GLfloat* view = glm::value_ptr(g_camera.GetViewMatrix());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        vao_bkg.Activate();
        pBkgShader->Activate();
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glEnable(GL_DEPTH_TEST);

        vao_grid.Activate();
        pGridShader->Activate();
        pGridShader->Set("view", view);
        glLineWidth(0.05f);
        glDrawArrays(GL_LINES, 0, grid.GetVertexCount());
        glLineWidth(1.0f);

        vao.Activate();
        pObjectShader->Activate();
        pObjectShader->Set("model", glm::value_ptr(cube.GetModelMatrix()));
        pObjectShader->Set("view", view);
        if (g_bTexture)
            pTexture->Activate();
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, cube.GetVertexCount());

        glfwSwapBuffers(pWindow);
        glfwPollEvents(); // Poll for and process events
    }
}