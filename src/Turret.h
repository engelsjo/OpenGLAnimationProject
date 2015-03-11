//created by Zach Ash

#ifndef TURRET_H_INCLUDED
#define TURRET_H_INCLUDED

#include "BufferObject.h"
#include "Cylinder.h"
#include "Cube.h"
#include "TPillar.h"
class Turret : public BufferObject {
private:
    Cylinder barrel;
    Cube turret;

protected:
public:
    void build (void*);
    void render(bool) const;
};
#endif // TURRET_H_INCLUDED
