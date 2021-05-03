#pragma once
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"
//#include "BufferLayout.h"
class VertexBuffer;
class BufferLayout;
class IndexBuffer;
class VertexArray
{
private:
	unsigned int m_RenderID;

public:
	VertexArray();  
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout, const IndexBuffer& ib);
};

