#pragma once

#include<glm/glm.hpp>
#include<vector>
class Texture;
class VertexBuffer;
class VertexArray;
class IndexBuffer;
class BufferLayout;
class Shader;
class Texture;

class Mesh
{
public:
	Mesh();
	~Mesh();
	void AddVertex(const glm::vec3& v);
	void AddNormal(const glm::vec3& n);
	void AddTexCoord(const glm::vec2& t);
	void AddIndex(int i);
	void SetupMesh();
private:
	
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec3> m_Colors;
	std::vector<glm::vec3> m_Normals;
	std::vector<glm::vec2> m_TexCoords;
	std::vector<unsigned int> m_Indices;

	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<VertexArray>  m_VAO;
	std::unique_ptr<IndexBuffer>  m_IBO;
	std::unique_ptr<BufferLayout> m_BufferLayout;
};

