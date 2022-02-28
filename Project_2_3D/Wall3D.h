#pragma once

#include "components/simple_scene.h"

#include "Utils.h"

class Wall3D
{
public:
	Wall3D();
	~Wall3D();

	Mesh* GetWallMesh();

private:
	

	Mesh* mWall;
	
};