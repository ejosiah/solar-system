//
//  gl_utility.h
//  earth
//
//  Created by Josiah Ebhomenye on 25/12/2016.
//  Copyright © 2016 Josiah Ebhomenye. All rights reserved.
//

#ifndef gl_utility_h
#define gl_utility_h

#include <maths/transformation.h>
#include <OpenGL/OpenGL.h>

void glMultipy(Matrix4& m){
    m.transpose();
    glMultMatrixf(m);
    m.transpose();
}


#endif /* gl_utility_h */
