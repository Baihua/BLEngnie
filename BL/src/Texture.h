#pragma once
#include<string>

class Texture
{
public:
	Texture(const std::string path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline unsigned int GetWidth() { return m_Width; }

private:
	unsigned int m_RenderID;
	std::string m_PathFile;
	int m_Width, m_Height, m_BPP;
	unsigned char* m_LocalBuffer;
};
