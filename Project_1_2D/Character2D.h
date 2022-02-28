#pragma once

#include <core/engine.h>
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"
#include <core/gpu/mesh.h>
#include <vector>

#include "components/simple_scene.h"

class Character2D
{
	public:
		Character2D();
		~Character2D();

		Mesh* GetCharacterHeadMesh(float& offsetX, float& offsetY);
		Mesh* GetCharacterLeftHandMesh(float& offsetX, float& offsetY);
		Mesh* GetCharacterRightHandMesh(float& offsetX, float& offsetY);
		Mesh* GetCharacterBackpackMesh(float& offsetX, float& offsetY);

	private:
		float characterHeadRadius;
		float characterHandRadius;
		float characterBackpackRadius;
		short numCharacterTriangles;

		Mesh* mCharacterHead;
		Mesh* mCharacterLHand;
		Mesh* mCharacterRHand;
		Mesh* mCharacterBackpack;
		

		float characterHeadOffsetX, characterHeadOffsetY;
		float characterLeftHandOffsetX, characterLeftHandOffsetY;
		float characterRightHandOffsetX, characterRightHandOffsetY;
		float characterBackpackOffsetX, characterBackpackOffsetY;
};
