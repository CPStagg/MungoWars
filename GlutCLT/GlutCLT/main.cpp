#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "mungo.h"
 
// ---- Prototypes ----
void Render(void);
void Initialise();
 
// ---- Main Function ----
int main(int argc, char** argv)
{
	glutInit(&argc,argv); 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0); 
	glutCreateWindow("GlutApp");
	glutDisplayFunc(Render);
	Initialise();
	glutMainLoop();
}

void DrawTriangleAt( double x, double y )
{
    double size = 0.05;
    double sin30 = 0.5;
    double sin60 = 0.86602540378444;
    
    glColor3f(1.0f, 0.0f, 0.5f);
	glBegin(GL_POLYGON);
    glVertex2f( x, y + size );
    glVertex2f( x - ( size * sin60 ), y - ( size * sin30 ) );
    glVertex2f( x + ( size * sin60 ), y - ( size * sin30 ) );
	glEnd();
}
 
// ---- Render Function ----
void Render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    static double x = -0.5;
    static bool increasing = true;
    if( increasing )
    {
        x += 0.01;
        increasing = ( x < 0.5 );
    }
    else
    {
        x -= 0.01;
        increasing = ( x < -0.5 );
    }
    
    DrawTriangleAt( x, 0.0 );
    DrawTriangleAt( 0.0, -0.7 );

 
	glFlush();
    
    glutPostRedisplay();
}
 
// ---- Initialise Function ----
void Initialise()
{
	glClearColor (0.0, 0.0, 1.0, 0.0); 
}

