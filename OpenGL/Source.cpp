#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "program.h"
#include "settings.h"



float update_height = height;
float update_width = width;


void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
    if (scale_render_on_window_resize) glViewport(0, 0, _width, _height); // setting openGL viewport on window resize
    update_height = _height;
    update_width = _width;
}

int main() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(swap_interval);
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "Sheep Rendering-Engine", NULL , NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (glewInit() != GLEW_OK) {
        std::cout << "wth bro !" << std::endl;
    }

    Program main_program;
    main_program.onStartup();

    double prev_time = glfwGetTime();
    int frame_count = 0;
    int fps_count = 0;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        if (glfwGetTime() > prev_time + 1)
        {
            fps_count = frame_count;
            frame_count = 0;
            prev_time = glfwGetTime();
            std::cout << fps_count << std::endl;
        }
        main_program.onUpdate();
        main_program.renderShapes();

        glfwSwapBuffers(window);
        glfwPollEvents();
        frame_count++;

    }

    main_program.onFinish();
    main_program.clearObjects();
    glfwTerminate();

    return 0;
}
