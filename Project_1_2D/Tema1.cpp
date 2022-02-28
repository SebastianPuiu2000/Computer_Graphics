#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>



using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


float maxi(float a, float b) {
    if (a > b)
        return a;
    else
        return b;
}

float mini(float a, float b) {
    if (a < b)
        return a;
    else
        return b;
}

float clamp(float value, float min, float max) {
    return maxi(min, mini(max, value));
}



Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0; 
    logicSpace.y = 0; 
    logicSpace.width = 4;  
    logicSpace.height = 4; 

    logicSpaceMiniMap.x = 0;   
    logicSpaceMiniMap.y = 0;    
    logicSpaceMiniMap.width = 10;  
    logicSpaceMiniMap.height = 10; 


    
    character = new Character2D();
    enemy = new Enemy2D();

    for (int j = 0; j < 5; j++) {
        enemies[j] = new Enemy2D();
        isEnemyAlive[j] = false;
        enemiesX[j] = OUT_OF_MAP;
        enemiesY[j] = OUT_OF_MAP;
    }

    // PROJECTILE

    projectileCorner = glm::vec3(0.0, 0.0, 0);
    projectileSize = 0.2f;

    Mesh* square = Projectile2D::CreateSquare("square", projectileCorner, projectileSize, glm::vec3(0, 0, 0), true);
    AddMeshToList(square);

    /////////////////////


    // MAP

    width1 = 0.2f;
    height1 = 10.f;

    map_height = height1;

    width2 = 10.f;
    height2 = 0.2f;

    map_width = width2;
    

    height_wall = new Wall2D(width1, height1, "height_wall", 0, 0, true, glm::vec3(1, 0.6, 0));
    AddMeshToList(height_wall->CreateWall());
    width_wall = new Wall2D(width2, height2, "width_wall", 1, 1, true, glm::vec3(1, 0.6, 0));
    AddMeshToList(width_wall->CreateWall());

  
    wall_0 = new Wall2D(4.f, 0.5f, "wall_0", 0, 0, 1, glm::vec3(0.6f, 0.6f, 0.6f));
    wall_1 = new Wall2D(1.f, 4.f, "wall_1", 0, 0, 1, glm::vec3(0.6f, 0.6f, 0.6f));
    wall_2 = new Wall2D(2.f, 2.f, "wall_2", 0, 0, 1, glm::vec3(0.6f, 0.6f, 0.6f));
    wall_3 = new Wall2D(2.f, 1.f, "wall_3", 0, 0, 1, glm::vec3(0.6f, 0.6f, 0.6f));

    
    AddMeshToList(wall_0->CreateWall());
    AddMeshToList(wall_1->CreateWall());
    AddMeshToList(wall_2->CreateWall());
    AddMeshToList(wall_3->CreateWall());

    /////////////////

    // HEALTH_BAR

    healthBar = new Wall2D(0.6f, 0.1f, "health", 0, 0, 0, glm::vec3(0, 0, 0));
    AddMeshToList(healthBar->CreateWall());

    fullHP = new Wall2D(0.6f, 0.1f, "fullHP", 0, 0, 1, glm::vec3(0.6, 1, 0));
    AddMeshToList(fullHP->CreateWall());

    goodHP = new Wall2D(0.45f, 0.1f, "goodHP", 0, 0, 1, glm::vec3(0.9, 1, 0));
    AddMeshToList(goodHP->CreateWall());

    halfHP = new Wall2D(0.3f, 0.1f, "halfHP", 0, 0, 1, glm::vec3(1, 0.5, 0));
    AddMeshToList(halfHP->CreateWall());

    lowHP = new Wall2D(0.15f, 0.1f, "lowHP", 0, 0, 1, glm::vec3(1, 0, 0));
    AddMeshToList(lowHP->CreateWall());
    

    ///////////////////////////////

  

    projectileFire = false;

    projectileStartFlag = true;

    projectileHit = false;

    projectileTimeLimit = 5000.f;


    characterX = 2.f;
    characterY = 2.f;

    mouseAngularStep = 0;

    healthX = 1.7f;
    healthY = 2.6f;

    canRenderEnemy = true;

    isEnemyDead = true;

    hitCounter = 0;

    enemySize = 0.4f;

    score = 0;
    enemySpawnTimer = 0;

    numEnemies = 5;

    numWalls = 8;

    numEdgeWalls = 4;

    healthPack = new HealthPack2D();

    healthPackX = 1.f;
    healthPackY = 1.f;

    healthPackWidth = 0.8f;
    healthPackHeight = 0.4f;

    isHealthPackSpawned = false;
    healthPackTimer = 0;

    stopRandomise = false;

    miniMapX = 20.f;
    miniMapY = 20.f;
    miniMapSide = 200.f;
    
}


glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

}


void Tema1::Update(float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();
    resY = resolution.y;
    resX = resolution.x;

    if (hitCounter > 3) {

        viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
        SetViewportArea(viewSpace, glm::vec3(0, 0, 0), true);

        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

        cout << endl << "Final score : " << score << endl;

        exit(0);
    }
    else {

        // GENERATE SCENE

        viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
        SetViewportArea(viewSpace, glm::vec3(0.2, 0.2, 0.5), true);

        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
        DrawScene(deltaTimeSeconds);

        // GENERATE MINI_MAP

        viewSpace = ViewportSpace(miniMapX, miniMapY, miniMapSide, miniMapSide);
        SetViewportArea(viewSpace, glm::vec3(0.2f), true);

        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpaceMiniMap, viewSpace);
        DrawScene(deltaTimeSeconds);


      
    }
}

void Tema1::DrawScene(float deltaTimeSeconds) {

    HealthPackSpawner(deltaTimeSeconds);

    EnemySpawner(deltaTimeSeconds);

    RenderProjectile(deltaTimeSeconds);

    RenderHealthBar(deltaTimeSeconds);

    RenderMap();

    RenderCharacter(deltaTimeSeconds);

    RenderEnemies(deltaTimeSeconds);

    RenderObstacles(deltaTimeSeconds);

    RenderHealthPack();
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{

    
    if (window->KeyHold(GLFW_KEY_W)) {

        characterHitObstacle = false;

        for (int j = 0; j < numWalls; j++) {

            if (CheckCollisionCharacterObject(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, characterX, characterY + deltaTime))
                characterHitObstacle = true;
        }

        if (!characterHitObstacle) {

            characterY = characterY + deltaTime;

            healthY = healthY + deltaTime;

            logicSpace.y = logicSpace.y + deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {

        characterHitObstacle = false;

        for (int j = 0; j < numWalls; j++) {

            if (CheckCollisionCharacterObject(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, characterX, characterY - deltaTime))
                characterHitObstacle = true;
        }

        if (!characterHitObstacle) {

            characterY = characterY - deltaTime;

            healthY = healthY - deltaTime;

            logicSpace.y = logicSpace.y - deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {

        characterHitObstacle = false;

        for (int j = 0; j < numWalls; j++) {

            if (CheckCollisionCharacterObject(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, characterX + deltaTime, characterY))
                characterHitObstacle = true;
        }

        if (!characterHitObstacle) {

            characterX = characterX + deltaTime;

            healthX = healthX + deltaTime;

            logicSpace.x = logicSpace.x + deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {

        characterHitObstacle = false;

        for (int j = 0; j < numWalls; j++) {

            if (CheckCollisionCharacterObject(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, characterX - deltaTime, characterY))
                characterHitObstacle = true;
        }

        if (!characterHitObstacle) {

            characterX = characterX - deltaTime;

            healthX = healthX - deltaTime;

            logicSpace.x = logicSpace.x - deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_Z)) {


        logicSpace.x = logicSpace.x - deltaTime;
        logicSpace.y = logicSpace.y - deltaTime;

        logicSpace.width = logicSpace.width + deltaTime * 2;
        logicSpace.height = logicSpace.height + deltaTime * 2;
    }

    if (window->KeyHold(GLFW_KEY_X)) {

        logicSpace.x = logicSpace.x + deltaTime;
        logicSpace.y = logicSpace.y + deltaTime;

        logicSpace.width = logicSpace.width - deltaTime * 2;
        logicSpace.height = logicSpace.height - deltaTime * 2;
    }

    

}


void Tema1::OnKeyPress(int key, int mods)
{
   
}


void Tema1::OnKeyRelease(int key, int mods)
{

}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    endY = (float)(logicSpace.height / STANDARD_RESOLUTION) * (resY - mouseY) - (float)((resY - STANDARD_RESOLUTION) / 2) * (float)(logicSpace.height / STANDARD_RESOLUTION) + logicSpace.y;
    endX = (float)(logicSpace.width / STANDARD_RESOLUTION) * mouseX - (float)((resX - STANDARD_RESOLUTION) / 2) * (float)(logicSpace.width / STANDARD_RESOLUTION) + logicSpace.x;

    mouseAngularStep = atan2((endY - characterY) , (endX - characterX));
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
  
    if (button == GLFW_MOUSE_BUTTON_RIGHT && projectileStartFlag == true) {

        startX = characterX;
        startY = characterY;


        endY = (float)(logicSpace.height / STANDARD_RESOLUTION) * (resY - mouseY) - (float)((resY - STANDARD_RESOLUTION) / 2) * (float)(logicSpace.height / STANDARD_RESOLUTION) + logicSpace.y;
        endX = (float)(logicSpace.width / STANDARD_RESOLUTION) * mouseX - (float) ((resX - STANDARD_RESOLUTION) / 2) * (float) (logicSpace.width / STANDARD_RESOLUTION) + logicSpace.x;

        projectileAngularStep = atan2((endY - characterY), (endX - characterX));

        projectileFire = true;
                
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}


void Tema1::HealthPackSpawner(float deltaTime) {


    if (healthPackTimer < SPAWN_TIME_FACTOR * deltaTime) {
        healthPackTimer += deltaTime;
    }
    else
    {
        if (isHealthPackSpawned == false) {

            canSpawnHealthPack = true;

            float a = map_width - 2;
            float b = map_height - 2;

            healthPackX = 2 + (float(rand()) / float((RAND_MAX)) * a);
            healthPackY = 2 + (float(rand()) / float((RAND_MAX)) * b);

            for (int j = 0; j < numWalls; j++) {
                if (CheckCollisionObstacleHealthPack(healthPackX, healthPackY, healthPackWidth, healthPackHeight, renderedWalls[j].translateX, renderedWalls[j].translateY, renderedWalls[j].width, renderedWalls[j].height)) {
                    canSpawnHealthPack = false;
                    break;
                }
            }

            if (CheckCollisionCharacterObject(healthPackWidth, healthPackHeight, healthPackX, healthPackY, characterX, characterY)) {
                canSpawnHealthPack = false;
            }

            if (canSpawnHealthPack == true) {
                isHealthPackSpawned = true;
                healthPackDespawnTimer = 0;
            }
            else {
                isHealthPackSpawned = false;
                healthPackTimer = 0;
            }
        }

        if (isHealthPackSpawned == true) {


            if (healthPackDespawnTimer > DESPAWN_TIME_FACTOR * deltaTime) {
                healthPackX = OUT_OF_MAP;
                healthPackY = OUT_OF_MAP;
                isHealthPackSpawned = false;
                healthPackTimer = 0;
            }
            healthPackDespawnTimer += deltaTime;

        }
    }

}

void Tema1::EnemySpawner(float deltaTime) {

    for (int j = 0; j < numEnemies; j++) {

        if (enemySpawnTimer < SPAWN_TIME_FACTOR * deltaTime) {
            enemySpawnTimer += deltaTime;
            break;
        }
        else
            if (isEnemyAlive[j] == false) {

                canSpawnEnemy = true;

                enemySpeedFactor = 2 + rand() % 3;
                enemySpeed[j] = deltaTime - deltaTime / enemySpeedFactor;

                float a = (map_width - 2) - 2;
                float b = (map_height - 2) - 2;

                enemiesX[j] = 2 + (float(rand()) / float((RAND_MAX)) * a);
                enemiesY[j] = 2 + (float(rand()) / float((RAND_MAX)) * b);


                if ((enemiesX[j] - characterX > -1) && (enemiesX[j] - characterX < 1)) {
                    canSpawnEnemy = false;
                }

                if ((enemiesY[j] - characterY > -1) && (enemiesY[j] - characterY < 1)) {
                    canSpawnEnemy = false;
                }


                if (canSpawnEnemy == false) {
                    enemiesX[j] = OUT_OF_MAP;
                    enemiesY[j] = OUT_OF_MAP;
                    isEnemyAlive[j] = false;
                }
                else
                {
                    isEnemyAlive[j] = true;
                    enemySpawnTimer = 0;
                    break;
                }

            }
    }
}

void Tema1::RenderProjectile(float deltaTime) {

    if (projectileHit) {
        if (projectileTimer < projectileTimeLimit) {
            projectileTimer = projectileTimer + deltaTime;
            projectileFire = false;
        }
        else
            projectileHit = false;
    }

    if (projectileFire == true) {

            if (projectileStartFlag == true) {

                projectileStartFlag = false;

                startX -= projectileSize / 2;
                startY -= projectileSize / 2;

                endX -= projectileSize / 2;
                endY -= projectileSize / 2;

                projectileTimer = 0;
                projectileTimeLimit = PROJECTILE_TIME_FACTOR * deltaTime;

                projectileSpeedFactor = PROJECTILE_DISTANCE_FACTOR * sqrt(pow((endX - startX), 2) + pow((endY - startY), 2));
                stepX = (endX - startX) / projectileSpeedFactor;
                stepY = (endY - startY) / projectileSpeedFactor;
              
            }

            if (projectileTimer < projectileTimeLimit) {
                projectileTimer = projectileTimer + deltaTime;

                projectileHitEnemy = false;

                for (int j = 0; j < numEnemies; j++) {
                    
                    if (CheckCollisionProjectileObject(enemySize, enemySize, enemiesX[j], enemiesY[j], startX + stepX + projectileSize / 2, startY + stepY + projectileSize / 2)) {
                        projectileHitEnemy = true;
                        isEnemyAlive[j] = false;
                        enemiesX[j] = OUT_OF_MAP;
                        enemiesY[j] = OUT_OF_MAP;
                        break;
                    }

                }

                if (projectileHitEnemy == false) {

                    if (!CheckCollisionProjectileObstacles(startX + stepX, startY + stepY)) {

                        startX += stepX;
                        startY += stepY;

                        modelMatrix = glm::mat3(1);

                        modelMatrix *= visMatrix * Transform2D::Translate(startX, startY);

                        modelMatrix *= Transform2D::Translate(projectileSize / 2, projectileSize / 2);
                        modelMatrix *= Transform2D::Rotate(projectileAngularStep);
                        modelMatrix *= Transform2D::Translate(-projectileSize / 2, -projectileSize / 2);


                        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
                    }
                    else
                    {
                        projectileHit = true;
                        projectileFire = false;
                        projectileStartFlag = true;
                    }
                }
                else
                {
                    score = score + 10;
                    cout << "Score : " << score << endl;

                    projectileHit = true;
                    projectileFire = false;
                    projectileStartFlag = true;
                }
            }
            else {
                projectileFire = false;
                projectileStartFlag = true;
            }
        
    }

}


void Tema1::RenderCharacter(float deltaTime)
{

    float offsetX = 1.f, offsetY = 1.f;

    RenderCharacterBodyPart(character->GetCharacterRightHandMesh(offsetX, offsetY), offsetX, offsetY, deltaTime);

    RenderCharacterBodyPart(character->GetCharacterLeftHandMesh(offsetX, offsetY), offsetX, offsetY, deltaTime);

    RenderCharacterBodyPart(character->GetCharacterHeadMesh(offsetX, offsetY), offsetX, offsetY, deltaTime);

    RenderCharacterBodyPart(character->GetCharacterBackpackMesh(offsetX, offsetY), offsetX, offsetY, deltaTime);

}



void Tema1::RenderCharacterBodyPart(Mesh* bodyPart, float offsetX, float offsetY, float deltaTime)
{
    modelMatrix = visMatrix * Transform2D::Translate(characterX, characterY);
    modelMatrix *= Transform2D::Rotate(mouseAngularStep);
    modelMatrix *=  Transform2D::Translate(offsetX, offsetY);

    RenderMesh2D(bodyPart, shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderEnemies(float deltaTime) {

    for (int j = 0; j < numEnemies; j++) {

        if (CheckCollisionCharacterObject(enemySize, enemySize, enemiesX[j], enemiesY[j], characterX, characterY) && isEnemyAlive[j]) {
            isEnemyAlive[j] = false;
            enemiesX[j] = OUT_OF_MAP;
            enemiesY[j] = OUT_OF_MAP;
            hitCounter++;
        }

        if (isEnemyAlive[j] == true)
            RenderEnemy(enemySpeed[j], enemiesX[j], enemiesY[j]);
    }

}

void Tema1::RenderEnemy(float deltaTime, float &enemyX, float &enemyY)
{

    float offsetX = 1.f, offsetY = 1.f;

    bool enemyCollision;


    if (enemyX < characterX) {

        enemyCollision = false;

        for (int j = 0; j < numEdgeWalls; j++) {
            if (CheckCollisionEnemyObstacle(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, enemyX + deltaTime, enemyY))
                enemyCollision = true;
        }

        if (enemyCollision == false && characterX - enemyX > TOLERANCE) {
            enemyX = enemyX + deltaTime;
        }

    }
    else {

        enemyCollision = false;

        for (int j = 0; j < numEdgeWalls; j++) {
            if (CheckCollisionEnemyObstacle(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, enemyX - deltaTime, enemyY))
                enemyCollision = true;
        }

        if (enemyCollision == false && enemyX - characterX > TOLERANCE) {
            enemyX = enemyX - deltaTime;
        }
    }

    if (enemyY < characterY) {

        enemyCollision = false;

        for (int j = 0; j < numEdgeWalls; j++) {
            if (CheckCollisionEnemyObstacle(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, enemyX , enemyY + deltaTime))
                enemyCollision = true;
        }

        if (enemyCollision == false && characterY - enemyY > TOLERANCE) {
            enemyY = enemyY + deltaTime;
        }
    }
    else {

        enemyCollision = false;
        
        for (int j = 0; j < numEdgeWalls; j++) {
            if (CheckCollisionEnemyObstacle(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, enemyX , enemyY - deltaTime))
                enemyCollision = true;
        }

        if (enemyCollision == false && enemyY - characterY > TOLERANCE) {
            enemyY = enemyY - deltaTime;
        }
    }

   
    RenderEnemyBodyPart(enemy->GetEnemyRightHandMesh(offsetX, offsetY), offsetX, offsetY, enemy->GetEnemyHandSize(), enemyX, enemyY, "right_hand");

    RenderEnemyBodyPart(enemy->GetEnemyLeftHandMesh(offsetX, offsetY), offsetX, offsetY, enemy->GetEnemyHandSize(), enemyX, enemyY, "left_hand");

    RenderEnemyBodyPart(enemy->GetEnemyHeadMesh(offsetX, offsetY), offsetX, offsetY, enemy->GetEnemyHeadSize(), enemyX, enemyY, "head");


}

void Tema1::RenderEnemyBodyPart(Mesh* bodyPart, float offsetX, float offsetY, float size, float enemyX, float enemyY, glm::string bodyPartName)
{
    
    enemyAngularStep = atan2((enemyY - characterY + enemySize/2), (enemyX - characterX + enemySize/2));
   
    modelMatrix = visMatrix * Transform2D::Translate(enemyX, enemyY);
    
    modelMatrix *= Transform2D::Translate(offsetX, offsetY);
    
    
    if (bodyPartName.compare("head") == 0) {

        modelMatrix *= Transform2D::Translate(enemySize / 2, enemySize / 2);
        modelMatrix *= Transform2D::Rotate(enemyAngularStep);
        modelMatrix *= Transform2D::Translate(-enemySize / 2, -enemySize / 2);
    }
   
    if (bodyPartName.compare("left_hand") == 0) {
        
        modelMatrix *= Transform2D::Translate(enemySize / 2 + size / 2, enemySize / 2 + size / 2);
        modelMatrix *= Transform2D::Rotate(enemyAngularStep);
        modelMatrix *= Transform2D::Translate(-(enemySize / 2 + size / 2), -(enemySize / 2 + size / 2));
    }

    if (bodyPartName.compare("right_hand") == 0) {

        modelMatrix *= Transform2D::Translate(enemySize / 2 + size / 2, -(enemySize / 2 - size / 2));
        modelMatrix *= Transform2D::Rotate(enemyAngularStep);
        modelMatrix *= Transform2D::Translate(-(enemySize / 2 + size / 2), enemySize / 2 - size / 2);

    }
    

    RenderMesh2D(bodyPart, shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderHealthBar(float deltaTime) {

    modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * Transform2D::Translate(healthX , healthY);

    RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);


    if (hitCounter == 0) {
        RenderMesh2D(meshes["fullHP"], shaders["VertexColor"], modelMatrix);
    }

    if (hitCounter == 1) {
        RenderMesh2D(meshes["goodHP"], shaders["VertexColor"], modelMatrix);
    }

    if (hitCounter == 2) {
        RenderMesh2D(meshes["halfHP"], shaders["VertexColor"], modelMatrix);
    }

    if (hitCounter == 3) {
        RenderMesh2D(meshes["lowHP"], shaders["VertexColor"], modelMatrix);
    }

}

void Tema1::RenderHealthPack() {

    float offsetX = 1.f, offsetY = 1.f;


    if (CheckCollisionCharacterObject(healthPackWidth, healthPackHeight, healthPackX, healthPackY, characterX, characterY) && isHealthPackSpawned == true) {

        isHealthPackSpawned = false;

        healthPackX = OUT_OF_MAP;
        healthPackY = OUT_OF_MAP;

        healthPackTimer = 0;

        if (hitCounter > 0)
            hitCounter--;
    }

    if (isHealthPackSpawned == true) {

        RenderHealthPackPart(healthPack->GetHealthPackVerticalBarMesh(offsetX, offsetY), offsetX, offsetY, healthPackX, healthPackY);

        RenderHealthPackPart(healthPack->GetHealthPackHorizontalBarMesh(offsetX, offsetY), offsetX, offsetY, healthPackX, healthPackY);

        RenderHealthPackPart(healthPack->GetHealthPackBoxMesh(offsetX, offsetY), offsetX, offsetY, healthPackX, healthPackY);
    }

}

void Tema1::RenderHealthPackPart(Mesh *part, float offsetX, float offsetY, float healthPackX, float healthPackY) {

    modelMatrix = visMatrix * Transform2D::Translate(healthPackX, healthPackY);
    modelMatrix *= Transform2D::Translate(offsetX, offsetY);
    RenderMesh2D(part, shaders["VertexColor"], modelMatrix);

}

void Tema1::RenderMap() {

    renderedWalls[0] = RenderInfo(width1, height1, 0, 0); 
    renderedWalls[1] = RenderInfo(width1, height1, width2 - width1, 0);
    renderedWalls[2] = RenderInfo(width2, height2, 0, 0);
    renderedWalls[3] = RenderInfo(width2, height2, 0, height1 - height2);


    modelMatrix = visMatrix * Transform2D::Translate(0, 0);
    RenderMesh2D(meshes["height_wall"], shaders["VertexColor"], modelMatrix); // LEFT : DOWN -> UP

    modelMatrix = visMatrix * Transform2D::Translate(width2 - width1, 0);
    RenderMesh2D(meshes["height_wall"], shaders["VertexColor"], modelMatrix); // RIGHT : DOWN -> UP

    modelMatrix = visMatrix * Transform2D::Translate(0, 0);
    RenderMesh2D(meshes["width_wall"], shaders["VertexColor"], modelMatrix); // DOWN : LEFT -> RIGHT

    modelMatrix = visMatrix * Transform2D::Translate(0, height1 - height2);
    RenderMesh2D(meshes["width_wall"], shaders["VertexColor"], modelMatrix); // UP : LEFT -> RIGHT

}

void Tema1::RenderObstacles(float deltaTime)
{

    if (stopRandomise == false) {

        float x, y;
        float a = ((map_width - 2) - 2) / 2;
        float b = ((map_height - 2) - 2) / 2;

        x = a - (float(rand()) / float((RAND_MAX)) * a);
        y = (2 + b + 0.5) - (float(rand()) / float((RAND_MAX)) * b);

        renderedWalls[4] = RenderInfo(wall_0->width, wall_0->height, x, y);


        x = (2 + a) + (float(rand()) / float((RAND_MAX)) * a);
        y = (2 + b) - (float(rand()) / float((RAND_MAX)) * b);

        renderedWalls[5] = RenderInfo(wall_1->width, wall_1->height, x, y);

        x = a - (float(rand()) / float((RAND_MAX)) * a);
        y = (2 + b) + (float(rand()) / float((RAND_MAX)) * b);

        renderedWalls[6] = RenderInfo(wall_2->width, wall_2->height, x, y);

        x = (2 + a) + (float(rand()) / float((RAND_MAX)) * a);
        y = (2 + b) + (float(rand()) / float((RAND_MAX)) * b);

        renderedWalls[7] = RenderInfo(wall_3->width, wall_3->height, x, y);

        stopRandomise = true;
    }


    modelMatrix = visMatrix * Transform2D::Translate(renderedWalls[4].translateX, renderedWalls[4].translateY);
    RenderMesh2D(meshes["wall_0"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix * Transform2D::Translate(renderedWalls[5].translateX, renderedWalls[5].translateY);
    RenderMesh2D(meshes["wall_1"], shaders["VertexColor"], modelMatrix);
    

    modelMatrix = visMatrix * Transform2D::Translate(renderedWalls[6].translateX, renderedWalls[6].translateY);
    RenderMesh2D(meshes["wall_2"], shaders["VertexColor"], modelMatrix);

    
    modelMatrix = visMatrix * Transform2D::Translate(renderedWalls[7].translateX, renderedWalls[7].translateY);
    RenderMesh2D(meshes["wall_3"], shaders["VertexColor"], modelMatrix);

    
}

bool Tema1::CheckCollisionEnemyObstacle(float width, float height, float cornerX, float cornerY, float enemyX, float enemyY)
{
    
    bool collisionX = cornerX + width >= enemyX &&
        enemyX + enemySize >= cornerX;
    
    bool collisionY = cornerY + height >= enemyY &&
        enemyY + enemySize >= cornerY;
    
    return collisionX && collisionY;
}

bool Tema1::CheckCollisionEnemyProjectile(float projectileX, float projectileY, float enemyX, float enemyY)
{
    
    bool collisionX = projectileX + projectileSize >= enemyX &&
        enemyX + enemySize >= projectileX;
    
    bool collisionY = projectileY + projectileSize >= enemyY &&
        enemyY + enemySize >= projectileY;
    
    return collisionX && collisionY;
}

bool Tema1::CheckCollisionObstacleHealthPack(float healthPackX, float healthPackY, float healthPackWidth, float healthPackHeight, float obstacleX, float obstacleY, float obstacleWidth, float obstacleHeight)
{
    
    bool collisionX = healthPackX + healthPackWidth >= obstacleX && 
        obstacleX + obstacleWidth >= healthPackX;      
    
    bool collisionY = healthPackY + healthPackHeight >= obstacleY &&
        obstacleY + obstacleHeight >= healthPackY;
    
    return collisionX && collisionY;
}

bool Tema1::CheckCollisionCharacterObject(float width, float height, float cornerX, float cornerY, float circleX, float circleY)
{
    
    glm::vec2 center(circleX, circleY);
    
    glm::vec2 aabb_half_extents(width / 2.0f, height / 2.0f); 
    glm::vec2 aabb_center(
        cornerX + aabb_half_extents.x,  
        cornerY + aabb_half_extents.y  
    );
    
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
   
    glm::vec2 closest = aabb_center + clamped;
    
    difference = closest - center;
    return glm::length(difference) < CHARACTER_RADIUS; 
}

bool Tema1::CheckCollisionProjectileObject(float width, float height, float cornerX, float cornerY, float circleX, float circleY)
{

    glm::vec2 center(circleX, circleY);

    glm::vec2 aabb_half_extents(width / 2.0f, height / 2.0f); 
    glm::vec2 aabb_center(
        cornerX + aabb_half_extents.x, 
        cornerY + aabb_half_extents.y 
    );
    
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    
    glm::vec2 closest = aabb_center + clamped;
    
    difference = closest - center;
    return glm::length(difference) < PROJECTILE_RADIUS;
}



bool Tema1::CheckCollisionProjectileObstacles(float projectileX, float projectileY) {

    bool projectileCollision = false;

    for (int j = 0; j < numWalls; j++) {
        if (CheckCollisionProjectileOneObstacle(renderedWalls[j].width, renderedWalls[j].height, renderedWalls[j].translateX, renderedWalls[j].translateY, projectileX, projectileY)) {
            projectileCollision = true;
            break;
        }
    }

    if (projectileCollision == true)
        return true;
    else
        return false;
}

bool Tema1::CheckCollisionProjectileOneObstacle(float width, float height, float cornerX, float cornerY, float projectileX, float projectileY)
{

    bool collisionX = projectileX + projectileSize >= cornerX &&
        cornerX + width >= projectileX;
   
    bool collisionY = projectileY + projectileSize >= cornerY &&
        cornerY + height >= projectileY;
   
    return collisionX && collisionY;
}


