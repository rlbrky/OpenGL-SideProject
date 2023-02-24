#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
	: m_RendererID(0), m_Filepath(filepath), m_LocalBuffer(nullptr),
					m_Width(0), m_Height(0), m_BPP(0)
{
	//Flip the png to fit openGL's loading texture format(bottom left is 0,0)
	stbi_set_flip_vertically_on_load(1);
	//stbi_load fills our variables with data(desired channel = 4 is for RGBA)
	m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	//You have to specify these 4 parameters to make sure your image gets loaded correctly, or you can get a black texture.
	//Min filter is to minimize the image to fit in, linear is to linearly resample the data.
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	//Mag is to scale the image if it is too small.
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); //X for texture
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); //Y for texture

	//First format(RGBA8) is the format that we want openGL to process, second format is the data format that we are supplying.
				//CHECK DOCUMENTATION FOR FURTHER INFORMATION(https://docs.gl/gl4/glTexImage2D)
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	Unbind();

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	//Specify the slot that our texture will be stored.(Can be used to reuse texture and stuff.)
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
