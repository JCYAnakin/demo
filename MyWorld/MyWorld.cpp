#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
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
#include "house.h"
#include "beetles.h"
#include "animator.h"
#include "Skybox.h"


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
void updateBeetlessHit();

static int currentButton;
static unsigned char currentKey;
static int currentFuncKey;
const float FPS = 30.0;
int count = 0;

// City Interaction State Variable
enum Action {TRANSLATE, ROTATE, SCALE, EXTRUDE, SELECT, MULTIPLESELECT, DESELECT_ALL, NAVIGATE};
enum Action currentAction = TRANSLATE;

GLfloat light_position0[] = {-12.0, 24.0,12.0, 1.0}; //1:infinity
GLfloat light_diffuse[]   = {1.0, 1.0, 1.0, 1.0};  //diffusion..
GLfloat light_specular[]  = {1.0, 1.0, 1.0, 1.0};  //"mirror"...
GLfloat light_ambient[]   = {1.0, 0.5, 1.0, 1.0};  //RGBA, environment..

// City terrain mesh
Terrain *terrain = NULL;
int gridSize = 16;



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

//Building Textures
RGBpixmap bulding_pixelMap[3];
char building_fileName1[] = "/Users/jason/Xcode/MyWorld/textures/building1.bmp";
char building_fileName2[] = "/Users/jason/Xcode/MyWorld/textures/building2.bmp";
char building_fileName3[] = "/Users/jason/Xcode/MyWorld/textures/building3.bmp";
//Road Textures
RGBpixmap road_pixelMap;
char road_fileName[] = "/Users/jason/Xcode/MyWorld/textures/road.bmp";
//Terrain Textures
RGBpixmap terrain_pixelMap;
char terrain_fileName[] = "/Users/jason/Xcode/MyWorld/textures/grass.bmp";
//Beetles
std::string beetles_fileName("/Users/jason/Xcode/MyWorld/forBeetles/city.obj");
std::string house_obj_fileName("/Users/jason/Xcode/MyWorld/forBeetles/city.obj");
std::string cannon_fileName("/Users/jason/Xcode/MyWorld/forBeetles/cannon.obj");
std::string cabin_fileName("/Users/jason/Xcode/MyWorld/forBeetles/turret.obj");
std::string wheel1_fileName("/Users/jason/Xcode/MyWorld/forBeetles/wheel1.obj");
std::string wheel2_fileName("/Users/jason/Xcode/MyWorld/forBeetles/wheel2.obj");
std::string wheel3_fileName("/Users/jason/Xcode/MyWorld/forBeetles/wheel3.obj");
std::string wheel4_fileName("/Users/jason/Xcode/MyWorld/forBeetles/wheel4.obj");

int num_of_beetless = 5;
int num_of_house = 4;
int selected_beetles = 0;
int beetlessHit = 0;
bool closeWindow = false;

Beetles *beetles[5];
House *house[5];
Animator *animator[5];

RGBpixmap beetles_body_pixelMap;
RGBpixmap beetles_cannon_pixelMap;
RGBpixmap beetles_cabin_pixelMap;
RGBpixmap beetles_wheel_pixelMap;

RGBpixmap house_pixelMap;

char beetles_body_fileName[] = "/Users/jason/Xcode/MyWorld/forBeetles/building3.bmp";
char beetles_cannon_fileName[] = "/Users/jason/Xcode/MyWorld/forBeetles/cannon.bmp";
char beetles_cabin_fileName[] = "/Users/jason/Xcode/MyWorld/forBeetles/turret.bmp";
char beetles_wheel_fileName[] = "/Users/jason/Xcode/MyWorld/forBeetles/wheel.bmp";

char house_pic_fileName[] = "/Users/jason/Xcode/MyWorld/forBeetles/building3.bmp";


Skybox* skybox;

