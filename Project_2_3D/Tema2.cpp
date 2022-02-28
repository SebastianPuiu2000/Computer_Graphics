#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{

    // Parametri necesari pentru proiectia ortografica/perspectiva
    left = -0.40;
    right = 0.40;
    bottom = -0.2;
    top = 0.2;
    zNear = 0.01f;
    zFar = 200.f;
    fov = RADIANS(90);

    reverseFirstPersonRotation = 0.f;
    reverseThirdPersonRotation = 0.f;

    verticalDirection = "UP";
    horizontalDirection = "NONE";

    angleX = 0;
    angleY = 0;
    angleZ = 0;

    projectileFire = false;
    projectileTimer = 0.f;

    projectileScaleFactor = 0.3f;

    thirdPersonMode = true;
    distanceToTarget = 6.f;
    maxDistanceToTarget = 6.f;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), distanceToTarget);

    cameraUI = new implemented::Camera();
    cameraUI->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), distanceToTarget);


    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }


    ground = new Ground3D();

    wall = new Wall3D();

    character = new Character3D();

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    // Se vor alege dimensiuni impare
    maze_width = 19;
    maze_height = 19;
    maze = new char[maze_height * maze_width];
    
    GenerateMaze(maze, maze_width, maze_height);

    if(maze_width > maze_height)
        numberOfEnemies = maze_width;
    else
        numberOfEnemies = maze_height;

    enemiesInfo = new EnemyInfo[numberOfEnemies];


    characterX = 0;
    characterY = -3.f;
    characterZ = 0;
    camera->TranslateUpward(3.f);
    cameraUI->TranslateUpward(3.f);

    scaleFactorHealthBarX = 1.f;
    scaleFactorTimerBarX = 1.f;

    oldPosition = camera->position;
    oldForward = camera->forward;
    oldDistanceToTarget = camera->distanceToTarget;

    isCameraRotating = true;

    {
        Shader* shader = new Shader("AnimationShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "AnimationVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "AnimationFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("ObjectShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "ObjectVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "ObjectFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }


    // Se va alege un multiplu de 4
    cellSize = 4;

    wallX = cellSize / 2;
    wallY = 4;
    wallZ = cellSize / 2;

    CharacterSpawner();
    EnemySpawner();

    // Dimensiune si plasare fereastra UI
    UI_X = 20;
    UI_Y = 20;
    UI_Width = 300;
    UI_Height = 100;
    
    // Prin decomentare se afiseaza in terminal labirintul in varianta 2D
    // ShowMaze(maze, maze_width, maze_height);

}

void Tema2::CharacterSpawner() {

    bool spawned = false;

    while (spawned == false) {

        int x = rand() % (maze_height * maze_width);

        if (maze[x] == 0) {

            maze[x] = 3;
            spawned = true;

            int a = x / maze_width;
            int b = x - a * maze_width;


            camera->position = glm::vec3(wallX + cellSize * a, 2.7, wallZ + cellSize * b) - camera->forward * camera->distanceToTarget;
            cameraUI->position = glm::vec3(wallX + cellSize * a, 2.7, wallZ + cellSize * b) - camera->forward * camera->distanceToTarget;
        }
    }
}


void Tema2::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema2::FrameStart()
{

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();


    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.2, 0.2, 0.5), true);

    DrawScene(deltaTimeSeconds);

   
    viewSpace = ViewportSpace(UI_X, UI_Y, UI_Width, UI_Height);
    SetViewportArea(viewSpace, glm::vec3(0.f), true);

    DrawUI(deltaTimeSeconds);
}


void Tema2::DrawScene(float deltaTimeSeconds) {

    CheckEndGame();

    RenderCharacter(deltaTimeSeconds);

    RenderMaze();

    RenderGround();

    RenderProjectile(deltaTimeSeconds);

    RenderAllEnemies();

    CameraAvoidWall();
}

void Tema2::CheckEndGame() {

    if (scaleFactorHealthBarX <= 0 || scaleFactorTimerBarX <= 0) {

        cout << endl << "Game over !" << endl;

        exit(0);
    }

    if (camera->GetTargetPosition().x < 0 || camera->GetTargetPosition().x > maze_height * cellSize) {

        cout << endl << "You won !" << endl;

        exit(0);
    }
}


void Tema2::DrawUI(float deltaTimeSeconds) {

        projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);

        RenderUI(deltaTimeSeconds);

        projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}



