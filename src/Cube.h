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
    vector<float> ambient_v;
    vector<float> diffuse_v;
    vector<float> specular_v;
    float shininess;

    float LENGTH = 1.0;
    float WIDTH = 1.0;
    float HEIGHT = 1.0; /* half thick */
    string MATERIAL = "Copper";
    int top_count;

protected:
public:
    void build (void*);
    void build_with_params(float length, float width, float height, string material);
    void render(bool) const;
};
#endif /* defined(__ProjectOne__Cube__) */


