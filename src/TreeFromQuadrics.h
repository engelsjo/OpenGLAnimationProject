//
//  TreeFromQuadrics.h
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/14/15.
//
//

#ifndef __ProjectTwo__TreeFromQuadrics__
#define __ProjectTwo__TreeFromQuadrics__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <string>
#include "GLUquadricSphere.h"
#include "GLUquadricCylinder.h"
using namespace std;
class TreeFromQuadrics{
    
public:
    GLUquadricSphere sphere;
    GLUquadricCylinder cyl;
    void build();
    void render();
};

#endif /* defined(__ProjectTwo__TreeFromQuadrics__) */
