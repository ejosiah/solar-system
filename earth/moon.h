//
//  moon.h
//  earth
//
//  Created by Josiah Ebhomenye on 25/12/2016.
//  Copyright © 2016 Josiah Ebhomenye. All rights reserved.
//

#ifndef moon_h
#define moon_h

#include "body.h"

class Moon : public Body{
protected:
    real radius;
    sphere sphere;
    
public:
    Moon(real r, real distanceFromEarth, real speed, Vector axis = {0, -1, 0}){
        radius = r;
        velocity = axis * speed;
        position = {0, 0, distanceFromEarth};
        orientation = {1, 0, 0, 0};
    }
    
    virtual void init() override{
        sphere = {radius, 50, 50, "/Users/jay/Downloads/moon.jpg"};
    };
    
    virtual void draw() override{
        glPushMatrix();
        glMultipy(transform);
        sphere.draw();
        glPopMatrix();
    };
    
    virtual void update(real elapsedTime) override{
        orientation.addScaled(velocity, elapsedTime);
        orientation.normailize();
        
        Matrix4 rotation(orientation);
        
        transform =   Identity4 * rotation * translate(position) * rotation;
        
    };
};


#endif /* moon_h */
