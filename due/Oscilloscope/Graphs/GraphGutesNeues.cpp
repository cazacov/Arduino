// 
// 
// 
#include "GraphGutesNeues.h"
#include "OsciCanvasInt.h"
#include "TextWriter.h"

void GraphGutesNeues::init()
{
	CanvasInt.init(0,0);
}

void GraphGutesNeues::draw()
{
	TextWriter tr;

	int del = 2000;

	for (int i = 0; i < 100; i++)
	{
		CanvasInt.init(1, del);

		tr.G(1,11);
		tr.U(4,11);
		tr.T(7,11);
		tr.E(10,11);
		tr.S(13,11);

		tr.N(1,6);
		tr.E(4,6);
		tr.U(7,6);
		tr.E(10,6);
		tr.S(13,6);

		tr.J(2,1);
		tr.A(5,1);
		tr.H(8,1);
		tr.R(11,1);
		
		del = del * 8 / 10;
	}
}