void Tema2::FrameEnd()
{

}



/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 4.0f * cellSize / 4;

    if (window->KeyHold(GLFW_KEY_W)) {
          

        // Calcularea lui newTargetPosition si verificarea daca intra in coloziune cu un perete
        float distance = cameraSpeed * deltaTime;
        glm::vec3 direction = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));
        glm::vec3 newPositon = camera->position + direction * distance;
        glm::vec3 newTargetPosition = newPositon + camera->forward * camera->distanceToTarget;

        // Daca newTargetPosition nu intra in coliziune cu un perete, inseamna ca poate fi mutat caracterul
        if(!CheckCharacterAllWallsCollision(newTargetPosition))
            camera->MoveForward(distance);

    }

    if (window->KeyHold(GLFW_KEY_S)) {
          
        // Calcularea lui newTargetPosition si verificarea daca intra in coloziune cu un perete
        float distance = -cameraSpeed * deltaTime;
        glm::vec3 direction = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));
        glm::vec3 newPositon = camera->position + direction * distance;
        glm::vec3 newTargetPosition = newPositon + camera->forward * camera->distanceToTarget;

        // Daca newTargetPosition nu intra in coliziune cu un perete, inseamna ca poate fi mutat caracterul
        if (!CheckCharacterAllWallsCollision(newTargetPosition))
            camera->MoveForward(distance);

    }

    if (window->KeyHold(GLFW_KEY_D)) {
           
        // Calcularea lui newTargetPosition si verificarea daca intra in coloziune cu un perete
        float distance = cameraSpeed * deltaTime;
        glm::vec3 direction = glm::normalize(camera->right);
        glm::vec3 newPositon = camera->position + direction * distance;
        glm::vec3 newTargetPosition = newPositon + camera->forward * camera->distanceToTarget;

        // Daca newTargetPosition nu intra in coliziune cu un perete, inseamna ca poate fi mutat caracterul
        if (!CheckCharacterAllWallsCollision(newTargetPosition))
            camera->TranslateRight(distance);

    }

    if (window->KeyHold(GLFW_KEY_A)) {

        // Calcularea lui newTargetPosition si verificarea daca intra in coloziune cu un perete
        float distance = -cameraSpeed * deltaTime;
        glm::vec3 direction = glm::normalize(camera->right);
        glm::vec3 newPositon = camera->position + direction * distance;
        glm::vec3 newTargetPosition = newPositon + camera->forward * camera->distanceToTarget;

        // Daca newTargetPosition nu intra in coliziune cu un perete, inseamna ca poate fi mutat caracterul
        if (!CheckCharacterAllWallsCollision(newTargetPosition)) {
            camera->TranslateRight(distance);
        }

    }

}


void Tema2::OnKeyPress(int key, int mods)
{

    if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {

        if (isCameraRotating == false) {

            if (thirdPersonMode) {

                // Trecere in FirstPersonMode
                thirdPersonMode = false;

                // Rotire inapoi in pozitia intiala
                camera->RotateThirdPerson_OX(reverseThirdPersonRotation);
                reverseThirdPersonRotation = 0.f;

                camera->TranslateForward(distanceToTarget);
                camera->distanceToTarget = 0;
            }

            else {

                // Trecere in ThirdPersonMode
                thirdPersonMode = true;

                // Rotire inapoi in pozitia intiala
                camera->RotateFirstPerson_OX(reverseFirstPersonRotation);
                reverseFirstPersonRotation = 0.f;

                camera->TranslateForward(-distanceToTarget);
                camera->distanceToTarget = distanceToTarget;
            }
        }
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        isCameraRotating = true;

        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (thirdPersonMode == false) {
            camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);

            reverseFirstPersonRotation += sensivityOX * deltaY;
        }

        if (thirdPersonMode == true) {

            camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY * deltaX);

            reverseThirdPersonRotation += sensivityOX * deltaY;
            
        }

        angleY += -sensivityOY * deltaX;

    }
    else {
        isCameraRotating = false;
    }

}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && projectileFire == false && thirdPersonMode == false) {

        oldPosition = camera->position;
        oldForward = camera->forward;
        oldDistanceToTarget = 0.5;

        projectileFire = true;

    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}


