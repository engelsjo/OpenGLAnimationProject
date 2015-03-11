//created by Zach Ash

#include "Track.h"

void Track::build (void* v) {
    wheel.build(.5,.5,1, "Copper");
    tread.build_with_params(.1,.2,1,"Black Rubber");
}

void Track::render(bool b) const {
    glPushMatrix();
    glTranslatef(-1.5,0,.5);
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-.6*i,0,.8*i);
        glRotatef(90,1,0,0);
        wheel.render();
        glPopMatrix();
    }
    for(int i = 1; i < 4; i++) {
        glTranslatef(1,0,0);
        glPushMatrix();
        glRotatef(90,1,0,0);
        wheel.render();
        glPopMatrix();
    }
    for(int i = 1; i < 3; i++) {
        glTranslatef(.6, 0, .8);
        glPushMatrix();
        glRotatef(90,1,0,0);
        wheel.render();
        glPopMatrix();
    }
    glPopMatrix();

    //big, complicated track rendering stuff
    glPushMatrix();
    glTranslatef(-1.5,0,0);
    for(int i = 0; i < 29; i++) {
        glTranslatef(3.0/29.0, 0, 0);
        tread.render(b);
    }
    glTranslatef(0,0,.5);
    for(int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef((float)cos(270+53.13/4 * i) * .5,0,(float)sin(270 + 53.13/4 * i)*.5);
        glRotatef(53.13/4*i,0,1,0);
        tread.render(b);
        glPopMatrix();
    }
    glTranslatef((float)cos(323.13)*.5, 0, (float)sin(323.13)*.5);
    for(int i = 0; i < 19; i++) {
        glTranslatef(1.2/19.0, 0, 1.6/19.0);
        glPushMatrix();
        glRotatef(53.13, 0,1,0);
        tread.render(b);
        glPopMatrix();
    }
    glTranslatef(-(float)cos(323.13)*.5, 0, -(float)sin(323.13)*.5);
    for(int i = 0; i < 11; i++) {
        glPushMatrix();
        glTranslatef((float)cos(323.13+126.87/11 * i) * .5,0,(float)sin(323.13 + 126.87/11 * i)*.5);
        glRotatef(53.13+126.87/11*i,0,1,0);
        tread.render(b);
        glPopMatrix();
    }
    glTranslatef(0,0,.5);

    for(int i = 0; i < 52; i++) {
        glTranslatef(-5.4/52.0, 0, 0);
        glPushMatrix();
        glRotatef(180,0,1,0);
        tread.render(b);
        glPopMatrix();
    }
    glTranslatef(0,0,-.5);
    for(int i = 0; i < 11; i++) {
        glPushMatrix();
        glTranslatef((float)cos(90+126.87/11 * i) * .5,0,(float)sin(90 + 126.87/11 * i)*.5);
        glRotatef(126.87/11*i - 180,0,1,0);
        tread.render(b);
        glPopMatrix();
    }
    glTranslatef((float)cos(216.87)*.5, 0, (float)sin(216.87)*.5);
    for(int i = 0; i < 19; i++) {
        glTranslatef(1.2/19.0, 0, -1.6/19.0);
        glPushMatrix();
        glRotatef(216.87-270,0,1,0);
        tread.render(b);
        glPopMatrix();
    }
    glTranslatef(-(float)cos(216.87)*.5, 0, -(float)sin(216.87)*.5);
    for(int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef((float)cos(216.87+53.13/4 * i) * .5,0,(float)sin(216.87 + 53.13/4 * i)*.5);
        glRotatef(216.87-270+53.13/4*i,0,1,0);
        tread.render(b);
        glPopMatrix();
    }
    glPopMatrix();
}
