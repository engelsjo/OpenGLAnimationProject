#include <iostream>
#include <chrono>
#include "Timer.hpp"
#include <cmath>
#include <algorithm>
#include <ctime>
#include <time.h>

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#undef GLFW_DLL
#include <GLFW/glfw3.h>

#include <math.h>
#include <stdlib.h>
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Tank.h"
#include "HeliBase.h"
#include "Blade.h"
#include "TreeFromQuadrics.h"

void init_model();
void win_refresh(GLFWwindow*);
float arc_ball_rad_square;
int screen_ctr_x, screen_ctr_y;

float time_elapsed;
static Timer timer;

Cube origin;
Sphere sphere;
Cube projectile;
Cylinder spot;
Tank tank;
HeliBase helibase;
Blade top_blade;
Blade rear_blade;
TreeFromQuadrics tree;
vector<int> tree_xs;
vector<int> tree_ys;

glm::mat4 camera_cf, light1_cf, light0_cf;
glm::mat4 tank_cf;
glm::mat4 helibase_cf, heli_blade_cf, heli_rear_cf;
glm::mat4 projectile_cf;

float left_speed, right_speed;
float turret_speed;
float proj_yspeed;
float rpm, rear_rpm;

float heli_auto_rad = 75.0f;
bool auto_pilot = true;
float gravity = 9.81; // m/s2
float heli_mass = 500; // kg
float force_gravity = gravity * heli_mass;
bool pause;

/* light source setting */
GLfloat light0_color[] = {1.0, 1.0, 1.0, 1.0};   /* color */
GLfloat light1_color[] = {1.0, 1.0, 0.8, 1.0};  /* color */
GLfloat black_color[] = {0.0, 0.0, 0.0, 1.0};   /* color */

using namespace std;
void err_function (int what, const char *msg) {
    cerr << what << " " << msg << endl;
}

void win_resize (GLFWwindow * win, int width, int height)
{
#ifdef DEBUG
    cout << __FUNCTION__ << " " << width << "x" << height << endl;
#endif
    int w, h;
    glfwGetWindowSize(win, &w, &h);
    screen_ctr_x = w / 2.0;
    screen_ctr_y = h / 2.0;
    float rad = min(h,w)/2;
    arc_ball_rad_square = rad * rad;
    /* Use the entire window for our view port */
    glViewport(0, 0, width, height);
    /* Use GL_PROJECTION to select the type of synthetic camera */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* near-plane(1) & far-plane(10) are always POSITIVE and they measure
     * the distances along the Z-axis in front of the camera */
    gluPerspective(60.0, static_cast<float> (width)/ static_cast<float> (height), 1, 10);
}

void win_refresh (GLFWwindow *win) {

    //    cout << __PRETTY_FUNCTION__ << endl;
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    /* place the camera using the camera coordinate frame */
    glMultMatrixf (glm::value_ptr(camera_cf));


    /* Specify the reflectance property of the ground using glColor
     (instead of glMaterial....)
     */
    glEnable (GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor3ub (29, 100, 56);

    glBegin (GL_QUADS);
    const int GROUND_SIZE = 150;
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (GROUND_SIZE, GROUND_SIZE);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (-GROUND_SIZE, GROUND_SIZE);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (-GROUND_SIZE, -GROUND_SIZE);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (GROUND_SIZE, -GROUND_SIZE);
    glEnd();
    glDisable (GL_COLOR_MATERIAL);


    /* place the light source in the scene. */
    glLightfv (GL_LIGHT0, GL_POSITION, glm::value_ptr(glm::column(light0_cf, 3)));

    /* recall that the last column of a CF is the origin of the CF */
    glm::vec4 point_on_heli = glm::vec4{3.5, 0, 0, 1}; //top of spotlight
    glm::vec4 point_wrt_world = helibase_cf * point_on_heli;

    glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(point_wrt_world));

    /* we use the Z-axis of the light CF as the spotlight direction */
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, glm::value_ptr(glm::column(light1_cf, 2)));


    glPushMatrix(); //render the moon
    {
        glMultMatrixf(glm::value_ptr(light0_cf));

        /* Render light-0 as an emmisive object */
        if (glIsEnabled(GL_LIGHT0))
            glMaterialfv(GL_FRONT, GL_EMISSION, light0_color);
        sphere.render();
        glMaterialfv(GL_FRONT, GL_EMISSION, black_color);
    }
    glPopMatrix();

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(tank_cf));
    tank.render(false);
    glPopMatrix();

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(projectile_cf));
    projectile.render(false);
    glPopMatrix();

    glPushMatrix();
    {
        glMultMatrixf(glm::value_ptr(helibase_cf));
        helibase.render(false);

        glPushMatrix();
        {
            glMultMatrixf(glm::value_ptr(heli_blade_cf));
            top_blade.render(false);

        }
        glPopMatrix();

        glPushMatrix();
        {
            glMultMatrixf(glm::value_ptr(heli_rear_cf));
            rear_blade.render(false);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glMultMatrixf(glm::value_ptr(light1_cf));
            spot.render();
        }
        glPopMatrix();

    }
    glPopMatrix();
    
    //render gluquadrics
    int nbr_of_trees = 75;
    for (int i = 0; i < nbr_of_trees; i++){ //plant nbr_of_trees
        
        glPushMatrix();
        if (tree.cyl.q_cyl != nullptr && tree.sphere.q_cyl != nullptr){
            glTranslatef(tree_xs[i], tree_ys[i], 0.0f);
            tree.render();
        }
        glPopMatrix();
    }


    /* must swap buffer at the end of render function */
    glfwSwapBuffers(win);
}

