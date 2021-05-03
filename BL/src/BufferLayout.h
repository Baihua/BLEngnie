#pragma once
#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;
	static unsigned int GetTypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		}
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout();
	~BufferLayout();
	template<typename T>
	void push(unsigned int count){
		ASSERT(false)
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, false });
		m_Stride += count*4;
	}
	inline unsigned int GetStride()const { return m_Stride; }
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
};

