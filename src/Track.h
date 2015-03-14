//created by Zach Ash

#ifndef TRACK_H_INCLUDED
#define TRACK_H_INCLUDED

#include "BufferObject.h"
#include "Cylinder.h"
#include "Cube.h"
class Track : public BufferObject {
private:
    Cylinder wheel;
    Cube tread;
    float distance_travelled;

protected:
public:
    void build (void*);
    void render(bool) const;
    void update(float);
};
#endif // TRACK_H_INCLUDED
