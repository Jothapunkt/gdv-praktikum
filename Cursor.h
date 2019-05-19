#include "Farbe.h"
#include <vector>
#pragma once
class Cursor
{
public:
	Cursor();
	~Cursor();

	void nextCol();
	void draw(int tick);

	float posx;
	float posy;
	float posz;
	float step;
	int col;
	bool helpLine;
	std::vector<Farbe> farben;
};

