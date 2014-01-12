// 
// 
// 

#include "MathInt.h"

void TMathInt::init()
{
	for (int i = 0; i <= 1024; i++)
	{
		sinArray[i] = sin(i * PI / (1024.0 * 2)) * 250;
	}
}

int TMathInt::sinInt(long t)
{
	if (t < 0)
	{
		return -sinInt(-t);
	}
	
	t = t & 0x00000FFF; // 2Pi = 4096
	if (t <= 1024)
	{
		return sinArray[t];
	}
	else if (t <= 2048)
	{
		return sinArray[2048 - t];
	}
	else if (t <= 3072)
	{
		return -sinArray[t - 2048];
	}
	else return -sinArray[4096 - t];
}


int TMathInt::cosInt(long t)
{
	if (t < 0)
	{
		return cosInt(-t);
	}
	return sinInt(t + 1024);
}
TMathInt MathInt;