void Tema2::RenderUI(float deltaTime) {

    float offsetX = 1.f, offsetY = 1.f, offsetZ = 1.f;


    RenderUIPart(character->GetCharacterHealthBarMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "health_bar");
    RenderUIPart(character->GetCharacterHealthBarFrameMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "health_bar_frame");

    RenderUIPart(character->GetCharacterTimerBarMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "timer_bar");
    RenderUIPart(character->GetCharacterTimerBarFrameMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "timer_bar_frame");

}

void Tema2::RenderUIPart(Mesh* bodyPart, float offsetX, float offsetY, float offsetZ, float deltaTime, glm::string bodyPartName) {

    modelMatrix = Transform3D::Translate(characterX, characterY+0.6, characterZ);

    modelMatrix = glm::translate(modelMatrix, cameraUI->GetTargetPosition());

    if (bodyPartName.compare("health_bar") == 0 || bodyPartName.compare("health_bar_frame") == 0) {
        offsetY -= 0.06f;
    }


    if (bodyPartName.compare("health_bar") == 0) {

        modelMatrix *= Transform3D::Translate(offsetX + (0.4f - scaleFactorHealthBarX * 0.4f), offsetY, offsetZ);
        modelMatrix *= Transform3D::Scale(scaleFactorHealthBarX, 1.f, 1.f);

    }

    if (bodyPartName.compare("timer_bar") == 0 || bodyPartName.compare("timer_bar_frame") == 0) {
        offsetY += 0.018f;
    }

    if (bodyPartName.compare("timer_bar") == 0) {

        scaleFactorTimerBarX -= 0.0001f;

        modelMatrix *= Transform3D::Translate(offsetX + (0.4f - scaleFactorTimerBarX * 0.4f), offsetY, offsetZ);
        modelMatrix *= Transform3D::Scale(scaleFactorTimerBarX, 1.f, 1.f);

    }


    if (bodyPartName.compare("health_bar") != 0 && bodyPartName.compare("timer_bar") != 0) {

        modelMatrix *= Transform3D::Translate(offsetX, offsetY, offsetZ);
    }

    RenderMeshUI(bodyPart, shaders["VertexColor"], modelMatrix);


    
    // Randare wireframe pentru health si timer
    modelMatrix = Transform3D::Translate(characterX, characterY + 0.6, characterZ);
    modelMatrix = glm::translate(modelMatrix, cameraUI->GetTargetPosition());

    modelMatrix *= Transform3D::Translate(offsetX, offsetY - 0.001, offsetZ - 0.004);
    modelMatrix *= Transform3D::Scale(1.f, 1.f, 1.f);

    RenderMeshUI(bodyPart, shaders["Simple"], modelMatrix);
    
}




void Tema2::RenderCharacter(float deltaTime) {

    float offsetX = 1.f, offsetY = 1.f, offsetZ = 1.f;

    if (thirdPersonMode) {

        RenderCharacterBodyPart(character->GetCharacterBodyMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "body");

        RenderCharacterBodyPart(character->GetCharacterHeadMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "head");

        RenderCharacterBodyPart(character->GetCharacterLeftHandMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "left_hand");
        RenderCharacterBodyPart(character->GetCharacterRightHandMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "right_hand");

        RenderCharacterBodyPart(character->GetCharacterLeftArmMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "left_arm");
        RenderCharacterBodyPart(character->GetCharacterRightArmMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "right_arm");

        RenderCharacterBodyPart(character->GetCharacterLeftFootMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "left_foot");
        RenderCharacterBodyPart(character->GetCharacterRightFootMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "right_foot");


        RenderCharacterBodyPart(character->GetCharacterLeftBraceMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "left_brace");
        RenderCharacterBodyPart(character->GetCharacterRightBraceMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "right_brace");

        RenderCharacterBodyPart(character->GetCharacterBackpackMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "backpack");

        RenderCharacterBodyPart(character->GetCharacterHealthBarMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "health_bar");
        RenderCharacterBodyPart(character->GetCharacterHealthBarFrameMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "health_bar_frame");

        RenderCharacterBodyPart(character->GetCharacterTimerBarMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "timer_bar");
        RenderCharacterBodyPart(character->GetCharacterTimerBarFrameMesh(offsetX, offsetY, offsetZ), offsetX, offsetY, offsetZ, deltaTime, "timer_bar_frame");
    }
    
}

