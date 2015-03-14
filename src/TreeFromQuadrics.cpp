//
//  TreeFromQuadrics.cpp
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/14/15.
//
//

#include "TreeFromQuadrics.h"
void TreeFromQuadrics::build ()
{
    //build the two parts of the tree
    cyl.build();
    sphere.build();
    
}


void TreeFromQuadrics::render()
{
    //center of the
    glPushMatrix();
    cyl.render();
    glPopMatrix();
    
    //render the top of the tree
    glPushMatrix();
    glTranslatef(0, 0, 15);
    sphere.render();
    glPopMatrix();

    
    
    
}