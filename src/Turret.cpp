//created by Zach Ash

#include "Turret.h"

void Turret::build (void* v) {
    turret.build_with_params(2, 3, 3, 200, 100, 100);
    barrel.build(.3,.3,4);
}

void Turret::render(bool b) const {
    glPushMatrix();
    glTranslatef(0,0,1);
    turret.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,0,1);
    glRotatef(90,0,1,0);
    barrel.render();
    glPopMatrix();
}
