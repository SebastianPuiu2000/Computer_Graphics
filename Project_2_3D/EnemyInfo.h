#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


class EnemyInfo
{
public:

	EnemyInfo();

	EnemyInfo(bool alive, float x, float y, float z);


	float isAlive;
	float positionX;
	float positionY;
	float positionZ;

	float startX;
	float endX;

	float startZ;
	float endZ;

	float deathAnimationTimer;

};
