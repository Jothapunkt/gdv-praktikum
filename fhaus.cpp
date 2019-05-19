#include "FHaus.h"
#include <iostream>
#include <GL/freeglut.h>
#include "Wuerfel.h"
#include "Farbe.h"


FHaus::FHaus(float nx, float ny, float nz, int nsegx, int nstock, int nsegz, Farbe nouterCol, Farbe ninnerCol, float nscale)
{
	std::cout << "Neues FHaus bei " << x << "/" << y << "/" << z << std::endl;
	x = nx;
	y = ny;
	z = nz;
	segmentex = 2 * nsegx;
	segmentez = 2 * nsegz;
	stockwerke = 2 * nstock;
	outerCol = nouterCol;
	innerCol = ninnerCol;
	scale = nscale;
}

void FHaus::draw() {
	glTranslatef(x, y, z);
	float cubeSize = 0.1 * scale;
	glColor4f(outerCol.r, outerCol.g, outerCol.b, outerCol.a);

	//Fassade in x-Richtung
	float plusy = 0.0;
	for (int stockwerk = 0; stockwerk < stockwerke + 1; stockwerk++) {
		float plusx = 0.0; //Speichert die Translationen entlang der Segmente

		for (int segment = 0; segment < segmentex + 1; segment++) {
			if (stockwerk % 2 == 0 || segment % 2 == 0) { //Ist dieses Segment Wand?
				Wuerfel(cubeSize);
				glTranslatef(0., 0., cubeSize * segmentez); //An der gegenüberliegenden Seite
				Wuerfel(cubeSize);
				glTranslatef(0., 0., -cubeSize * segmentez);
			}
			glTranslatef(cubeSize, 0., 0.);
			plusx += cubeSize;
		}

		glTranslatef(-plusx, 0., 0.);
		glTranslatef(0., cubeSize, 0.);
		plusy += cubeSize;
	}
	glTranslatef(0.0, -plusy, 0.0);

	//Fassade in z-Richtung
	plusy = 0.0;
	for (int stockwerk = 0; stockwerk < stockwerke + 1; stockwerk++) {
		float plusz = 0.0; //Speichert die Translationen entlang der Segmente

		for (int segment = 0; segment < segmentez; segment++) {
			if (stockwerk % 2 == 0 || segment % 2 == 0) { //Ist dieses Segment Wand?
				Wuerfel(cubeSize);
				glTranslatef(cubeSize * segmentex, 0., 0.); //An der gegenüberliegenden Seite
				Wuerfel(cubeSize);
				glTranslatef(-cubeSize * segmentex, 0., 0.);
			}
			glTranslatef(0., 0., cubeSize);
			plusz += cubeSize;
		}

		glTranslatef(0., 0., -plusz);
		glTranslatef(0., cubeSize, 0.);
		plusy += cubeSize;
	}
	glTranslatef(0.0, -plusy, 0.0);

	//Boden- und Dachfläche, Füllung

	plusy = 0.0;
	for (int stockwerk = 0; stockwerk < stockwerke + 1; stockwerk++) {
		float plusx = cubeSize; //Starte um ein Segment nach innen versetzt, weil die Wand nicht ersetzt werden soll
		float pluszouter = cubeSize;

		glTranslatef(cubeSize, 0., cubeSize);

		for (int segx = 2; segx < segmentex + 1; segx++) {
			
			float plusz = 0.0;
			for (int segz = 2; segz < segmentez + 1; segz++) {
				if (stockwerk == 0 || stockwerk == stockwerke) {
					glColor4f(outerCol.r, outerCol.g, outerCol.b, outerCol.a);
				}
				else {
					glColor4f(innerCol.r, innerCol.g, innerCol.b, innerCol.a);
				}

				Wuerfel(cubeSize);

				glTranslatef(0., 0., cubeSize);
				plusz += cubeSize;
			}

			glTranslatef(cubeSize, 0., -plusz);
			plusx += cubeSize;
		}

		glTranslatef(-plusx, cubeSize, -pluszouter);
		plusy += cubeSize;
	}

}


FHaus::~FHaus()
{
}
