#include "mbed.h"
#include "Stepper.h"

Stepper stepper(PA_4,PA_5,PA_6,PA_7); 

int main()
{

  while (1) 
  {
    stepper.Interval(0.1);   
    stepper.Direction(true); 
    stepper.Run();  
    ThisThread::sleep_for(5s);         
    stepper.Direction(false);
    ThisThread::sleep_for(5s);         
    stepper.Stop();
    ThisThread::sleep_for(5s);         
  }
}
