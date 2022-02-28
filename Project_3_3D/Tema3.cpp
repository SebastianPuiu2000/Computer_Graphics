#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}

////////////////////////////  INITIALIZARE  //////////////////////////////////////

void Tema3::Init()
{

    wallX = 0, wallY = 1, wallZ = 0;
    ground_width = 8, ground_height = 8;
    dance_mode = 0;

    // proprietati ale luminii si ale materialelor
    lightDirection = glm::vec3(0.3, -1, 0.3);
    materialShininess = 30;
    materialKd = 0.5;
    materialKs = 0.5;

    // numarul, pozitiile si culorile luminilor provenite din bucatile de podea alaturate dansatorului
    lightsNumber = 9;
    lightPos = new glm::vec3[lightsNumber];
    lightColor = new glm::vec3[lightsNumber];

    MeshesGenerator();
    
    ShadersGenerator();

    ColorMatrixGenerator();

    DancerSpawner();

    SpotLightSpawner();
    
}

////////////////////////////  GENERARE MESH-URI  //////////////////////////////////////

void Tema3::MeshesGenerator() {

    ConeMeshGenerator();
    BoxMeshGenerator();
    SphereMeshGenerator();
}

void Tema3::BoxMeshGenerator() {

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;
}

void Tema3::SphereMeshGenerator() {

    Mesh* mesh = new Mesh("sphere");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
    meshes[mesh->GetMeshID()] = mesh;
}

void Tema3::ConeMeshGenerator() {

    float x;
    int numTriangles = 50;
    int radius = 1;

    Mesh* mCone = new Mesh("cone");

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.9f, 0.5f));

    for (GLushort i = 0; i < numTriangles; ++i)
    {
        x = 2.0f * (GLfloat)M_PI * i / numTriangles;

        vertices.emplace_back(
            glm::vec3(cos(x) * radius, sin(x) * radius, 3),
            glm::vec3(1.f, 0.9f, 0.5f));
        indices.push_back(i);
    }
    indices.push_back(numTriangles);
    indices.push_back(1);

    mCone->InitFromData(vertices, indices);
    mCone->SetDrawMode(GL_TRIANGLE_FAN);

    meshes["cone"] = mCone;
}

////////////////////////////  GENERARE SHADERE  //////////////////////////////////////

void Tema3::ShadersGenerator() {

    DancerShaderGenerator();
    GroundhaderGenerator();
    SpotLightShaderGenerator();
    WallShaderGenerator();
}

void Tema3::DancerShaderGenerator() {

    Shader* shader = new Shader("MyDancerShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "DancerVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "DancerFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
}
void Tema3::GroundhaderGenerator() {

    Shader* shader = new Shader("MyGroundShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "GroundVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "GroundFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
}
void Tema3::SpotLightShaderGenerator() {

    Shader* shader = new Shader("MySpotLightShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "SpotLightVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "SpotLightFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
}
void Tema3::WallShaderGenerator() {

    Shader* shader = new Shader("MyWallShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "WallVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "WallFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
}

////////////////////////////  GRID CULORI  //////////////////////////////////////


void Tema3::ColorMatrixGenerator() {

    colourMatrix = new Colour[ground_width * ground_height];

    for (int j = 0; j < ground_width; j++) {
        for (int i = 0; i < ground_height; i++) {

            colourMatrix[j * ground_width + i].R = (float(rand()) / float((RAND_MAX)));
            colourMatrix[j * ground_width + i].G = (float(rand()) / float((RAND_MAX)));
            colourMatrix[j * ground_width + i].B = (float(rand()) / float((RAND_MAX)));

        }
    }
}

////////////////////////////  SPAWNERE  //////////////////////////////////////

void Tema3::DancerSpawner() {

    dancersNumber = 5;
    dancers = new DancerInfo[dancersNumber];

    for (int i = 0; i < dancersNumber; i++) {
        dancers[i].X = i;
        dancers[i].Y = 1.3;
        dancers[i].Z = i;
    }
}

void Tema3::SpotLightSpawner() {

    spotLightsNumber = 4;
    spotLightPos = new glm::vec3[spotLightsNumber];
    spotLightColor = new glm::vec3[spotLightsNumber];

    spotLightPos[0] = glm::vec3(wallX + 0.9, wallY + 1.5, wallZ + 0.9);
    spotLightPos[1] = glm::vec3(wallX + 3.3, wallY + 1.5, wallZ + 0.9);
    spotLightPos[2] = glm::vec3(wallX + 0.9, wallY + 1.5, wallZ + 3.3);
    spotLightPos[3] = glm::vec3(wallX + 3.3, wallY + 1.5, wallZ + 3.3);

    spotLightColor[0] = glm::vec3(1, 0, 0);
    spotLightColor[1] = glm::vec3(0, 1, 0);
    spotLightColor[2] = glm::vec3(0, 0, 1);
    spotLightColor[3] = glm::vec3(1, 0, 1);

}


////////////////////////////  FRAME-URI  //////////////////////////////////////


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema3::Update(float deltaTimeSeconds)
{
    RenderDancers(deltaTimeSeconds);

    RenderGround();

    RenderWalls();

    RenderSpotLights(deltaTimeSeconds);
}


void Tema3::FrameEnd()
{
    
}





/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2;

    // deplasarea camerei prin scena
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    // activare dans
    if (key == GLFW_KEY_P) {
        dance_mode = !dance_mode;
    }

}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}

////////////////////////////  LOGICA REFLECTOARE  //////////////////////////////////////

void Tema3::RenderSpotLights(float deltaTimeSeconds) {

    
    MoveSpotLights(deltaTimeSeconds);

    for (int i = 0; i < spotLightsNumber; i++) {

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        glDepthMask(GL_FALSE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, spotLightPos[i]);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f));

        modelMatrix = glm::rotate(modelMatrix, lightDirection.x, glm::vec3(0, 0, 1));
        modelMatrix = glm::rotate(modelMatrix, -lightDirection.z, glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));

        RenderSpotLightMesh(meshes["cone"], shaders["MySpotLightShader"], modelMatrix, spotLightColor[i]);

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glDisable(GL_CULL_FACE);

       
    }
   
}

