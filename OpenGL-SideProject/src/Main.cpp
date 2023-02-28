#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include <imgui/imgui_impl_opengl3.h>

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
    window = glfwCreateWindow(1024, 500, "OLA", NULL, NULL);
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
              50.0f,  50.0f, 0.0f,   1.0f, 1.0f,      //0
             -50.0f, -50.0f, 0.0f,  0.0f, 0.0f,      //1
              50.0f, -50.0f, 0.0f,  1.0f, 0.0f,      //2
             -50.0f,  50.0f, 0.0f,  0.0f, 1.0f       //3
        };

        unsigned int indices[] = {
            0, 2, 1,
            1, 3, 0
        };

        //Blending for alpha pixels to get correct texture.(For transparency)
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(vertices, 4 * 5 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        //4:3 aspect ratio
        glm::mat4 proj = glm::ortho(0.0f, 1024.0f, 0.0f, 500.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader shader("res/shader/Shader.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.4f, 0.2f, 0.7f, 1.0f);

        Texture texture("res/textures/moyai.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        ImGui::CreateContext();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

        ImGui::StyleColorsDark();

        glm::vec3 translation1(200, 200, 0);
        glm::vec3 translation2(400, 200, 0);

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

            

            {
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translation1);
				glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, shader);
            }

            {
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translation2);
				glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, shader);
            }
			

            
            //shader.SetUniform4f("u_Color", r, 0.2f, 0.7f, 1.0f);
			

            

            if (r > 1.0f)
                increment = -0.005f;
            else if (r < 0.0f)
                increment = 0.005f;

            r += increment;

			{
				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
				ImGui::SliderFloat3("translation 1", &translation1.x, 0.0f, 1024.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::SliderFloat3("translation 2", &translation2.x, 0.0f, 1024.0f); 
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}