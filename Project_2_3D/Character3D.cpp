#include "Character3D.h"

Character3D::Character3D() :
	
	offsetBodyX(0.f), offsetBodyY(2.4f), offsetBodyZ(0.f),

	offsetBackpackX(0.f), offsetBackpackY(2.6f), offsetBackpackZ(0.415f),

	offsetLeftBraceX(-0.3f), offsetLeftBraceY(3.04f), offsetLeftBraceZ(0.1f),
	offsetRightBraceX(0.3f), offsetRightBraceY(3.04f), offsetRightBraceZ(0.1f),

	offsetHealthBarX(0.f), offsetHealthBarY(2.75f), offsetHealthBarZ(0.62f),
	offsetHealthBarFrameX(0.f), offsetHealthBarFrameY(2.75f), offsetHealthBarFrameZ(0.6f),

	offsetTimerBarX(0.f), offsetTimerBarY(2.45f), offsetTimerBarZ(0.62f),
	offsetTimerBarFrameX(0.f), offsetTimerBarFrameY(2.45f), offsetTimerBarFrameZ(0.6f),

	offsetHeadX(0.f), offsetHeadY(3.3f), offsetHeadZ(0.f),

	offsetLeftHandX(-0.6f), offsetLeftHandY(1.96f), offsetLeftHandZ(0.f),
	offsetRightHandX(0.6f), offsetRightHandY(1.96f), offsetRightHandZ(0.f),

	offsetLeftArmX(-0.6f), offsetLeftArmY(2.64f), offsetLeftArmZ(0.f),
	offsetRightArmX(0.6f), offsetRightArmY(2.64f), offsetRightArmZ(0.f),

	offsetLeftFootX(-0.24f), offsetLeftFootY(1.0f), offsetLeftFootZ(0.f),
	offsetRightFootX(0.24f), offsetRightFootY(1.0f), offsetRightFootZ(0.f)
{

	/* Create the character's body */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.4f, -0.7f, 0.4f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.7f, 0.4f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.7f, 0.4f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.7f, 0.4f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, -0.7f, -0.4f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.7f, -0.4f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.7f, -0.4f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.7f, -0.4f), glm::vec3(0.3f, 0.5f, 0.f))
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

		mBody = Utils::CreateMesh("body", vertices, indices);
	}

	/* Create the character's health_bar */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.4f, -0.1f, 0.01f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.1f, 0.01f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.1f, 0.01f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.1f, 0.01f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, -0.1f, -0.01f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.1f, -0.01f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.1f, -0.01f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.1f, -0.01f), glm::vec3(1.f, 0.f, 0.f))
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

		mHealthBar = Utils::CreateMesh("health_bar", vertices, indices);
	}

	/* Create the character's health_bar_frame */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.4f, -0.1f, 0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.1f, 0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.1f, 0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.1f, 0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, -0.1f, -0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.1f, -0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.1f, -0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.1f, -0.01f), glm::vec3(0.f, 0.f, 0.f))
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

		mHealthBarFrame = Utils::CreateMesh("health_bar_frame", vertices, indices);
	}


	/* Create the character's timer_bar */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.4f, -0.1f, 0.01f), glm::vec3(1.f, 0.6f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.1f, 0.01f), glm::vec3(1.f, 0.6f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.1f, 0.01f), glm::vec3(1.f, 0.6f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.1f, 0.01f), glm::vec3(1.f, 0.6f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, -0.1f, -0.01f), glm::vec3(1.f, 0.6f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.1f, -0.01f), glm::vec3(1.f, 0.6f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.1f, -0.01f), glm::vec3(1.f, 0.6f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.1f, -0.01f), glm::vec3(1.f, 0.6f, 0.f))
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

		mTimerBar = Utils::CreateMesh("timer_bar", vertices, indices);
	}

	/* Create the character's timer_bar_frame */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.4f, -0.1f, 0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.1f, 0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.1f, 0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.1f, 0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, -0.1f, -0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.1f, -0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.1f, -0.01f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.1f, -0.01f), glm::vec3(0.f, 0.f, 0.f))
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

		mTimerBarFrame = Utils::CreateMesh("timer_bar_frame", vertices, indices);
	}
	
	/* Create the character's head */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.2f, -0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.2f, -0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.2f, 0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.2f, -0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.2f, -0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.2f, 0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.2f, 0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f))
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

		mHead = Utils::CreateMesh("head", vertices, indices);
	}

	/* Create the character's left arm */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.16f, -0.46f, 0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.16f, -0.46f, 0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.16f, 0.46f, 0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.16f, 0.46f, 0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.16f, -0.46f, -0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.16f, -0.46f, -0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.16f, 0.46f, -0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.16f, 0.46f, -0.2f), glm::vec3(0.3f, 0.5f, 0.f))
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

		mLeftArm = Utils::CreateMesh("left_arm", vertices, indices);
	}

	/* Create the character's right arm */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.16f, -0.46f, 0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.16f, -0.46f, 0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.16f, 0.46f, 0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.16f, 0.46f, 0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.16f, -0.46f, -0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.16f, -0.46f, -0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(-0.16f, 0.46f, -0.2f), glm::vec3(0.3f, 0.5f, 0.f)),
			VertexFormat(glm::vec3(0.16f, 0.46f, -0.2f), glm::vec3(0.3f, 0.5f, 0.f))
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

		mRightArm = Utils::CreateMesh("right_arm", vertices, indices);
	}

	/* Create the character's left hand */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.16f, -0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.16f, -0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.16f, 0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.16f, 0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.16f, -0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.16f, -0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.16f, 0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.16f, 0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f))
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

		mLeftHand = Utils::CreateMesh("left_hand", vertices, indices);
	}

	/* Create the character's right hand */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.16f, -0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.16f, -0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.16f, 0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.16f, 0.2f, 0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.16f, -0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.16f, -0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(-0.16f, 0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f)),
			VertexFormat(glm::vec3(0.16f, 0.2f, -0.2f), glm::vec3(0.9f, 0.7f, 0.3f))
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

		mRightHand = Utils::CreateMesh("right_hand", vertices, indices);
	}

	/* Create the character's left foot */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.16f, -0.68f, 0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.16f, -0.68f, 0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-0.16f, 0.68f, 0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.16f, 0.68f, 0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-0.16f, -0.68f, -0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.16f, -0.68f, -0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-0.16f, 0.68f, -0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.16f, 0.68f, -0.2f), glm::vec3(0.f, 0.f, 1.f))
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

		mLeftFoot = Utils::CreateMesh("left_foot", vertices, indices);
	}

	/* Create the character's right foot */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.16f, -0.68f, 0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.16f, -0.68f, 0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-0.16f, 0.68f, 0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.16f, 0.68f, 0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-0.16f, -0.68f, -0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.16f, -0.68f, -0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-0.16f, 0.68f, -0.2f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.16f, 0.68f, -0.2f), glm::vec3(0.f, 0.f, 1.f))
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

		mRightFoot = Utils::CreateMesh("right_foot", vertices, indices);
	}


	/* Create the character's backpack */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.4f, -0.4f, 0.18f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.4f, 0.18f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.4f, 0.18f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.4f, 0.18f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, -0.4f, -0.18f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.4f, -0.4f, -0.18f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.4f, 0.4f, -0.18f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.4f, 0.4f, -0.18f), glm::vec3(0.3f, 0.1f, 0.f))
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

		mBackpack = Utils::CreateMesh("backpack", vertices, indices);
	}

	/* Create the character's backpack's left_brace */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.06f, -0.12f, 0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.06f, -0.12f, 0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.06f, 0.12f, 0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.06f, 0.12f, 0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.06f, -0.12f, -0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.06f, -0.12f, -0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.06f, 0.12f, -0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.06f, 0.12f, -0.4f), glm::vec3(0.3f, 0.1f, 0.f))
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

		mLeftBrace = Utils::CreateMesh("left_brace", vertices, indices);
	}

	/* Create the character's backpack's right_brace */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.06f, -0.12f, 0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.06f, -0.12f, 0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.06f, 0.12f, 0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.06f, 0.12f, 0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.06f, -0.12f, -0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.06f, -0.12f, -0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(-0.06f, 0.12f, -0.4f), glm::vec3(0.3f, 0.1f, 0.f)),
			VertexFormat(glm::vec3(0.06f, 0.12f, -0.4f), glm::vec3(0.3f, 0.1f, 0.f))
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

		mRightBrace = Utils::CreateMesh("right_brace", vertices, indices);
	}
	

}

