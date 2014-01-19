// 
// 
// 

#include "GraphHelloHabr.h"
#include "OsciCanvasInt.h"
#include "TextWriter.h"

void GraphHelloHabr::init()
{
	CanvasInt.init(0,0);
}

void GraphHelloHabr::draw()
{
	TextWriter tr;

	int del = 1500;

	for (int i = 0; i < 100; i++)
	{
		CanvasInt.init(1, del);

		tr.H(1,10);
		tr.E(4,10);
		tr.L(7,10);
		tr.L(10,10);
		tr.O(13,10);

		tr.H(3,3);
		tr.A(6,3);
		tr.B(9,3);
		tr.R(12,3);
		
		del = del * 8 / 10;
	}
}


