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
    TPillar slope1;
    TPillar slope2;
    Cube body;
    Turret turret;
    Track track1;
    Track track2;
    Guard guard;

protected:
public:
    void build (void*);
    void render(bool) const;
};
#endif // TANK_H_INCLUDED
