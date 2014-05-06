
#include "Window.h"
#include "Renderer.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
    
    Window window;
    Renderer renderer;
	
	glutMainLoop();
	
	return 0;		
}