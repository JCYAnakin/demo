#ifndef house_h
#define house_h
#include <math.h>
#include "VectorAndPoint.h"

class House{
    
public:
    Vector3D translation;
    Vector3D angles; //angle around the Y axis
    MyObj *body;
    
    void draw() {
        this->body->draw();
    }
};

#endif /* house_h */
