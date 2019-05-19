#include "Farbe.h"



Farbe::Farbe(float nr, float ng, float nb, float na)
{
	r = nr;
	g = ng;
	b = nb;
	a = na;
}

Farbe::Farbe() {
	r = 1.0;
	g = 1.0;
	b = 1.0;
	a = 1.0;
}


Farbe::~Farbe()
{
}
