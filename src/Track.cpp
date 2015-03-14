//created by Zach Ash

#include "Track.h"

void Track::build (void* v) {
    wheel.build(.5,.5,1, "Copper");
    tread.build_with_params(.1,.2,1,"Black Rubber");
    distance_travelled = 0;
}

void Track::render(bool b) const {
    glPushMatrix();
    glTranslatef(-1.5,0,.5);

    //render wheels
    //back wheels
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-.6*i,0,.8*i);
        glRotatef(90,1,0,0);
        wheel.render();
        glPopMatrix();
    }
    //bottom wheels
    for(int i = 1; i < 4; i++) {
        glTranslatef(1,0,0);
        glPushMatrix();
        glRotatef(90,1,0,0);
        wheel.render();
        glPopMatrix();
    }
    //front wheels
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

    int numTracks = 100;
    float distInc = (12.4 + M_PI) / numTracks;
    float dist_trav = distance_travelled;

    while(dist_trav > distInc)
        dist_trav -= distInc;
    while(dist_trav < 0)
        dist_trav += distInc;

    for(int i = 0; i < numTracks; i++) {
        float dist = distInc * i + dist_trav;
        glPushMatrix();
        if(dist <= 3.0) {
            glTranslatef(dist - 1.5, 0, 0);
            glRotatef(180 , 0, 1, 0);
            tread.render(b);
        }
        else if(dist - 3.0 <= M_PI * 53.13/360.0) {
            dist -= 3.0;
            float theta = 270 + 180 * dist / (M_PI*0.5);
            glTranslatef(1.5 + cos(theta * M_PI/180.0) * .5, 0, .5 + sin(theta * M_PI/180.0) * .5);
            glRotatef(theta * M_PI/180.0, 0, 1, 0);
            tread.render(b);
        }
        else if(dist - 3.0 - M_PI * 53.13/360.0 <= 2.0) {
            dist -= 3.0 + M_PI * 53.13/360.0;
            float theta = 270 + 53.13;
            glTranslatef(1.5 + cos(theta * M_PI/180.0) * .5 + 1.2/2.0 * dist, 0, .5 + sin(theta * M_PI/180.0) * .5 + 1.6/2.0 * dist);
            glRotatef(theta * M_PI/180.0, 0, 1, 0);
            tread.render(b);
        }
        else if(dist - 5.0 - M_PI * 53.13/360.0 <= M_PI * 126.87/360.0) {
            dist -= 5.0 + M_PI * 53.13/360.0;
            float theta = 270 + 53.13 + 180 * dist / (M_PI*0.5);
            glTranslatef(1.5 + cos(theta * M_PI/180.0) * .5 + 1.2, 0, .5 + sin(theta * M_PI/180.0) * .5 + 1.6);
            glRotatef(theta * M_PI/180.0, 0, 1, 0);
            tread.render(b);
        }
        else if(dist - 5.0 - M_PI * 1.0/2.0 <= 5.4) {
            dist -= 5.4 + M_PI * 1.0/2.0;
            float theta = 270 + 180;
            glTranslatef(1.5 + cos(theta * M_PI/180.0) * .5 + 1.2 - dist, 0, .5 + sin(theta * M_PI/180.0) * .5 + 1.6);
            glRotatef(theta * M_PI/180.0, 0, 1, 0);
            tread.render(b);
        }
        else if(dist - 10.4 - M_PI * 1.0/2.0 <= M_PI * 126.87/360.0) {
            dist -= 10.4 + M_PI * 1.0/2.0;
            float theta = 270 + 180 + 180 * dist / (M_PI*0.5);
            glTranslatef(1.5 + cos(theta * M_PI/180.0) * .5 + 1.2 - 5.4, 0, .5 + sin(theta * M_PI/180.0) * .5 + 1.6);
            glRotatef(theta * M_PI/180.0, 0, 1, 0);
            tread.render(b);
        }
        else if(dist - 10.4 - M_PI * 306.87/360.0 <= 2.0) {
            dist -= 10.4 + M_PI * 306.87/360.0;
            float theta = 270 + 180 + 126.87;
            glTranslatef(1.5 + cos(theta * M_PI/180.0) * .5 + 1.2 - 5.4 + 1.2/2.0 * dist, 0, .5 + sin(theta * M_PI/180.0) * .5 + 1.6 - 1.6/2.0 * dist);
            glRotatef(theta * M_PI/180.0, 0, 1, 0);
            tread.render(b);
        }
        else {
            dist -= 12.4 + M_PI * 306.87/360.0;
            float theta = 270 + 180 + 126.87 + 180 * dist / (M_PI*0.5);
            glTranslatef(1.5 + cos(theta * M_PI/180.0) * .5 + 1.2 - 5.4, 0, .5 + sin(theta * M_PI/180.0) * .5 + 1.6);
            glRotatef(theta * M_PI/180.0, 0, 1, 0);
            tread.render(b);
        }


        glPopMatrix();
    }
    glPopMatrix();
}

void Track::update(float dist) {
    distance_travelled += dist;
}
