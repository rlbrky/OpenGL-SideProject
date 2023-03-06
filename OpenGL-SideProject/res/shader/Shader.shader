#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in float texIndex;

//output to fragment shader(v stands for varying)
out vec2 v_TexCoords;
out float v_TexIndex;

//Model View Projection Matrix
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoords = texCoords;
	v_TexIndex = texIndex;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoords;
in float v_TexIndex;

uniform vec4 u_Color;
uniform sampler2D u_Texture[2];

void main()
{
	int index = int(v_TexIndex);
	//vec4 texColor = texture(u_Texture, v_TexCoords);
	vec4 texColor = texture(u_Texture[index], v_TexCoords);
	color = texColor;
}