#include "Piano.h"
#include <Arduino.h>
#include "MotorController.h"

MotorController stepperMotor(11);

Piano* piano;

char* haeschenKlein =
"G12,E12,E11,F12,D12,D11,"		// Häschen klein ging alein
"C12,D12,E12,F12,G12,G12,G11,"	//in die weite Welt hinein
"G12,E12,E11,F12,D12,D11,"		// Stock und Hut steht im gut
"C12,E12,G12,G12,E11,P21,";		// Hans ist wohl-gemut

char* ode =
"A22,A22,B22,C22,C22,B22,A22,G12,F12,F12,G12,A22,A23,G14,G11,"
"A22,A22,B22,C22,C22,B22,A22,G12,F12,F12,G12,A22,G13,F14,F11,"
"G12,A24,B24,A22,F12,G12,A24,B24,A22,F12,G12,A24,B24,A22,G12,F12,G12,C11,"
"A22,A22,B22,C22,C22,B22,A22,G12,F12,F12,G12,A22,G13,F14,F11"
;

char* elka =
"C12,A22,A22,G12,A22,F12,C12,C12,C12,A22,A22,B22,G12,C21,"
"C21,D12,D12,B22,B22,A22,G12,F12,C12,A22,A22,G12,A22,F11,"
;

void setup() {
	Serial.begin(9600);           // set up Serial library at 9600 bps
	Serial.println("Stepper test!");
	stepperMotor.calibrate();
	Serial.println("Calibration done!");
	piano = new Piano(&stepperMotor);
}

void loop() {
	piano->play(ode);
	while (1);
}

