//
//  TPillar.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/7/15.
//
//  Triangular Pillar for the front of the Castle

#ifndef __ProjectOne__TPillar__
#define __ProjectOne__TPillar__

#include <stdio.h>
#include "BufferObject.h"
#include "ReflectanceTable.h"

class TPillar : public BufferObject {
private:
    float LENGTH = 1;
    float WIDTH = .5;
    float HEIGHT = 1;

    string MATERIAL = "Jade";


protected:
public:
    void build (void*);
    void build_with_params(float length, float width, float height, string material);
    void render(bool) const;
};

#endif /* defined(__ProjectOne__TPillar__) */


