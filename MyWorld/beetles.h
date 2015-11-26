#ifndef BeetlesSim_Beetles_h
#define BeetlesSim_Beetles_h
#include <math.h>
#include "VectorAndPoint.h"

class Beetles {
    
    public:
    Vector3D translation;
    Vector3D angles; //angle around the Y axis
    
    //Meshes
    MyObj *body      = nullptr;
    MyObj *(*wheels) = nullptr;
    MyObj *cannon    = nullptr;
    MyObj *cabin     = nullptr;
    
    //Camera
    Vector3D lookFrom;
    Vector3D lookAt;
    
    //Other
    int num_of_wheels;
    float cam_height;
  
    bool cannonFired = false;
    bool cannonHit = false;
  
    bool hit = false;
    
    
  
    Beetles() {
        this->num_of_wheels = 0;
        this->cam_height = 1;
    };
    
    
    void set_wheels (std::vector<MyObj *> &wheels) {
        if(this->wheels){
            free(this->wheels);
        }
        
        this->num_of_wheels = (int) wheels.size();
        this->wheels = &wheels[0];
        
        for(int i = 0; i < num_of_wheels; i++) {
            this->wheels[i]->translation.x += this->translation.x;
            this->wheels[i]->translation.y += this->translation.y;
            this->wheels[i]->translation.z += this->translation.z;
        }
    };
    
    void draw() {
      if (this->hit) {
        this->body->mat_diffuse[0] = 1.0;
        this->body->mat_diffuse[1] = 0.0;
        this->body->mat_diffuse[2] = 0.0;
        this->cannon->mat_diffuse[0] = 1.0;
        this->cannon->mat_diffuse[1] = 0.0;
        this->cannon->mat_diffuse[2] = 0.0;
        this->cabin->mat_diffuse[0] = 1.0;
        this->cabin->mat_diffuse[1] = 0.0;
        this->cabin->mat_diffuse[2] = 0.0;
      }
        this->body->draw();
        //this->cannon->draw();
        //this->cabin->draw();
        
        for (int i = 0; i < num_of_wheels; i++) {
            this->wheels[i]->draw();
        }
//
//        if (this->cannonFired || this->cannonHit) {
//          this->round->draw();
//        }
        
    };
    
    /*Moves the Beetles by Vector */
    void moveBy (Vector3D position) {
        this->translation.x += position.x;
        this->translation.y += position.y;
        this->translation.z += position.z;
        
        this->body->translation.x += position.x;
        this->body->translation.y += position.y;
        this->body->translation.z += position.z;
        
        this->cannon->translation.x += position.x;
        this->cannon->translation.y += position.y;
        this->cannon->translation.z += position.z;
        
        this->cabin->translation.x += position.x;
        this->cabin->translation.y += position.y;
        this->cabin->translation.z += position.z;
        
        for(int i = 0; i < num_of_wheels; i++) {
            this->wheels[i]->translation.x += position.x;
            this->wheels[i]->translation.y += position.y;
            this->wheels[i]->translation.z += position.z;
        }
        
    };
    
    /*Moves the Beetles Forward or backwards */
    void moveBy (float distance) {
      
        int sign = distance < 0 ? 1 : -1;
      
        float new_x  = distance * sinf(this->angles.y * 3.14159265 / 180);
        float new_z  = distance * cosf(this->angles.y * 3.14159265 / 180);
        
        this->translation.x += new_x;
        this->translation.z += new_z;
        
        this->body->translation.x += new_x;
        this->body->translation.z += new_z;
        
        this->cannon->translation.x += new_x;
        this->cannon->translation.z += new_z;
        
        this->cabin->translation.x += new_x;
        this->cabin->translation.z += new_z;
        
        for(int i = 0; i < num_of_wheels; i++) {
            this->wheels[i]->translation.x += new_x;
            this->wheels[i]->translation.z += new_z;
            this->wheels[i]->angles.x += 5 * -sign;
        }
    };
    
    
    /* Rotates the Beetless
       Rotations doesn't affect the cannon or the cabin
     */
    void rotateBy (float angle) {
        this->angles.y += angle;
        
        //Body transformation
        this->body->angles.y += angle;
        
        //Wheels transformation
        for (int i = 0; i < num_of_wheels; i++) {
            this->wheels[i]->angles.y += angle;
        }
    };
    
    /* Rotates the Beetles Cannon */
    void rotateCannon (float angle) {
        this->cannon->angles.y += angle;
    }
    
    /* Rotates the Turret */
    
    void rotateBeetles(float angle) {
        rotateBy (angle);
        rotateCannon (angle);
    }
  
};

#endif