void init_gl() {
    //set up shading / lighting
    glClearColor (0.0, 0.0, 0.0, 1.0); /* black background */

    /* fill front-facing polygon */
    glPolygonMode (GL_FRONT, GL_FILL);
    /* draw outline of back-facing polygon */
    glPolygonMode (GL_BACK, GL_LINE);

    /* Enable shading */
    glEnable (GL_LIGHTING);
    glEnable (GL_NORMALIZE); /* Tell OpenGL to renormalize normal vector
                              after transformation */

    /* initialize two light sources */
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT0, GL_AMBIENT, light0_color);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_color);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light0_color);
    glEnable (GL_LIGHT1);
    glLightfv (GL_LIGHT1, GL_AMBIENT, light1_color);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light1_color);
    glLightfv (GL_LIGHT1, GL_SPECULAR, light1_color);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 40); //spot light

    glEnable (GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);

    glLineWidth(3.0);

    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    camera_cf = glm::translate(glm::vec3{-125, 125, -225}) * camera_cf;
    camera_cf = glm::rotate(glm::radians(-45.0f), glm::vec3{0, 0, 1}) * camera_cf;
    camera_cf = glm::rotate(glm::radians(-45.0f), glm::vec3{1, 0, 0}) * camera_cf;
    camera_cf = glm::scale(glm::vec3 {.02,.02,.02}) * camera_cf;

    tank_cf = glm::translate(glm::vec3{40,0,0});

    //set up helicopter's cfs
    helibase_cf = glm::translate(glm::vec3{0, 0, 40}) * glm::translate(glm::vec3{0, 75, 0});
    heli_blade_cf = glm::translate(glm::vec3{0, 0, 5.75}) * glm::rotate (glm::radians(45.0f), glm::vec3{0,0,1});
    heli_rear_cf =  glm::translate(glm::vec3{-11, -1.2, 3.75}) * glm::scale(glm::vec3{.25, .25, .25}) * glm::rotate (glm::radians(90.0f), glm::vec3{1,0,0});

    //init the rpm speed
    rpm = 50;
    rear_rpm = 100;

    right_speed = 0;
    left_speed = 0;
    turret_speed = 0;

    //create projectile off screen
    projectile_cf = glm::translate(glm::vec3{0,0,-1000});
    proj_yspeed = 0;
    pause = false;
}

void make_model() {
    time_elapsed = 0;
    //build object models
    origin.build_with_params(40, 10, 10, "Chrome");
    tank.build(nullptr);

    //build the helicopter
    helibase.build(nullptr);
    top_blade.build(nullptr);
    rear_blade.build(nullptr);


    //build "moon"
    sphere.build(15, 20);
    //build spot-light
    spot.build(1 + tan(glm::radians(20.0f)), 1, 2, "Ruby");

    //build projectile
    projectile.build_with_params(.2,1,.2,"Chrome");
    
    //build gluquadrics
    tree.build();

    //set the light sources
    light0_cf = glm::translate(glm::vec3{-100, 100, 75});

    light1_cf = glm::translate(glm::vec3{3.5, 0, 1}) * glm::rotate(glm::radians(180.0f), glm::vec3{1, 0, 0});
    
    //render gluquadrics and remember their locations
    int nbr_of_trees = 75;
    for (int i = 0; i < nbr_of_trees; i++){ //plant nbr_of_trees
        int rand_pos_or_neg = rand() % 2;
        int rand_x = rand() % 150;
        rand_x = rand_pos_or_neg ? rand_x * - 1 : rand_x;
        int rand_y = rand() % 150;
        tree_xs.push_back(rand_x);
        tree_ys.push_back(rand_y);
        
        glPushMatrix();
        glTranslatef((float)rand_x, (float)rand_y, 0.0f);
        if (tree.cyl.q_cyl != nullptr && tree.sphere.q_cyl != nullptr){
            tree.render();
        }
        glPopMatrix();
    }

}

