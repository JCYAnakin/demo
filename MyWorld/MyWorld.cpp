#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <math.h>
#include <utility>
#include <vector>
#include "VectorAndPoint.h"
#include "Terrain.h"
#include "BMPHandler.h"
#include "MyObj.h"
#include "beetles.h"
#include "plane.h"
#include "animator.h"
#include "Skybox.h"

using namespace std;

int gridSize = 40;
Terrain *terrain = NULL;
Beetles *beetles[4];
MyObj *house[2];
MyObj *ball[2];
MyObj *cow[5];
MyObj *isis[2];
MyObj *statue[5];
Plane *plane;
Animator *animator[5];
Skybox* skybox;
int num_of_beetless = 4;
int num_of_house = 2;
int num_of_balls = 2;
int num_of_cows = 5;
int num_of_isis = 2;
int num_of_statues = 5;
int selected_beetles = 0;
//textures
char terrain_fileName[] = "/Users/jason/Xcode/MyWorld/textures/grass.bmp";
char beetles_body_fileName[] = "/Users/jason/Xcode/MyWorld/textures/car.bmp";
char beetles_wheel_fileName[] = "/Users/jason/Xcode/MyWorld/textures/wheel.bmp";
char house_pic_fileName[] = "/Users/jason/Xcode/MyWorld/textures/building3.bmp";
char ball_pic_fileName[] = "/Users/jason/Xcode/MyWorld/textures/ball.bmp";
char cow_pic_fileName[] = "/Users/jason/Xcode/MyWorld/textures/cow.bmp";
char isis_pic_fileName[] = "/Users/jason/Xcode/MyWorld/textures/isis.bmp";
char statue_pic_fileName[] = "/Users/jason/Xcode/MyWorld/textures/statue.bmp";
char plane_pic_fileName[] = "/Users/jason/Xcode/MyWorld/textures/isis.bmp";


//pixel maps
RGBpixmap terrain_pixelMap;
RGBpixmap beetles_body_pixelMap;
RGBpixmap beetles_wheel_pixelMap;
RGBpixmap house_pixelMap;
RGBpixmap cow_pixelMap;
RGBpixmap ball_pixelMap;
RGBpixmap isis_pixelMap;
RGBpixmap statue_pixelMap;
RGBpixmap plane_pixelMap;

//OBJs
string beetles_obj_fileName("/Users/jason/Xcode/MyWorld/obj/car.obj");
string house_obj_fileName("/Users/jason/Xcode/MyWorld/obj/city.obj");
string cow_obj_fileName("/Users/jason/Xcode/MyWorld/obj/cow.obj");
string ball_obj_fileName("/Users/jason/Xcode/MyWorld/obj/ball.obj");
string isis_obj_fileName("/Users/jason/Xcode/MyWorld/obj/isis.obj");
string statue_obj_fileName("/Users/jason/Xcode/MyWorld/obj/statue.obj");
string plane_obj_fileName("/Users/jason/Xcode/MyWorld/obj/statue.obj");
string wheel1_fileName("/Users/jason/Xcode/MyWorld/obj/wheel1.obj");
string wheel2_fileName("/Users/jason/Xcode/MyWorld/obj/wheel2.obj");
string wheel3_fileName("/Users/jason/Xcode/MyWorld/obj/wheel3.obj");
string wheel4_fileName("/Users/jason/Xcode/MyWorld/obj/wheel4.obj");


void initOpenGL();
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotionHandler(int xMouse, int yMouse);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void functionUpKeys(int key, int x, int y);
void functionKeys(int key, int x, int y);
void timer(int value);
void updateCameraPos();
float* calculatebeetlesBoundingBox(Beetles* mesh);
bool checkForBeetlesBeetlesCollision(Beetles* mesh1, Beetles* mesh2);
bool checkBeetlesCollisionWithEnemyBeetlessAndBuildings(Beetles* selectedBeetles);
void limitCameraAngle();
void animationFunction (float delta_time);
void loadBeetles(Beetles **beetles);

static int currentButton;
static unsigned char currentKey;
static int currentFuncKey;
const float FPS = 30.0;
int count = 0;

