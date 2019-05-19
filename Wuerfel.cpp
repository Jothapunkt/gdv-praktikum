/*
    wuerfel.cpp definiert einen Würfel über seine 6 Seiten
    Last Update:  13.10.2011   W.-D. Groch
*/ 
#include <GL/freeglut.h>
#include "Wuerfel.h"


void Wuerfel(GLfloat fSeitenL)
{ 
	glBegin(GL_POLYGON);   //Vorderseite
	glNormal3f(0.,0.,1.);
	glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rechte Seite
	glNormal3f(1., 0., 0.);
	glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rueckseite
	glNormal3f(0., 0., 1.);
	glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Linke Seite
	glNormal3f(1., 0., 0.);
	glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Deckflaeche
	glNormal3f(0., 1., 0.);
	glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Bodenflaeche
	glNormal3f(0., 1., 0.);
	glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	glEnd();

	return;
}