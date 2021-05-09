#include "Mesh.h"

#include<iostream>
#include <map>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"
#include<memory>
Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::AddVertex(const glm::vec3& v)
{
	m_Vertices.push_back(v);
}

void Mesh::AddNormal(const glm::vec3& n) 
{
	m_Normals.push_back(n);
}

void Mesh::AddTexCoord(const glm::vec2& t)
{
	m_TexCoords.push_back(t);
}

void Mesh::AddIndex(int i)
{
	m_Indices.push_back(i);
}

void Mesh::SetupMesh()
{
	std::vector<float> data;
	bool hasColor  = m_Vertices.size() == m_Colors.size();
	bool hasNormal = m_Vertices.size() == m_Normals.size();
	bool hasTexCoord = m_Vertices.size() == m_TexCoords.size();

	for (size_t i = 0; i < m_Vertices.size(); i++)
	{
		data.push_back(m_Vertices[i].x);
		data.push_back(m_Vertices[i].y);
		data.push_back(m_Vertices[i].z);
		if (hasColor)
		{
			data.push_back(m_Colors[i].x);
			data.push_back(m_Colors[i].y);
			data.push_back(m_Colors[i].z);
		}

		if (hasNormal)
		{
			data.push_back(m_Normals[i].x);
			data.push_back(m_Normals[i].y);
			data.push_back(m_Normals[i].z);
		}

		if (hasTexCoord)
		{
			data.push_back(m_TexCoords[i].x);
			data.push_back(m_TexCoords[i].y);
		}
	}
	
	m_VBO = std::make_unique<VertexBuffer>(data, sizeof(float)*data.size());
	m_IBO = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size());
	m_BufferLayout = std::make_unique<BufferLayout>();
	m_BufferLayout->push<float>(3);
	if (hasColor)
		m_BufferLayout->push<float>(3);

	if (hasNormal)
		m_BufferLayout->push<float>(3);

	if (hasTexCoord)
		m_BufferLayout->push<float>(2);

	m_VAO = std::make_unique<VertexArray>();
	
	m_VAO->AddBuffer(*m_VBO, *m_BufferLayout, *m_IBO);
}