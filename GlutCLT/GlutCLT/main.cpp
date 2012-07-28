#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <math.h>

#include "mungo.h"
 
// ---- Prototypes ----
void Render(void);
void Initialise();

MungoManager s_MungoManager;
double      s_Time = 0.0;

void CreateMungos()
{
    Coords c1( -1.0, 0.0 );
    Coords c2( 1.0, 0.5 );
    Coords d1 = ( c1 * -1 );
    Coords d2 = ( c2 * -1 );
    Coords e1( 0.75, -0.5 );
    Coords e2( 0.55, 0.65 );
    
    s_MungoManager.AddMungo( MungoFactory::CreateStaticMungo( c1 ) );
    s_MungoManager.AddMungo( MungoFactory::CreateStaticMungo( c2 ) );
    MungoCPtr firstMover = MungoFactory::CreateLinearMungo( c1, c2, 1.0, 3.0 );
    MungoCPtr secondMover = MungoFactory::CreateLinearMungo( d1, d2, 1.0, 3.0 );
    MungoCPtr thirdMover = MungoFactory::CreateLinearMungo( e1, e2, 0.0, 5.0 );
    
    thirdMover->AssignColor( MColor( 1.0, 0.4, 0.4 ) );
    
    s_MungoManager.AddMungo( firstMover );
    s_MungoManager.AddMungo( secondMover );
    s_MungoManager.AddMungo( thirdMover );
    
    s_MungoManager.AddMungo( MungoFactory::CreateTemporalOffset( firstMover, 0.4 ) );
    s_MungoManager.AddMungo( MungoFactory::CreateTemporalOffset( firstMover, 0.8 ) );
    
    MungoCPtr firstHalfway = MungoFactory::CreateHalfWayBetween( firstMover, secondMover);
    firstHalfway->AssignColor( MColor( 0.2, 0.4, 1.0 ) );
    
    s_MungoManager.AddMungo( firstHalfway );
    s_MungoManager.AddMungo( MungoFactory::CreateHalfWayBetween( firstMover, thirdMover));

    s_MungoManager.AddMungo( MungoFactory::CreateOrbitAroundMungo(firstMover, 0.5, 7.0));
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
    
	glBegin(GL_POLYGON);
    glVertex2f( x, y + size );
    glVertex2f( x - ( size * sin60 ), y - ( size * sin30 ) );
    glVertex2f( x + ( size * sin60 ), y - ( size * sin30 ) );
	glEnd();
}

void DrawMungo( const Mungo& mungo, double time )
{
    Coords pos = mungo.GetCoordsAtTime( time );
    MColor col = mungo.GetColor();
    glColor3f( col.r, col.g, col.b );
    DrawTriangleAt( pos.x, pos.y );
}
 
// ---- Render Function ----
void Render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    s_Time += 0.001;
    
    const int nMungos = s_MungoManager.nMungos();
    for( int i = 0; i < nMungos; ++i )
    {
        Coords tempCoords;
        const Mungo& mungo = s_MungoManager.GetMungo( i );
        DrawMungo( mungo, s_Time );
    }
 
	glFlush();
    
    glutPostRedisplay();
}
 
// ---- Initialise Function ----
void Initialise()
{
	glClearColor (0.0, 0.0, 1.0, 0.0); 
}

