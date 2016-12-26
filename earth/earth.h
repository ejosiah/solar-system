//
//  earth.h
//  earth
//
//  Created by Josiah Ebhomenye on 25/12/2016.
//  Copyright © 2016 Josiah Ebhomenye. All rights reserved.
//

#ifndef earth_h
#define earth_h

#include <maths/transformation.h>
#include "body.h"
#include "sphere.h"
#include "gl_utility.h"


class Earth : public Body{
protected:
    sphere earth;
    sphere clouds;
    Quaternion cloudQ;
    Vector cloudV;
    
public:
    Earth(real speed, Vector axis = {-0.398894, 0.916997, 0}){
        velocity = axis * speed;
        cloudV = Vector{0, -1, 0} * speed;
        position = {0, 0, 0};
        orientation = cloudQ = {1, 0, 0, 0};
        transform = Identity4 * translate(position);
    }
    
    virtual void init() override{
        earth = {5, 20, 20, "/Users/jay/projects/earth/earthmap1k.jpg"};
        clouds = {5.2, 50, 50, {1.0, 1.0, 1.0, 0.3}, "/Users/jay/projects/earth/earthcloudmaptrans.jpg"};
    };
    
    virtual void draw() override{
        glPushMatrix();
        glMultipy(transform);
        earth.draw();
        
        glDepthMask(false);
        Matrix4 m(cloudQ);
        glMultipy(m);
        clouds.draw();
        glDepthMask(true);
        
        
        glPopMatrix();
    };
    
    virtual void update(real elapsedTime) override{
        orientation.addScaled(velocity, elapsedTime);
        cloudQ.addScaled(cloudV, elapsedTime);
        
        orientation.normailize();
        cloudQ.normailize();
        
        Matrix4 rotation(orientation);
        
        transform =  Identity4
                     * rotate(180, {1, 0, 0})
                     * translate({0, earth.r, 0})
                     * rotation
                     * translate({0, -earth.r, 0});
        
    };
};

#endif /* earth_h */
