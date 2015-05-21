//
//  Renderer.h
//  boringl
//
//  Created by Nils Hofmeister on 06/05/14.
//  Copyright (c) 2014 Nils Hofmeister. All rights reserved.
//

#ifndef __boringl__Renderer__
#define __boringl__Renderer__

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Camera;

class Renderer
{
public:
    Renderer( Camera& cam );
    virtual ~Renderer();
    
    void draw();
    
private:
    void init();
    
    static void idle();
    
    const int m_textureHeight;
    const int m_textureWidth;
    
    Camera& m_camera;
};

#endif /* defined(__boringl__Renderer__) */
