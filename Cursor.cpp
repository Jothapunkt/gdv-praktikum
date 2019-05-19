#include "Cursor.h"
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include "Wuerfel.h"



Cursor::Cursor()
{
	posx = 0.0;
	posy = 0.0;
	posz = 0.0;

	step = 0.1;

	col = 0;

	helpLine = false;

	farben.push_back(Farbe(0.2, 0.2, 0.2, 1.)); //Asphaltfarben
	farben.push_back(Farbe(0.75, 0.75, 0.75, 1.)); //Sehr helles grau
	farben.push_back(Farbe(0.4, 0., 0., 1.)); //Dunkelrot
	farben.push_back(Farbe(0., 0., 0.6, 0.7)); //Wasser
	farben.push_back(Farbe(1., 1., 1., 0.5)); //Eis
}


Cursor::~Cursor()
{
}

void Cursor::draw(int tick) {
	glTranslatef(posx, posy, posz);
	Farbe c = farben.at(col);
	glColor4f(c.r, c.g, c.b, c.a * 0.7);
	Wuerfel(step);

	if (helpLine) {
		glColor3f(0.0, 1.0, 0.0); //Y-Achse
		glBegin(GL_LINES);

		glVertex3f(0., -4.0f, 0.);
		glVertex3f(0., 4.0f, 0.);

		glEnd();
		glFlush();
	}
}

void Cursor::nextCol() {
	col = (col + 1) % farben.size();
}
