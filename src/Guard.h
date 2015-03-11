//created by Zach Ash

#ifndef GUARD_H_INCLUDED
#define GUARD_H_INCLUDED

#include "BufferObject.h"
#include "Cube.h"
class Guard : public BufferObject {
private:
    Cube mainBar;
    Cube sideBar;

protected:
public:
    void build (void*);
    void render(bool) const;
};
#endif // GUARD_H_INCLUDED
