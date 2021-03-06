#include "Cylinder.h"
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include "ReflectanceTable.h"

Cylinder::~Cylinder() {
    glDeleteBuffers(1, &v_buf);
    glDeleteBuffers(1, &i_buf);
    glDeleteBuffers(1, &n_buf);
}

void Cylinder::build(float topRad, float botRad, float height, string material) {
    
    MATERIAL = material;
    
    glGenBuffers (1, &v_buf);
    glGenBuffers (1, &i_buf);
    glGenBuffers (1, &n_buf);
    float delta = 2 * M_PI / N_POINTS;

    /* points in top ring */

    float angle = 0.0f;
    for (int k = 0; k  < N_POINTS; k++)
    {
        float x = topRad * cos(angle);
        float y = topRad * sin(angle);
        vertices.push_back (x);
        vertices.push_back (y);
        vertices.push_back (height/2);
        angle += delta;

    }

    /* vertices at the bottom ring */
    angle = 0.0f;
    for (int k = 0; k  < N_POINTS; k++)
    {
        float x = botRad * cos(angle);
        float y = botRad * sin(angle);
        vertices.push_back (x);
        vertices.push_back (y);
        vertices.push_back (-height/2);
        angle += delta;
    }

    /* push the TOP CENTER point */
    vertices.push_back (0);  /* x */
    vertices.push_back (0); /* y */
    vertices.push_back (height/2); /* z */
    
    // push the BOTTOM CENTER point
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(-height/2);


    for (int n = 0; n < 2; n++) {
        angle = 0;
        for (int k = 0; k < N_POINTS; k++) {
            float xTop = topRad * cos(angle);
            float yTop = topRad * sin(angle);
            float xBot = botRad * cos(angle);
            float yBot = botRad * sin(angle);
            glm::vec3 vertTangent{xTop - xBot, yTop - yBot, height};
            glm::vec3 horTangent{sin(angle), -cos(angle), 0};
            glm::vec3 normal = glm::normalize(glm::cross(vertTangent, horTangent));
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
            angle += delta;
        }
    }
    normals.push_back(0); /* normal vector for the top center vertice */
    normals.push_back(0);
    normals.push_back(1.0f);
    
    normals.push_back(0);
    normals.push_back(0);
    normals.push_back(-1);

    /* fill in the vertices */

    for (int k = 0; k < N_POINTS; k++)
    {
        index.push_back (k);
        index.push_back (k + N_POINTS);
    }
    /* close the quad_strip_index for wall */
    index.push_back (0);
    index.push_back (N_POINTS);

    /* first index of the tri-fan */
    index.push_back (N_POINTS * 2);
    /* index of rest of the tri-fan */
    for (int k = 0; k < N_POINTS; k++)
        index.push_back (k);
    /* close the last arc of the tri-fan */
    index.push_back (0);
    
    
    //bottom tri fan
    index.push_back(N_POINTS * 2 + 1);
    for (int k = 2 * N_POINTS - 1; k >= N_POINTS; k--){
        index.push_back(k);
    }
    index.push_back(2 * N_POINTS -1);


    /* copy the two CPU arrays to GPU */

    /* select the buffer */
    glBindBuffer (GL_ARRAY_BUFFER, v_buf);
    /* allocate in GPU and copy from CPU */
    glBufferData (GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
            vertices.data(), GL_STATIC_DRAW);
    /* deselect the buffer */
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    /* select the buffer */
    glBindBuffer (GL_ARRAY_BUFFER, n_buf);
    /* allocate in GPU and copy from CPU */
    glBufferData (GL_ARRAY_BUFFER, normals.size() * sizeof(float),
            normals.data(), GL_STATIC_DRAW);
    /* deselect the buffer */
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, i_buf);
    /* allocate in GPU and copy from CPU */
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLushort),
            index.data(), GL_STATIC_DRAW);
    /* deselect the buffer */
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    
    
    //init the lookup_table
    ReflectanceTable material_table;
    material_table.init_table();
    
    vector<float> ambient_v = material_table.lookup_table[MATERIAL]["AMBIENT"];
    vector<float> diffuse_v = material_table.lookup_table[MATERIAL]["DIFFUSE"];
    vector<float> specular_v = material_table.lookup_table[MATERIAL]["SPECULAR"];
    float shininess = material_table.lookup_table[MATERIAL]["SHININESS"][0];
    
    for(int i = 0; i < 4; i++) {
        AMBIENT[i] = ambient_v[i];
        DIFFUSE[i] = diffuse_v[i];
        SPECULAR[i] = specular_v[i];
    }
    SHININESS = shininess;
}

void Cylinder::render() const {
    //set up light components
    glMaterialfv(GL_FRONT, GL_AMBIENT, AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS);
    /* select the buffs */
    glPushAttrib(GL_ENABLE_BIT);
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glBindBuffer (GL_ARRAY_BUFFER, v_buf);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, n_buf);
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, i_buf);

    int N = 2*N_POINTS + 2;
    glDrawElements (GL_QUAD_STRIP, N, GL_UNSIGNED_SHORT, 0);
    glDrawElements (GL_TRIANGLE_FAN, N_POINTS + 2, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * N));
    glDrawElements (GL_TRIANGLE_FAN, N_POINTS + 2, GL_UNSIGNED_SHORT,
                    (void *) (sizeof(GLushort) * (N + N_POINTS + 2)));

    /* deselect the buffs */
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopAttrib();
}