RGBpixmap round_pixelMap;

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My");
    
    initOpenGL();
    //initShaders();
    
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
    
    glClearColor(0.6, 0.6, 0.6, 0.0);
    glClearDepth(1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST);
    
    // Set up Terrain Grid
    Vector3D startPoint = Vector3D(-16.0f,0.0f,16.0f);
    terrain = new Terrain(gridSize);
    terrain->InitGrid(gridSize, startPoint, 32.0, 32.0);
    
    // Set up Skybox
    int skyTextureNums[] = {1,2,3,4,5,6};
    skybox = new Skybox();
    skybox->setTextures();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //updateCameraPos();
    gluLookAt(lookFromx, lookFromy, lookFromz,lookAtx, lookAty, lookAtz, upx, upy, upz);
    
    Vector3D scale;
    Vector3D trans;
    Vector3D angles;
    //Texturing
    glEnable(GL_TEXTURE_2D);
    
    // Terrain textures
    readBMPFile(&terrain_pixelMap, terrain_fileName);
    setTexture(&terrain_pixelMap, 2005);

    //Set Texture for Terrain
    terrain->setTextureID(2005);
    
    readBMPFile(&beetles_body_pixelMap, beetles_body_fileName);
    setTexture(&beetles_body_pixelMap, 2006);
    
    readBMPFile(&beetles_wheel_pixelMap, beetles_wheel_fileName);
    setTexture(&beetles_wheel_pixelMap, 2009);
    
    
    for(int i = 0; i < num_of_beetless; i++){
        loadBeetles(&beetles[i]);
        animator[i] = new Animator(beetles[i],5.0,180);
    }
    for(int i = 0; i < num_of_house; i++){
        //load_obj(house_obj_fileName[i], &(*house[i])->body)
        //loadBeetles(&beetles[i]);
    }
    
    beetles[0]->moveBy(Vector3D(0.0,-0.7,0.0));
    beetles[1]->moveBy(Vector3D(-7.0,0.0,-7.0));
    beetles[2]->moveBy(Vector3D(5.0,0.0,-10.0));
    beetles[3]->moveBy(Vector3D(13.0,0.0,-2.0));
    beetles[4]->moveBy(Vector3D(-14.0,0.0,5.0));
    beetles[0]->body->scaleFactor.x=beetles[0]->body->scaleFactor.y=beetles[0]->body->scaleFactor.z = 0.003;
    beetles[1]->body->scaleFactor.x=beetles[1]->body->scaleFactor.y=beetles[1]->body->scaleFactor.z = 0.003;
    beetles[2]->body->scaleFactor.x=beetles[2]->body->scaleFactor.y=beetles[2]->body->scaleFactor.z = 0.003;
    beetles[3]->body->scaleFactor.x=beetles[3]->body->scaleFactor.y=beetles[3]->body->scaleFactor.z = 0.003;
    beetles[4]->body->scaleFactor.x=beetles[4]->body->scaleFactor.y=beetles[4]->body->scaleFactor.z = 0.003;
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
    for (int i = 0; i < num_of_beetless; i++) {
        beetles[i]->draw();
    }
    
    // Enable depth offset with terrain with respect to roads so that roads
    // won't get drawn inside the terrain
    glEnable(GL_POLYGON_OFFSET_FILL);
    terrain->DrawGrid(gridSize);
    glDisable(GL_POLYGON_OFFSET_FILL);
    
    
    glutSwapBuffers();
}


