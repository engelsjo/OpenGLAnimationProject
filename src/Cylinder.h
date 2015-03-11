#ifndef MY_CYLINDER_H
#define MY_CYLINDER_H

#include <vector>
#include <GL/glew.h>
#include "BufferObject.h"
using namespace std;

class Cylinder{
private:
    const int N_POINTS = 20;
//    const float TOP_RAD = 1.0f;
//    const float BOT_RAD = 0.8f;
//    const float CONE_HEIGHT = 0.5f;
    GLuint v_buf, i_buf, n_buf;
    vector<float> vertices, normals;
    vector<GLushort> index;
    string MATERIAL = "Copper";
    float AMBIENT[4];
    float DIFFUSE[4];
    float SPECULAR[4];
    float SHININESS;

public:
    ~Cylinder();
    void build(float topRad, float botRad, float height, string material);
    void render() const;
};
#endif
