#include "lab_m1/lab5/lab5.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;
using namespace createObjects;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab5::Lab5()
{
}


Lab5::~Lab5()
{
}

float getAngleToXoZ(glm::vec3 vec) {
    float lenProjection = sqrt(vec.x * vec.x + vec.z * vec.z);
    return atan(vec.y / lenProjection);
}

float distance(glm::vec3 tank1, glm::vec3 tank2) {
    return  sqrt(pow(tank1.x - tank2.x, 2) + pow(tank1.z - tank2.z, 2));
}

bool collisions(glm::vec3 tank1, glm::vec3 tank2, float raza) {
    float dist = distance(tank1, tank2);
    if (dist < 2 * raza)
        return true;
    else
        return false;
}

float ppp(glm::vec3 tank1, glm::vec3 tank2) {
    return abs(3.0f - distance(tank1, tank2));
}


void Lab5::checkCollision(Tank* tank) {
    for (int i = 0; i < numEnemies; i++) {
        if (tank != enemies[i]) {
            if (collisions(tank->getTrackPos(), enemies[i]->getTrackPos(), 1.5)) {

                float p = ppp(tank->getTrackPos(), enemies[i]->getTrackPos());
                glm::vec3 distance = tank->getTrackPos() - enemies[i]->getTrackPos();
                glm::vec3 space = p * glm::normalize(distance);

                tank->Collision(space * 0.5f);
                enemies[i]->Collision(space * -0.5f);
            }
        }
        else {
            if (collisions(tank->getTrackPos(), player->getTrackPos(), 1.5)) {

                float p = ppp(tank->getTrackPos(), player->getTrackPos());
                glm::vec3 distance = tank->getTrackPos() - player->getTrackPos();
                glm::vec3 space = p * glm::normalize(distance);

                tank->Collision(space * 0.5f);
                player->Collision(space * -0.5f);
            }
        }
    }
}

bool Lab5::checkCollisionProjectileEnemy(int idx) {
    for (int i = 0; i < numEnemies; i++) {
        glm::vec3 centerSphere = player->getProjectiles()[idx].position + glm::vec3(player->getProjectiles()[idx].translateX, 0, player->getProjectiles()[idx].translateZ);
        glm::vec3 box = enemies[i]->getTurretPos();
        float x = fmax(box.x - 1.4, fmin(centerSphere.x, box.x + 1.4));
        float y = fmax(box.y - 0.6, fmin(centerSphere.y, box.y + 0.6));
        float z = fmax(box.z - 1.3, fmin(centerSphere.z, box.z + 1.3));

        float distance = sqrt(
            (x - centerSphere.x) * (x - centerSphere.x) +
            (y - centerSphere.y) * (y - centerSphere.y) +
            (z - centerSphere.z) * (z - centerSphere.z));
        if (distance < 0.1) {
            enemies[i]->setHealthPoints();
            if (enemies[i]->getHealthPoints() == 0) {
                player->setPoints();
            }
            return true;
        }
    }
    return false;
}

bool Lab5::checkCollisionProjectilePlayer(int idx, int enidx) {
    for (int i = 0; i < numEnemies; i++) {
        if (i != enidx) {
            glm::vec3 centerSphere = enemies[enidx]->getProjectiles()[idx].position + glm::vec3(enemies[enidx]->getProjectiles()[idx].translateX, 0, enemies[enidx]->getProjectiles()[idx].translateZ);
            glm::vec3 box = enemies[i]->getTurretPos();
            float x = fmax(box.x - 1.4, fmin(centerSphere.x, box.x + 1.4));
            float y = fmax(box.y - 0.6, fmin(centerSphere.y, box.y + 0.6));
            float z = fmax(box.z - 1.3, fmin(centerSphere.z, box.z + 1.3));

            float distance = sqrt(
                (x - centerSphere.x) * (x - centerSphere.x) +
                (y - centerSphere.y) * (y - centerSphere.y) +
                (z - centerSphere.z) * (z - centerSphere.z));
            if (distance < 0.1) {
                enemies[i]->setHealthPoints();
                return true;
            }
        }
        else {
            glm::vec3 centerSphere = enemies[enidx]->getProjectiles()[idx].position + glm::vec3(enemies[enidx]->getProjectiles()[idx].translateX, 0, enemies[enidx]->getProjectiles()[idx].translateZ);
            glm::vec3 box = player->getTurretPos();
            float x = fmax(box.x - 1.4, fmin(centerSphere.x, box.x + 1.4));
            float y = fmax(box.y - 0.6, fmin(centerSphere.y, box.y + 0.6));
            float z = fmax(box.z - 1.3, fmin(centerSphere.z, box.z + 1.3));

            float distance = sqrt(
                (x - centerSphere.x) * (x - centerSphere.x) +
                (y - centerSphere.y) * (y - centerSphere.y) +
                (z - centerSphere.z) * (z - centerSphere.z));
            if (distance < 0.1) {
                player->setHealthPoints();
                return true;
            }
        }
    }
    return false;
}

