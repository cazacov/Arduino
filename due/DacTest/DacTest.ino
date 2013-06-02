void setup() 
{
  analogWriteResolution(12);
}

double zeit = 0;
double inc = 3.1415926 / 100.0;


void loop() 
{
  double x = sin(zeit*3)*2000; 
  double y = cos(zeit*4.003)*2000;
  analogWrite(DAC0, x + 2000);
  analogWrite(DAC1, y + 2000);  
  zeit = zeit + inc;
  //delayMicroseconds(1000);
}


/*
void loop() 
{
  double r = cos(3.00*zeit)*sin(4*zeit);
  
  double x = cos(zeit) * r *2000; 
  double y = sin(zeit)* r *2000;
  analogWrite(DAC0, x + 2000);
  analogWrite(DAC1, y + 2000);  
  zeit = zeit + inc;
  //delayMicroseconds(1000);
}
*/