// City Interaction State Variable
enum Action {TRANSLATE, ROTATE, SCALE, EXTRUDE, SELECT, MULTIPLESELECT, DESELECT_ALL, NAVIGATE};
enum Action currentAction = TRANSLATE;

GLfloat light_position0[] = {-12.0, 50.0,12.0, 1.0}; //1:infinity
GLfloat light_diffuse[]   = {1.0, 1.0, 1.0, 1.0};  //diffusion..
GLfloat light_specular[]  = {1.0, 1.0, 1.0, 1.0};  //"mirror"...
GLfloat light_ambient[]   = {1.0, 1.0, 1.0, 1.0};  //RGBA, environment..

// City terrain mesh




float radius = 12;			// Camera Distance
// Camera Control
Vector3D lookFrom;
Vector3D lookAt;
Vector3D up;
float lookFromx = 0;		// Camera X  Position
float lookFromy = 0;	// Camera Y Position
float lookFromz = radius;		// Camera Z Position

float theta = 0;		// Camera X angle
float phy = 80;		// Camera Y angle

float upx = 0;			// Up Vector
float upy = 1;
float upz = 0;

float lookAtx = 0;		// Camera is looking at
float lookAty = 0;
float lookAtz = 0;

float camerax = 0;		// Camera X Position
float cameray = 0;	// Camera Y Position
float cameraz = radius;		// Camera Z Position


static float zoom = 1.0;

GLint glutWindowWidth    = 750;
GLint glutWindowHeight   = 500;

//// Wolrd Boundaries
//GLdouble worldLeftBase  =  -8.0;
//GLdouble worldRightBase =  8.0;
//GLdouble worldBottomBase=  -8.0;
//GLdouble worldTopBase   =  8.0;

bool closeWindow = false;

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My");
    
    initOpenGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotionHandler);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(functionKeys);
    glutSpecialUpFunc(functionUpKeys);
    glutTimerFunc(1000.0 / FPS, timer, 0);
    glutMainLoop();
    return 0;
}
int width, height;

