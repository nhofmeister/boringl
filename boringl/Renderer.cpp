//
//  Renderer.cpp
//  boringl
//
//  Created by Nils Hofmeister on 06/05/14.
//  Copyright (c) 2014 Nils Hofmeister. All rights reserved.
//

#include "Renderer.h"

#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "Camera.h"

static GLfloat whiteLight[3] = {1.0f, 1.0f, 1.0f};
static GLfloat greenLight[3] = {0.0f, 1.0f, 0.0f};
static GLfloat lightPosition[4] = {0.0f, 0.0f, 0.0f, 1.0f};
static GLuint teaTex;

static int minFilter = GL_LINEAR;
static int magFilter = GL_LINEAR;
static int wrapS = GL_REPEAT;
static int wrapT = GL_REPEAT;
static int envMode = GL_MODULATE;

static Renderer* CURRENT_INSTANCE = NULL;

static void drawCallback()
{
    assert( NULL != CURRENT_INSTANCE );
    CURRENT_INSTANCE->draw();
}


Renderer::Renderer( Camera& cam )
    : m_textureHeight(256)
    , m_textureWidth(256)
    , m_camera( cam )
{
    init();
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
    CURRENT_INSTANCE = this;
    
    glutDisplayFunc( drawCallback );
    glutIdleFunc( idle );
    
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
    
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	
    GLubyte texture_image[256][256][3];
    for(int i=0; i<m_textureWidth; i++)
    {
        for(int j=0; j<m_textureWidth; j++)
        {
            texture_image[i][j][0] = 255;
            texture_image[i][j][1] = 255*(i & 0x04);
            texture_image[i][j][2] = 255*(j & 0x04);
        }
    }
	
	glGenTextures(2, &teaTex);
	glBindTexture(GL_TEXTURE_2D, teaTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, envMode);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image);
	
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
	glEnable(GL_LIGHT0);
    
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
}

void Renderer::idle()
{
    glutPostRedisplay();
}

void Renderer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_camera.Update();
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
	glTranslatef(0.0f, 10.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glPopMatrix();
	
	glTranslatef(0.0f,-0.75f, -2.0f);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	
    // Draw Teapot
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, greenLight);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteLight);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glTranslatef(0.0f, 0.5f, 0.0f);
	glutSolidTeapot(1.0f);
	glPopMatrix();
    
	// Draw Floor
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteLight);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteLight);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2f(0.0f, 2.0f); glVertex3f(2.0f, 0.0f, -2.0f);
	glTexCoord2f(2.0f, 2.0f); glVertex3f(-2.0f, 0.0f, -2.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();
	
	glutSwapBuffers();
}