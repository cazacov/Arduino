// 
// 
// 

#include "Piano.h"



int Piano::noteCoordinate(char * note)
{
	if (strlen(note) != 2)
	{
		Serial.println("Falsche note");
	}
	int pos = motorController->posMm();

	if (note[0] != 'P') // not a pause
	{
		pos = ((note[0] - 'A') * -22.79) + 144;
	}
	if (note[1] == '1')
	{
		pos += 159;
	}
	else if (note[1] == '0')
	{
		pos += 319;
	}
	return pos;
}

Piano::Piano(MotorController* mc)
{
	motorController = mc;
}

void Piano::play(char * melody)
{
	motorController->start();
	int pos = noteCoordinate(melody); // first note
	Serial.println(pos);
	motorController->gotoMm(pos);
	while (*melody) {
		long now = millis();

		if (melody[0] != 'P') // not a pause
		{
			motorController->dong();
		}
		if (strlen(melody) < 5)
		{
			break;
		}
		int noteLength = 1000;
		switch (melody[2])
		{
			case '1':
				noteLength = 1000;
				break;
			case '2':
				noteLength = 500;
				break;
			case '3':
				noteLength = 750;
				break;
			case '4':
				noteLength = 250;
				break;
		}



		int noteTime = noteLength - 15;
		long nextNote = now + noteTime;
		int nextPos = noteCoordinate(melody + 4);
		int travelTime = abs(motorController->posMm() - nextPos) * 7;

		if (noteTime > travelTime)
		{
			delay(noteTime - travelTime);
		}
		motorController->gotoMm(nextPos);
		Serial.println(pos);
		while (millis() < nextNote)
		{
			;
		}
		melody += 4;
	}
	delay(500);
	motorController->stop();
}
