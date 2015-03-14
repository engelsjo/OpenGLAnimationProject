//
//  GLUquadricSphere.cpp
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/14/15.
//
//

#include "GLUquadricSphere.h"
#include "ReflectanceTable.h"
#include <vector>
#include <GLUT/GLUT.h>

using namespace std;
void GLUquadricSphere::build() {
    q_cyl = gluNewQuadric();
    
    /* control the direction of normal vectors */
    gluQuadricOrientation (q_cyl, GLU_OUTSIDE);
    
    /* control the generation of normal vectors: one normal per vertex */
    gluQuadricNormals (q_cyl, GLU_SMOOTH);
    
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

void GLUquadricSphere::render() {
    /* more code here for rendering other components */
    glMaterialfv(GL_FRONT, GL_AMBIENT, AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS);
    gluSphere(q_cyl, 7.5, 25, 25);
}