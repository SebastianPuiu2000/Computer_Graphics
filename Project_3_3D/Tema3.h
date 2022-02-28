#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"

namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
     public:
         Tema3();
        ~Tema3();

        void Init() override;

        struct Colour
        {
            float R;
            float G;
            float B;
        };

        struct DancerInfo
        {
            float X = 0.0;
            float Y = 0.0;
            float Z = 0.0;

            int lockX = 0;
            float timerX = 0.0;

            int lockZ = 0;
            float timerZ = 0.0;

            int randX = 0;
            int randZ = 0;
        };

        struct ConeInfo
        {
            int lockX = 0;
            float timerX = 0.0;

            int lockZ = 0;
            float timerZ = 0.0;

            int randX = 0;
            int randZ = 0;
        };

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

        void ColorMatrixGenerator();

        void MeshesGenerator();
        void BoxMeshGenerator();
        void SphereMeshGenerator();
        void ConeMeshGenerator();

        void ShadersGenerator();
        void DancerShaderGenerator();
        void GroundhaderGenerator();
        void SpotLightShaderGenerator();
        void WallShaderGenerator();

        void DancerSpawner();
        void SpotLightSpawner();

        void RenderDancers(float deltaTimeSeconds);
        void RenderDancer(float deltaTimeSeconds, DancerInfo &dancer);
        void MoveDancer(float deltaTimeSeconds, DancerInfo &dancer);

        void RenderSpotLights(float deltaTimeSeconds);
        void MoveSpotLights(float deltaTimeSeconds);

        void RenderGround();

        void RenderWalls();

        void RenderDancerMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int numberLights, const glm::vec3& color = glm::vec3(1));
        void RenderWallMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, glm::vec3 groundLightPosition);
        void RenderGroundMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void RenderSpotLightMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);


        glm::vec3 lightDirection;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        glm::mat4 modelMatrix, visMatrix;

        int wallX, wallY, wallZ;
        int ground_width, ground_height;

        float R, G, B;
        int dance_mode;

        int dancersNumber;
        DancerInfo* dancers;

        ConeInfo cone;

        Colour* colourMatrix;

        int lightsNumber;
        glm::vec3 *lightPos;
        glm::vec3 *lightColor;

        int spotLightsNumber;
        glm::vec3 *spotLightPos;
        glm::vec3 *spotLightColor;

    };
}   // namespace m1