void Tema2::RenderCharacterBodyPart(Mesh* bodyPart, float offsetX, float offsetY, float offsetZ, float deltaTime, glm::string bodyPartName) {

    modelMatrix = Transform3D::Translate(characterX, characterY, characterZ);

    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    
    
    modelMatrix *= Transform3D::RotateOX(angleX);
    modelMatrix *= Transform3D::RotateOY(angleY);
    modelMatrix *= Transform3D::RotateOZ(angleZ);
    

    if (bodyPartName.compare("health_bar") == 0) {

        modelMatrix *= Transform3D::Translate(offsetX + (0.4f - scaleFactorHealthBarX * 0.4f), offsetY, offsetZ); //hardcodare
        modelMatrix *= Transform3D::Scale(scaleFactorHealthBarX, 1.f, 1.f);
        
    }


    if (bodyPartName.compare("timer_bar") == 0) {

        scaleFactorTimerBarX -= 0.0001f;

        modelMatrix *= Transform3D::Translate(offsetX + (0.4f - scaleFactorTimerBarX * 0.4f), offsetY, offsetZ); //hardcodare
        modelMatrix *= Transform3D::Scale(scaleFactorTimerBarX, 1.f, 1.f);

    }


    if (bodyPartName.compare("health_bar") != 0 && bodyPartName.compare("timer_bar") != 0) {

        modelMatrix *= Transform3D::Translate(offsetX, offsetY, offsetZ);
    }

    RenderMesh(bodyPart, shaders["VertexColor"], modelMatrix);
}

void Tema2::ShowMaze(char* maze, int width, int height) {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            switch (maze[i * width + j])
            {
                case 1:  cout << "[]";  break; // perete
                case 3:  cout << "??";  break; // caracter
                case 4:  cout << "##";  break; // inamic
                default: cout << "!!";  break; // tunel
            }
        }

        cout << endl;
    }
}

void Tema2::CarveMaze(char* maze, int width, int height, int x, int y) {

    // Algoritm de tunelare pentru obtinerea labirintului

    int x1, y1;
    int x2, y2;

    int dx, dy;

    int dir, count;

    dir = rand() % 4;

    count = 0;

    while (count < 4) {

        dx = 0;
        dy = 0;

        switch(dir)
        {
            case 0: dx = 1; break;

            case 1: dy = 1; break;

            case 2: dx = -1; break;

            default: dy = -1; break;
        }

        x1 = x + dx;
        y1 = y + dy;

        x2 = x1 + dx;
        y2 = y1 + dy;

        if (x2 > 0 && x2 < width && y2 > 0 && y2 < height && maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {

            maze[y1 * width + x1] = 0;
            maze[y2 * width + x2] = 0;

            x = x2; 
            y = y2;

            dir = rand() % 4;
            count = 0;
        }
        else {
            dir = (dir + 1) % 4;
            count += 1;
        }

    }
}

void Tema2::GenerateMaze(char* maze, int width, int height) {

    // Initializarea labirintului
    for (int i = 0; i < width * height; i++) {
        maze[i] = 1;
    }

    maze[1 * width + 1] = 0;

    // Tunelarea labirintului
    for (int i = 1; i < height; i += 2) {
        for (int j = 1; j < width; j += 2) {
            CarveMaze(maze, width, height, j, i);
        }
    }

    // Setare prima iesire
    maze[0 * width + 1] = 0;

    // Setare a doua iesire
    maze[(height - 1) * width + (width - 2)] = 0;

}

void Tema2::RenderMaze() {

    for (int j = 0; j < maze_width; j++) {
        for (int i = 0; i < maze_height; i++) {
            if (maze[i * maze_width + j] == 1) {
                modelMatrix = Transform3D::Translate(wallX + i * cellSize, wallY, wallZ + j * cellSize);
                modelMatrix *= Transform3D::Scale(cellSize / 4, 1, cellSize / 4);
                RenderMesh(wall->GetWallMesh(), shaders["VertexColor"], modelMatrix);
            }
        }
    }
}


void Tema2::RenderGround() {


    modelMatrix = Transform3D::Translate((maze_width * cellSize) / 2, 0, (maze_height * cellSize) / 2);

    modelMatrix *= Transform3D::Scale((maze_width * cellSize), 0, (maze_height * cellSize));

    RenderSimpleMesh(ground->GetGroundMesh(), shaders["ObjectShader"], modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));

}


