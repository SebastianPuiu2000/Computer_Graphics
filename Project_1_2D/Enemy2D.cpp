#include "Enemy2D.h"

Enemy2D::Enemy2D() :
	enemyHeadSize(0.4f),
	enemyHandSize(0.2f),
	numEnemyTriangles(50)
{

	{
		mEnemyHead = new Mesh("enemy_head");

		glm::vec3 corner = glm::vec3 (0, 0, 0);
		glm::vec3 color = glm::vec3(1, 0, 0);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(enemyHeadSize, 0, 0), color),
			VertexFormat(corner + glm::vec3(enemyHeadSize, enemyHeadSize, 0), color),
			VertexFormat(corner + glm::vec3(0, enemyHeadSize, 0), color)
		};

		std::vector<unsigned int> indices = { 0, 1, 2, 3 };

		
		indices.push_back(0);
		indices.push_back(2);
		
		mEnemyHead->InitFromData(vertices, indices);

		enemyHeadOffsetX = 0.f;
		enemyHeadOffsetY = 0.f;
	}

	{
		mEnemyRHand = new Mesh("enemy_rightHand");

		glm::vec3 corner = glm::vec3(0, 0, 0);
		glm::vec3 color = glm::vec3(0.4, 0, 0);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(enemyHandSize, 0, 0), color),
			VertexFormat(corner + glm::vec3(enemyHandSize, enemyHandSize, 0), color),
			VertexFormat(corner + glm::vec3(0, enemyHandSize, 0), color)
		};

		std::vector<unsigned int> indices = { 0, 1, 2, 3 };


		indices.push_back(0);
		indices.push_back(2);

		mEnemyRHand->InitFromData(vertices, indices);

		enemyRightHandOffsetX = -0.1f;
		enemyRightHandOffsetY = 0.3f;
	}

	{
		mEnemyLHand = new Mesh("enemy_leftHand");

		glm::vec3 corner = glm::vec3(0, 0, 0);
		glm::vec3 color = glm::vec3(0.4, 0, 0);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(enemyHandSize, 0, 0), color),
			VertexFormat(corner + glm::vec3(enemyHandSize, enemyHandSize, 0), color),
			VertexFormat(corner + glm::vec3(0, enemyHandSize, 0), color)
		};

		std::vector<unsigned int> indices = { 0, 1, 2, 3 };


		indices.push_back(0);
		indices.push_back(2);

		mEnemyLHand->InitFromData(vertices, indices);

		enemyLeftHandOffsetX = -0.1f;
		enemyLeftHandOffsetY = -0.1f;
	}

	
}

Mesh* Enemy2D::GetEnemyHeadMesh(float& offsetX, float& offsetY)
{
	offsetX = enemyHeadOffsetX;
	offsetY = enemyHeadOffsetY;

	return mEnemyHead;
}

Mesh* Enemy2D::GetEnemyLeftHandMesh(float& offsetX, float& offsetY)
{
	offsetX = enemyLeftHandOffsetX;
	offsetY = enemyLeftHandOffsetY;

	return mEnemyLHand;
}

Mesh* Enemy2D::GetEnemyRightHandMesh(float& offsetX, float& offsetY)
{
	offsetX = enemyRightHandOffsetX;
	offsetY = enemyRightHandOffsetY;

	return mEnemyRHand;
}

float Enemy2D::GetEnemyHeadSize()
{
	return enemyHeadSize;
}

float Enemy2D::GetEnemyHandSize()
{
	return enemyHandSize;
}