bool Lab5::checkCollisionProjectileBuilding(int idx, Tank *tank) {
    for (int i = 0; i < 15; i++) {
        glm::vec3 centerSphere = tank->getProjectiles()[idx].position + glm::vec3(tank->getProjectiles()[idx].translateX, 0, tank->getProjectiles()[idx].translateZ);
        glm::vec3 box = buildings[i].position;
        float x, y, z;
        if (buildings[i].type == 0) {
            x = fmax(box.x - 20, fmin(centerSphere.x, box.x + 20));
            y = fmax(box.y - 5, fmin(centerSphere.y, box.y + 5));
            z = fmax(box.z - 5, fmin(centerSphere.z, box.z + 5));
        } else if (buildings[i].type == 1) {
            x = fmax(box.x - 5, fmin(centerSphere.x, box.x + 5));
            y = fmax(box.y - 20, fmin(centerSphere.y, box.y + 20));
            z = fmax(box.z - 5, fmin(centerSphere.z, box.z + 5));
        } else if (buildings[i].type == 2) {
            x = fmax(box.x - 5, fmin(centerSphere.x, box.x + 5));
            y = fmax(box.y - 5, fmin(centerSphere.y, box.y + 5));
            z = fmax(box.z - 20, fmin(centerSphere.z, box.z + 20));
        }

        float distance = sqrt(
            (x - centerSphere.x) * (x - centerSphere.x) +
            (y - centerSphere.y) * (y - centerSphere.y) +
            (z - centerSphere.z) * (z - centerSphere.z));
        if (distance < 0.1) {
            return true;
        }
    }
    return false;
}

bool Lab5::checkCollisionTankBuilding(Tank* tank) {
    bool check = false;
    for (int i = 0; i < 15; i++) {
        glm::vec3 a = tank->getTrackPos();
        glm::vec3 b = buildings[i].position;

        if (buildings[i].type == 0) {
            check = (
                (a.x - 1.5) <= (b.x + 20) &&
                (a.x + 1.5) >= (b.x - 20) &&
                (a.z - 1.5) <= (b.z + 5) &&
                (a.z + 1.5) >= (b.z - 5)
                );
        } else  if (buildings[i].type == 1) {
            check =  (
                (a.x - 1.5) <= (b.x + 5) &&
                (a.x + 1.5) >= (b.x - 5) &&
                (a.z - 1.5) <= (b.z + 5) &&
                (a.z + 1.5) >= (b.z - 5)
                );
        } else  if (buildings[i].type == 2) {
            check = (
                (a.x - 1.5) <= (b.x + 5) &&
                (a.x + 1.5) >= (b.x - 5) &&
                (a.z - 1.5) <= (b.z + 20) &&
                (a.z + 1.5) >= (b.z - 20)
                );
        }
        if (check) {
            float p;
            if (buildings[i].type == 0) {
                float r;
                if ((a.z - 1.5) <= (b.z + 5) && (a.z + 1.5) >= (b.z - 5))
                    r = 20;
                else r = 5;
                p = abs(r + 1.5 -sqrt((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z)));
            } else if (buildings[i].type == 1) {
                float r = 5;
                p = abs(r + 1.5 - sqrt((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z)));
            } else if (buildings[i].type == 2) {
                float r;
                if ((a.z - 1.5) <= (b.z + 20) && (a.z + 1.5) >= (b.z - 20))
                    r = 5;
                else r = 20;
                p = abs(r + 1.5 - sqrt((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z)));
            }
            glm::vec3 distance = a - b;
            glm::vec3 space = p * glm::normalize(distance);

            tank->Collision(space * 0.5f);
        }

    }
    return check;
}