void Tema2::RenderProjectile(float deltaTime) {

    if (projectileFire == true) {

        // Orice proiectil va avea un anumit timp de existenta
        if (projectileTimer < 50 * deltaTime) {
            projectileTimer += deltaTime;
        }
        else {
            projectileFire = false;
            projectileTimer = 0.f;
        }

        float speed = 10.0f;
        float distance = speed * deltaTime;


        glm::vec3 position = oldPosition + glm::normalize(oldForward) * distance;

        glm::vec3 targetPosition = position + oldForward * oldDistanceToTarget;
        projectilePosition = targetPosition;

        oldPosition = position;

        if (CheckProjectileAllWallsCollision(targetPosition)) {
            projectileFire = false;
            projectileTimer = 0.f;
        }

        
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix = glm::translate(modelMatrix, targetPosition);
        modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);

        RenderSimpleMesh(meshes["sphere"], shaders["ObjectShader"], modelMatrix, glm::vec3(0.f, 0.f, 0.f));
    }

}


void Tema2::EnemySpawner() {

    for (int k = 0; k < numberOfEnemies; k++) {

        float ik = 0, jk = 0;

        bool spawned = false;

        while (spawned == false) {

            int x = rand() % (maze_height * maze_width);

            if (maze[x] == 0) {

                maze[x] = 4;
                spawned = true;

                ik = x / maze_width;
                jk = x - ik * maze_width;

            }
        }


        enemiesInfo[k].isAlive = true;

        enemiesInfo[k].positionX = wallX + ik * cellSize - cellSize / 2 + 0.5 * (cellSize / 4);
        enemiesInfo[k].positionY = 2.5f;
        enemiesInfo[k].positionZ = wallZ + jk * cellSize - cellSize / 2 + 0.5 * (cellSize / 4);

        enemiesInfo[k].startX = wallX + ik * cellSize - cellSize / 2 + 0.5 * (cellSize / 4);
        enemiesInfo[k].endX = wallX + ik * cellSize + cellSize / 2 - 0.5 * (cellSize / 4);

        enemiesInfo[k].startZ = wallZ + jk * cellSize - cellSize / 2 + 0.5 * (cellSize / 4);
        enemiesInfo[k].endZ = wallZ + jk * cellSize + cellSize / 2 - 0.5 * (cellSize / 4);

        enemiesInfo[k].deathAnimationTimer = 0.f;
    }
}

void Tema2::RenderAllEnemies() {

    glm::vec3 characterPosition = camera->GetTargetPosition();

    for (int i = 0; i < numberOfEnemies; i++) {

        if (enemiesInfo[i].isAlive == true) {
            if (!CheckProjectileEnemyCollision(enemiesInfo[i].positionX, enemiesInfo[i].positionY, enemiesInfo[i].positionZ, 0.5f * (cellSize / 4), projectilePosition.x, projectilePosition.y, projectilePosition.z, 0.15f)) {
                    RenderOneEnemy(enemiesInfo[i].positionX, enemiesInfo[i].positionY, enemiesInfo[i].positionZ, enemiesInfo[i].startX, enemiesInfo[i].endX, enemiesInfo[i].startZ, enemiesInfo[i].endZ);
            }
            else {
                enemiesInfo[i].isAlive = false;

                projectileFire = false;
                projectileTimer = 0.f;
            }

            if (!CheckCharacterEnemyCollision(enemiesInfo[i].positionX, enemiesInfo[i].positionY, enemiesInfo[i].positionZ, 0.5f * (cellSize / 4), characterPosition.x, characterPosition.y, characterPosition.z, 0.5f)) {
                RenderOneEnemy(enemiesInfo[i].positionX, enemiesInfo[i].positionY, enemiesInfo[i].positionZ, enemiesInfo[i].startX, enemiesInfo[i].endX, enemiesInfo[i].startZ, enemiesInfo[i].endZ);
            }
            else {
                enemiesInfo[i].isAlive = false;

                scaleFactorHealthBarX -= 0.25f;
            }
        }
        else {
            if (enemiesInfo[i].deathAnimationTimer < 10) {

                enemiesInfo[i].deathAnimationTimer += 0.1f;

                modelMatrix = Transform3D::Translate(enemiesInfo[i].positionX, enemiesInfo[i].positionY, enemiesInfo[i].positionZ);
                modelMatrix *= Transform3D::Scale(cellSize / 4, cellSize / 4, cellSize / 4);

                RenderAnimatedMesh(meshes["sphere"], shaders["AnimationShader"], modelMatrix, glm::vec3(0.f, 1.f, 0.f));
            }
        }
    }
}

