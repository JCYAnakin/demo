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
#include "Mesh.h"
#include "BMPHandler.h"
#include "ObjMesh.h"
#include "Tank.h"
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
float* calculateBuildingBoundingBox(BuildingMesh* mesh);
float* calculateTankBoundingBox(Tank* mesh);
float* calculateCannonRoundBoundingBox(Tank* mesh);
bool checkForTankBuildingCollision(Tank* mesh1, BuildingMesh* mesh2);
bool checkForCannonRoundTankCollision(Tank* mesh1, Tank* mesh2);
bool checkForCannonRoundBuildingCollision(Tank* mesh1, BuildingMesh* mesh2);
bool checkForTankTankCollision(Tank* mesh1, Tank* mesh2);
bool checkTankCollisionWithEnemyTanksAndBuildings(Tank* selectedTank);
bool checkCannonRoundCollisionWithTanksAndBuildings(Tank* selectedTank);
void limitCameraAngle();
void animationFunction (float delta_time);
void loadTank(Tank **tank);
void updateTanksHit();

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


// Building meshes
Mesh *buildings[25];
int numBuildings = 0;
float buildingFloorHeight = 0.25;	// Building Floor Height for city building

// Street meshes
Mesh *streets[11];
int numStreets = 0;

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

float angleTheta = 0;		// Camera X angle
float anglePhi = 80;		// Camera Y angle

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

float xbefore;			// Previous X position of tank
float zbefore;			// Previous Y position of tank


GLint glutWindowWidth    = 750;
GLint glutWindowHeight   = 500;

// Wolrd Boundaries
GLdouble worldLeftBase  =  -8.0;
GLdouble worldRightBase =  8.0;
GLdouble worldBottomBase=  -8.0;
GLdouble worldTopBase   =  8.0;

// World view boundaries
GLdouble wvLeftBase		=  worldLeftBase,
wvRightBase	=  worldRightBase,
wvBottomBase	=  worldBottomBase,
wvTopBase		=  worldTopBase;

//Building Textures
RGBpixmap bulding_pixelMap[3];
char building_fileName1[] = "/Users/jason/Desktop/opengl/TankSim-master/textures/building1.bmp";
char building_fileName2[] = "/Users/jason/Desktop/opengl/TankSim-master/textures/building2.bmp";
char building_fileName3[] = "/Users/jason/Desktop/opengl/TankSim-master/textures/building3.bmp";
//Road Textures
RGBpixmap road_pixelMap;
char road_fileName[] = "/Users/jason/Desktop/opengl/TankSim-master/textures/road.bmp";
//Terrain Textures
RGBpixmap terrain_pixelMap;
char terrain_fileName[] = "/Users/jason/Desktop/opengl/TankSim-master/textures/grass.bmp";

//Tank
std::string tank_fileName("/Users/jason/Desktop/opengl/TankSim-master/tank1/city.obj");
std::string cannon_fileName("/Users/jason/Desktop/opengl/TankSim-master/tank1/cannon.obj");
std::string turret_fileName("/Users/jason/Desktop/opengl/TankSim-master/tank1/turret.obj");
std::string wheel1_fileName("/Users/jason/Desktop/opengl/TankSim-master/tank1/wheel1.obj");
std::string wheel2_fileName("/Users/jason/Desktop/opengl/TankSim-master/tank1/wheel2.obj");
std::string wheel3_fileName("/Users/jason/Desktop/opengl/TankSim-master/tank1/wheel3.obj");
std::string wheel4_fileName("/Users/jason/Desktop/opengl/TankSim-master/tank1/wheel4.obj");

int num_of_tanks = 5;
int selected_tank = 0;
int tanksHit = 0;
bool closeWindow = false;

Tank *tank[5];
Animator *animator[5];

