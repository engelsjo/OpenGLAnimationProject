//
//  Cube.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/3/15.
//
//

#ifndef __ProjectOne__Cube__
#define __ProjectOne__Cube__

#include <stdio.h>
#include "BufferObject.h"
class Cube : public BufferObject {
private:
    float LENGTH = 1.0;
    float WIDTH = 1.0;
    float HEIGHT = 1.0; /* half thick */
    int top_count;
    float COLOR_R = 255;
    float COLOR_G = 255;
    float COLOR_B = 255;
    
protected:
public:
    void build (void*);
    void build_with_params(float length, float width, float height, float r, float g, float b);
    void render(bool) const;
};
#endif /* defined(__ProjectOne__Cube__) */