void Tema2::RenderOneEnemy(float &pozX, float &pozY, float &pozZ, float startX, float endX, float startZ, float endZ) {

    glm::mat4 modelMatrix = glm::mat4(1);
    
    float speed = 8.f * (cellSize / 4);

    if (verticalDirection.compare("UP") == 0 && horizontalDirection.compare("NONE") == 0) {

        // Se verifica coliziunea in partea de sus

        if (pozX < endX) {

            pozX += 0.01 * speed;
        }
        else {
            verticalDirection = "NONE";
            horizontalDirection = "RIGHT";
        }

    }

    if (verticalDirection.compare("NONE") == 0 && horizontalDirection.compare("RIGHT") == 0) {

        // Se verifica coliziunea in partea dreapta

        if (pozZ < endZ) {

            pozZ += 0.01 * speed;
        }
        else {

            verticalDirection = "DOWN";
            horizontalDirection = "NONE";
        }
    }

    if (verticalDirection.compare("DOWN") == 0 && horizontalDirection.compare("NONE") == 0) {

        // Se verifica coliziunea in partea de jos

        if (pozX > startX) {
            pozX -= 0.01f * speed;
        }
        else {

            verticalDirection = "NONE";
            horizontalDirection = "LEFT";
        }
    }

    if (verticalDirection.compare("NONE") == 0 && horizontalDirection.compare("LEFT") == 0) {

        // Se verifica coliziunea in partea stanga

        if (pozZ > startZ) {

            pozZ -= 0.01 * speed;
        }
        else {

            verticalDirection = "UP";
            horizontalDirection = "NONE";
        }
    }

    modelMatrix = Transform3D::Translate(pozX, pozY, pozZ);
    modelMatrix *= Transform3D::Scale(cellSize / 4, cellSize / 4, cellSize / 4);
    
    RenderSimpleMesh(meshes["sphere"], shaders["ObjectShader"], modelMatrix, glm::vec3(0.f, 0.7f, 1.f));
}


void Tema2::CameraAvoidWall() {

    if (thirdPersonMode) {

        int moveCamera = 1;

        // Camera va iesi din peretele in care se afla
        while (moveCamera == 1) {
            moveCamera = 0;

            if (CheckCameraAllWallsCollision() == true) {
                moveCamera = 1;

                camera->TranslateForward(camera->distanceToTarget);
                camera->distanceToTarget -= 0.01;
                distanceToTarget -= 0.01;
                camera->TranslateForward(-camera->distanceToTarget);
            }
        }

        moveCamera = 1;

        // Camera se apropie de distanta maxima permisa, atata timp cat nu atinge un perete
        while (moveCamera == 1 && camera->distanceToTarget < maxDistanceToTarget) {

            camera->TranslateForward(camera->distanceToTarget);
            camera->distanceToTarget += 0.01;
            distanceToTarget += 0.01;
            camera->TranslateForward(-camera->distanceToTarget);

            if (CheckCameraAllWallsCollision() == true) {
                moveCamera = 0;
            }
        }
    }
}






bool Tema2::CheckCharacterAllWallsCollision(glm::vec3 targetPosition) {

    for (int j = 0; j < maze_width; j++)
        for (int i = 0; i < maze_height; i++) {
            if (maze[i * maze_width + j] == 1) {
                
                if (CheckCharacterWallCollision(targetPosition.x, targetPosition.y, targetPosition.z, 0.6f, wallX + i * cellSize + cellSize / 2, wallX + i * cellSize - cellSize / 2, wallY + cellSize, wallY - cellSize, wallZ + j * cellSize + cellSize / 2, wallZ + j * cellSize - cellSize / 2)) {
                    return true;
                }
            }
        }

    return false;
}


bool Tema2::CheckProjectileAllWallsCollision(glm::vec3 targetPosition) {

    for (int j = 0; j < maze_width; j++)
        for (int i = 0; i < maze_height; i++) {
            if (maze[i * maze_width + j] == 1) {

                if (CheckProjectileOneWallCollision(targetPosition.x, targetPosition.y, targetPosition.z, 0.15f, wallX + i * cellSize + cellSize / 2, wallX + i * cellSize - cellSize / 2, wallY + cellSize, wallY - cellSize, wallZ + j * cellSize + cellSize / 2, wallZ + j * cellSize - cellSize / 2)) {
                    return true;
                }
            }
        }

    return false;
}


