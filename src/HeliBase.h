//
//  HeliBase.h
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/11/15.
//
//

#ifndef __ProjectTwo__HeliBase__
#define __ProjectTwo__HeliBase__

#include <stdio.h>
#include "BufferObject.h"
#include "Cylinder.h"
#include "Cube.h"
class HeliBase : public BufferObject {
private:
    //bottom stand of copter
    Cylinder stand_large;
    Cylinder stand_small;
    
    //tail part
    Cylinder tail;
    
    //main frame
    Cube main_frame;
    
    //front of copter
    Cylinder windshield;
    Cylinder rear;
    
protected:
public:
    void build (void*);
    void render(bool) const;
};

#endif /* defined(__ProjectTwo__HeliBase__) */
