#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "mungo.h"
 
// ---- Prototypes ----
void Render(void);
void Initialise();

MungoManager s_MungoManager;
double      s_Time = 0.0;

void CreateMungos()
{
    Coords c1( 0.25, 0.25 );
    Coords c2( -0.25, -0.25 );
    s_MungoManager.AddMungo( MungoFactory::CreateStaticMungo( c1 ) );
    s_MungoManager.AddMungo( MungoFactory::CreateStaticMungo( c2 ) );
    MungoCPtr firstMover = MungoFactory::CreateLinearMungo( c1, c2, 1.0, 3.0 );
    s_MungoManager.AddMungo( firstMover );
    s_MungoManager.AddMungo( MungoFactory::CreateTemporalOffset( firstMover, 0.4 ) );
    s_MungoManager.AddMungo( MungoFactory::CreateTemporalOffset( firstMover, 0.8 ) );
}
 
// ---- Main Function ----
int main(int argc, char** argv)
{
    CreateMungos();
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
    
    s_Time += 0.005;
    
    const int nMungos = s_MungoManager.nMungos();
    for( int i = 0; i < nMungos; ++i )
    {
        Coords tempCoords;
        s_MungoManager.GetCoords( i, s_Time, &tempCoords );
        DrawTriangleAt( tempCoords.x, tempCoords.y );
    }
 
	glFlush();
    
    glutPostRedisplay();
}
 
// ---- Initialise Function ----
void Initialise()
{
	glClearColor (0.0, 0.0, 1.0, 0.0); 
}

