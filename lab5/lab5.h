#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"
#include "lab_m1/lab5/createObjects.h"
#include "lab_m1/lab5/Tank.h"
#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)


namespace m1
{
    class Lab5 : public gfxc::SimpleScene
    {
     public:
        Lab5();
        ~Lab5();

        struct Building {
            glm::vec3 position;
            int type;
            Mesh* building;
            glm::vec3 color;
        };

        void Init() override;

     private:
         void checkCollision(Tank* tank);
         bool checkCollisionProjectileEnemy(int idx);
         bool checkCollisionProjectilePlayer(int idx, int enidx);
         bool checkCollisionProjectileBuilding(int idx, Tank* tank);
         bool checkCollisionTankBuilding(Tank *tank);

        void FrameStart() override;

        void RenderPlayer(float deltaTimeSeconds);
        void RenderEnemy(float deltaTimeSeconds, int i);
        void RenderProjectilesPlayer(float deltaTimeSeconds);
        void RenderProjectilesEnemies(float deltaTimeSeconds);
        void RenderBuildings(float deltaTimeSeconds);
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, glm::vec3 hp);

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

     protected:
        implemented::Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        glm::vec3 cameraOffset;
        float cameraOffsetVal;
        float cameraHeight;
        float delta;

        // TODO(student): If you need any other class variables, define them here.
        GLfloat fov;
        GLfloat left;
        GLfloat right;
        GLfloat bottom;
        GLfloat top;
        bool perspective;

        Tank* player;
        std::vector<Tank*> enemies;
        int numEnemies;
        glm::vec3 player_forward;

        Mesh* ground;
        vector<Building> buildings;

        float timer;
    };
}   // namespace m1
