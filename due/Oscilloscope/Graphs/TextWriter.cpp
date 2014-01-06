// 
// 
// 

#include "TextWriter.h"

void TextWriter::A(int x0, int y0)
{
	unsigned int a[][4] = {{0,0, 0,2}, {0,2, 1,4}, {1,4, 2,2}, {2,2, 2,0}, {0,2, 2,2}};

	drawLetter(x0, y0, a, sizeof(a)/sizeof(a[0]));
}

void TextWriter::E(int x0, int y0)
{
	unsigned int e[][4] = {{2,4, 0,4}, {0,2, 2,2}, {2,0, 0,0}, {0,0, 0,4}};

	drawLetter(x0, y0, e, sizeof(e)/sizeof(e[0]));
}

void TextWriter::G(int x0, int y0)
{
	unsigned int g[][4] = {{2,3, 1,4}, {1,4, 0,2}, {0,2, 1,0}, {1,0, 2,1}, {2,1, 1,1}};

	drawLetter(x0, y0, g, sizeof(g)/sizeof(g[0]));

}
	 
void TextWriter::H(int x0, int y0)
{
	unsigned int h[][4] = {{0,0, 0,4}, {2,4, 2,0}, {2,2, 0,2}};

	drawLetter(x0, y0, h, sizeof(h)/sizeof(h[0]));
}

void TextWriter::J(int x0, int y0)
{
	unsigned int j[][4] = {{0,0, 2,0}, {2,0, 2,4}};

	drawLetter(x0, y0, j, sizeof(j)/sizeof(j[0]));
}
void TextWriter::N(int x0, int y0)
{
	unsigned int n[][4] = {{0,0, 0,4}, {0,4, 2,0}, {2,0, 2,4}};

	drawLetter(x0, y0, n, sizeof(n)/sizeof(n[0]));
}

void TextWriter::R(int x0, int y0)
{
	unsigned int r[][4] = {{0,0, 0,4}, {0,4, 2,3}, {2,3, 0,2}, {0,2, 2,0}};

	drawLetter(x0, y0, r, sizeof(r)/sizeof(r[0]));
}

void TextWriter::S(int x0, int y0)
{
	unsigned int s[][4] = {{2,4, 0,4}, {0,4, 0,2}, {0,2, 2,2}, {2,2, 2,0}, {2,0, 0,0}};

	drawLetter(x0, y0, s, sizeof(s)/sizeof(s[0]));
}

void TextWriter::T(int x0, int y0)
{
	unsigned int t[][4] = {{0,4, 2,4}, {1,4, 1,0}};

	drawLetter(x0, y0, t, sizeof(t)/sizeof(t[0]));
}

void TextWriter::U(int x0, int y0)
{
	unsigned int u[][4] = {{0,4, 0,0}, {0,0, 2,0}, {2,0, 2,4}};

	drawLetter(x0, y0, u, sizeof(u)/sizeof(u[0]));
}

void TextWriter::drawLetter(int x0, int y0, unsigned int coordinates[][4], int lineCount)
{
	for (int i = 0; i < lineCount; i++)
	{
		CanvasInt.line(
			(x0 + coordinates[i][0]) << 5,
			(y0 + coordinates[i][1]) << 5,
			(x0 + coordinates[i][2]) << 5,
			(y0 + coordinates[i][3]) << 5);
	}
}





