#pragma once

#include<glm/glm.hpp>
#include<vector>
class Texture;


class Mesh
{
public:
	Mesh();
	~Mesh();
	bool LoadObj(const char* path);
private:
	
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec3> m_Colors;
	std::vector<glm::vec3> m_Normals;
	std::vector<glm::vec3> m_TexCoords;
	std::vector<unsigned int> m_Indices;
	//std::vector<Texture> m_Textures;
};