// Setup openGL */
void initOpenGL()
{
    // for my lights..
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST);
    
    //Terrain
    Vector3D startPoint = Vector3D(-40.0f,0.0f,40.0f);
    terrain = new Terrain(gridSize);
    terrain->InitGrid(gridSize, startPoint, 80.0, 80.0);
    
    //Skybox
    skybox = new Skybox();
    skybox->setTextures();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(lookFromx, lookFromy, lookFromz,lookAtx, lookAty, lookAtz, upx, upy, upz);
    
    Vector3D scale;
    Vector3D trans;
    Vector3D angles;
    //Texturing
    glEnable(GL_TEXTURE_2D);
    
    // Terrain textures
    readBMPFile(&terrain_pixelMap, terrain_fileName);
    setTexture(&terrain_pixelMap, 7);
    
    //Set Texture for Terrain
    terrain->setTextureID(7);
    
    //texture for beetles
    readBMPFile(&beetles_body_pixelMap, beetles_body_fileName);
    setTexture(&beetles_body_pixelMap, 8);
    
    readBMPFile(&beetles_wheel_pixelMap, beetles_wheel_fileName);
    setTexture(&beetles_wheel_pixelMap, 9);
    //texture for house
    readBMPFile(&house_pixelMap, house_pic_fileName);
    setTexture(&house_pixelMap, 10);
    //texture for cow
    readBMPFile(&cow_pixelMap, cow_pic_fileName);
    setTexture(&cow_pixelMap, 11);
    //texture for isis
    readBMPFile(&isis_pixelMap, isis_pic_fileName);
    setTexture(&isis_pixelMap, 12);
    //texture for ball
    readBMPFile(&ball_pixelMap, ball_pic_fileName);
    setTexture(&ball_pixelMap, 13);
    //texture for statue
    readBMPFile(&statue_pixelMap, statue_pic_fileName);
    setTexture(&statue_pixelMap, 14);
    //plane
    readBMPFile(&plane_pixelMap, plane_pic_fileName);
    setTexture(&plane_pixelMap, 15);
    
    
    
    for(int i = 0; i < num_of_beetless; i++){
        beetles[i] = new Beetles();
        
        load_obj(beetles_obj_fileName, &beetles[i]->body);
        vector<MyObj *> * wheels = new vector<MyObj *>();
        MyObj *wheel;
        //Loads Wheels
        load_obj(wheel1_fileName, &wheel);
        wheels->push_back(wheel);
        load_obj(wheel2_fileName, &wheel);
        wheels->push_back(wheel);
        load_obj(wheel3_fileName, &wheel);
        wheels->push_back(wheel);
        load_obj(wheel4_fileName, &wheel);
        wheels->push_back(wheel);
        (beetles[i])->set_wheels(*wheels);
        (beetles[i])->body->setTextureMapID(8);
        (beetles[i])->wheels[0]->setTextureMapID(9);
        (beetles[i])->wheels[1]->setTextureMapID(9);
        (beetles[i])->wheels[2]->setTextureMapID(9);
        (beetles[i])->wheels[3]->setTextureMapID(9);
        //for the animation
        animator[i] = new Animator(beetles[i],5.0,180);
    }
    for(int i = 0; i < num_of_house; i++){
        house[i] = new MyObj();
        load_obj(house_obj_fileName, &house[i]);
        house[i]->setTextureMapID(10);
    }
    for(int i = 0; i < num_of_balls; i++)
    {
        ball[i] = new MyObj();
        load_obj(ball_obj_fileName, &ball[i]);
        ball[i]->setTextureMapID(13);
    }
    for(int i = 0; i < num_of_cows; i++)
    {
        cow[i] = new MyObj();
        load_obj(cow_obj_fileName, &cow[i]);
        cow[i]->setTextureMapID(11);
    }
    for(int i = 0; i < num_of_isis; i++)
    {
        isis[i] = new MyObj();
        load_obj(isis_obj_fileName, &isis[i]);
        isis[i]->setTextureMapID(12);
    }
    for(int i = 0; i < num_of_statues; i++)
    {
        statue[i] = new MyObj();
        load_obj(statue_obj_fileName, &statue[i]);
        statue[i]->setTextureMapID(14);
    }
    plane = new Plane();
    load_obj(plane_obj_fileName, &(plane->body));
    plane->body->setTextureMapID(15);
    
    beetles[0]->makeMove(Vector3D(10.0,0.0,10.0));
    beetles[1]->makeMove(Vector3D(10.0,0.0,-10.0));
    beetles[2]->makeMove(Vector3D(-10.0,0.0,10.0));
    beetles[3]->makeMove(Vector3D(-10.0,0.0,-10.0));
    
    house[0]->makeMove(Vector3D(0.0,-1.0,10.0));
    house[1]->makeMove(Vector3D(0.0,-1.0,-10.0));
    house[0]->makeScale(Vector3D(0.008,0.008,0.008));
    house[1]->makeScale(Vector3D(0.008,0.008,0.008));
    //house[0]->setMatdiffuse(0.5, 0.5, 0.5, 1.0);
    
    ball[0]->makeMove(Vector3D(8.0, 0.0, 8.0));
    ball[1]->makeMove(Vector3D(-8.0, 0.0, 8.0));
    ball[0]->makeRotate(Vector3D(90,0,0));
    ball[0]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    ball[1]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    
    cow[0]->makeMove(Vector3D(6.0,0.0,6.0));
    cow[1]->makeMove(Vector3D(-6.0,0.0,-6.0));
    cow[2]->makeMove(Vector3D(6.0,0.0,-6.0));
    cow[3]->makeMove(Vector3D(-8.0,0.0,6.0));
    cow[4]->makeMove(Vector3D(0.0,0.0,10.0));
    cow[0]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    cow[1]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    cow[2]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    cow[3]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    cow[4]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    
    isis[0]->makeMove(Vector3D(12.0, 0.0, 12.0));
    isis[1]->makeMove(Vector3D(-8.0, 0.0, 12.0));
    isis[0]->makeRotate(Vector3D(-90,0,0));
    isis[1]->makeRotate(Vector3D(-90,0,0));
    isis[0]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    isis[1]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    
    statue[0]->makeMove(Vector3D(14.0,0.0,11.0));
    statue[1]->makeMove(Vector3D(-11.0,0.0,-14.0));
    statue[2]->makeMove(Vector3D(14.0,0.0,-10.0));
    statue[3]->makeMove(Vector3D(-13.0,0.0,10.0));
    statue[4]->makeMove(Vector3D(8.0,0.0,13.0));
    statue[0]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    statue[1]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    statue[2]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    statue[3]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    statue[4]->setMatAmbient(0.5, 0.5, 0.5, 1.0);
    
    //plane->makeScale(Vector3D(0.008,0.008,0.008));
    plane->makeMove(Vector3D(4.0,8.0,4.0));
    plane->lookFrom = *(new Vector3D(4.0,7.0,4.0));
    plane->lookAt = *(new Vector3D(0.0,0.0,0.0));
    
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    
    glLoadIdentity();
    
    if (currentAction == NAVIGATE)
        ;
    else
        updateCameraPos();
    
    // Draw Skybox
    skybox->DrawSkybox(lookFromx, lookFromy, lookFromz, upx, upy, upz, true);
    gluLookAt(lookFromx, lookFromy, lookFromz, lookAtx, lookAty, lookAtz, upx, upy, upz);
    //skybox->DrawSkybox(10, 10, lookFromz, upx, upy, upz, false);
    //Draw beetless
    for (int i = 0; i < num_of_beetless; i++)
    {
        beetles[i]->draw();
    }
    for(int i = 0; i < num_of_house; i++)
    {
        house[i]->draw();
    }
    for(int i = 0; i < num_of_balls; i++)
    {
        ball[i]->draw();
    }
    for(int i = 0; i < num_of_cows; i++)
    {
        cow[i]->draw();
    }
    for(int i = 0; i < num_of_isis; i++)
    {
        isis[i]->draw();
    }
    for(int i = 0; i < num_of_statues; i++)
    {
        statue[i]->draw();
    }
    plane->draw();
    
    // Enable depth offset with terrain with respect to roads so that roads
    // won't get drawn inside the terrain
    glEnable(GL_POLYGON_OFFSET_FILL);
    terrain->DrawGrid(gridSize);
    glDisable(GL_POLYGON_OFFSET_FILL);
    
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glutWindowWidth = w; glutWindowHeight = h;
    glViewport(0, 0, (GLsizei) glutWindowWidth, (GLsizei) glutWindowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0*zoom,(float)glutWindowWidth/(float)glutWindowHeight,0.2,80.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y)
{
    currentKey = key;
    switch (key)
    {
            // Navigate
        case 'n':
            if (currentAction != NAVIGATE)
            {
                currentAction = NAVIGATE;
                
                lookFromx = plane->lookFrom.x;
                lookFromy = plane->lookFrom.y;
                lookFromz = plane->lookFrom.z;
                
                lookAtx = plane->lookAt.x;
                lookAty = plane->lookAt.y;
                lookAtz = plane->lookAt.z;
            }
            else
            {
                currentAction = TRANSLATE;
                lookAtx = 0;
                lookAty = 0;
                lookAtz = 0;
                
                lookFromx = camerax;
                lookFromy = cameray;
                lookFromz = cameraz;
            }
            break;
        case 'a':
        {
            float hypotenuse = sqrt((lookFromx-lookAtx)*(lookFromx-lookAtx)+(lookAtz-lookFromz)*(lookAtz-lookFromz));
            float xForward = (lookAtz-lookFromz)/hypotenuse;
            float zForward = -(lookAtx-lookFromx)/hypotenuse;
            lookAtx+=xForward;
            lookFromx+=xForward;
            lookAtz+=zForward;
            lookFromz+=zForward;
            plane->makeMove(Vector3D(xForward,0,zForward));
            plane->lookFrom.x+=xForward;
            plane->lookFrom.z+=zForward;
            plane->lookAt.x+=xForward;
            plane->lookAt.z+=zForward;
            break;
        }
        case 'd':
        {
            float hypotenuse = sqrt((lookFromx-lookAtx)*(lookFromx-lookAtx)+(lookAtz-lookFromz)*(lookAtz-lookFromz));
            float xForward = -(lookAtz-lookFromz)/hypotenuse;
            float zForward = (lookAtx-lookFromx)/hypotenuse;
            lookAtx+=xForward;
            lookFromx+=xForward;
            lookAtz+=zForward;
            lookFromz+=zForward;
            plane->makeMove(Vector3D(xForward,0,zForward));
            plane->lookFrom.x+=xForward;
            plane->lookFrom.z+=zForward;
            plane->lookAt.x+=xForward;
            plane->lookAt.z+=zForward;
            break;

        }
        case 'w':
        {
            float hypotenuse = sqrt((lookFromx-lookAtx)*(lookFromx-lookAtx)+(lookAtz-lookFromz)*(lookAtz-lookFromz));
            float xForward = (lookAtx-lookFromx)/hypotenuse;
            float zForward = (lookAtz-lookFromz)/hypotenuse;
            lookAtx+=xForward;
            lookFromx+=xForward;
            lookAtz+=zForward;
            lookFromz+=zForward;
            plane->makeMove(Vector3D(xForward,0,zForward));
            plane->lookFrom.x+=xForward;
            plane->lookFrom.z+=zForward;
            plane->lookAt.x+=xForward;
            plane->lookAt.z+=zForward;
            break;
        }
        case 's':
        {
            float hypotenuse = sqrt((lookFromx-lookAtx)*(lookFromx-lookAtx)+(lookAtz-lookFromz)*(lookAtz-lookFromz));
            float xForward = (lookAtx-lookFromx)/hypotenuse;
            float zForward = (lookAtz-lookFromz)/hypotenuse;
            lookAtx-=xForward;
            lookFromx-=xForward;
            lookAtz-=zForward;
            lookFromz-=zForward;
            plane->makeMove(Vector3D(xForward,0,zForward));
            plane->lookFrom.x-=xForward;
            plane->lookFrom.z-=zForward;
            plane->lookAt.x-=xForward;
            plane->lookAt.z-=zForward;
            break;
        }
        case 'j':
        {
            if(currentAction == NAVIGATE)
                upx+=0.1;
            break;
        }
        case 'l':
        {
            
        }
        case 'i':
        {
            
        }
        case 'k':
        {
            
        }
        case '0':  //for the plane: get back to the orgin position.
        {
            /*plane->makeMove(Vector3D(4.0,8.0,4.0));
            plane->lookFrom = *(new Vector3D(4.0,8.0,4.0));
            plane->lookAt = *(new Vector3D(0.0,0.0,0.0));*/
            lookAtx = lookAty = lookAtz = 0;
            lookFromx = 4.0;
            lookFromy = 7.0;
            lookFromz = 4.0;
            plane->moveTo(Vector3D(4.0,8.0,4.0));
//            plane->translation.x = plane->body->translation.x = 4;
//            plane->translation.y = plane->body->translation.y = 8;
//            plane->translation.z = plane->body->translation.z = 4;
            plane->rotateFactor.x = plane->body->rotateFactor.x = 0;
            plane->rotateFactor.y = plane->body->rotateFactor.y = 0;
            plane->rotateFactor.z = plane->body->rotateFactor.z = 0;
            plane->lookFrom.x = 4.0;
            plane->lookFrom.y = 8.0;
            plane->lookFrom.z = 4.0;
            plane->lookAt.x = 0;
            plane->lookAt.y = 0;
            plane->lookAt.z = 0;
            
            //updateCameraPos();
        }
    }
    
    // if 'esc' key pressed
    if (key == 27)
        closeWindow = true;
    
    // don't use custom shaders
    if (key == 'o')
        glUseProgram(0);
    
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) {
    currentKey = '\0';
}