void Lab5::Init()
{
    renderCameraTarget = true;

    camera = new implemented::Camera();

    player = new Tank();
    player->init(15, "player");

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    ground = createGround(glm::vec3(1, 0.4, 0.4), 100);

    for (int i = 0; i < 15; i++) {
        int c = rand() % 3;
        int p = rand() % 3;
        int random1 = rand() % (80 - (10) + 1) + (10);
        int random3 = rand() % (-10 - (-80) + 1) + (-80);
        int random4 = rand() % (-10 - (-80) + 1) + (-80);
        int random2 = rand() % (80 - (10) + 1) + (10);

        if (p == 0) {
            if (c == 0)
                buildings.push_back({ glm::vec3(random1, 0, random2), p,createPPP1(glm::vec3(1, 0.2, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 0.2, 0.2) });
            else if (c == 1)
                buildings.push_back({ glm::vec3(random3, 0, random2), p, createPPP1(glm::vec3(1, 0.6, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 0.6, 0.2) });
            else if (c == 2)
                buildings.push_back({ glm::vec3(random1, 0, random4), p, createPPP1(glm::vec3(1, 1, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 1, 0.2) });
        } else if (p == 1) {
            if (c == 0)
                buildings.push_back({ glm::vec3(random3, 0, random4), p, createPPP2(glm::vec3(1, 0.2, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 0.2, 0.2) });
            else if (c == 1)
                buildings.push_back({ glm::vec3(random1, 0, random4), p, createPPP2(glm::vec3(1, 0.6, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 0.6, 0.2) });
            else if (c == 2)
                buildings.push_back({ glm::vec3(random3, 0, random2), p, createPPP2(glm::vec3(1, 1, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 1, 0.2) });
        } else if (p == 2) {
            if (c == 0)
                buildings.push_back({ glm::vec3(random1, 0, random4), p, createPPP3(glm::vec3(1, 0.2, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 0.2, 0.2) });
            else if (c == 1)
                buildings.push_back({ glm::vec3(random1, 0, random2), p, createPPP3(glm::vec3(1, 0.6, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 0.6, 0.2) });
            else if (c == 2)
                buildings.push_back({ glm::vec3(random1, 0, random4), p, createPPP3(glm::vec3(1, 1, 0.2), 5, "box" + to_string(i)), glm::vec3(1, 1, 0.2) });
        }
    }

    cameraOffsetVal = 5;
    cameraHeight = 2;
    player_forward = player->getDir();
    player_forward.y = 0;
    cameraOffset = glm::vec3(cameraOffsetVal * player_forward.x, cameraHeight, cameraOffsetVal * player_forward.z);
    camera->Set(player->getBodyPos() + cameraOffset, player->getBodyPos(), glm::vec3(0, 1, 0));

    numEnemies = 5;
    for (int i = 0; i < numEnemies; i++) {
        enemies.push_back( new Tank() );
    }

    for (int i = 0; i < numEnemies; i++) {
        enemies[i]->init(1, "enemy");
        bool collided = true;
        while (collided) {
            collided = false;
            enemies[i]->setPos();
            for (int j = 0; j < i; j++) {
                collided = collisions(enemies[i]->getTrackPos(), enemies[j]->getTrackPos(), 1.5);
            }
            collided = checkCollisionTankBuilding(enemies[i]);
        }
    }

    fov = 60.f;
    left = -10.f;
    right = 10.f;
    bottom = -7.f;
    top = 7.f;
    perspective = true;
    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab5", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab5", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    timer = 60;
}


void Lab5::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Lab5::RenderPlayer(float deltaTimeSeconds) 
{
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->getTrackPos());
        modelMatrix = glm::rotate(modelMatrix, player->getTankAngle(), glm::vec3(0, 1, 0));
        RenderSimpleMesh(player->getTrack(), shaders["LabShader"], modelMatrix, glm::vec3(1, 0.8, 0.89), player->getHP_vec());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->getBodyPos());
        modelMatrix = glm::rotate(modelMatrix, player->getTankAngle(), glm::vec3(0, 1, 0));
        RenderSimpleMesh(player->getBody(), shaders["LabShader"], modelMatrix, glm::vec3(0.6, 0, 0.298), player->getHP_vec());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->getTurretPos());
        modelMatrix = glm::rotate(modelMatrix, player->getTankAngle() + player->getTurretAngle(), glm::vec3(0, 1, 0));
        RenderSimpleMesh(player->getTurret(), shaders["LabShader"], modelMatrix, glm::vec3(1, 0, 0.498), player->getHP_vec());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->getCannonPos());
        modelMatrix = glm::rotate(modelMatrix, player->getTankAngle() + player->getTurretAngle(), glm::vec3(0, 1, 0));
        RenderSimpleMesh(player->getCannon(), shaders["LabShader"], modelMatrix, glm::vec3(1, 0.4, 0.698), player->getHP_vec());
    }
}

void Lab5::RenderEnemy(float deltaTimeSeconds, int i) {

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemies[i]->getTrackPos());
        modelMatrix = glm::rotate(modelMatrix, enemies[i]->getTankAngle(), glm::vec3(0, 1, 0));
        RenderSimpleMesh(enemies[i]->getTrack(), shaders["LabShader"], modelMatrix, glm::vec3(0.89, 0.8, 1), enemies[i]->getHP_vec());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemies[i]->getBodyPos());
        modelMatrix = glm::rotate(modelMatrix, enemies[i]->getTankAngle(), glm::vec3(0, 1, 0));
        RenderSimpleMesh(enemies[i]->getBody(), shaders["LabShader"], modelMatrix, glm::vec3(0.298, 0, 0.6), enemies[i]->getHP_vec());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemies[i]->getTurretPos());
        modelMatrix = glm::rotate(modelMatrix, enemies[i]->getTankAngle() + enemies[i]->getTurretAngle(), glm::vec3(0, 1, 0));
        RenderSimpleMesh(enemies[i]->getTurret(), shaders["LabShader"], modelMatrix, glm::vec3(0.6, 0.2, 1), enemies[i]->getHP_vec());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemies[i]->getCannonPos());
        modelMatrix = glm::rotate(modelMatrix, enemies[i]->getTankAngle() + enemies[i]->getTurretAngle(), glm::vec3(0, 1, 0));
        RenderSimpleMesh(enemies[i]->getCannon(), shaders["LabShader"], modelMatrix, glm::vec3(0.8, 0.6, 1), enemies[i]->getHP_vec());
    }
}

