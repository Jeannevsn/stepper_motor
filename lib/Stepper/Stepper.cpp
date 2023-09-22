#include "Stepper.h"
#include "mbed.h"
  
Stepper::Stepper(PinName Coil1, PinName Coil2, PinName Coil3, PinName Coil4) : _Coils(Coil1, Coil2, Coil3, Coil4)
{
    _Coils = 0;
    stepcount = 0;
    Prevtime = 0;
    secinter = 0.5;
    lastsecinter = 0;
    StepDir = 1;
    stepping = 0;
    stepincr = 0;
    stepper_steps[0] = 0x09;
    stepper_steps[1] = 0x0A;
    stepper_steps[2] = 0x06;
    stepper_steps[3] = 0x05;
    
}
 
void Stepper::Run() 
{   
   
    run = 1; 
    stepping = 0;
    
    if(secinter != lastsecinter) 
    {  
        ticker.attach(callback(this, &Stepper::stepper_isr),secinter);
        lastsecinter = secinter;
    }
}

void Stepper::Stop() 
{
    run = 0;
    stepping = 0;

    
}

void Stepper::Direction(bool dir) 
{   
    if(dir == true)
    {
        StepDir = 1;
    }
    else if(dir == false)
    {
        StepDir = -1;  
    }
}

void Stepper::Interval(float sec) 
{
    secinter = sec;
    if(secinter != lastsecinter) 
    {  
        ticker.attach(callback(this, &Stepper::stepper_isr),secinter);
        lastsecinter = secinter;
    }
}

void Stepper::Step(int steps)
{
    Steps = steps;
    stepincr = 0;
    run = 0;
    stepping = 1;
    
    if(secinter != lastsecinter) 
    {  
        ticker.attach(callback(this, &Stepper::stepper_isr),secinter);
        lastsecinter = secinter;
    }
    
    
}

void Stepper::stepper_isr()
{
    if(run == 1)
    { 
        _Coils = stepper_steps[stepcount];
             
        stepcount = stepcount + StepDir;
        
        if(stepcount > 3)
        {
            stepcount = 0;    
        }
        if(stepcount < 0)
        {
            stepcount = 3;    
        }
         
    }
    
    if(stepping == 1 && stepincr < Steps)
    { 
        _Coils = stepper_steps[stepcount];
             
        stepcount = stepcount + StepDir;
        stepincr++;
        
        if(stepcount > 3)
        {
            stepcount = 0;    
        }
        if(stepcount < 0)
        {
            stepcount = 3;    
        }
         
    }

    
    
}

       