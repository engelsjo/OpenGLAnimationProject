//created by Zach Ash

#include "Tank.h"

void Tank::build (void* v) {
    slope1.build_with_params(1, 4, 1, "Copper");
    slope2.build_with_params(1, 4, 2, "Copper");
    body.build_with_params(3, 6, 4, "Bronze");
    turret.build(v);
    track1.build(v);
    track2.build(v);
    guard.build(v);
}

void Tank::render(bool b) const {
    glPushMatrix();
    glTranslatef(0,0,2);
    body.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,3.4);
    guard.render(b);
    glTranslatef(0,5,0);
    guard.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0);
    track1.render(b);
    glTranslatef(0,5,0);
    track2.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,2,.5);
    glRotatef(180,0,0,1);
    glRotatef(-90, 0, 1, 0);
    slope1.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,2,1.5);
    glRotatef(180,0,0,1);
    slope2.render(b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,3.5);
    turret.render(b);
    glPopMatrix();
}

void Tank::update(float rdist, float ldist) {
    track1.update(rdist);
    track2.update(ldist);
}
