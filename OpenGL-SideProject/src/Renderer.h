#pragma once

#include<GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//Macros for error checking, first one puts a breakpoint to the location which an error occured.
#define ASSERT(x) if (!(x)) __debugbreak();
//This one calls our error checking functions for each function we write. 
//x = the function that will be checked. The "\" means that it will ignore newline and you don't have to write code on one line.
//The "#" before x means that it will be turned to string so that we can print it on console.
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};