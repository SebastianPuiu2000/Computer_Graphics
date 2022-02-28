#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/Camera.h"
#include <lab_m1/Tema2/Character3D.h>
#include <lab_m1/Tema2/Utils.h>
#include <lab_m1/Tema2/Transform3D.h>
#include <lab_m1/Tema2/Wall3D.h>
#include <lab_m1/Tema2/Ground3D.h>
#include <lab_m1/Tema2/EnemyInfo.h>

#include <Core/GPU/Mesh.h>
#include "components/transform.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;


        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear);


        void DrawScene(float deltaTimeSeconds);
        void DrawUI(float deltaTimeSeconds);


        void CheckEndGame();
        void RenderMaze();
        void RenderGround();
        void RenderProjectile(float deltaTime);
        void CameraAvoidWall();


        void CharacterSpawner();
        void RenderCharacter(float deltaTime);
        void RenderCharacterBodyPart(Mesh* bodyPart, float offsetX, float offsetY, float offsetZ, float deltaTime, glm::string bodyPartName);

        void RenderUI(float deltaTime);
        void RenderUIPart(Mesh* bodyPart, float offsetX, float offsetY, float offsetZ, float deltaTime, glm::string bodyPartName);


        void EnemySpawner();
        void RenderAllEnemies();
        void RenderOneEnemy(float& pozX, float& pozY, float& pozZ, float startX, float endX, float startZ, float endZ);
        void RenderEnemyBodyPart(Mesh* bodyPart, float offsetX, float offsetY, float size, float enemyX, float enemyY, glm::string bodyPartName);


        void GenerateMaze(char* maze, int width, int height);
        void CarveMaze(char* maze, int width, int height, int x, int y);
        void ShowMaze(char* maze, int width, int height);
        

        bool CheckCameraWallCollision(float cameraHitboxX, float cameraHitBoxY, float cameraHitBoxZ, float cameraHitboxR, float wallMaxX, float wallMinX, float wallMaxY, float wallMinY, float wallMaxZ, float wallMinZ);
        bool CheckCameraAllWallsCollision();
        bool CheckProjectileEnemyCollision(float enemyX, float enemyY, float enemyZ, float enemyR, float projectileX, float projectileY, float projectileZ, float projectileR);
        bool CheckCharacterAllWallsCollision(glm::vec3 targetPosition);
        bool CheckCharacterWallCollision(float characterHitboxX, float characterHitBoxY, float characterHitBoxZ, float characterHitboxR, float wallMaxX, float wallMinX, float wallMaxY, float wallMinY, float wallMaxZ, float wallMinZ);
        bool CheckProjectileAllWallsCollision(glm::vec3 targetPosition);
        bool CheckProjectileOneWallCollision(float projectileX, float projectileY, float projectileZ, float characterHitboxR, float wallMaxX, float wallMinX, float wallMaxY, float wallMinY, float wallMaxZ, float wallMinZ);
        bool CheckCharacterEnemyCollision(float enemyX, float enemyY, float enemyZ, float enemyR, float characterX, float characterY, float characterZ, float characterR);


        void RenderAnimatedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void RenderMeshUI(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;


    protected:
        implemented::Camera* camera;
        implemented::Camera* cameraUI;
        glm::mat4 projectionMatrix;

        float projectileRadius;
        float projectileScaleFactor;
       

        float distanceToTarget;

        bool isCameraRotating;
        float reverseFirstPersonRotation;
        float reverseThirdPersonRotation;
        

        int maze_width;
        int maze_height;
        char *maze;


        float angleX;
        float angleY;
        float angleZ;

        Character3D* character;

        glm::mat4 modelMatrix, visMatrix;


        float characterX;
        float characterY;
        float characterZ;

        int wallX;
        int wallY;
        int wallZ;

        Wall3D* wall;

        Ground3D* ground;


        float scaleFactorHealthBarX;
        float scaleFactorTimerBarX;

        

        glm::vec3 oldPosition;
        glm::vec3 oldForward;
        float oldDistanceToTarget;

        bool projectileFire;
        float projectileTimer;

        glm::vec3 projectilePosition;


        glm::string verticalDirection;
        glm::string horizontalDirection;

        int numberOfEnemies;
        EnemyInfo *enemiesInfo;


        float left;
        float right;
        float bottom;
        float top;
        float zNear;
        float zFar;
        float fov;

        ViewportSpace viewSpace;

        bool thirdPersonMode;

        float cellSize;

        float maxDistanceToTarget;

        float UI_X;
        float UI_Y;
        float UI_Height;
        float UI_Width;

    };
}   // namespace m1
