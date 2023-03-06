#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	unsigned int texID;
public:
	Texture(const std::string& filepath);
	~Texture();

	//Specify the slot that we are binding our texture to.
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	unsigned int GetTexID();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};