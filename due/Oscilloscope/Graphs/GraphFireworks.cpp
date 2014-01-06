// 
// 
// 
#include "Arduino.h"
#include "GraphFireworks.h"
#include "OsciCanvasInt.h"

void GraphFireworks::init()
{
	CanvasInt.init(0,0);
}

void GraphFireworks::draw()
{
	float a = 0.1;
	
	float x = random(512);
	float y = 0;
	int x1 = 100 + random(311);
	int y1 = 300 + random(111);

	int tmax = sqrt(2 * y1 / a);

	float vy = a * tmax;
	float vx = (x1 - x) / tmax;

	for (int t = 0; t < tmax; t++)
	{
		x = x + vx;
		y = y + vy;
		vy -= a;
		CanvasInt.point(x, y);
		delay(20);
	}

	float particleSpeed[10][2];
	float particleCoord[10][2];
	
	float particleSpeedMax = sqrt(300.0 / a) * a;

	for (int i = 0; i < 10; i++)
	{
		particleCoord[i][0] = x;
		particleCoord[i][1] = y;

		float w = (i * 4.0 + 1.0 + random(100) / 50.0 ) * PI / 20.0;
		float pSpeed = particleSpeedMax * (15 + random(6)) / 20;

		particleSpeed[i][0] = pSpeed * sin(w);
		particleSpeed[i][1] = pSpeed * cos(w);
	}

	for (int t = 0; t < 30; t++)
	{
		for (int i = 0; i < 10; i++)
		{
			CanvasInt.point(particleCoord[i][0], particleCoord[i][1]);
			
			particleCoord[i][0] += particleSpeed[i][0];
			particleCoord[i][1] += particleSpeed[i][1];

			// graviatation
			particleSpeed[i][1] -= a;

			// air 
			particleSpeed[i][0] = particleSpeed[i][0] * 0.97;
			particleSpeed[i][1] = particleSpeed[i][1] * 0.97;

			delay(4);
		}
	}
}

