#include "HealthPack2D.h"

HealthPack2D::HealthPack2D() :
	boxWidth(0.8f),
	boxHeight(0.4f),
	hBarWidth(0.2f),
	hBarHeight(0.06f),
	vBarWidth(0.06f),
	vBarHeight(0.2f)
{
	
	{
		mBox = new Mesh("box");

		glm::vec3 corner = glm::vec3(0, 0, 0);
		glm::vec3 color = glm::vec3(0.4, 1, 0.4);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(boxWidth, 0, 0), color),
			VertexFormat(corner + glm::vec3(boxWidth, boxHeight, 0), color),
			VertexFormat(corner + glm::vec3(0, boxHeight, 0), color)
		};

		std::vector<unsigned int> indices = { 0, 1, 2, 3 };


		indices.push_back(0);
		indices.push_back(2);

		mBox->InitFromData(vertices, indices);

		boxOffsetX = 0.f;
		boxOffsetY = 0.f;
	}

	{
		mHorizontalBar = new Mesh("horizontalBar");

		glm::vec3 corner = glm::vec3(0, 0, 0);
		glm::vec3 color = glm::vec3(1, 1, 1);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(hBarWidth, 0, 0), color),
			VertexFormat(corner + glm::vec3(hBarWidth, hBarHeight, 0), color),
			VertexFormat(corner + glm::vec3(0, hBarHeight, 0), color)
		};

		std::vector<unsigned int> indices = { 0, 1, 2, 3 };


		indices.push_back(0);
		indices.push_back(2);

		mHorizontalBar->InitFromData(vertices, indices);

		horizontalBarOffsetX = 0.3f;
		horizontalBarOffsetY = 0.17f;
	}

	{
		mVerticalBar = new Mesh("verticalBar");

		glm::vec3 corner = glm::vec3(0, 0, 0);
		glm::vec3 color = glm::vec3(1, 1, 1);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(vBarWidth, 0, 0), color),
			VertexFormat(corner + glm::vec3(vBarWidth, vBarHeight, 0), color),
			VertexFormat(corner + glm::vec3(0, vBarHeight, 0), color)
		};

		std::vector<unsigned int> indices = { 0, 1, 2, 3 };


		indices.push_back(0);
		indices.push_back(2);

		mVerticalBar->InitFromData(vertices, indices);

		verticalBarOffsetX = 0.37f;
		verticalBarOffsetY = 0.1f;
	}

}

Mesh* HealthPack2D::GetHealthPackBoxMesh(float& offsetX, float& offsetY)
{
	offsetX = boxOffsetX;
	offsetY = boxOffsetY;

	return mBox;
}

Mesh* HealthPack2D::GetHealthPackVerticalBarMesh(float& offsetX, float& offsetY)
{
	offsetX = verticalBarOffsetX;
	offsetY = verticalBarOffsetY;

	return mVerticalBar;
}

Mesh* HealthPack2D::GetHealthPackHorizontalBarMesh(float& offsetX, float& offsetY)
{
	offsetX = horizontalBarOffsetX;
	offsetY = horizontalBarOffsetY;

	return mHorizontalBar;
}


