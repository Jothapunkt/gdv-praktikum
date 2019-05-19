// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include "Wuerfel.h"
#include "Hochhaus.h"
#include "fhaus.h"
#include "Cursor.h"
#include <vector>
#include "Wolke.h"
#include "Cube.h"

float yRotation = 0.0; //Rotation der gesamten Szene
float xRotation = 0.0;
float zRotation = 0.0;

int tick = 0;

bool showAxis = false;

float fRotation = 315.0; //Rotation des Schaukastens
float propellerRotation = 315.0;
int fps = 50; //Bildrate
int stage = 0; //Kante des Rechteckpfads, die gerade abgeflogen wird, 0-3
float progress = 0.0; //Fortschritt in der aktuellen Stage
std::vector<Wolke> wolken = {};
std::vector<Hochhaus> hochhaeuser = {};
std::vector<FHaus> fhaeuser = {};
std::vector<Cube> cubes = {};

Cursor cursor = Cursor();

void Init()	
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgeführt werden müssen
	
   // Licht
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	
	GLfloat spot_direction[] = { -1.0, -4.6, -0.5 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,
		spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0);

	GLfloat light_specular[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	GLfloat light_strength[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_strength); // Ambient Licht Nr. 0 rechts oben

	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glEnable(GL_COLOR_MATERIAL);

	// Normalen fuer korrekte Beleuchtungs-Berechnung normalisieren
	glEnable(GL_NORMALIZE);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	//Wolken erstellen
	wolken.push_back(Wolke(-0.5, 0., 0.5, 1.3, 0.3, 1.8));
	wolken.push_back(Wolke(-0.9, 0., 0.2, 0.6, 0.4, 0.8));
	wolken.push_back(Wolke(1.4, 0.2, -0.6, 1.7, 0.4, 1.0));

	wolken.push_back(Wolke(1.2, 0., 0.8, 1.8, 0.3, 1.3));
	wolken.push_back(Wolke(0.6, 0., -0.7, 1.0, 0.4, 1.0));
	wolken.push_back(Wolke(0.3, 0.2, -0.1, 0.6, 0.4, 1.2));

	//Farben erstellen
	Farbe colCrimson = Farbe(0.4, 0., 0., 1.);
	Farbe colGray = Farbe(0.4, 0.4, 0.4, 1.);
	Farbe colGlass = Farbe(.9, .9, .9, 1.);
	Farbe colBeige = Farbe(.5, .45, 0.3, 1.);

	//FHäuser erstellen
	fhaeuser.push_back(FHaus(1.2,0.,1.2, 3, 6, 3, colGray, colGlass, .5)); //Graues Hochhaus

	fhaeuser.push_back(FHaus(0., 0., -1.6, 5, 2, 2, colBeige, colGlass, .5));
	fhaeuser.push_back(FHaus(0., 0., -1., 5, 2, 2, colBeige, colGlass, .5));
	fhaeuser.push_back(FHaus(.5, 0., -1.6, 3, 4, 8, colBeige, colGlass, .5));
}