RGBpixmap tank_body_pixelMap;
RGBpixmap tank_cannon_pixelMap;
RGBpixmap tank_turret_pixelMap;
RGBpixmap tank_wheel_pixelMap;
const char* skyboxFileNames[] =
{
    "/Users/jason/Desktop/opengl/TankSim-master/textures/back.bmp","/Users/jason/Desktop/opengl/TankSim-master/textures/left.bmp","/Users/jason/Desktop/opengl/TankSim-master/textures/front.bmp",
    "/Users/jason/Desktop/opengl/TankSim-master/textures/right.bmp","/Users/jason/Desktop/opengl/TankSim-master/textures/top.bmp","/Users/jason/Desktop/opengl/TankSim-master/textures/bottom.bmp"
};
char tank_body_fileName[] = "/Users/jason/Desktop/opengl/TankSim-master/tank1/building3.bmp";
char tank_cannon_fileName[] = "/Users/jason/Desktop/opengl/TankSim-master/tank1/cannon.bmp";
char tank_turret_fileName[] = "/Users/jason/Desktop/opengl/TankSim-master/tank1/turret.bmp";
char tank_wheel_fileName[] = "/Users/jason/Desktop/opengl/TankSim-master/tank1/wheel.bmp";

Skybox* skybox;

std::string round_fileName("/Users/jason/Desktop/opengl/TankSim-master/round/round.obj");
char round_texture_fileName[] = "/Users/jason/Desktop/opengl/TankSim-master/round/fire.bmp";
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
    skybox = new Skybox(skyTextureNums, skyboxFileNames);
    skybox->setTextures();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //updateCameraPos();
    gluLookAt(lookFromx, lookFromy, lookFromz,lookAtx, lookAty, lookAtz, upx, upy, upz);
    
    Vector3D scale;
    Vector3D trans;
    Vector3D angles;
    
//    // Create a building
//    int numFloors = 10;
//    scale.x = scale.z = 0.5;
//    
//    scale.y = 1.0;
//    trans.x = -3.0;
//    trans.z = -1.0;
//    trans.y = 0;
//    
//    buildings[0] = createMesh(scale, trans, buildingFloorHeight, numFloors);
//    buildings[1] = createMesh(scale, Vector3D(0,0,0), buildingFloorHeight, 20);
//    buildings[2] = createMesh(scale, Vector3D(0,0,5), buildingFloorHeight, 25);
//    buildings[3] = createMesh(scale, Vector3D(-2,0,3), buildingFloorHeight, 20);
//    buildings[4] = createMesh(scale, Vector3D(5,0,2), buildingFloorHeight, 20);
//    buildings[5] = createMesh(scale, Vector3D(1,0,2), buildingFloorHeight, 30);
//    buildings[6] = createMesh(scale, Vector3D(1,0,6), buildingFloorHeight, 20);
//    buildings[7] = createMesh(scale, Vector3D(1.8,0,0), buildingFloorHeight, 10);
//    buildings[8] = createMesh(scale, Vector3D(3.8,0,5), buildingFloorHeight, 20);
//    buildings[9] = createMesh(scale, Vector3D(5,0,6), buildingFloorHeight, 13);
//    buildings[10] = createMesh(scale, Vector3D(1.8,0,-6), buildingFloorHeight, 22);
//    buildings[11] = createMesh(scale, Vector3D(5,0,-4), buildingFloorHeight, 15);
//    buildings[12] = createMesh(scale, Vector3D(8,0,-6.0), buildingFloorHeight, 18);
//    buildings[13] = createMesh(scale, Vector3D(8,0,-3), buildingFloorHeight, 22);
//    buildings[14] = createMesh(scale, Vector3D(8,0,3), buildingFloorHeight, 40);
//    numBuildings = 15;
    