Character3D::~Character3D()
{
	delete mHead;
	delete mBody;
	delete mLeftArm;
	delete mRightArm;
	delete mLeftHand;
	delete mRightHand;
	delete mLeftFoot;
	delete mRightFoot;
}


Mesh* Character3D::GetCharacterBodyMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetBodyX;
	offsetY = offsetBodyY;
	offsetZ = offsetBodyZ;

	return mBody;
}

Mesh* Character3D::GetCharacterHeadMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetHeadX;
	offsetY = offsetHeadY;
	offsetZ = offsetHeadZ;

	return mHead;
}

Mesh* Character3D::GetCharacterLeftHandMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetLeftHandX;
	offsetY = offsetLeftHandY;
	offsetZ = offsetLeftHandZ;

	return mLeftHand;
}

Mesh* Character3D::GetCharacterRightHandMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetRightHandX;
	offsetY = offsetRightHandY;
	offsetZ = offsetRightHandZ;

	return mRightHand;
}

Mesh* Character3D::GetCharacterLeftArmMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetLeftArmX;
	offsetY = offsetLeftArmY;
	offsetZ = offsetLeftArmZ;

	return mLeftArm;
}

Mesh* Character3D::GetCharacterRightArmMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetRightArmX;
	offsetY = offsetRightArmY;
	offsetZ = offsetRightArmZ;

	return mRightArm;
}

