//created by Zach Ash

#include "Turret.h"

void Turret::build (void* v) {
    turret.build_with_params(2, 3, 3, "Gold");
    barrel.build(.3,.3,4.5, "Polished Gold");
}

void Turret::render(bool b) const {
    glPushMatrix();
    glTranslatef(0,0,1);
    turret.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,0,1);
    glRotatef(70,0,1,0);
    barrel.render();
    glPopMatrix();
}
