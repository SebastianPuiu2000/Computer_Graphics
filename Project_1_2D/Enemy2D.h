#pragma once

#include <core/engine.h>
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"
#include <core/gpu/mesh.h>
#include <vector>

#include "components/simple_scene.h"

class Enemy2D
{
	public:
		Enemy2D();
		~Enemy2D();

		Mesh* GetEnemyHeadMesh(float& offsetX, float& offsetY);
		Mesh* GetEnemyLeftHandMesh(float& offsetX, float& offsetY);
		Mesh* GetEnemyRightHandMesh(float& offsetX, float& offsetY);
		float GetEnemyHeadSize();
		float GetEnemyHandSize();
		

		float enemyHeadSize;
		float enemyHandSize;

	private:
		
		short numEnemyTriangles;

		Mesh* mEnemyHead;
		Mesh* mEnemyLHand;
		Mesh* mEnemyRHand;
		

		float enemyHeadOffsetX, enemyHeadOffsetY;
		float enemyLeftHandOffsetX, enemyLeftHandOffsetY;
		float enemyRightHandOffsetX, enemyRightHandOffsetY;
};