// Called at initialization and whenever user resizes the window */
void reshape(int w, int h)
{
    glutWindowWidth = w; glutWindowHeight = h;
    //glViewport(0, 0, viewportWidth, viewportHeight);
    glViewport(0, 0, (GLsizei) glutWindowWidth, (GLsizei) glutWindowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // keep same aspect ratio as screen window
    gluPerspective(60.0*zoom,(float)glutWindowWidth/(float)glutWindowHeight,0.2,80.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Vector3D pos = Vector3D(0,0,0);

// Mouse Control coordinates
int prevx, prevy;

int selectedControlPoint = -1;

void mouse(int button, int state, int x, int y)
{
    currentButton = button;
    
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
        if (yMouse < prevy) {
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

/**************************************************************************
 * Timer function to limit Frames Per Second
 **************************************************************************/
void timer(int value)
{
    if (closeWindow) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        exit(EXIT_SUCCESS);
    }
    glutTimerFunc(1000.0 / FPS, timer, 0);
    updateBeetlessHit();
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
                
                lookFromx = beetles[selected_beetles]->lookFrom.x;
                lookFromy = beetles[selected_beetles]->lookFrom.y;
                lookFromz = beetles[selected_beetles]->lookFrom.z;
                
                lookAtx = beetles[selected_beetles]->lookAt.x;
                lookAty = beetles[selected_beetles]->lookAt.y;
                lookAtz = beetles[selected_beetles]->lookAt.z;
            }
            else
            {
                currentAction = TRANSLATE;
                lookAtx = lookFromx;
                lookAty = lookFromy;
                lookAtz = lookFromz;
                
                lookFromx = camerax;
                lookFromy = cameray;
                lookFromz = cameraz;
            }
            break;
//        case 'a':
//            lookAtx-=1;
//            break;
//        case 'd':
//            lookAtx-=1;
//            break;
//        case 'w':
//            lookAty+=1;
//            break;
//        case 's':
//            lookAty-=1;
//            break;
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
                beetles[selected_beetles]->moveBy(-distance);
                if (checkBeetlesCollisionWithEnemyBeetlessAndBuildings(beetles[selected_beetles])) {
                    beetles[selected_beetles]->moveBy(distance);
                }
                break;
            case GLUT_KEY_UP:
                beetles[selected_beetles]->moveBy(distance);
                if (checkBeetlesCollisionWithEnemyBeetlessAndBuildings(beetles[selected_beetles])) {
                    beetles[selected_beetles]->moveBy(-distance);
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
                beetles[selected_beetles]->rotateCannon(angle);
                break;
            case 'e':
                beetles[selected_beetles]->rotateCannon(-angle);
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

void loadBeetles(Beetles **beetles_new){
    *beetles_new = new Beetles();
    
    load_obj(beetles_fileName, &(*beetles_new)->body);
    load_obj(cannon_fileName, &(*beetles_new)->cannon);
    load_obj(cabin_fileName, &(*beetles_new)->cabin);
    
    std::vector<MyObj *> * wheels = new std::vector<MyObj *>();
    MyObj *wheel;
    
    //Loads Wheels
    load_obj(wheel1_fileName, &wheel);
    wheels->push_back(wheel);
    wheel->use_center_x_translate = true;
    
    load_obj(wheel2_fileName, &wheel);
    wheels->push_back(wheel);
    wheel->use_center_x_translate = true;
    
    load_obj(wheel3_fileName, &wheel);
    wheels->push_back(wheel);
    wheel->use_center_x_translate = true;
    
    load_obj(wheel4_fileName, &wheel);
    wheels->push_back(wheel);
    wheel->use_center_x_translate = true;
    (*beetles_new)->set_wheels(*wheels);
    
    (*beetles_new)->body->setTextureMapID(2006);
    (*beetles_new)->cannon->setTextureMapID(2007);
    (*beetles_new)->cabin->setTextureMapID(2008);
    (*beetles_new)->wheels[0]->setTextureMapID(2009);
    (*beetles_new)->wheels[1]->setTextureMapID(2009);
    (*beetles_new)->wheels[2]->setTextureMapID(2009);
    (*beetles_new)->wheels[3]->setTextureMapID(2009);
}

void updateBeetlessHit() {
    beetlessHit = 0;
    
    for (int i = 0; i < num_of_beetless; i++)
        if (beetles[i]->hit)
            beetlessHit++;
}