//    // Create a street
//    scale.z = 0.1;
//    scale.x = 0.5;
//    scale.y = 1.0;
//    trans.x = -4.0;
//    trans.y = -0.08;
//    trans.z = -8.0;
//    
//    streets[0] = createMesh(scale, Vector3D(-4.5,-0.08,-8.0), 1.0, 15);
//    streets[0]->angles.x = 90.0;
//    streets[0]->angles.y = 90.0;
//    streets[0]->angles.z = 00.0;
//    streets[1] = createMesh(scale, Vector3D(-4.5,-0.08,-5.0), 1.0, 15);
//    streets[1]->angles.x = 90.0;
//    streets[1]->angles.y = 90.0;
//    streets[1]->angles.z = 00.0;
//    streets[2] = createMesh(scale, Vector3D(-4.5,-0.08,-2.0), 1.0, 15);
//    streets[2]->angles.x = 90.0;
//    streets[2]->angles.y = 90.0;
//    streets[2]->angles.z = 00.0;
//    streets[3] = createMesh(scale, Vector3D(-4.5,-0.08,1.0), 1.0, 15);
//    streets[3]->angles.x = 90.0;
//    streets[3]->angles.y = 90.0;
//    streets[3]->angles.z = 00.0;
//    streets[4] = createMesh(scale, Vector3D(-4.5,-0.08,4.0), 1.0, 15);
//    streets[4]->angles.x = 90.0;
//    streets[4]->angles.y = 90.0;
//    streets[4]->angles.z = 00.0;
//    streets[5] = createMesh(scale, Vector3D(-4.5,-0.08,7.0), 1.0, 15);
//    streets[5]->angles.x = 90.0;
//    streets[5]->angles.y = 90.0;
//    streets[5]->angles.z = 00.0;
//    streets[6] = createMesh(scale, Vector3D(10,-0.08,-8.0), 1.0, 15);
//    streets[6]->angles.x = 90.0;
//    streets[6]->angles.y = 00.0;
//    streets[6]->angles.z = 00.0;
//    streets[7] = createMesh(scale, Vector3D(2.75,-0.08,-8.0), 1.0, 15);
//    streets[7]->angles.x = 90.0;
//    streets[7]->angles.y = 00.0;
//    streets[7]->angles.z = 00.0;
//    streets[8] = createMesh(scale, Vector3D(6.5,-0.08,-8.0), 1.0, 15);
//    streets[8]->angles.x = 90.0;
//    streets[8]->angles.y = 00.0;
//    streets[8]->angles.z = 00.0;
//    streets[9] = createMesh(scale, Vector3D(-1.0,-0.08,-8.0), 1.0, 15);
//    streets[9]->angles.x = 90.0;
//    streets[9]->angles.y = 00.0;
//    streets[9]->angles.z = 00.0;
//    streets[10] = createMesh(scale, trans, 1.0, 15);
//    streets[10]->angles.x = 90.0;
//    streets[10]->angles.y = 00.0;
//    streets[10]->angles.z = 00.0;
//    numStreets = 11;
    
    //Texturing
    glEnable(GL_TEXTURE_2D);
    
    //Load building textures
//    readBMPFile(&bulding_pixelMap[0],building_fileName1);
//    setTexture(&bulding_pixelMap[0],2001);
    
//    readBMPFile(&bulding_pixelMap[1],building_fileName2);
//    setTexture(&bulding_pixelMap[1],2002);
    
//    readBMPFile(&bulding_pixelMap[2],building_fileName3);
//    setTexture(&bulding_pixelMap[2],2003);
    
    //Road Textures
//    readBMPFile(&road_pixelMap, road_fileName);
//    setTexture(&road_pixelMap, 2004);
    
    // Terrain textures
    readBMPFile(&terrain_pixelMap, terrain_fileName);
    setTexture(&terrain_pixelMap, 2005);
    
//    //Set Texture for buildings
//    for (int i = 0; i < numBuildings; i++) {
//        if ((i % 2) == 0) {
//            setTextureMapID(buildings[i],2001);
//        } else if ((i % 3) == 0) {
//            setTextureMapID(buildings[i],2002);
//        } else {
//            setTextureMapID(buildings[i],2003);
//        }
//        
//    }
    