void functionUpKeys (int key, int x, int y) {
    currentFuncKey = -1;
}

void functionKeys(int key, int x, int y) {
    currentFuncKey = key;
}



Vector3D pos = Vector3D(0,0,0);
// Mouse Control coordinates
int prevx, prevy;
vector<pair<int, int>> aa;
int selectedControlPoint = -1;

void mouse(int button, int state, int x, int y)
{
    currentButton = button;
    //aa.push_back(button);
    
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                prevx = x;
                prevy = y;
            }
            break;
            
        default:
            break;
    }
    
    glutPostRedisplay();
}


/**************************************************************************
 * Mouse Control
 **************************************************************************/

void mouseMotionHandler(int xMouse, int yMouse)
{
    //aa.push_back(pair<int, int>(xMouse, yMouse));
    if(currentAction == TRANSLATE){
        if (currentButton == GLUT_LEFT_BUTTON)
        {
            Vector3D wpos;
            
            theta += prevx - xMouse;
            phy += prevy - yMouse;
            
            while (theta < -180)
                theta += 360;
            while (theta > 180)
                theta -= 360;
            while (phy < 0)
                phy += 360;
            
            //limitCameraAngle();
            
        }
        else if (currentButton == GLUT_RIGHT_BUTTON)
        {
            if (yMouse > prevy) {
                //if (radius < 35) {
                radius++;
                //}
            } else {
                if (radius > 6) {
                    radius--;
                }
            }
        }
        
        prevx = xMouse;
        prevy = yMouse;
        
        return;
    }
    else if (currentAction == NAVIGATE)
    {
        float hypotenuse = sqrt((xMouse-prevx)*(xMouse-prevx)+(yMouse-prevy)*(yMouse-prevy));
        float xForward = (xMouse-prevx)/hypotenuse;
        float zForward = (yMouse-prevy)/hypotenuse;
        lookAtx+=xForward;
        lookFromx+=xForward;
        lookAtz+=zForward;
        lookFromz+=zForward;
        plane->makeMove(Vector3D(xForward,0,zForward));
        plane->lookFrom.x+=xForward;
        plane->lookFrom.z+=zForward;
        plane->lookAt.x+=xForward;
        plane->lookAt.z+=zForward;
    }
}

