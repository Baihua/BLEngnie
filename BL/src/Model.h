#pragma once
#include <vector>
#include <memory>
class Mesh;

class Renderer;
class Model
{
public:
	Model();
	~Model();
	bool LoadObj(const char* path);
private:

	glm::mat4 m_View;
	glm::mat4 m_Proj;
	glm::vec3 m_Postion;
};

