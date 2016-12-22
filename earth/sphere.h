//
//  sphere.h
//  earth
//
//  Created by Josiah Ebhomenye on 19/12/2016.
//  Copyright © 2016 Josiah Ebhomenye. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include <cmath>
#include <vector>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

static float PI = 3.142857;
struct vec4{
    float x, y, z, w;
};
struct vec3{
    float x, y, z;
};

struct vec2{
    float x, y;
};

static const vec4 DEFAULT_COLOR{1.0, 1.0, 1.0, 1.0};

class sphere{
public:
    float r;
private:
    float p, q;
    vec4 color;
    const char* texture;
    GLuint textureId;
    std::vector<vec4> colors;
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<vec2> texCoords;
    
    std::vector<GLuint> indices;
    
    
    
public:
    sphere(){}
    
    sphere(float r, float q, float p, const char* texture, vec4 color = DEFAULT_COLOR)
    :sphere(r, q, p, color, texture){
        
    }
    
    sphere(float r, float q, float p, vec4 color = DEFAULT_COLOR):sphere(r, q, p, color, nullptr){
        
    }
    
    sphere(float r, float q, float p, vec4 color, const char* texture)
    :r(r), p(p), q(q), color(color), texture(texture){
        init();
    }
    
    void init(){
        fillVertices();
        fillIndices();
        if(texture != nullptr){
            initTexture();
        }
    }
    
    void initTexture(){
        textureId = SOIL_load_OGL_texture(texture,
                                          SOIL_LOAD_AUTO,
                                          SOIL_CREATE_NEW_ID,
                                          SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    }
    
    void initBuffers(){
        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glColorPointer(4, GL_FLOAT, 0, &colors[0]);
        glEnableClientState(GL_COLOR_ARRAY);
        
        
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glEnableClientState(GL_NORMAL_ARRAY);

        glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    
    void fillVertices() {
        
        for (int j = 0; j <= q; j++) {
            for (int i = 0; i <= p; i++) {
                vertices.push_back(vec3{f(i, j, q, p, r), g(i, j, q, p, r), h(i, j, q, p, r)});
                normals.push_back(vec3{fn(i, j, q, p, r), gn(i, j, q, p, r), hn(i, j, q, p, r)});
                texCoords.push_back(vec2{float(i) / p, float(j) / q});
                colors.push_back(color);
            }
        }
    }
    
    void fillIndices() {
        for (int j = 0; j < q; j++) {
            for (int i = 0; i <= p; i++) {
                indices.push_back((j + 1)*(p + 1) + i);
                indices.push_back(j*(p + 1) + i);
            }
        }
    }
    
    float f(int i, int j, int q, int p, float r) {
        float u = 2 * float(i) / p * PI;
        float v = float(j) / q * PI;
        
        return r * cosf(u) * sinf(v);
    }
    
    float g(int i, int j, int q, int p, float r) {
        float v = float(j) / q * PI;
        
        return r * cosf(v);
    }
    
    float h(int i, int j, int q, int p, float r) {
        float u = 2 * float(i) / p * PI;
        float v = float(j) / q * PI;
        return r * sinf(u) * sinf(v);
    }
    
    float fn(int i, int j, int q, int p, float r) {
        float u = 2 * float(i) / p * PI;
        float v = float(j) / q * PI;
        
        return cosf(u) * sinf(v);
    }
    
    float gn(int i, int j, int q, int p, float r) {
        float v = float(j) / q * PI;
        
        return cosf(v);
    }
    
    float hn(int i, int j, int q, int p, float r) {
        float u = 2 * float(i) / p * PI;
        float v = float(j) / q * PI;
        
        return  sinf(u) * sinf(v);
        
    }
    
    void draw(){
        if(texture != nullptr){
            if(color.w < 1){
                glDepthMask(false);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }else{
                glBlendFunc(GL_ONE, GL_ZERO);
            }
            glBindTexture(GL_TEXTURE_2D, textureId);
        }
        initBuffers();
        glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, &indices[0]);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDepthMask(true);

    }
};


#endif /* sphere_h */
