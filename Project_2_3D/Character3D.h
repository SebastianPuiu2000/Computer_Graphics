#pragma once

#include "components/simple_scene.h"

#include "Utils.h"

class Character3D
{
public:
	Character3D();
	~Character3D();


	Mesh* GetCharacterHeadMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterBodyMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterLeftHandMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterRightHandMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterLeftArmMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterRightArmMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterLeftFootMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterRightFootMesh(float& offsetX, float& offsetY, float& offsetZ);


	Mesh* GetCharacterHealthBarMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterHealthBarFrameMesh(float& offsetX, float& offsetY, float& offsetZ);

	Mesh* GetCharacterTimerBarMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterTimerBarFrameMesh(float& offsetX, float& offsetY, float& offsetZ);

	Mesh* GetCharacterBackpackMesh(float& offsetX, float& offsetY, float& offsetZ);

	Mesh* GetCharacterLeftBraceMesh(float& offsetX, float& offsetY, float& offsetZ);
	Mesh* GetCharacterRightBraceMesh(float& offsetX, float& offsetY, float& offsetZ);


private:
	float offsetHeadX, offsetHeadY, offsetHeadZ;

	float offsetBodyX, offsetBodyY, offsetBodyZ;

	float offsetLeftHandX, offsetLeftHandY, offsetLeftHandZ;
	float offsetRightHandX, offsetRightHandY, offsetRightHandZ;

	float offsetLeftArmX, offsetLeftArmY, offsetLeftArmZ;
	float offsetRightArmX, offsetRightArmY, offsetRightArmZ;
	
	float offsetLeftFootX, offsetLeftFootY, offsetLeftFootZ;
	float offsetRightFootX, offsetRightFootY, offsetRightFootZ;

	float offsetHealthBarX, offsetHealthBarY, offsetHealthBarZ;
	Mesh* mHealthBar;

	float offsetHealthBarFrameX, offsetHealthBarFrameY, offsetHealthBarFrameZ;
	Mesh* mHealthBarFrame;

	float offsetTimerBarX, offsetTimerBarY, offsetTimerBarZ;
	Mesh* mTimerBar;

	float offsetTimerBarFrameX, offsetTimerBarFrameY, offsetTimerBarFrameZ;
	Mesh* mTimerBarFrame;

	float offsetBackpackX, offsetBackpackY, offsetBackpackZ;
	Mesh* mBackpack;

	float offsetLeftBraceX, offsetLeftBraceY, offsetLeftBraceZ;
	Mesh* mLeftBrace;

	float offsetRightBraceX, offsetRightBraceY, offsetRightBraceZ;
	Mesh* mRightBrace;

	Mesh* mHead;
	Mesh* mBody;
	Mesh* mLeftHand;
	Mesh* mRightHand;
	Mesh* mLeftArm;
	Mesh* mRightArm;
	Mesh* mLeftFoot;
	Mesh* mRightFoot;
};