void Lab5::RenderProjectilesPlayer(float deltaTimeSeconds) {
    for (int i = 0; i < player->getProjectiles().size(); i++) {

        if (player->getProjectiles()[i].show) {
            glm::mat4 modelMatrix = glm::mat4(1);
            player->setTranslate(deltaTimeSeconds, i);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(player->getProjectiles()[i].translateX, 0, player->getProjectiles()[i].translateZ));
            modelMatrix = glm::translate(modelMatrix, player->getProjectiles()[i].position);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
            RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, glm::vec3(0.2, 0, 0.0196), glm::vec3(3));

            if (checkCollisionProjectileEnemy(i) || checkCollisionProjectileBuilding(i, player)) {
                player->updatePLife(i);
            }
        }
    }
}

void Lab5::RenderProjectilesEnemies(float deltaTimeSeconds) {
    for (int j = 0; j < numEnemies; j++) {
        for (int i = 0; i < enemies[j]->getProjectiles().size(); i++) {

            if (enemies[j]->getProjectiles()[i].show) {
                glm::mat4 modelMatrix = glm::mat4(1);
                enemies[j]->setTranslate(deltaTimeSeconds, i);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(enemies[j]->getProjectiles()[i].translateX, 0, enemies[j]->getProjectiles()[i].translateZ));
                modelMatrix = glm::translate(modelMatrix, enemies[j]->getProjectiles()[i].position);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
                RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, glm::vec3(0.2, 0, 0.2), glm::vec3(3));

                if (checkCollisionProjectilePlayer(i, j) || checkCollisionProjectileBuilding(i, enemies[j])) {
                    enemies[j]->updatePLife(i);
                }
            }
        }
    }
}