void fire() {
    proj_yspeed = 2;
    projectile_cf = tank_cf;
    projectile_cf *= glm::rotate(tank.turret_position, glm::vec3{0,0,1});
    projectile_cf *= glm::translate(glm::vec3{4,0,5});
    projectile_cf *= glm::rotate(27.0f, glm::vec3{0,1,0});
}

/* action: GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT */
void key_handler (GLFWwindow *win, int key, int scan_code, int action, int mods)
{
    //cout << __FUNCTION__ << endl;
    if (action != GLFW_PRESS) return;
    if (mods == GLFW_MOD_SHIFT) {
        switch(key) {
            case GLFW_KEY_X:
                helibase_cf *= glm::translate(glm::vec3{-1, 0, 0});
                break;
            case GLFW_KEY_Y:
                helibase_cf *= glm::translate(glm::vec3{0, -1, 0});
                break;
            case GLFW_KEY_Z:
                helibase_cf *= glm::translate(glm::vec3{0, 0, -1});
                break;
            case GLFW_KEY_P:
                if(pause)
                    pause = false;
                else
                    pause = true;

        }
    }
    else {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(win, true);
                break;
            case GLFW_KEY_RIGHT:
                camera_cf = glm::translate(glm::vec3{-.05, 0, 0}) * camera_cf;
                break;
            case GLFW_KEY_LEFT:
                camera_cf = glm::translate(glm::vec3{.05, 0, 0}) * camera_cf;
                break;
            case GLFW_KEY_UP:
                camera_cf = glm::translate(glm::vec3{0, -.05, 0}) * camera_cf;
                break;
            case GLFW_KEY_DOWN:
                camera_cf = glm::translate(glm::vec3{0, .05, 0}) * camera_cf;
                break;
            case GLFW_KEY_W:
                left_speed++;
                break;
            case GLFW_KEY_S:
                left_speed--;
                break;
            case GLFW_KEY_E:
                right_speed++;
                break;
            case GLFW_KEY_D:
                right_speed--;
                break;
            case GLFW_KEY_Q:
                turret_speed++;
                break;
            case GLFW_KEY_A:
                turret_speed--;
                break;
            case GLFW_KEY_P:
                rpm += 5;
                break;
            case GLFW_KEY_L:
                rpm -= 5;
                break;
            case GLFW_KEY_O:
                rear_rpm += 1;
                break;
            case GLFW_KEY_K:
                rear_rpm -= 1;
                break;
            case GLFW_KEY_0: //turn off the moon
                if (glIsEnabled(GL_LIGHT0))
                    glDisable(GL_LIGHT0);
                else
                    glEnable(GL_LIGHT0);
                break;
            case GLFW_KEY_1: //turn off the spot light
                if (glIsEnabled(GL_LIGHT1))
                    glDisable(GL_LIGHT1);
                else
                    glEnable(GL_LIGHT1);
                break;
            case GLFW_KEY_X:
                helibase_cf *= glm::translate(glm::vec3{1, 0, 0});
                break;
            case GLFW_KEY_Y:
                helibase_cf *= glm::translate(glm::vec3{0, 1, 0});
                break;
            case GLFW_KEY_Z:
                helibase_cf *= glm::translate(glm::vec3{0, 0, 1});
                break;
            case GLFW_KEY_5:
                rpm = 0;
                break;
            case GLFW_KEY_SPACE:
                fire();
            case GLFW_KEY_R: //forward
                helibase_cf = helibase_cf * glm::rotate(.1f, glm::vec3{0, 1, 0});
                break;
            case GLFW_KEY_F: //backward
                helibase_cf = helibase_cf * glm::rotate(.1f, glm::vec3{0, -1, 0});
                break;
            case GLFW_KEY_G: //left
                helibase_cf = helibase_cf * glm::rotate(.1f, glm::vec3{-1, 0, 0});
                break;
            case GLFW_KEY_H: //right
                helibase_cf = helibase_cf * glm::rotate(.1f, glm::vec3{1, 0, 0});
                break;
            case GLFW_KEY_M: //turn off heli auto mode
                auto_pilot = auto_pilot ? false : true;
                if (auto_pilot){
                    helibase_cf = glm::translate(glm::vec3{0, 0, 0}); //reset the heli when going to auto pilot
                    helibase_cf = glm::translate(glm::vec3{0, 0, 40}) * glm::translate(glm::vec3{0, 75, 0});
                }
                break;
        }
    }
    win_refresh(win);
}