//    //Set Texture for streets
//    for (int i = 0; i < numStreets; i++) {
//        setTextureMapID(streets[i], 2004);
//    }
    
    //Set Texture for Terrain
    terrain->setTextureID(2005);
    
    readBMPFile(&tank_body_pixelMap, tank_body_fileName);
    setTexture(&tank_body_pixelMap, 2006);
    
    readBMPFile(&tank_cannon_pixelMap, tank_cannon_fileName);
    setTexture(&tank_cannon_pixelMap, 2007);
    
    readBMPFile(&tank_turret_pixelMap, tank_turret_fileName);
    setTexture(&tank_turret_pixelMap, 2008);
    
    readBMPFile(&tank_wheel_pixelMap, tank_wheel_fileName);
    setTexture(&tank_wheel_pixelMap, 2009);
    
    for(int i = 0; i < num_of_tanks; i++){
        loadTank(&tank[i]);
        animator[i] = new Animator(tank[i],5.0,180);
    }
    
    tank[0]->moveBy(Vector3D(7.0,0.0,7.0));
    tank[1]->moveBy(Vector3D(-7.0,0.0,-7.0));
    tank[2]->moveBy(Vector3D(5.0,0.0,-10.0));
    tank[3]->moveBy(Vector3D(13.0,0.0,-2.0));
    tank[4]->moveBy(Vector3D(-14.0,0.0,5.0));
    
    //load Round files
    readBMPFile(&round_pixelMap, round_texture_fileName);
    setTexture(&round_pixelMap, 2010);
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
    // Draw Buildings
//    for (int i = 0; i < numBuildings; i++)
//    {
//        drawMesh(buildings[i]);
//    }
    
    // Draw Streets
//    for (int i = 0; i < numStreets; i++)
//    {
//        // Enable depth offset for roads travelling across the x-axis
//        // This will avoid z-fighting between criss-crossing roads
//        if (i > 5) {
//            glEnable(GL_POLYGON_OFFSET_FILL);
//            glPolygonOffset(1, 10);
//        } else {
//            glDisable(GL_POLYGON_OFFSET_FILL);
//        }
//        drawMesh(streets[i]);
//    }
    
    //Draw tanks
    for (int i = 0; i < num_of_tanks; i++) {
        tank[i]->draw();
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
        
        angleTheta += prevx - xMouse;
        anglePhi += prevy - yMouse;
        
        while (angleTheta < -180)
            angleTheta += 360;
        while (angleTheta > 180)
            angleTheta -= 360;
        while (anglePhi < 0)
            anglePhi += 360;
        
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
    updateTanksHit();
    //animationFunction(10.0/FPS);
    glutPostRedisplay();
}


/**************************************************************************
 * Utility Functions
 **************************************************************************/
void updateCameraPos()
{
    // Spherical coordinates formula
    lookFromx = lookAtx + radius * sin(anglePhi*0.0174532) * sin(angleTheta*0.0174532);
    lookFromy = lookAty + radius * cos(anglePhi*0.0174532);
    lookFromz = lookAtz + radius * sin(anglePhi*0.0174532) * cos(angleTheta*0.0174532);
}
/**************************************************************************
 * Bounds calculations
 **************************************************************************/
float* calculateBuildingBoundingBox(BuildingMesh* mesh)
{
    float xmin, xmax, zmin, zmax;
    
    float scalefactor = mesh->scaleFactor.z;
    if (mesh->scaleFactor.x > mesh->scaleFactor.z) {
        scalefactor = mesh->scaleFactor.x;
    }
    
    xmin = mesh->translation.x - scalefactor;
    xmax = mesh->translation.x + scalefactor;
    zmin = mesh->translation.z - scalefactor;
    zmax = mesh->translation.z + scalefactor;
    
    float* bounds = (float*)malloc(4 * sizeof(float));
    bounds[0] = xmin; bounds[1] = xmax; bounds[2] = zmin; bounds[3] = zmax;
    
    return bounds;
}

float* calculateTankBoundingBox(Tank* mesh)
{
    float xmin, xmax, zmin, zmax;
    
    // estimate tank bounding box size
    float scalefactor = 0.7;
    
    xmin = mesh->translation.x - scalefactor;
    xmax = mesh->translation.x + scalefactor;
    zmin = mesh->translation.z - scalefactor;
    zmax = mesh->translation.z + scalefactor;
    
    float* bounds = (float*)malloc(4 * sizeof(float));
    bounds[0] = xmin; bounds[1] = xmax; bounds[2] = zmin; bounds[3] = zmax;
    
    return bounds;
}

