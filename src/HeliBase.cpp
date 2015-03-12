//
//  HeliBase.cpp
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/11/15.
//
//

#include "HeliBase.h"
#include <math.h>


void HeliBase::build (void*)
{
    
    stand_large.build(.5, .5, 6, "Black Rubber");
    stand_small.build(.5, .5, 1.5, "Black Rubber");
    main_frame.build_with_params(4, 8, 4.5, "Ruby");
    windshield.build(2, 2, 4.25, "Black Plastic");
    rear.build(2, .5, 8, "Obsidian");
    
}


void HeliBase::render(bool) const
{
    vector<double> y_vals ={-2, 2};
    for (auto y: y_vals){
        //render the long stands of the legs
        glPushMatrix();
        glTranslatef(0, y, .25);
        glRotatef(90, 0, 1, 0);
        stand_large.render();
        glPopMatrix();
        
        //render the front skiis
        glPushMatrix();
        glTranslatef(2.8, 0, 0);
        glTranslatef(0, y, .75*sin(45));
        glRotatef(45, 0, 1, 0);
        stand_small.render();
        glPopMatrix();
        
        //render two vert stands
        glPushMatrix();
        glTranslatef(0, y, 1);
        stand_small.render();
        glPopMatrix();
        
    }
    
    //render the main frame
    glPushMatrix();
    glTranslatef(0, 0, 3.75);
    main_frame.render(false);
    glPopMatrix();
    
    //render wind shield
    glPushMatrix();
    glTranslatef(4, 0, 3.75);
    glRotatef(90, 1, 0, 0);
    windshield.render();
    glPopMatrix();
    
    //render the rear
    glPushMatrix();
    glTranslatef(-8, 0, 3.75);
    glRotatef(90, 0, 1, 0);
    rear.render();
    glPopMatrix();

    
    
}
