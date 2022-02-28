#include "Ground3D.h"

Ground3D::Ground3D()
{

	/* Create the ground */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.5f, -0.01f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f)),
			VertexFormat(glm::vec3(0.5f, -0.01f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f)),
			VertexFormat(glm::vec3(-0.5f, 0.01f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f)),
			VertexFormat(glm::vec3(0.5f, 0.01f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f)),
			VertexFormat(glm::vec3(-0.5f, -0.01f, -0.5f), glm::vec3(0.1f, 0.1f, 0.1f)),
			VertexFormat(glm::vec3(0.5f, -0.01f, -0.5f), glm::vec3(0.1f, 0.1f, 0.1f)),
			VertexFormat(glm::vec3(-0.5f, 0.01f, -0.5f), glm::vec3(0.1f, 0.1f, 0.1f)),
			VertexFormat(glm::vec3(0.5f, 0.01f, -0.5f), glm::vec3(0.1f, 0.1f, 0.1f))
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

		mGround = Utils::CreateMesh("ground", vertices, indices);
	}
}

Mesh* Ground3D::GetGroundMesh()
{
	return mGround;
}