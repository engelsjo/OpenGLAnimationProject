//
//  Blade.h
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/12/15.
//
//

#ifndef __ProjectTwo__Blade__
#define __ProjectTwo__Blade__

#include <stdio.h>
#include "BufferObject.h"
#include "Cylinder.h"
#include "Cube.h"
class Blade : public BufferObject {
private:
    Cylinder center;
    Cube blade;
    
protected:
public:
    void build (void*);
    void render(bool) const;
};

#endif /* defined(__ProjectTwo__Blade__) */
