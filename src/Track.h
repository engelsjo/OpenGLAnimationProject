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

protected:
public:
    void build (void*);
    void render(bool) const;
};
#endif // TRACK_H_INCLUDED
