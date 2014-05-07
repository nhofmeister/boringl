//
//  Window.cpp
//  boringl
//
//  Created by Nils Hofmeister on 06/05/14.
//  Copyright (c) 2014 Nils Hofmeister. All rights reserved.
//

#include "Window.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Window::Window()
    : m_windowID( 0 )
{
    init();
}


Window::~Window()
{
    if( 0 != m_windowID )
    {
        glutDestroyWindow( m_windowID );
        m_windowID = 0;
    }
}

void Window::init()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition (10, 10);
	glutInitWindowSize (512, 512);
	m_windowID = glutCreateWindow ("Ramazotti");
}