void Lab5::RenderBuildings(float deltaTimeSeconds) {
    for (int i = 0; i < 15; i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, buildings[i].position);
        RenderSimpleMesh(buildings[i].building, shaders["LabShader"], modelMatrix, buildings[i].color, glm::vec3(3));
    }
}

void Lab5::Update(float deltaTimeSeconds)
{
    glm::vec3 cen = glm::normalize(player->getTrackPos());
    if (renderCameraTarget) {
        player_forward = player->getDir();
        player_forward.y = 0;
        cameraOffset = glm::vec3(cameraOffsetVal * player_forward.x, cameraHeight, cameraOffsetVal * player_forward.z);
        camera->Set(player->getBodyPos() + cameraOffset, player->getBodyPos(), glm::vec3(0, 1, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderSimpleMesh(ground, shaders["LabShader"], modelMatrix, glm::vec3(1, 0.4, 0.4), glm::vec3(3));
    }

    RenderBuildings(deltaTimeSeconds);

    RenderPlayer(deltaTimeSeconds);

    for (int i = 0; i < numEnemies; i++) {
        RenderEnemy(deltaTimeSeconds, i);
    }
    if (timer > 0 && player->getHealthPoints() > 0) {
        for (int i = 0; i < numEnemies; i++) {
            if (enemies[i]->getHealthPoints() > 0) {
                enemies[i]->updateMotion(deltaTimeSeconds);
            }
            enemies[i]->update(deltaTimeSeconds);
            checkCollision(enemies[i]);
            checkCollisionTankBuilding(enemies[i]);
            if (distance(player->getTrackPos(), enemies[i]->getTrackPos()) < 20) {
                
                enemies[i]->rotateTurret(deltaTimeSeconds, player);
            }
        }
    }

    player->update(deltaTimeSeconds);
    RenderProjectilesPlayer(deltaTimeSeconds);
    RenderProjectilesEnemies(deltaTimeSeconds);

    if (player->getHealthPoints() > 0 && timer > 0) {
        timer -= deltaTimeSeconds;
    }
    else if (player->getHealthPoints() <= 0 && timer > 0){
        printf("GAME OVER\n");
    }
    else if (player->getHealthPoints() > 0 && timer <= 0) {
        printf("SCORE: %d\n", player->getPoints());
    }
}


void Lab5::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Lab5::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, glm::vec3 hp)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    int location = glGetUniformLocation(shader->GetProgramID(), "Model");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));


    // Bind view matrix
    location = glGetUniformLocation(shader->GetProgramID(), "View");
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    location = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    location = glGetUniformLocation(shader->GetProgramID(), "object_color");
    glUniform3fv(location, 1, glm::value_ptr(color));

    location = glGetUniformLocation(shader->GetProgramID(), "health_points");
    glUniform3fv(location, 1, glm::value_ptr(hp));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}



/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab5::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    delta = deltaTime;
        // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {

    }
    else  if (timer > 0 && player->getHealthPoints() > 0) {
        if (window->KeyHold(GLFW_KEY_W)) {
            player->move(deltaTime, true);
            checkCollision(player);
            checkCollisionTankBuilding(player);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            player->rotateTank(deltaTime, true);
            checkCollision(player);
            checkCollisionTankBuilding(player);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            player->move(deltaTime, false);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            player->rotateTank(deltaTime, false);
        }
    }

}


void Lab5::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
}


void Lab5::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;
        // Rotate the camera in third-person mode around
        // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
        // variables for setting up the rotation speed.
        camera->RotateThirdPerson_OX(-deltaY * sensivityOY);
        camera->RotateThirdPerson_OY(-deltaX * sensivityOX);
        
    }
    else {
            if ((720 - mouseY) > 360) {
                player->rotateTurret(deltaX * 2.0f, NULL);
            }
            else {
                player->rotateTurret(-deltaX * 2.0f, NULL);

            }
        
    }
}


void Lab5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1 && timer > 0) {
        if (player->canShoot <= 0 && player->getHealthPoints() > 0) {
            player->shoot();
        }
    }
}


void Lab5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab5::OnWindowResize(int width, int height)
{
}
