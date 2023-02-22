#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OLA", NULL, NULL);
    glfwSwapInterval(1);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    { //This scope is to fix a bug that openGL generates when terminating the program.
        //Triangle points XYZ coordinates
        float vertices[] = {
            0.5f, 0.5f, 0.0f,       //0
            -0.5f, -0.5f, 0.0f,     //1
            0.5f, -0.5f, 0.0f,       //2
            -0.5f, 0.5f, 0.0f       //3
        };

        unsigned int indices[] = {
            0, 2, 1,
            1, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(vertices, 4 * 3 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("res/shader/Shader.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.4f, 0.2f, 0.7f, 1.0f);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.2f, 0.7f, 1.0f);

            va.Bind();
            ib.Bind();

            //glDrawArrays(GL_TRIANGLES, 0, 3);
                                //The last variable is nullptr because we already binded our buffer in line 132.
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f)
                increment = -0.005f;
            else if (r < 0.0f)
                increment = 0.005f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}