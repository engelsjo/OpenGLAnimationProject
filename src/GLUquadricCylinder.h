//
//  GLUquadricCylinder.h
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/14/15.
//
//

#ifndef __ProjectTwo__GLUquadricCylinder__
#define __ProjectTwo__GLUquadricCylinder__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <string>
using namespace std;
class GLUquadricCylinder{
    
public:
    string MATERIAL = "Copper";
    float AMBIENT[4];
    float DIFFUSE[4];
    float SPECULAR[4];
    float SHININESS;
    GLUquadric* q_cyl;
    void build();
    void render();
};


#endif /* defined(__ProjectTwo__GLUquadricCylinder__) */
