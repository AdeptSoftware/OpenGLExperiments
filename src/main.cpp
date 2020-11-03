#include <GLAD/glad.h>		// Должно идти первым
#include <GLFW/glfw3.h>
#include <iostream>

int Terminate(const char* buf) {
    std::cout << buf << std::endl;
    glfwTerminate();
    return -1;
}

int main(void) {
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
        return Terminate("Window don't create!");

    glfwMakeContextCurrent(window); // Make the window's context current

    if (!gladLoadGL())
        return Terminate("Can't load GLAD!");
    std::cout << "OpenGL " << GLVersion.major << '.' << GLVersion.minor << std::endl;

    glClearColor(1, 0, 0, 1);	// Красный фон
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
