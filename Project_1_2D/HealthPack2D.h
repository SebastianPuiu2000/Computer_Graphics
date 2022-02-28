#pragma once

#include <core/engine.h>
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"
#include <core/gpu/mesh.h>
#include <vector>

#include "components/simple_scene.h"

class HealthPack2D
{
public:
	HealthPack2D();
	~HealthPack2D();

	Mesh* GetHealthPackBoxMesh(float& offsetX, float& offsetY);
	Mesh* GetHealthPackVerticalBarMesh(float& offsetX, float& offsetY);
	Mesh* GetHealthPackHorizontalBarMesh(float& offsetX, float& offsetY);
	
	float boxWidth;
	float boxHeight;

	float hBarWidth;
	float hBarHeight;

	float vBarWidth;
	float vBarHeight;

private:

	Mesh* mBox;
	Mesh* mVerticalBar;
	Mesh* mHorizontalBar;

	float boxOffsetX, boxOffsetY;
	float verticalBarOffsetX, verticalBarOffsetY;
	float horizontalBarOffsetX, horizontalBarOffsetY;

	

};
