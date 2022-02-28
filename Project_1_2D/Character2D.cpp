#include "Character2D.h"

Character2D::Character2D() :
	characterHeadRadius(0.3f),
	characterHandRadius(0.1f),
	characterBackpackRadius(0.26f),
	numCharacterTriangles(60)
{
	float x;

	{
		mCharacterHead = new Mesh("character_head");

		std::vector<VertexFormat> vertices;
		std::vector<unsigned int> indices;

		vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.9f, 0.5f));

		for (GLushort i = 0; i < numCharacterTriangles; ++i)
		{
			x = 2.0f * (GLfloat)M_PI * i / numCharacterTriangles;

			vertices.emplace_back(
				glm::vec3(cos(x) * characterHeadRadius, sin(x) * characterHeadRadius, 0),
				glm::vec3(1.f, 0.9f, 0.5f));
			indices.push_back(i);
		}
		indices.push_back(numCharacterTriangles);
		indices.push_back(1);

		mCharacterHead->InitFromData(vertices, indices);
		mCharacterHead->SetDrawMode(GL_TRIANGLE_FAN);

		characterHeadOffsetX = 0.f;
		characterHeadOffsetY = 0.f;
	}

	{
		mCharacterRHand = new Mesh("character_rightHand");

		std::vector<VertexFormat> vertices;
		std::vector<unsigned int> indices;

		vertices.emplace_back(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(1.f, 0.9f, 0.5f));

		for (GLushort i = 0; i < numCharacterTriangles; ++i)
		{
			x = 2.0f * (GLfloat)M_PI * i / numCharacterTriangles;

			vertices.emplace_back(
				glm::vec3(cos(x) * characterHandRadius, sin(x) * characterHandRadius, 0),
				glm::vec3(0.f, 0.f, 0.f));
			indices.push_back(i);
		}
		indices.push_back(numCharacterTriangles);
		indices.push_back(1);

		mCharacterRHand->InitFromData(vertices, indices);
		mCharacterRHand->SetDrawMode(GL_TRIANGLE_FAN);

		characterRightHandOffsetX = 0.28f;
		characterRightHandOffsetY = -0.2f;
	}

	{
		mCharacterLHand = new Mesh("character_leftHand");

		std::vector<VertexFormat> vertices;
		std::vector<unsigned int> indices;

		vertices.emplace_back(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(1.f, 0.9f, 0.5f));

		for (GLushort i = 0; i < numCharacterTriangles; ++i)
		{
			x = 2.0f * (GLfloat)M_PI * i / numCharacterTriangles;

			vertices.emplace_back(
				glm::vec3(cos(x) * characterHandRadius, sin(x) * characterHandRadius, 0),
				glm::vec3(0.f, 0.f, 0.f));
			indices.push_back(i);
		}
		indices.push_back(numCharacterTriangles);
		indices.push_back(1);

		mCharacterLHand->InitFromData(vertices, indices);
		mCharacterLHand->SetDrawMode(GL_TRIANGLE_FAN);

		characterLeftHandOffsetX = 0.28f;
		characterLeftHandOffsetY = 0.2f;
	}

	{
		mCharacterBackpack = new Mesh("character_backpack");

		std::vector<VertexFormat> vertices;
		std::vector<unsigned int> indices;

		vertices.emplace_back(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.4f, 1.f, 0.3f));

		for (GLushort i = 0; i < numCharacterTriangles; ++i)
		{
			x = 2.0f * (GLfloat)M_PI * i / numCharacterTriangles;

			vertices.emplace_back(
				glm::vec3(cos(x) * characterBackpackRadius, sin(x) * characterBackpackRadius, 0),
				glm::vec3(0.f, 0.f, 0.f));
			indices.push_back(i);
		}
		indices.push_back(numCharacterTriangles);
		indices.push_back(1);

		mCharacterBackpack->InitFromData(vertices, indices);
		mCharacterBackpack->SetDrawMode(GL_TRIANGLE_FAN);

		characterBackpackOffsetX = -0.18f;
		characterBackpackOffsetY = 0.f;
	}
}

Mesh* Character2D::GetCharacterHeadMesh(float& offsetX, float& offsetY)
{
	offsetX = characterHeadOffsetX;
	offsetY = characterHeadOffsetY;

	return mCharacterHead;
}

Mesh* Character2D::GetCharacterLeftHandMesh(float& offsetX, float& offsetY)
{
	offsetX = characterLeftHandOffsetX;
	offsetY = characterLeftHandOffsetY;

	return mCharacterLHand;
}

Mesh* Character2D::GetCharacterRightHandMesh(float& offsetX, float& offsetY)
{
	offsetX = characterRightHandOffsetX;
	offsetY = characterRightHandOffsetY;

	return mCharacterRHand;
}

Mesh* Character2D::GetCharacterBackpackMesh(float& offsetX, float& offsetY)
{
	offsetX = characterBackpackOffsetX;
	offsetY = characterBackpackOffsetY;

	return mCharacterBackpack;
}