/*
 The virtual trackball technique implemented here is based on:
 https://www.opengl.org/wiki/Object_Mouse_Trackball
 */
void cursor_handler (GLFWwindow *win, double xpos, double ypos) {
    int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
    static glm::vec3 first_click;
    static glm::mat4 current_cam;
    static bool is_tracking = false;

    glm::vec3 this_vec;
    if (state == GLFW_PRESS) {
        /* TODO: use glUnproject? */
        float x = (xpos - screen_ctr_x);
        float y = -(ypos - screen_ctr_y);
        float hypot_square = x * x + y * y;
        float z;

        /* determine whether the mouse is on the sphere or on the hyperbolic sheet */
        if (2 * hypot_square < arc_ball_rad_square)
            z = sqrt(arc_ball_rad_square - hypot_square);
        else
            z = arc_ball_rad_square / 2.0 / sqrt(hypot_square);
        if (!is_tracking) {
            /* store the mouse position when the button was pressed for the first time */
            first_click = glm::normalize(glm::vec3{x, y, z});
            current_cam = camera_cf;
            is_tracking = true;
        }
        else {
            /* compute the rotation w.r.t the initial click */
            this_vec = glm::normalize(glm::vec3{x, y, z});
            /* determine axis of rotation */
            glm::vec3 N = glm::cross(first_click, this_vec);

            /* determine the angle of rotation */
            float theta = glm::angle(first_click, this_vec);

            /* create a quaternion of the rotation */
            glm::quat q{cos(theta / 2), sin(theta / 2) * N};
            /* apply the rotation w.r.t to the current camera CF */
            camera_cf = current_cam * glm::toMat4(glm::normalize(q));
        }
        win_refresh(win);
    }
    else {
        is_tracking = false;
    }
}

void scroll_handler (GLFWwindow *win, double xscroll, double yscroll) {
    /* translate along the camera Z-axis */
    glm::mat4 z_translate = glm::translate((float)yscroll * glm::vec3{0, 0, .05});
    camera_cf =  z_translate * camera_cf;
    win_refresh(win);

}

void update_heli(float elapsedTime)
{
    //function for updating the helicopter
    if (auto_pilot){ //fly the heli in big circles around the map
        float rps = .125f;
        rear_rpm = 0;
        float rotations = rps * elapsedTime;
        float delta = -(rotations * 360);
        //post multiply to rotate around the cf of the world
        helibase_cf = glm::rotate(delta, glm::vec3{0, 0, 1}) * helibase_cf;

    }else{ //do some physics
        //calc vector for gravitational pull
        glm::vec4 gravity_vector = glm::vec4{0, 0, -1, 0} * (force_gravity);

        //little bit of a physics hack... assume force upwards is equal to gravity at factor involving rpm
        float force_up = (rpm * 1000);


        //convert z axis of heli to a vector wrt world cf
        //first locate two points on helicopter wrt helicopter cf
        glm::vec4 point_wrt_world1 = helibase_cf * glm::vec4{0, 0, 0, 1};
        glm::vec4 point_wrt_world2 = helibase_cf * glm::vec4{0 ,0, 1, 1};
        glm::vec4 vector_up_wrt_world = (point_wrt_world2 - point_wrt_world1) * force_up;

        //add the two vectors to get resultant
        glm::vec4 resultant_vector = gravity_vector + vector_up_wrt_world;
        float magnitude = glm::length(resultant_vector); //total magnitude of vector
        float resultant_accel = magnitude / heli_mass;
        float distance = resultant_accel * elapsedTime * elapsedTime; //distance to travel along vector

        //scale resultant vector by distance I am to travel based upon time elapsed and newtons second law
        if (magnitude){ //only translate if the resultant had some mag
            float prop_of_travel = (distance / magnitude) * 50000;
            resultant_vector *= prop_of_travel;
            //translate wrt the world because resultant is wrt world
            helibase_cf = glm::translate(glm::vec3(resultant_vector)) * helibase_cf;
        }

    }

    //calc the big blade spin
    float rps = rpm / 60.0 * 25;
    float rotations = rps * elapsedTime;
    float theta = rotations * 360;
    heli_blade_cf *= glm::rotate(theta, glm::vec3{0, 0, 1});

    //calc the small blade spin
    rps = rear_rpm / 60.0 * 25;
    rotations = rps * elapsedTime;
    theta = rotations * 360;
    heli_rear_cf *= glm::rotate(theta, glm::vec3{0, 0, 1});

    //render the pivot from rear blade
    helibase_cf *= glm::rotate(theta, glm::vec3{0, 0, 1});

}

