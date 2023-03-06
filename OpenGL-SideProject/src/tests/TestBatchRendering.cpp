#include "TestBatchRendering.h"

#include "Renderer.h"
#include "imgui/imgui.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
	TestBatchRendering::TestBatchRendering()
		:m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), 
			m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
				m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
		float vertices[] = {
			-50.0f, -50.0f,		0.0f, 0.0f,		0.0f,
			 50.0f, -50.0f,		1.0f, 0.0f,		0.0f,
			 50.0f, 50.0f,			1.0f, 1.0f,		0.0f,
			-50.0f,  50.0f,		0.0f, 1.0f,		0.0f,

			150.0f, 150.0f,			0.0f, 0.0f,		1.0f,
			200.0f, 150.0f,			1.0f, 0.0f,		1.0f,
			200.0f, 200.0f,			1.0f, 1.0f,		1.0f,
			150.0f, 200.0f,			0.0f, 1.0f,		1.0f
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VBO = std::make_unique<VertexBuffer>(vertices, 8 * 5 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		layout.Push<float>(1);

		m_VAO->AddBuffer(*m_VBO, layout);
		m_IBO = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shader/Shader.shader");
		m_Shader->Bind();
		m_Texture1 = std::make_unique<Texture>("res/textures/moyai.png");
		m_Texture2 = std::make_unique<Texture>("res/textures/Clueless.png");
		//m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestBatchRendering::~TestBatchRendering()
	{

	}

	void TestBatchRendering::OnUpdate(float deltaTime)
	{

	}

	void TestBatchRendering::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		GLCall(glBindTextureUnit(0, m_Texture1->GetTexID()));
		GLCall(glBindTextureUnit(1, m_Texture2->GetTexID()));

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;

			//m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestBatchRendering::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
	}

}