Mesh* Character3D::GetCharacterLeftFootMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetLeftFootX;
	offsetY = offsetLeftFootY;
	offsetZ = offsetLeftFootZ;

	return mLeftFoot;
}

Mesh* Character3D::GetCharacterRightFootMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetRightFootX;
	offsetY = offsetRightFootY;
	offsetZ = offsetRightFootZ;

	return mRightFoot;
}

Mesh* Character3D::GetCharacterHealthBarMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetHealthBarX;
	offsetY = offsetHealthBarY;
	offsetZ = offsetHealthBarZ;

	return mHealthBar;
}

Mesh* Character3D::GetCharacterHealthBarFrameMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetHealthBarFrameX;
	offsetY = offsetHealthBarFrameY;
	offsetZ = offsetHealthBarFrameZ;

	return mHealthBarFrame;
}

Mesh* Character3D::GetCharacterTimerBarMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetTimerBarX;
	offsetY = offsetTimerBarY;
	offsetZ = offsetTimerBarZ;

	return mTimerBar;
}

Mesh* Character3D::GetCharacterTimerBarFrameMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetTimerBarFrameX;
	offsetY = offsetTimerBarFrameY;
	offsetZ = offsetTimerBarFrameZ;

	return mTimerBarFrame;
}

Mesh* Character3D::GetCharacterBackpackMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetBackpackX;
	offsetY = offsetBackpackY;
	offsetZ = offsetBackpackZ;

	return mBackpack;
}

Mesh* Character3D::GetCharacterLeftBraceMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetLeftBraceX;
	offsetY = offsetLeftBraceY;
	offsetZ = offsetLeftBraceZ;

	return mLeftBrace;
}

Mesh* Character3D::GetCharacterRightBraceMesh(
	float& offsetX,
	float& offsetY,
	float& offsetZ
)
{
	offsetX = offsetRightBraceX;
	offsetY = offsetRightBraceY;
	offsetZ = offsetRightBraceZ;

	return mRightBrace;
}