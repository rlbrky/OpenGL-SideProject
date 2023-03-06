#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
//layout(location = 1) in vec2 texCoords;
layout(location = 1) in vec4 Color;

//output to fragment shader(v stands for varying)
//out vec2 v_TexCoords;
out vec4 v_Color;

//Model View Projection Matrix
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	//v_TexCoords = texCoords;
	v_Color = Color;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//in vec2 v_TexCoords;
in vec4 v_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoords);
	//color = texColor;
	color = v_Color;
}