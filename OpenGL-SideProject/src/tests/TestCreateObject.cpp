#pragma once

#include "TestCreateObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

test::TestCreateObject::TestCreateObject()
	: vb(nullptr, 0), 
{
	vb(nullptr, 0);

	shader.Bind();
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);
}

test::TestCreateObject::~TestCreateObject()
{
	va.Unbind();
	shader.Unbind();
	vb.Unbind();
	ib.Unbind();
}

void test::TestCreateObject::CreateSquare(float length)
{
	float vertices[] = {
		-length / 2, -length / 2, 0.0f, 0.0f, //0
		 length / 2, -length / 2, 1.0f, 0.0f, //1
		 length / 2,  length / 2, 1.0f, 1.0f, //2
		-length / 2,  length / 2, 0.0f, 1.0f //3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	vb(vertices, 4 * 4 * sizeof(float));

	layout.Push<float>(2); //Object Coordinates
	layout.Push<float>(2); //Texture Coordinates
	va.AddBuffer(vb, layout);

	ib(indices, 6);

	//4:3 aspect ratio
	glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
}

void test::TestCreateObject::OnUpdate(float deltaTime)
{

}

void test::TestCreateObject::OnRender()
{

}

void test::TestCreateObject::OnImGuiRender()
{

}