void Tema3::MoveSpotLights(float deltaTimeSeconds) {


    if (cone.lockX == 0) {
        cone.randX = rand() % 3;
    }
    if (cone.lockZ == 0) {
        cone.randZ = rand() % 3;
    }

    // verificarea faptului ca nu iese din harta pe asa OX
    if (cone.randX == 0 && lightDirection.x - 0.001 <= -0.3) {
        cone.randX = 1;
        cone.timerX = 0;
    }

    // verificarea faptului ca nu iese din harta pe axa OX
    if (cone.randX == 1 && lightDirection.x + 0.001 >= 0.3) {
        cone.randX = 0;
        cone.timerX = 0;
    }

    if (cone.randX == 0) {
        lightDirection.x -= 0.001;
        cone.lockX = 1;
    }

    if (cone.randX == 1) {
        lightDirection.x += 0.001;
        cone.lockX = 1;
    }

    // limitare de mers intr-o directie
    if (cone.timerX < 500 * deltaTimeSeconds) {
        cone.timerX += deltaTimeSeconds;
    }
    else {
        cone.timerX = 0;
        cone.lockX = 0;
    }

    // verificarea faptului ca nu iese din harta pe axa OZ
    if (cone.randZ == 0 && lightDirection.z - 0.001 <= -0.3) {
        cone.randZ = 1;
        cone.timerZ = 0;
    }

    // verificarea faptului ca nu iese din harta pe axa OZ
    if (cone.randZ == 1 && lightDirection.z + 0.001 >= 0.3) {
        cone.randZ = 0;
        cone.timerZ = 0;
    }

    if (cone.randZ == 0) {
        lightDirection.z -= 0.001;
        cone.lockZ = 1;
    }

    if (cone.randZ == 1) {
        lightDirection.z += 0.001;
        cone.lockZ = 1;
    }

    // limitare de mers intr-o directie
    if (cone.timerZ < 500 * deltaTimeSeconds) {
        cone.timerZ += deltaTimeSeconds;
    }
    else {
        cone.timerZ = 0;
        cone.lockZ = 0;
    }
    
}

////////////////////////////  LOGICA DANSATORI  //////////////////////////////////////

void Tema3::RenderDancers(float deltaTimeSeconds) {

    // randarea tuturor dansatorilor
    for (int i = 0; i < dancersNumber; i++) {
        RenderDancer(deltaTimeSeconds, dancers[i]);
    }
}

