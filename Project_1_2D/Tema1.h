#pragma once

#include "components/simple_scene.h"
#include <lab_m1/Tema1/Character2D.h>
#include <lab_m1/Tema1/Enemy2D.h>
#include <lab_m1/Tema1/Wall2D.h>
#include <lab_m1/Tema1/RenderInfo.h>
#include <lab_m1/Tema1/HealthPack2D.h>
#include "lab_m1/Tema1/Transform2D.h"
#include "lab_m1/Tema1/Projectile2D.h"


#define TWO_PI			            (6.28318530718f)
#define NUM_TRIANGLES	            (50)
#define PROJECTILE_TIME_FACTOR      (100.f)
#define PROJECTILE_DISTANCE_FACTOR  (30.f)
#define STANDARD_RESOLUTION         (720.f)
#define OUT_OF_MAP                  (300.f)
#define SPAWN_TIME_FACTOR           (300.f)
#define DESPAWN_TIME_FACTOR         (500.f)
#define TOLERANCE                   (0.1f)
#define CHARACTER_RADIUS            (0.3f)
#define PROJECTILE_RADIUS           (0.11f)

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {

    public:
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


    public:
        Tema1();
        ~Tema1();

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

        void RenderCharacter(float deltaTime);
        void RenderEnemy(float deltaTime, float& enemyX, float& enemyY);

        void RenderEnemies(float deltaTime);

        void RenderEnemyBodyPart(Mesh* bodyPart, float offsetX, float offsetY, float size, float enemyX, float enemyY, glm::string bodyPartName);
        void RenderCharacterBodyPart(Mesh* bodyPart, float offsetX, float offsetY, float deltaTime);

        void RenderMap();

        void RenderObstacles(float deltaTime);

        void RenderHealthBar(float deltaTime);

        void RenderHealthPack();
        void RenderHealthPackPart(Mesh* part, float offsetX, float offsetY, float healthPackX, float healthPackY);

        void RenderProjectile(float deltaTime);

        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void DrawScene(float deltaTimeSeconds);
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

        bool CheckCollisionCharacterObject(float height, float width, float cornerX, float cornerY, float circleX, float circleY);

        bool CheckCollisionEnemyProjectile(float projectileX, float projectileY, float enemyX, float enemyY);
        bool CheckCollisionEnemyObstacle(float height, float width, float cornerX, float cornerY, float enemyX, float enemyY);

        bool CheckCollisionProjectileObstacles(float projectileX, float projectileY);
        bool CheckCollisionProjectileOneObstacle(float height, float width, float cornerX, float cornerY, float projectileX, float projectileY);

        bool CheckCollisionObstacleHealthPack(float healthPackX, float healthPackY, float healthPackWidth, float healthPackHeight, float obstacleX, float obstacleY, float obstacleWidth, float obstacleHeight);

        void EnemySpawner(float deltaTime);

        void HealthPackSpawner(float deltaTime);

        bool CheckCollisionProjectileObject(float height, float width, float cornerX, float cornerY, float circleX, float circleY);

    protected:

        Wall2D* height_wall;
        Wall2D* width_wall;

        float height1;
        float width1;

        float height2;
        float width2;

        float map_height;
        float map_width;

        int numEdgeWalls;

        RenderInfo renderedWalls[8];

        Wall2D* wall_0;
        Wall2D* wall_1;
        Wall2D* wall_2;
        Wall2D* wall_3;

        int numWalls;
        bool stopRandomise;


        HealthPack2D* healthPack;

        float healthPackWidth;
        float healthPackHeight;

        float healthPackTimer;
        float healthPackDespawnTimer;

        bool isHealthPackSpawned;

        float healthPackX;
        float healthPackY;

        bool canSpawnHealthPack;



        Character2D* character;

        float characterX;
        float characterY;

        int hitCounter;

        int score;

        bool characterHitObstacle;

        float mouseAngularStep;



        glm::vec3 projectileCorner;
        float projectileSize;

        float stepX, stepY;
        float endX, endY;
        float startX, startY;

        int projectileStartFlag;
        int projectileFire;
        
        float projectileSpeedFactor;
        float projectileTimeLimit;
        float projectileTimer;
        float projectileAngularStep;

        bool projectileHitEnemy;

        float projectileCooldown;

        bool projectileHit;


        Enemy2D* enemy;

        Enemy2D* enemies[5];
        float enemiesY[5];
        float enemiesX[5];
        bool isEnemyAlive[5];
        int numEnemies;

        bool canRenderEnemy;
        bool isEnemyDead;
        float enemySize;
        float enemyAngularStep;

        float enemySpeed[5];
        float enemySpeedFactor;
        float enemySpawnTimer;

        bool canSpawnEnemy;


        Wall2D* healthBar;
        Wall2D* fullHP;
        Wall2D* goodHP;
        Wall2D* halfHP;
        Wall2D* lowHP;

        float healthX, healthY;

        float resY, resX;

        float miniMapX;
        float miniMapY;
        float miniMapSide;

        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        LogicSpace logicSpaceMiniMap;
        glm::mat3 modelMatrix, visMatrix;


    };
}   // namespace m1
