#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace test
{
	class Shader;
	class Texture;

	class TestCreateObject : public Test
	{
	public:
		TestCreateObject();
		~TestCreateObject();

		void CreateSquare(float length);

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		Shader shader("res/shader/Shader.shader");
		Texture texture("res/textures/moyai.png");
		IndexBuffer ib;
	};
}