/**************************************************************************
 * Timer function to limit Frames Per Second
 **************************************************************************/
void timer(int value)
{
    if (closeWindow) {
        //this_thread::sleep_for(chrono::milliseconds(2000));
        exit(EXIT_SUCCESS);
    }
    glutTimerFunc(1000.0 / FPS, timer, 0);
    //animationFunction(10.0/FPS);
    glutPostRedisplay();
}


/**************************************************************************
 * Utility Functions
 **************************************************************************/
void updateCameraPos()
{
    // Spherical coordinates formula
    lookFromx = lookAtx + radius * sin(phy*0.0174532) * sin(theta*0.0174532);
    lookFromy = lookAty + radius * cos(phy*0.0174532);
    lookFromz = lookAtz + radius * sin(phy*0.0174532) * cos(theta*0.0174532);
}
/**************************************************************************
 * Bounds calculations
 **************************************************************************/

float* calculateBeetlesBoundingBox(Beetles* mesh)
{
    float xmin, xmax, zmin, zmax;
    
    // estimate beetles bounding box size
    float scalefactor = 0.7;
    
    xmin = mesh->translation.x - scalefactor;
    xmax = mesh->translation.x + scalefactor;
    zmin = mesh->translation.z - scalefactor;
    zmax = mesh->translation.z + scalefactor;
    
    float* bounds = (float*)malloc(4 * sizeof(float));
    bounds[0] = xmin; bounds[1] = xmax; bounds[2] = zmin; bounds[3] = zmax;
    
    return bounds;
}