void Tema3::RenderDancer(float deltaTimeSeconds, DancerInfo &dancer) {

    MoveDancer(deltaTimeSeconds, dancer);

    int pos_i = 0;
    int pos_j = 0;

    // descopar in ce casuta sa afla dansatorul curent
    for (int j = 0; j < ground_width; j++) {
        for (int i = 0; i < ground_height; i++) {

            if (dancer.X >= wallX + i * 0.6 - 0.3 && dancer.X <= wallX + i * 0.6 + 0.3) {
                if (dancer.Z >= wallZ + j * 0.6 - 0.3 && dancer.Z <= wallZ + j * 0.6 + 0.3) {
                    pos_i = i;
                    pos_j = j;
                }
            }
        }
    }

    // ###
    // #@#
    // ###
    // determin care sunt luminile si culorile alaturate ce il vor compune
    
    int k = 0;

    for (int j = pos_j - 1; j <= pos_j + 1; j++) {
        for (int i = pos_i - 1; i <= pos_i + 1; i++) {

            if (j >= 0 && j <= 7 && i >= 0 && i <= 7) {
                lightPos[k] = glm::vec3(wallX + i * 0.6, wallY + 0.001, wallZ + j * 0.6);

                R = colourMatrix[j * ground_width + i].R;
                G = colourMatrix[j * ground_width + i].G;
                B = colourMatrix[j * ground_width + i].B;
                lightColor[k] = glm::vec3(R, G, B);

                k++;
            }
        }
    }

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(dancer.X, dancer.Y, dancer.Z));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.6, 0.3));

    RenderDancerMesh(meshes["box"], shaders["MyDancerShader"], modelMatrix, k);
}

void Tema3::MoveDancer(float deltaTimeSeconds, DancerInfo &dancer) {
    
    if (dance_mode == 1) {

        if (dancer.lockX == 0) {
            dancer.randX = rand() % 3;
        }
        if (dancer.lockZ == 0) {
            dancer.randZ = rand() % 3;
        }

        // verificarea faptului ca nu iese din harta pe axa OX
        if (dancer.randX == 0 && dancer.X - 0.01 <= wallX + 0.1) {
            dancer.randX = 1;
            dancer.timerX = 0;
        }

        // verificarea faptului ca nu iese din harta pe axa OX
        if (dancer.randX == 1 && dancer.X + 0.01 >= wallX + 7 * 0.6) {
            dancer.randX = 0;
            dancer.timerX = 0;
        }

        if (dancer.randX == 0) {
            dancer.X -= 0.01;
            dancer.lockX = 1;
        }

        if (dancer.randX == 1) {
            dancer.X += 0.01;
            dancer.lockX = 1;
        }

        // limitare de mers intr-o directie
        if (dancer.timerX < 100 * deltaTimeSeconds) {
            dancer.timerX += deltaTimeSeconds;
        }
        else {
            dancer.timerX = 0;
            dancer.lockX = 0;
        }

        // verificarea faptului ca nu iese din harta pe axa OZ
        if (dancer.randZ == 0 && dancer.Z - 0.01 <= wallZ + 0.1) {
            dancer.randZ = 1;
            dancer.timerZ = 0;
        }

        // verificarea faptului ca nu iese din harta pe axa OZ
        if (dancer.randZ == 1 && dancer.Z + 0.01 >= wallZ + 7 * 0.6) {
            dancer.randZ = 0;
            dancer.timerZ = 0;
        }

        if (dancer.randZ == 0) {
            dancer.Z -= 0.01;
            dancer.lockZ = 1;
        }

        if (dancer.randZ == 1) {
            dancer.Z += 0.01;
            dancer.lockZ = 1;
        }

        // limitare de mers intr-o directie
        if (dancer.timerZ < 100 * deltaTimeSeconds) {
            dancer.timerZ += deltaTimeSeconds;
        }
        else {
            dancer.timerZ = 0;
            dancer.lockZ = 0;
        }

    }
}

////////////////////////////  LOGICA PODEA  //////////////////////////////////////

void Tema3::RenderGround() {

    int k;

    for (int j = 0; j < ground_width; j++) {
        for (int i = 0; i < ground_height; i++) {

            // se decide, la intamplare, daca se schimba culoarea
            k = rand() % 400;
            // culorile se aleg si acestea la intamplare 
            if (k == 2) {
                colourMatrix[j * ground_width + i].R = (float(rand()) / float((RAND_MAX)));
                colourMatrix[j * ground_width + i].G = (float(rand()) / float((RAND_MAX)));
                colourMatrix[j * ground_width + i].B = (float(rand()) / float((RAND_MAX)));
            }
            
            R = colourMatrix[j * ground_width + i].R;
            G = colourMatrix[j * ground_width + i].G;
            B = colourMatrix[j * ground_width + i].B;

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(wallX + i * 0.6, wallY, wallZ + j * 0.6));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6, 0.01, 0.6));

            RenderGroundMesh(meshes["box"], shaders["MyGroundShader"], modelMatrix, glm::vec3(R, G, B));
        }
    }

}

////////////////////////////  LOGICA PERETI  //////////////////////////////////////

