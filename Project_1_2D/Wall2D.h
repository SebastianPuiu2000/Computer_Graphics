#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


class Wall2D
{
public:

	Wall2D();

	Wall2D(float x, float y, std::string z, float a, float b, bool f, glm::vec3 c);

	Mesh* CreateWall();

	void SetColorRed();

	float translateX;
	float translateY;
	std::string name;
	float height;
	float width;
	glm::vec3 leftBottomCorner;
	glm::vec3 color;
	bool fill;
};
