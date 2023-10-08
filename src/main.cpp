#include "mbed.h"

// pin definitions
int stepper(int swpulse, int m0, int m1, int m2, int dir, int dur);
DigitalOut STBY(D8);
DigitalOut STEP(D7);
DigitalOut DIr(D6);
DigitalOut EN(D12);
DigitalOut M0(D11);
DigitalOut M1(D10);
DigitalOut M2(D9);

int main()
{
    STBY = 0;
    EN = 0;
    M0 = 0;
    M1 = 1;
    M2 = 0;

    ThisThread::sleep_for(1s);
    while (1)
    {
        stepper(1000, 1, 0, 0, 0, 1);
    }
}

//  function stepper for EVALSP820-XS
int stepper(int swpulse, int m0, int m1, int m2, int dir, int dur)
{
    MO=m0;
    M1=m1;
    M2=m2;
    DIr=dir;
    EN = 1;
    // STEP GENERATOR
    for (int i = 0; i < swpulse; i++)
    {
        STEP = 1;
        ThisThread::sleep_for(100ms);
        STEP = 0;
        ThisThread::sleep_for(100ms);
    }
    EN = 0; // output stage off
    return 0;
}