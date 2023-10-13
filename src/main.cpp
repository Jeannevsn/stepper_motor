#include "mbed.h"

// pin definitions
int stepper(int swpulse, int m0, int m1, int m2, int dir, int dur);
void clockwise(void);
void counterclockwise(void);
DigitalOut STBY(D8);
DigitalOut STEP(D7);
DigitalOut DIr(D6);
DigitalOut EN(D12);
DigitalOut M0(D11);
DigitalOut M1(D10);
DigitalOut M2(D9);

int main()
{
    STBY = 1;
    EN = 1;
    M0 = 0;
    M1 = 0;
    M2 = 0;

    ThisThread::sleep_for(1s);
    while (1)
    {
        printf("clockwise\n");
        clockwise();
        ThisThread::sleep_for(1s);
        printf("counterclockwise\n");
        counterclockwise();
        ThisThread::sleep_for(1s);
    }
    return 0;
}

//  function stepper for EVALSP820-XS
int stepper(int swpulse, int m0, int m1, int m2, int dir, int dur)
{
    M0 = m0;
    M1 = m1;
    M2 = m2;
    DIr = dir;
    EN = 1;
    // STEP GENERATOR
    for (int i = 0; i < swpulse; i++)
    {
        STEP = 1;
        ThisThread::sleep_for(1ms);
        STEP = 0;
        ThisThread::sleep_for(1ms);
    }
    EN = 0;
    return 0;
}

void clockwise(void)
{
    stepper(1000, 0, 0, 0, 1, 1);
}

void counterclockwise(void)
{
    stepper(1000, 0, 0, 0, 0, 1);
}