void RenderScene() //Zeichenfunktion
{
   // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
   glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.4, 0.6, 1.0, 1.0);
   gluLookAt(3., 3., 3., 0., 0., 0., 0., 1., 0.);

   glRotatef(xRotation, 1., 0., 0.);
   glRotatef(yRotation, 0., 1., 0.);
   glRotatef(zRotation, 0., 0., 1.);

   glPushMatrix(); //Frische Matrix

   /************************
   Koordinatenachsen
   *************************/
   if (showAxis) {
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
   }

   /***************
   Cursor
   ****************/

   glPopMatrix();
   glPushMatrix();

   cursor.draw(tick);

   /***************
   Grundfläche
   ****************/

   glPopMatrix();
   glPushMatrix();

   glColor4f(0.2f, 0.4f, 0.2f, 1.0f); //Grasgrün
   glScalef(1., 0.05, 1.);
   glTranslatef(0., -2.0, 0.);
   Wuerfel(4.);

   glPopMatrix();
   glPushMatrix();

   glColor4f(0.2f, 0., 0., 1.0f); //Erdfarben
   glScalef(1., 0.2, 1.);
   glTranslatef(0., -3.0, 0.);
   Wuerfel(4.);


   /************************
   Wolken
   *************************/

   glPopMatrix();
   glPushMatrix();

   glColor4f(1.0f, 1.0f, 1.0f, 0.3f); //Durchscheinend Weiß
   glTranslatef(0.0, 1.5, 0.0);

   for (int i = 0; i < wolken.size(); i++) {
	   glPushMatrix();
	   wolken.at(i).draw();
	   glPopMatrix();
   }

   /******************
   Cubes
   ******************/

   glPopMatrix();
   glPushMatrix();

   for (int i = 0; i < cubes.size(); i++) {
	   glPushMatrix();
	   cubes.at(i).draw();
	   glPopMatrix();
   }

   /******************
   Hochhäuser
   ******************/

   glPopMatrix();
   glPushMatrix();

   glColor4f(0.35f, 0.35f, 0.35f, 1.0f); //Grau

   for (int i = 0; i < hochhaeuser.size(); i++) {
	   glPushMatrix();
	   hochhaeuser.at(i).draw();
	   glPopMatrix();
   }

   /*****************
   FHäuser
   *****************/
   
   glPopMatrix();
   glPushMatrix();

   glColor4f(0.35f, 0.35f, 0.35f, 1.0f); //Grau

   for (int i = 0; i < fhaeuser.size(); i++) {
	   glPushMatrix();
	   fhaeuser.at(i).draw();
	   glPopMatrix();
   }

   /************************
   Flugzeug für Rechteckflug
   *************************/

    glPopMatrix();
	glPushMatrix();

	glColor4f(0.0f, 0.3f, 0.0f, 1.0f);	//Rot

	glTranslatef(0.0f, 1.0f, 0.0f); //Verschiebe Flugzeug nach oben
	
	if (stage == 0) { glTranslatef(-2.0 + progress, 0.0, -2.0);}
	if (stage == 1) { glTranslatef(2.0, 0.0, -2.0 + progress); }
	if (stage == 2) { glTranslatef(2.0 - progress, 0.0, 2.0); }
	if (stage == 3) { glTranslatef(-2.0, 0.0, 2.0 - progress); }
	
	glRotatef(-90.0 * stage, 0.0, 1.0, 0.0);

	glPushMatrix();

	//Rumpf
	glScalef(0.5, 0.2, 0.4);
	Wuerfel(0.4);

	glPopMatrix();
	glPushMatrix();

	//Hauptflügel
	glScalef(0.4, 0.05, 2.);
	Wuerfel(0.4);

	glPopMatrix();
	glPushMatrix();

	//Heck
	glTranslatef(-0.2, 0.0, 0.0);
	glScalef(0.6, 0.1, 0.2);
	Wuerfel(0.4);

	glPopMatrix();
	glPushMatrix();

	//Heckflügel
	glTranslatef(-0.3, 0.0, 0.0);
	glScalef(0.3, 0.05, 0.7);
	Wuerfel(0.4);

	glPopMatrix();
	glPushMatrix();

	//Heckflosse
	glTranslatef(-0.3, 0.1, 0.0);
	glScalef(0.3, 0.4, 0.05);
	Wuerfel(0.4);

	glPopMatrix();
	glPushMatrix();

	//Halterung für Propeller
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	//Weiß
	glTranslatef(0.1, 0., 0.);
	glScalef(0.2, 0.1, 0.1);
	Wuerfel(0.4);

	glPopMatrix();

	//Propeller
	glRotatef(propellerRotation, 1.0, 0.0, 0.0);
	glTranslatef(0.13, 0., 0.);
	glScalef(0.05, 0.05, 0.5);
	Wuerfel(0.4);

	glPopMatrix();

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
   // x msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
   // inkrementiert und dem Callback wieder uebergeben. 
   
   //Rotation ändern

   fRotation = fRotation - 1.5;
   // Rotationswinkel aendern 
   if
	   (fRotation <= 0.0) {
	   fRotation = fRotation + 360.0;
   }

   tick = value;

   propellerRotation = propellerRotation - 18.5;

   if (propellerRotation <= 0.0) {
	   propellerRotation = propellerRotation + 360.0;
   }

   progress = progress + 0.02;
   if (progress >= 4.0) {
	   progress = 0.0;
	   stage = (stage + 1) % 4;
   }

   // RenderScene aufrufen
   glutPostRedisplay();
   // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
   int wait_msec = 1000/fps;
   glutTimerFunc(wait_msec, Animate, ++value);
}

bool ef(float a, float b) {
	return (abs(a - b) < 0.0001);
}

void deleteAtCursor() {
	std::vector<Cube> newCubes = {};

	for (int i = 0; i < cubes.size(); i++) {
		if (!ef(cubes.at(i).x,cursor.posx) || !ef(cubes.at(i).y, cursor.posy) || !ef(cubes.at(i).z,cursor.posz)) {
			newCubes.push_back(cubes.at(i));
		}
	}

	cubes = newCubes;
}

void makeCube() {
	deleteAtCursor();
	cubes.push_back(Cube(cursor.posx, cursor.posy, cursor.posz, cursor.farben.at(cursor.col), cursor.step));
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	GLfloat xMousePos = float(x);
	GLfloat yMousePos = float(y);
	std::cout << "key = " << key << "  " << xMousePos << ", " << yMousePos << std::endl;


	//Kamerarotation
	if (key == 'w') { xRotation += 6.5; }
	if (key == 's') { xRotation -= 6.5; }
	if (key == 'd') { yRotation += 6.5;	}
	if (key == 'a') { yRotation -= 6.5; }

	while (xRotation > 360.0) { xRotation -= 360.0;  }
	while (yRotation > 360.0) { yRotation -= 360.0; }

	//Koordinatenachsen umschalten
	if (key == 'o') { showAxis = !showAxis; }

	//Hilfslinie zum Cursor finden umschalten
	if (key == 'c') { cursor.helpLine = !cursor.helpLine; }

	//Cubes erstellen/löschen
	
	if (key == (char)8) { deleteAtCursor(); }
	if (key == (char)13) { makeCube(); }

	//Cursor bewegen
	if (key == ' ') { cursor.posy += cursor.step; }

	// RenderScene aufrufen.
	glutPostRedisplay();
}

void SpecialFunc(int key, int x, int y)
// Funktions- und Pfeil-Tasten abfragen
{
	GLfloat xMousePos = float(x);
	GLfloat yMousePos = float(y);

	//Cursor bewegen
	if (key == GLUT_KEY_RIGHT) { cursor.posx += cursor.step; }
	if (key == GLUT_KEY_LEFT) { cursor.posx -= cursor.step; }
	if (key == GLUT_KEY_UP) { cursor.posz -= cursor.step; }
	if (key == GLUT_KEY_DOWN) { cursor.posz += cursor.step; }
	if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R) { cursor.posy -= cursor.step; }

	if (key == GLUT_KEY_CTRL_L || key == GLUT_KEY_CTRL_R) { cursor.nextCol(); }

	// RenderScene aufrufen.
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize( 600, 600 );         // Fenster-Konfiguration
   glutCreateWindow( "Marouane Kherrabi; Jakob Höfner" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene );         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   glutKeyboardFunc(KeyboardFunc);
   glutSpecialFunc(SpecialFunc);
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
