//created by Zach Ash

#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

#include "BufferObject.h"
#include "Turret.h"
#include "Guard.h"
#include "Track.h"
#include "TPillar.h"
#include "Cube.h"
class Tank : public BufferObject {
private:
    Cube body;
    Turret turret;
    Track track1;
    Track track2;
    Guard guard;
    TPillar slope1;
    TPillar slope2;

protected:
public:
    float turret_position;

    void build (void*);
    void render(bool) const;
    void update(float r, float l, float t);
};
#endif // TANK_H_INCLUDED