bool Tema2::CheckCameraAllWallsCollision() {

    for (int j = 0; j < maze_width; j++)
        for (int i = 0; i < maze_height; i++) {
            if (maze[i * maze_width + j] == 1) {

                if (CheckCameraWallCollision(camera->position.x, camera->position.y, camera->position.z, 0.2f, wallX + i * cellSize + cellSize / 2, wallX + i * cellSize - cellSize / 2, wallY + cellSize, wallY - cellSize, wallZ + j * cellSize + cellSize / 2, wallZ + j * cellSize - cellSize / 2)) {
                    return true;
                }
            }
        }

    return false;
}








bool Tema2::CheckCameraWallCollision(float cameraHitboxX, float cameraHitboxY, float cameraHitboxZ, float cameraHitboxR, float wallMaxX, float wallMinX, float wallMaxY, float wallMinY, float wallMaxZ, float wallMinZ) {

    float x = std::max(wallMinX, std::min(cameraHitboxX, wallMaxX));
    float y = std::max(wallMinY, std::min(cameraHitboxY, wallMaxY));
    float z = std::max(wallMinZ, std::min(cameraHitboxZ, wallMaxZ));

    float distance = std::sqrt((x - cameraHitboxX) * (x - cameraHitboxX) +
        (y - cameraHitboxY) * (y - cameraHitboxY) +
        (z - cameraHitboxZ) * (z - cameraHitboxZ));

    return distance < cameraHitboxR;
}


bool Tema2::CheckCharacterWallCollision(float characterHitboxX, float characterHitboxY, float characterHitboxZ, float characterHitboxR, float wallMaxX, float wallMinX, float wallMaxY, float wallMinY, float wallMaxZ, float wallMinZ) {

    float x = std::max(wallMinX, std::min(characterHitboxX, wallMaxX));
    float y = std::max(wallMinY, std::min(characterHitboxY, wallMaxY));
    float z = std::max(wallMinZ, std::min(characterHitboxZ, wallMaxZ));

    float distance = std::sqrt((x - characterHitboxX) * (x - characterHitboxX) +
        (y - characterHitboxY) * (y - characterHitboxY) +
        (z - characterHitboxZ) * (z - characterHitboxZ));

    return distance < characterHitboxR;
}



bool Tema2::CheckProjectileOneWallCollision(float projectileX, float projectileY, float projectileZ, float characterHitboxR, float wallMaxX, float wallMinX, float wallMaxY, float wallMinY, float wallMaxZ, float wallMinZ) {

    float x = std::max(wallMinX, std::min(projectileX, wallMaxX));
    float y = std::max(wallMinY, std::min(projectileY, wallMaxY));
    float z = std::max(wallMinZ, std::min(projectileZ, wallMaxZ));

    float distance = std::sqrt((x - projectileX) * (x - projectileX) +
        (y - projectileY) * (y - projectileY) +
        (z - projectileZ) * (z - projectileZ));

    return distance < characterHitboxR;
}



bool Tema2::CheckProjectileEnemyCollision(float enemyX, float enemyY, float enemyZ, float enemyR, float projectileX, float projectileY, float projectileZ, float projectileR) {

    float distance = std::sqrt((enemyX - projectileX) * (enemyX - projectileX) +
        (enemyY - projectileY) * (enemyY - projectileY) +
        (enemyZ - projectileZ) * (enemyZ - projectileZ));

    return distance < (enemyR + projectileR);

}

bool Tema2::CheckCharacterEnemyCollision(float enemyX, float enemyY, float enemyZ, float enemyR, float characterX, float characterY, float characterZ, float characterR) {

    float distance = std::sqrt((enemyX - characterX) * (enemyX - characterX) +
        (enemyY - characterY) * (enemyY - characterY) +
        (enemyZ - characterZ) * (enemyZ - characterZ));

    return distance < (enemyR + characterR);

}





void Tema2::RenderAnimatedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;


    shader->Use();

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");

    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    int time = glGetUniformLocation(shader->GetProgramID(), "time");
    glUniform1f(time, (float)Engine::GetElapsedTime());


    mesh->Render();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    
    shader->Use();

    GLint color_location = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(color_location, 1, glm::value_ptr(color));


    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");

    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));


    mesh->Render();
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    
    shader->Use();

    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tema2::RenderMeshUI(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;


    shader->Use();

    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(cameraUI->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}