float* calculateCannonRoundBoundingBox(Tank* mesh)
{
    float xmin, xmax, zmin, zmax;
    
    // estimate round bounding box size
    float scalefactor = 0.2;
    
    xmin = mesh->round->translation.x - scalefactor;
    xmax = mesh->round->translation.x + scalefactor;
    zmin = mesh->round->translation.z - scalefactor;
    zmax = mesh->round->translation.z + scalefactor;
    
    float* bounds = (float*)malloc(4 * sizeof(float));
    bounds[0] = xmin; bounds[1] = xmax; bounds[2] = zmin; bounds[3] = zmax;
    
    return bounds;
}

/**************************************************************************
 * Collision detection functions between two objects
 **************************************************************************/
bool checkForTankBuildingCollision(Tank* mesh1, BuildingMesh* mesh2)
{
    float* tankBounds_ptr = calculateTankBoundingBox(mesh1);
    float* buildingBounds_ptr = calculateBuildingBoundingBox(mesh2);
    
    float tankBounds[] = {tankBounds_ptr[0], tankBounds_ptr[1], tankBounds_ptr[2], tankBounds_ptr[3]};
    float buildingBounds[] = {buildingBounds_ptr[0], buildingBounds_ptr[1], buildingBounds_ptr[2], buildingBounds_ptr[3]};
    
    free(tankBounds_ptr); free(buildingBounds_ptr);
    
    bool collision = false;
    float margin = 0.0;
    
    // xmin of mesh 1 <= xmax of mesh2 AND xmax of mesh 1 >= xmin of mesh 2
    if (tankBounds[0] - margin < buildingBounds[1] && tankBounds[1] + margin > buildingBounds[0])
        // zmin of mesh 1 <= zmax of mesh2 AND zmax of mesh 1 >= zmin of mesh 2
        if (tankBounds[2] - margin < buildingBounds[3] && tankBounds[3] + margin > buildingBounds[2])
            collision = true;  // collision detected
    
    return collision;
}

bool checkForCannonRoundTankCollision(Tank* mesh1, Tank* mesh2)
{
    float* cannonRound_ptr = calculateCannonRoundBoundingBox(mesh1);
    float* tankBounds_ptr = calculateTankBoundingBox(mesh2);
    
    float cannonRoundBounds[] = {cannonRound_ptr[0], cannonRound_ptr[1], cannonRound_ptr[2], cannonRound_ptr[3]};
    float tankBounds[] = {tankBounds_ptr[0], tankBounds_ptr[1], tankBounds_ptr[2], tankBounds_ptr[3]};
    
    free(cannonRound_ptr); free(tankBounds_ptr);
    
    bool collision = false;
    float margin = 0.0;
    
    // xmin of mesh 1 <= xmax of mesh2 AND xmax of mesh 1 >= xmin of mesh 2
    if (cannonRoundBounds[0] - margin < tankBounds[1] && cannonRoundBounds[1] + margin > tankBounds[0])
        // zmin of mesh 1 <= zmax of mesh2 AND zmax of mesh 1 >= zmin of mesh 2
        if (cannonRoundBounds[2] - margin < tankBounds[3] && cannonRoundBounds[3] + margin > tankBounds[2])
            collision = true;  // collision detected
    
    return collision;
}

bool checkForCannonRoundBuildingCollision(Tank* mesh1, BuildingMesh* mesh2)
{
    float* cannonRound_ptr = calculateCannonRoundBoundingBox(mesh1);
    float* buildingBounds_ptr = calculateBuildingBoundingBox(mesh2);
    
    float cannonRoundBounds[] = {cannonRound_ptr[0], cannonRound_ptr[1], cannonRound_ptr[2], cannonRound_ptr[3]};
    float buildingBounds[] = {buildingBounds_ptr[0], buildingBounds_ptr[1], buildingBounds_ptr[2], buildingBounds_ptr[3]};
    
    free(cannonRound_ptr); free(buildingBounds_ptr);
    
    bool collision = false;
    float margin = 0.0;
    
    // xmin of mesh 1 <= xmax of mesh2 AND xmax of mesh 1 >= xmin of mesh 2
    if (cannonRoundBounds[0] - margin < buildingBounds[1] && cannonRoundBounds[1] + margin > buildingBounds[0])
        // zmin of mesh 1 <= zmax of mesh2 AND zmax of mesh 1 >= zmin of mesh 2
        if (cannonRoundBounds[2] - margin < buildingBounds[3] && cannonRoundBounds[3] + margin > buildingBounds[2])
            collision = true;  // collision detected
    
    return collision;
}

