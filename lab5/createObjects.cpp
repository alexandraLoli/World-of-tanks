#include "createObjects.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;

Mesh* createObjects::createTrack(glm::vec3 color, float scale, string name) {

	Mesh* track = new Mesh(name);
    std::vector<VertexFormat> vertices
    {

        //0-19
        VertexFormat(glm::vec3(5 * scale, 3 * scale,  15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(15 * scale, 3 * scale, 15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(5 * scale, 0 * scale,  15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(15 * scale, 0 * scale,  15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(5 * scale, -3 * scale,  12 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(15 * scale, -3 * scale,  12 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(5 * scale, 3 * scale,  -15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(15 * scale, 3 * scale, -15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(5 * scale, 0 * scale,  -15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(15 * scale, 0 * scale,  -15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(5 * scale, -3 * scale,  -12 * scale), glm::vec3(0, 1, 1),color),
        VertexFormat(glm::vec3(15 * scale, -3 * scale,  -12 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(15 * scale, 3 * scale,  12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(15 * scale, 0 * scale,  12 * scale), glm::vec3(1, 0, 0),color),
        VertexFormat(glm::vec3(15 * scale, 3 * scale,  -12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(15 * scale, 0 * scale,  -12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(5 * scale, 3 * scale,  12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(5 * scale, 0 * scale,  12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(5 * scale, 3 * scale,  -12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(5 * scale, 0 * scale,  -12 * scale), glm::vec3(1, 0, 0), color),

        //20-39
        VertexFormat(glm::vec3(-15 * scale, 3 * scale,  15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-5 * scale, 3 * scale, 15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-15 * scale, 0 * scale,  15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-5 * scale, 0 * scale,  15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-15 * scale, -3 * scale,  12 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-5 * scale, -3 * scale,  12 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-15 * scale, 3 * scale,  -15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-5 * scale, 3 * scale, -15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-15 * scale, 0 * scale,  -15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-5 * scale, 0 * scale,  -15 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-15 * scale, -3 * scale,  -12 * scale), glm::vec3(0, 1, 1),color),
        VertexFormat(glm::vec3(-5 * scale, -3 * scale,  -12 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-5 * scale, 3 * scale,  12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(-5 * scale, 0 * scale,  12 * scale), glm::vec3(1, 0, 0),color),
        VertexFormat(glm::vec3(-5 * scale, 3 * scale,  -12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(-5 * scale, 0 * scale,  -12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(-15 * scale, 3 * scale,  12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(-15 * scale, 0 * scale,  12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(-15 * scale, 3 * scale,  -12 * scale), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(-15 * scale, 0 * scale,  -12 * scale), glm::vec3(1, 0, 0), color),
    };

    std::vector<unsigned int> indices
    {
        // fata
        0, 2, 1,
        1, 2, 3,
        2, 4, 3,
        3, 4, 5,
        // lateral fata
        1, 3, 12,
        12, 3, 13,
        3, 5, 13,
        12, 5, 14,
        14, 5, 11,
        14, 15, 9,
        14, 9, 7,
        15, 11, 9,
        // sus
        0, 1, 7,
        0, 7, 6,
        //jos
        4, 11, 5,
        4, 10, 11,
        //lateral spate
        0, 16, 17,
        0, 17, 2,
        2, 17, 4,
        16, 18, 10,
        16, 10, 4,
        18, 6, 8,
        18, 8, 19,
        19, 8, 10,
        // spate
        6, 7, 8,
        7, 9, 8,
        8, 9, 11,
        8, 11, 10,


        // fata
       20, 22, 21,
       21, 22, 23,
       22, 24, 23,
       23, 24, 25,
       // lateral fata
       21, 23, 32,
       32, 23, 33,
       23, 25, 33,
       32, 25, 34,
       34, 25, 31,
       34, 35, 29,
       34, 29, 27,
       35, 31, 29,
       // sus
       20, 21, 27,
       20, 27, 26,
       //jos
       24, 31, 25,
       24, 30, 31,
       //lateral spate
       20, 36, 37,
       20, 37, 22,
       22, 37, 24,
       36, 38, 30,
       36, 30, 24,
       38, 26, 28,
       38, 28, 39,
       39, 28, 30,
       // spate
       26, 27, 28,
       27, 29, 28,
       28, 29, 31,
       28, 31, 30,
    };

    track->SetDrawMode(GL_TRIANGLES);
    track->InitFromData(vertices, indices);
    return track;
}


Mesh* createObjects::createBody(glm::vec3 color, float scale, string name) {

    Mesh* body = new Mesh(name);
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-14 * scale, 6 * scale,  10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(14 * scale, 6 * scale, 10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-14 * scale, -6 * scale,  13 * scale), glm::vec3(0, 1, 1),color),
        VertexFormat(glm::vec3(14 * scale, -6 * scale,  13 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-14 * scale, 6 * scale,  -10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(14 * scale, 6 * scale, -10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-14 * scale, -6 * scale,  -13 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(14 * scale, -6 * scale,  -13 * scale), glm::vec3(0, 1, 1), color),
    };

    std::vector<unsigned int> indices
    {
        //fata
        0, 2, 1,
        1, 2, 3,
        //spate
        4, 5, 6,
        5, 7, 6,
        //lateral fata
        1, 3, 5,
        5, 3, 7,
        //lateral spate
        0, 4, 2,
        4, 6, 2,
        // jos
        2, 6, 7,
        2, 7, 3,
        //sus
        0, 1, 5,
        0, 5, 4,
    };

    body->SetDrawMode(GL_TRIANGLES);
    body->InitFromData(vertices, indices);
    return body;
}

Mesh* createObjects::createTurret(glm::vec3 color, float scale, string name) {

    Mesh* turret = new Mesh(name);
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-14 * scale, 3 * scale,  4 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(14 * scale, 3 * scale, 4 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-14 * scale, -3 * scale,  6 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(14 * scale, -3 * scale,  6 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-14 * scale, 3 * scale,  -2 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(14 * scale, 3 * scale, -2 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-14 * scale, -3 * scale,  -6 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(14 * scale, -3 * scale,  -6 * scale), glm::vec3(0, 1, 1), color),
    };

    std::vector<unsigned int> indices
    {
        //fata
        0, 2, 1,
        1, 2, 3,
        //spate
        4, 5, 6,
        5, 7, 6,
        //lateral fata
        1, 3, 5,
        5, 3, 7,
        //lateral spate
        0, 4, 2,
        4, 6, 2,
        // jos
        2, 6, 7,
        2, 7, 3,
        //sus
        0, 1, 5,
        0, 5, 4,
    };

    turret->SetDrawMode(GL_TRIANGLES);
    turret->InitFromData(vertices, indices);
    return turret;
}

Mesh* createObjects::createCannon(glm::vec3 color, float scale, string name) {

    Mesh* cannon = new Mesh(name);
    std::vector<VertexFormat> vertices
    {
        // 0, 1, 2, 3, 4, 5, 6
        VertexFormat(glm::vec3(0 * scale, 0 * scale,  10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-6 * scale, 4 * scale, 10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0.5 * scale, 7 * scale,  10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(6.5 * scale, 3.3 * scale,  10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(6 * scale, -4 * scale,  10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-0.5 * scale, -7.3 * scale, 10 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-6.5 * scale, -3.3 * scale,  10 * scale), glm::vec3(0, 1, 1), color),

        //7, 8, 9, 10, 11, 12, 13
        VertexFormat(glm::vec3(-6 * scale, 4 * scale, -60 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0.5 * scale, 7 * scale,  -60 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(6.5 * scale, 3.3 * scale,  -60 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(6 * scale, -4 * scale,  -60 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-0.5 * scale, -7.3 * scale, -60 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-6.5 * scale, -3.3 * scale,  -60 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0 * scale, 0 * scale,  -60 * scale), glm::vec3(0, 1, 1), color),
    };

    std::vector<unsigned int> indices
    {
        //hexagon fata
        1, 0, 2,
        2, 0, 3,
        3, 0, 4,
        4, 0, 5,
        5, 0, 6,
        6, 0, 1,
        //hexagoh spate
        7, 13, 12,
        12, 13, 11,
        11, 13, 10,
        10, 13, 9,
        9, 13, 8,
        8, 13, 7,
        //latura 1-2
        1, 2, 8,
        1, 8, 7,
        //latura 2-3
        2, 3, 9,
        2, 9, 8,
        //latura 3-4
        3, 4, 10,
        3, 10, 9,
        //latura 4-5
        5, 10, 4,
        5, 11, 10,
        //latura 5-6
        6, 11, 5,
        6, 12, 11,
        //latura 6-1
        1, 7, 12,
        1, 12, 6
    };

    cannon->SetDrawMode(GL_TRIANGLES);
    cannon->InitFromData(vertices, indices);
    return cannon;
}

Mesh* createObjects::createGround(glm::vec3 color, float scale) {
    Mesh* ground = new Mesh("ground");
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-1 * scale, 0 * scale,  -1 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(1 * scale, 0 * scale,  -1 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(1 * scale, 0 * scale,  1 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-1 * scale, 0 * scale,  1 * scale), glm::vec3(0, 1, 1), color),
    };

    std::vector<unsigned int> indices
    {
        0, 1, 3,
        1, 2, 3,
    };

    ground->SetDrawMode(GL_TRIANGLES);
    ground->InitFromData(vertices, indices);
    return ground;
}
Mesh* createObjects::createPPP1(glm::vec3 color, float scale, string name) {
    printf(name.c_str());
    Mesh* cube = new Mesh(name);
    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-4 * scale, -1 * scale, 1 * scale), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(4 * scale, -1 * scale,  1 * scale), glm::vec3(1, 0, 1),  color),
        VertexFormat(glm::vec3(-4 * scale, 1 * scale,  1 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(4 * scale, 1 * scale,  1 * scale), glm::vec3(1, 0, 1),  color),
        VertexFormat(glm::vec3(-4 * scale, -1 * scale,  -1 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(4 * scale, -1 * scale,  -1 * scale), glm::vec3(1, 0, 1),  color),
        VertexFormat(glm::vec3(-4 * scale, 1 * scale,  -1 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(4 * scale, 1 * scale,  -1 * scale), glm::vec3(1, 0, 1),  color),


        // TODO(student): Complete the vertices data for the cube mesh

    };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4,

    };
    cube->SetDrawMode(GL_TRIANGLES);
    cube->InitFromData(vertices, indices);
    return cube;
}

Mesh* createObjects::createPPP2(glm::vec3 color, float scale, string name) {
    Mesh* cube = new Mesh(name);
    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-1 * scale, -4 * scale, 1 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(1 * scale, -4 * scale,  1 * scale), glm::vec3(1, 0, 1),  color),
        VertexFormat(glm::vec3(-1 * scale, 4 * scale,  1 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(1 * scale, 4 * scale,  1 * scale), glm::vec3(1, 0, 1),  color),
        VertexFormat(glm::vec3(-1 * scale, -4 * scale,  -1 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(1 * scale, -4 * scale,  -1 * scale), glm::vec3(1, 0, 1),  color),
        VertexFormat(glm::vec3(-1 * scale, 4 * scale,  -1 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(1 * scale, 4 * scale,  -1 * scale), glm::vec3(1, 0, 1),  color),


        // TODO(student): Complete the vertices data for the cube mesh

    };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4,

    };
    cube->SetDrawMode(GL_TRIANGLES);
    cube->InitFromData(vertices, indices);
    return cube;
}

Mesh* createObjects::createPPP3(glm::vec3 color, float scale, string name) {
    Mesh* cube = new Mesh(name);
    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-1 * scale, -1 * scale, 4 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(1 * scale, -1 * scale,  4 * scale), glm::vec3(1, 0, 1),  color),
        VertexFormat(glm::vec3(-1 * scale, 1 * scale,  4 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(1 * scale, 1 * scale,  4 * scale), glm::vec3(1, 0, 1),  color),
        VertexFormat(glm::vec3(-1 * scale, -1 * scale,  -4 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(1 * scale, -1 * scale,  -4 * scale), glm::vec3(1, 0, 1), color),
        VertexFormat(glm::vec3(-1 * scale, 1 * scale,  -4 * scale), glm::vec3(0, 1, 1),  color),
        VertexFormat(glm::vec3(1 * scale, 1 * scale,  -4 * scale), glm::vec3(1, 0, 1),  color),


        // TODO(student): Complete the vertices data for the cube mesh

    };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4,

    };
    cube->SetDrawMode(GL_TRIANGLES);
    cube->InitFromData(vertices, indices);
    return cube;
}

