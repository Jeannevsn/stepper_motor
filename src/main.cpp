#include "mbed.h"
#include "Stepper.h"

    /*// Définir les broches de sortie pour le moteur pas à pas
    DigitalOut coil_A_1(D9);
    DigitalOut coil_A_2(D10);
    DigitalOut coil_B_1(D11);
    DigitalOut coil_B_2(D12);

    // Fonction pour avancer le moteur d'une étape dans le sens horaire
    void stepClockwise() {
        coil_A_1 = 1;
        coil_A_2 = 0;
        coil_B_1 = 0;
        coil_B_2 = 1;
        ThisThread::sleep_for(100ms); // Délai pour contrôler la vitesse
        coil_A_1 = 0;
        coil_A_2 = 0;
        coil_B_1 = 0;
        coil_B_2 = 0;
        ThisThread::sleep_for(100ms); // Délai pour contrôler la vitesse
    }

    // Fonction pour avancer le moteur d'une étape dans le sens antihoraire
    void stepCounterClockwise() {
        coil_A_1 = 0;
        coil_A_2 = 1;
        coil_B_1 = 1;
        coil_B_2 = 0;
        ThisThread::sleep_for(1s); // Délai pour contrôler la vitesse
    }

    int main() {

        while (1) {
            // Faites tourner le moteur dans le sens horaire
            for (int i = 0; i < 10; i++) { // Vous pouvez ajuster le nombre d'étapes
                stepClockwise();
                printf("i = %d\n", i);
            }

            // Faites une pause
           ThisThread::sleep_for(2s);

            // Faites tourner le moteur dans le sens antihoraire
            for (int i = 0; i < 10; i++) {
                stepCounterClockwise();
                printf("i = %d\n", i);
            }

            // Faites une pause
            ThisThread::sleep_for(2s);
        }
    }*/

    // variables will  change:

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
    /*int number = 0;
    int freq = 10;
    int swpulse = 0;
    int lettura = 0;
    int dur = 0.1;
    int mode = 0;
    int m0 = 0;
    int m1 = 0;
    int m2 = 0;
    int dir = 0;
    unsigned long tempMillis;*/
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
    if (m0 == 0)
    {
        M0 = 0;
    }
    else
    {
        M0 = 1;
    }
    if (m1 == 0)
    {
        M1 = 0;
    }
    else
    {
        M1 = 1;
    }
    if (m2 == 0)
    {
        M2 = 0;
    }
    else
    {
        M2 = 1;
    }
    if (dir == 0)
    {
        DIr = 0;
    }
    else
    {
        DIr = 1;
    }
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