/**************************************************************************
 * Collision detection functions between two objects
 **************************************************************************/


bool checkForBeetlesBeetlesCollision(Beetles* mesh1, Beetles* mesh2)
{
    float* beetlesBounds1_ptr = calculateBeetlesBoundingBox(mesh1);
    float* beetlesBounds2_ptr = calculateBeetlesBoundingBox(mesh2);
    
    float beetlesBounds1[] = {beetlesBounds1_ptr[0], beetlesBounds1_ptr[1], beetlesBounds1_ptr[2], beetlesBounds1_ptr[3]};
    float beetlesBounds2[] = {beetlesBounds2_ptr[0], beetlesBounds2_ptr[1], beetlesBounds2_ptr[2], beetlesBounds2_ptr[3]};
    
    free(beetlesBounds1_ptr); free(beetlesBounds2_ptr);
    
    bool collision = false;
    float margin = 0.0;
    
    // xmin of mesh 1 <= xmax of mesh2 AND xmax of mesh 1 >= xmin of mesh 2
    if (beetlesBounds1[0] - margin < beetlesBounds2[1] && beetlesBounds1[1] + margin > beetlesBounds2[0])
        // zmin of mesh 1 <= zmax of mesh2 AND zmax of mesh 1 >= zmin of mesh 2
        if (beetlesBounds1[2] - margin < beetlesBounds2[3] && beetlesBounds1[3] + margin > beetlesBounds2[2])
            collision = true;  // collision detected
    
    return collision;
}

