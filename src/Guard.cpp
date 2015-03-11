//created by Zach Ash

#include "Guard.h"

void Guard::build (void* v) {
    mainBar.build_with_params(.2,4,1, "Copper");
    sideBar.build_with_params(.2,1.5,1, "Copper");
}

void Guard::render(bool b) const {
    glPushMatrix();
    mainBar.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.6495,0,-.375);
    glRotatef(-30,0,1,0);
    sideBar.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.6495,0,-.375);
    glRotatef(30,0,1,0);
    sideBar.render(b);
    glPopMatrix();
}
