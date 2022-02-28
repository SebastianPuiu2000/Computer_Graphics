#pragma once

#include "components/simple_scene.h"

#include "Utils.h"

class Ground3D
{
public:
	Ground3D();
	~Ground3D();

	Mesh* GetGroundMesh();

private:
	

	Mesh* mGround;
	
};