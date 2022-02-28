#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


class RenderInfo
{
public:

	RenderInfo();

	RenderInfo(float x, float y,  float a, float b);


	float translateX;
	float translateY;
	float height;
	float width;


};
