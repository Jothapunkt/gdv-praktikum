// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include "Wuerfel.h"

float fRotation = 315.0;
int fps = 50;

void Init()	
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgeführt werden müssen

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

void RenderScene() //Zeichenfunktion
{
   // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
   glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.9, 0.5, 0.0, 1.0);
   gluLookAt(0., 0., 3., 0., 0., 0., 0., 1., 0.);

   glColor3f(1.0, 0.0, 0.0); //X-Achse
   glBegin(GL_LINES);

   glVertex3f(-4.0, 0.0f, 0.0f);
   glVertex3f(4.0, 0.0f, 0.0f);

   glEnd();
   glFlush();

   glColor3f(0.0, 1.0, 0.0); //Y-Achse
   glBegin(GL_LINES);

   glVertex3f(0.0, -4.0f, 0.0f);
   glVertex3f(0.0, 4.0f, 0.0f);

   glEnd();
   glFlush();

   glColor3f(0.0, 0.0, 1.0); //Z-Achse
   glBegin(GL_LINES);

   glVertex3f(0.0, 0.0f, -4.0f);
   glVertex3f(0.0, 0.0f, 4.0f);

   glEnd();
   glFlush();
   
   glutWireCube(0.2);

   //Roboterarm
   glTranslatef(0.1, 0.1, 0.);
   glRotatef(fRotation, 0.0, 0.0, 1.0);

   glPushMatrix();

   glScalef(1., 0.5, 0.5);
   glTranslatef(0.2, 0.0, 0.0);

   Wuerfel(0.4);
   
   glPopMatrix();

   glScalef(1., 0.2, 0.2);
   glTranslatef(0.6, 0., 0.);

   Wuerfel(0.4);

   glutSwapBuffers();
}

void Reshape(int width,int height)
{
   // Hier finden die Reaktionen auf eine Veränderung der Größe des 
   // Graphikfensters statt

	// Matrix für Transformation: Frustum->viewport 
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen 
	glLoadIdentity();
	// Viewport definieren  
	glViewport(0, 0, width, height);
	// Frustum definieren (siehe unten) 
	gluPerspective(45., 1., 0.1, 8.0);
	// Matrix für Modellierung/Viewing 
	glMatrixMode(GL_MODELVIEW);
}

void Animate (int value)    
{
   // Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
   // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
   // inkrementiert und dem Callback wieder uebergeben. 
   std::cout << "value=" << value << std::endl;
   //Rotation ändern

   fRotation = fRotation - 1.0;
   // Rotationswinkel aendern 
   if
	   (fRotation <= 0.0) {
	   fRotation = fRotation + 360.0;
   }

   // RenderScene aufrufen
   glutPostRedisplay();
   // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
   int wait_msec = 1000/fps;
   glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char **argv)
{
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize( 600, 600 );         // Fenster-Konfiguration
   glutCreateWindow( "Marouane Kherrabi; Jakob Höfner" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene );         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