void update() {
    auto elapsed_time = timer.elapsed() * 1000;
    timer.reset();

    float elapsedTime = (float)elapsed_time* 100000;

    //update the helicopter cfs
    update_heli(elapsed_time);

    //update the coordinate frames here
    float dist = (right_speed + left_speed) * elapsedTime /200000.0;

    if(left_speed == right_speed) {
        tank_cf *= glm::translate(glm::vec3{30*dist,0,0});
    }
    else if(-left_speed == right_speed) {
        float theta = 180 * right_speed * elapsedTime /100000.0 / (M_PI * 2.5);
        tank_cf *= glm::rotate(theta, glm::vec3{0,0,1});
    }
    else if(left_speed == 0) {
        float theta = 180 * right_speed * elapsedTime /100000.0 / (M_PI * 2.5);
        tank_cf *= glm::translate(glm::vec3{2.5*sin(theta),0,0});
        tank_cf *= glm::rotate(theta, glm::vec3{0,0,1});
    }
    else if (right_speed == 0) {
        float theta = 180 * left_speed * elapsedTime /100000.0 / (M_PI * 2.5);
        tank_cf *= glm::translate(glm::vec3{2.5*sin(theta),0,0});
        tank_cf *= glm::rotate(-theta, glm::vec3{0,0,1});
    }
    else if(left_speed < right_speed){
        float rat = (float) left_speed/right_speed;
        float r = 2.5 * (rat+1)/(rat-1);
        float theta = 180 * dist / (M_PI * r);
        tank_cf *= glm::translate(glm::vec3{r*sin(theta),0,0});
        tank_cf *= glm::rotate(-theta, glm::vec3{0,0,1});
    }
    else {
        float rat = (float) right_speed/left_speed;
        float r = 2.5 * (rat+1)/(rat-1);
        float theta = -180 * dist / (M_PI * r);
        tank_cf *= glm::translate(glm::vec3{-r*sin(theta),0,0});
        tank_cf *= glm::rotate(-theta, glm::vec3{0,0,1});
    }

    float rdist = right_speed * elapsedTime / 200000.0;
    float ldist = left_speed * elapsedTime / 200000.0;
    float tdist = turret_speed * elapsedTime / 100;
    tank.update(rdist, ldist, tdist);


    projectile_cf *= glm::translate(glm::vec3{elapsedTime*4, proj_yspeed * elapsedTime, 0});
    projectile_cf *= glm::rotate((float)atan((proj_yspeed-9.81*elapsedTime)/4) - (float)atan(proj_yspeed/4), glm::vec3{0,1,0});
    proj_yspeed -= 9.81*elapsedTime;
}


int main(){
    /* initialize random seed: */
    srand (time(NULL));
    
    if(!glfwInit()) {
        cerr << "Can't initialize GLFW" << endl;
        glfwTerminate();
        exit (EXIT_FAILURE);
    }

    glfwSetErrorCallback(err_function);
    GLFWwindow * win;
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    win = glfwCreateWindow(100, 50, "CIS 367 Project 2 -- Tank", NULL, NULL);
    if (!win) {
        cerr << "Can't create window" << endl;
        exit (EXIT_FAILURE);
    }

    glfwSetWindowRefreshCallback(win, win_refresh);
    /* On Mac with Retina display there is a discrepancy between units measured in
     * "screen coordinates" and "pixels" */
    glfwSetWindowSizeCallback(win, win_resize);  /* use this for non-retina displays */
    //glfwSetFramebufferSizeCallback(win, win_resize); /* use this for retina displays */
    glfwSetKeyCallback(win, key_handler);
    glfwSetCursorPosCallback(win, cursor_handler);
    glfwSetScrollCallback(win, scroll_handler);
    glfwMakeContextCurrent(win);

    /* glewInit must be invoked AFTER glfwMakeContextCurrent() */
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf (stderr, "GLEW init error %s\n", glewGetErrorString(err));
        exit (EXIT_FAILURE);
    }

    /* GL functions can be called, only AFTER the window is created */
    const GLubyte *version = glGetString (GL_VERSION);
    printf ("GL Version is %s\n", version);


    glfwSetWindowSize(win, 800, 600);
    glfwSwapInterval(1);
    init_gl();
    make_model();

    win_refresh(win);

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        timer = Timer();
        if(!pause)
            update();
        win_refresh(win);
    }
    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