void Tema3::RenderWalls() {


    for (int i = 0; i < ground_width; i++) {

        // generarea peretilor tip coloana de pe partea stanga a ringului de dans
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(wallX + i * 0.6, wallY + 0.8, wallZ - 0.3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6, 1.6, 0.001));

        R = colourMatrix[0 * ground_width + i].R;
        G = colourMatrix[0 * ground_width + i].G;
        B = colourMatrix[0 * ground_width + i].B;

        RenderWallMesh(meshes["box"], shaders["MyWallShader"], modelMatrix, glm::vec3(R, G, B), glm::vec3(wallX + i * 0.6, wallY + 0.001, wallZ));


        // generarea peretilor tip coloana de pe partea dreapta a ringului de dans
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(wallX + i * 0.6, wallY + 0.8, wallZ + 7 * 0.6 + 0.3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6, 1.6, 0.001));

        R = colourMatrix[7 * ground_width + i].R;
        G = colourMatrix[7 * ground_width + i].G;
        B = colourMatrix[7 * ground_width + i].B;

        RenderWallMesh(meshes["box"], shaders["MyWallShader"], modelMatrix, glm::vec3(R, G, B), glm::vec3(wallX + i * 0.6, wallY + 0.001, wallZ + 7 * 0.6));


        // generarea peretilor tip coloana de pe partea din spate a ringului de dans
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(wallX - 0.3, wallY + 0.8, wallZ + i * 0.6));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6, 1.6, 0.001));

        R = colourMatrix[i * ground_width + 0].R;
        G = colourMatrix[i * ground_width + 0].G;
        B = colourMatrix[i * ground_width + 0].B;

        RenderWallMesh(meshes["box"], shaders["MyWallShader"], modelMatrix, glm::vec3(R, G, B), glm::vec3(wallX, wallY + 0.001, wallZ + i * 0.6));


        // generarea peretilor tip coloana de pe partea din fata a ringului de dans
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(wallX + 7 * 0.6 + 0.3, wallY + 0.8, wallZ + i * 0.6));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6, 1.6, 0.001));

        R = colourMatrix[i * ground_width + 7].R;
        G = colourMatrix[i * ground_width + 7].G;
        B = colourMatrix[i * ground_width + 7].B;

        RenderWallMesh(meshes["box"], shaders["MyWallShader"], modelMatrix, glm::vec3(R, G, B), glm::vec3(wallX + 7 * 0.6, wallY + 0.001, wallZ + i * 0.6));
    }

}

////////////////////////////  RENDER MESH  //////////////////////////////////////

void Tema3::RenderDancerMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int numberLights, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);


    int light_direction_location = glGetUniformLocation(shader->program, "light_direction");
    glUniform3fv(light_direction_location, 1, glm::value_ptr(lightDirection));


    GLint spot_light_location = glGetUniformLocation(shader->program, "spot_light_position");
    glUniform3fv(spot_light_location, 4, glm::value_ptr(spotLightPos[0]));

    GLint spot_light_color_location = glGetUniformLocation(shader->program, "spot_light_color");
    glUniform3fv(spot_light_color_location, 4, glm::value_ptr(spotLightColor[0]));

    // Set shader uniforms for light properties
    GLint light_location = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_location, 9, glm::value_ptr(lightPos[0]));


    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(object_color, 9, glm::value_ptr(lightColor[0]));


    GLint loc_number_lights = glGetUniformLocation(shader->program, "number_lights");
    glUniform1i(loc_number_lights, numberLights);


    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}




void Tema3::RenderGroundMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int light_direction_location = glGetUniformLocation(shader->program, "light_direction");
    glUniform3fv(light_direction_location, 1, glm::value_ptr(lightDirection));


    GLint spot_light_location = glGetUniformLocation(shader->program, "spot_light_position");
    glUniform3fv(spot_light_location, 4, glm::value_ptr(spotLightPos[0]));

    GLint spot_light_color_location = glGetUniformLocation(shader->program, "spot_light_color");
    glUniform3fv(spot_light_color_location, 4, glm::value_ptr(spotLightColor[0]));

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);


    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema3::RenderWallMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, glm::vec3 lightPosition)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);


    int light_direction_location = glGetUniformLocation(shader->program, "light_direction");
    glUniform3fv(light_direction_location, 1, glm::value_ptr(lightDirection));


    GLint spot_light_location = glGetUniformLocation(shader->program, "spot_light_position");
    glUniform3fv(spot_light_location, 4, glm::value_ptr(spotLightPos[0]));

    GLint spot_light_color_location = glGetUniformLocation(shader->program, "spot_light_color");
    glUniform3fv(spot_light_color_location, 4, glm::value_ptr(spotLightColor[0]));


    // Set shader uniforms for light properties
    GLint light_location = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_location, 1, glm::value_ptr(lightPosition));


    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);


    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema3::RenderSpotLightMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);


    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);


    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}