/**************************************************************************
 * Collision detection functions between one object and several
 **************************************************************************/
bool checkBeetlesCollisionWithEnemyBeetlessAndBuildings(Beetles* selectedBeetles)
{
    bool collision = false;
    for (int i = 0; i < num_of_beetless; i++) {
        if (i == selected_beetles)
            continue;
        if (checkForBeetlesBeetlesCollision(selectedBeetles, beetles[i]))
            collision = true;
    }
    
    return collision;
}

bool checkEnemyBeetlesCollisionWithEnemyBeetlessAndBuildings(Beetles* enemyBeetles, int enemyBeetlesIndex)
{
    bool collision = false;
    
    for (int i = 0; i < num_of_beetless; i++) {
        if (i == enemyBeetlesIndex)
            continue;
        if (checkForBeetlesBeetlesCollision(enemyBeetles, beetles[i]))
            collision = true;
    }
    
    return collision;
}


/**************************************************************************
 * Limit Camera angle
 **************************************************************************/
void limitCameraAngle()
{
    if (phy > 80)
        phy = 80;
    if (phy < 30)
        phy = 30;
}
/* Handles input from the keyboard, non-arrow keys */



void animationFunction (float delta_time) {
    static float distance = 0.2 * delta_time;
    static float angle = 2.0 * delta_time;
    
    for(int i =0; i < num_of_beetless; i++) {
        if (i != selected_beetles && !beetles[i]->hit) {
            animator[i]->animate(distance,angle);
            if (checkEnemyBeetlesCollisionWithEnemyBeetlessAndBuildings(beetles[i], i)) {
                animator[i]->animate(-distance,angle);
            }
        }
    }
    
    if (currentAction == NAVIGATE)
    {
        switch (currentFuncKey)
        {
            case GLUT_KEY_DOWN:
                beetles[selected_beetles]->makeMove(-distance);
                if (checkBeetlesCollisionWithEnemyBeetlessAndBuildings(beetles[selected_beetles])) {
                    beetles[selected_beetles]->makeMove(distance);
                }
                break;
            case GLUT_KEY_UP:
                beetles[selected_beetles]->makeMove(distance);
                if (checkBeetlesCollisionWithEnemyBeetlessAndBuildings(beetles[selected_beetles])) {
                    beetles[selected_beetles]->makeMove(-distance);
                }
                break;
            case GLUT_KEY_RIGHT:
                beetles[selected_beetles]->rotateBy(-angle);
                break;
                
            case GLUT_KEY_LEFT:
                beetles[selected_beetles]->rotateBy(angle);
                break;
        }
        
        switch (currentKey) {
            case 'a':
                break;
            case 'd':
                break;
            case 'q':
                //beetles[selected_beetles]->rotateCannon(angle);
                break;
            case 'e':
                //beetles[selected_beetles]->rotateCannon(-angle);
                break;
        }
        
        lookFromx = beetles[selected_beetles]->lookFrom.x;
        lookFromy = beetles[selected_beetles]->lookFrom.y;
        lookFromz = beetles[selected_beetles]->lookFrom.z;
        
        lookAtx = beetles[selected_beetles]->lookAt.x;
        lookAty = beetles[selected_beetles]->lookAt.y+1;
        lookAtz = beetles[selected_beetles]->lookAt.z;
    }
}