//
//  body.h
//  earth
//
//  Created by Josiah Ebhomenye on 25/12/2016.
//  Copyright © 2016 Josiah Ebhomenye. All rights reserved.
//

#ifndef body_h
#define body_h

#include <maths/Quaternion.h>
#include <maths/Matrix4.h>
#include <maths/vector.h>
#include "sphere.h"

using namespace physics;

class Body{
protected:
    Quaternion orientation;
    Vector position;
    Vector velocity;
    Matrix4 transform;
    
public:
    virtual void init() = 0;
    
    virtual void draw() = 0;
    
    virtual void update(real elapsedTime) = 0;
};

#endif /* body_h */