bool checkForTankTankCollision(Tank* mesh1, Tank* mesh2)
{
    float* tankBounds1_ptr = calculateTankBoundingBox(mesh1);
    float* tankBounds2_ptr = calculateTankBoundingBox(mesh2);
    
    float tankBounds1[] = {tankBounds1_ptr[0], tankBounds1_ptr[1], tankBounds1_ptr[2], tankBounds1_ptr[3]};
    float tankBounds2[] = {tankBounds2_ptr[0], tankBounds2_ptr[1], tankBounds2_ptr[2], tankBounds2_ptr[3]};
    
    free(tankBounds1_ptr); free(tankBounds2_ptr);
    
    bool collision = false;
    float margin = 0.0;
    
    // xmin of mesh 1 <= xmax of mesh2 AND xmax of mesh 1 >= xmin of mesh 2
    if (tankBounds1[0] - margin < tankBounds2[1] && tankBounds1[1] + margin > tankBounds2[0])
        // zmin of mesh 1 <= zmax of mesh2 AND zmax of mesh 1 >= zmin of mesh 2
        if (tankBounds1[2] - margin < tankBounds2[3] && tankBounds1[3] + margin > tankBounds2[2])
            collision = true;  // collision detected
    
    return collision;
}

/**************************************************************************
 * Collision detection functions between one object and several
 **************************************************************************/
bool checkTankCollisionWithEnemyTanksAndBuildings(Tank* selectedTank)
{
    bool collision = false;
    
    for (int i = 0; i < numBuildings; i++)
        if (checkForTankBuildingCollision(selectedTank, buildings[i]))
            collision = true;
    
    for (int i = 0; i < num_of_tanks; i++) {
        if (i == selected_tank)
            continue;
        if (checkForTankTankCollision(selectedTank, tank[i]))
            collision = true;
    }
    
    return collision;
}

bool checkCannonRoundCollisionWithTanksAndBuildings(Tank* selectedTank)
{
    bool collision = false;
    
    for (int i = 0; i < numBuildings; i++)
        if (checkForCannonRoundBuildingCollision(selectedTank, buildings[i]))
            collision = true;
    
    for (int i = 0; i < num_of_tanks; i++) {
        if (i == selected_tank) {
            continue;
        } else if (checkForCannonRoundTankCollision(selectedTank, tank[i])) {
            tank[i]->hit = true;
            collision = true;
        }
    }
    
    return collision;
}

bool checkEnemyTankCollisionWithEnemyTanksAndBuildings(Tank* enemyTank, int enemyTankIndex)
{
    bool collision = false;
    
    for (int i = 0; i < numBuildings; i++)
        if (checkForTankBuildingCollision(enemyTank, buildings[i]))
            collision = true;
    
    for (int i = 0; i < num_of_tanks; i++) {
        if (i == enemyTankIndex)
            continue;
        if (checkForTankTankCollision(enemyTank, tank[i]))
            collision = true;
    }
    
    return collision;
}


/**************************************************************************
 * Limit Camera angle
 **************************************************************************/
