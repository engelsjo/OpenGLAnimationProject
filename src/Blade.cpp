//
//  Blade.cpp
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/12/15.
//
//

#include "Blade.h"

void Blade::build (void*)
{
    center.build(.5, .5, 1, "Chrome");
    blade.build_with_params(.25, 16, 1, "Chrome");
    
}


void Blade::render(bool) const
{
    //center of the blade
    glPushMatrix();
    glTranslatef(0, 0, .5);
    center.render();
    glPopMatrix();
    
    //blade 1 portion
    glPushMatrix();
    glTranslatef(0, 0, 1);
    blade.render(false);
    glPopMatrix();
    
    //blade 2 portion
    glPushMatrix();
    glTranslatef(0, 0, 1);
    glRotatef(90, 0, 0, 1);
    blade.render(false);
    glPopMatrix();
    
    
    
}
