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

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();
    
private:
    void init();
    
    static void idle();
    static void draw();
    
    const int m_textureHeight;
    const int m_textureWidth;
};

#endif /* defined(__boringl__Renderer__) */
