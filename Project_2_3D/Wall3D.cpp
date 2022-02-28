#include "Wall3D.h"

Wall3D::Wall3D()
{
	
	/* Create the wall */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-2.f, -4.f, 2.f), glm::vec3(0.6f, 0.f, 0.4f)),
			VertexFormat(glm::vec3(2.f, -4.f, 2.f), glm::vec3(0.6f, 0.f, 0.4f)),
			VertexFormat(glm::vec3(-2.f, 4.f, 2.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(2.f, 4.f, 2.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-2.f, -4.f, -2.f), glm::vec3(0.6f, 0.f, 0.4f)),
			VertexFormat(glm::vec3(2.f, -4.f, -2.f), glm::vec3(0.6f, 0.f, 0.4f)),
			VertexFormat(glm::vec3(-2.f, 4.f, -2.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(2.f, 4.f, -2.f), glm::vec3(0.f, 0.f, 0.f))
		};

		std::vector<unsigned int> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		mWall = Utils::CreateMesh("wall", vertices, indices);
	}
}

Mesh* Wall3D::GetWallMesh()
{
	return mWall;
}