void limitCameraAngle()
{
    if (anglePhi > 80)
        anglePhi = 80;
    if (anglePhi < 30)
        anglePhi = 30;
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
                tank[selected_tank]->updateCamera();
                
                lookFromx = tank[selected_tank]->lookFrom.x;
                lookFromy = tank[selected_tank]->lookFrom.y;
                lookFromz = tank[selected_tank]->lookFrom.z;
                
                lookAtx = tank[selected_tank]->lookAt.x;
                lookAty = tank[selected_tank]->lookAt.y;
                lookAtz = tank[selected_tank]->lookAt.z;
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
    
    for(int i =0; i < num_of_tanks; i++) {
        if (i != selected_tank && !tank[i]->hit) {
            animator[i]->animate(distance,angle);
            if (checkEnemyTankCollisionWithEnemyTanksAndBuildings(tank[i], i)) {
                animator[i]->animate(-distance,angle);
            }
        }
    }
    
    if (tank[selected_tank]->cannonFired) {
        if (checkCannonRoundCollisionWithTanksAndBuildings(tank[selected_tank])) {
            tank[selected_tank]->round->body->setTextureMapID(2010);
            tank[selected_tank]->cannonFired = false;
            tank[selected_tank]->cannonHit = true;
        }
    }
    
    if (tank[selected_tank]->cannonHit) {
        tank[selected_tank]->round->lived += delta_time;
    }
    
    if (tank[selected_tank]->round->lived >= tank[selected_tank]->round->live_for) {
        tank[selected_tank]->round->lived = 0;
        tank[selected_tank]->cannonHit = false;
    }
    
    // animates round if fired (check for firing occurs in draw() for Tank)
    tank[selected_tank]->animateRound();
    
    if (currentAction == NAVIGATE)
    {
        switch (currentFuncKey)
        {
            case GLUT_KEY_DOWN:
                tank[selected_tank]->moveBy(-distance);
                if (checkTankCollisionWithEnemyTanksAndBuildings(tank[selected_tank])) {
                    tank[selected_tank]->moveBy(distance);
                }
                break;
            case GLUT_KEY_UP:
                tank[selected_tank]->moveBy(distance);
                if (checkTankCollisionWithEnemyTanksAndBuildings(tank[selected_tank])) {
                    tank[selected_tank]->moveBy(-distance);
                }
                break;
            case GLUT_KEY_RIGHT:
                tank[selected_tank]->rotateBy(-angle);
                break;
                
            case GLUT_KEY_LEFT:
                tank[selected_tank]->rotateBy(angle);
                break;
        }
        
        switch (currentKey) {
            case 'a':
                tank[selected_tank]->rotateTurret(angle);
                break;
            case 'd':
                tank[selected_tank]->rotateTurret(-angle);
                break;
            case 'q':
                tank[selected_tank]->rotateCannon(angle);
                break;
            case 'e':
                tank[selected_tank]->rotateCannon(-angle);
                break;
            case 'f':
                tank[selected_tank]->fireCannon();
                break;
        }
        
        lookFromx = tank[selected_tank]->lookFrom.x;
        lookFromy = tank[selected_tank]->lookFrom.y;
        lookFromz = tank[selected_tank]->lookFrom.z;
        
        lookAtx = tank[selected_tank]->lookAt.x;
        lookAty = tank[selected_tank]->lookAt.y+1;
        lookAtz = tank[selected_tank]->lookAt.z;
    }
}

void loadTank(Tank **tank_new){
    *tank_new = new Tank();
    
    load_obj(round_fileName, &(*tank_new)->round->body);
    
    load_obj(tank_fileName, &(*tank_new)->body);
    load_obj(cannon_fileName, &(*tank_new)->cannon);
    load_obj(turret_fileName, &(*tank_new)->turret);
    
    std::vector<ObjMesh *> * wheels = new std::vector<ObjMesh *>();
    ObjMesh *wheel;
    
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
    (*tank_new)->set_wheels(*wheels);
    
    (*tank_new)->body->setTextureMapID(2006);
    (*tank_new)->cannon->setTextureMapID(2007);
    (*tank_new)->turret->setTextureMapID(2008);
    (*tank_new)->wheels[0]->setTextureMapID(2009);
    (*tank_new)->wheels[1]->setTextureMapID(2009);
    (*tank_new)->wheels[2]->setTextureMapID(2009);
    (*tank_new)->wheels[3]->setTextureMapID(2009);
}

void updateTanksHit() {
    tanksHit = 0;
    
    for (int i = 0; i < num_of_tanks; i++)
        if (tank[i]->hit)
            tanksHit++;
}