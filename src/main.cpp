#include "mbed.h"

#define ID_base 0x100

#define CONFIGURATION_CMD_ID (ID_base + 0x01)
#define DEPLACEMENT_CMD_ID (ID_base + 0x02)
#define ALIMENTATION_CMD_ID (ID_base + 0x03)
#define POSITIONFDC1_CMD_ID (ID_base + 0x04)
#define FDC1_CMD_ID (ID_base + 0x05)

// pin definitions
int stepper(int swpulse, int m0, int m1, int m2, int dir, int dur);
void clockwise(void);
void counterclockwise(void);
void configureMode(uint8_t mode);
void moveMotor(uint16_t nombrePas, uint8_t vitesse, uint8_t direction);
void controlerAlimentation(uint8_t etat);
void position_FDC1(int FDC1);
void MoveMotorByFDC1(int FDC1);
DigitalOut STBY(D7);
DigitalOut STEP(D6);
DigitalOut DIr(D3);
DigitalOut EN(A2);
DigitalOut M0(D5);
DigitalOut M1(D9);
DigitalOut M2(D8);
CAN can(PA_11, PA_12, 1000000);

int main()
{
    STBY = 1;
    EN = 1;
    M0 = 0;
    M1 = 0;
    M2 = 0;
    ThisThread::sleep_for(1s);
    /*while (1)
    {
        printf("clockwise\n");
        clockwise();
        ThisThread::sleep_for(1s);
        printf("counterclockwise\n");
        counterclockwise();
        ThisThread::sleep_for(1s);
    }*/

    while (1)
    {
        CANMessage msg;
        if (can.read(msg))
        {
            printf("Message received: %d : %d\n", msg.id, msg.data[0]);

            switch (msg.id) // check ID message
            {
            case CONFIGURATION_CMD_ID: // congifuration mode
                configureMode(msg.data[0]);
                break;
            case DEPLACEMENT_CMD_ID: // deplacement
                moveMotor((msg.data[0] << 8) | msg.data[1], msg.data[2], msg.data[3]);
                break;
            case ALIMENTATION_CMD_ID: // alimentation
                controlerAlimentation(msg.data[0]);
                break;
            case POSITIONFDC1_CMD_ID: // position FDC1
                position_FDC1(msg.data[0]);
                break;
            case FDC1_CMD_ID: // le moteur tourne ou non en fonction de la position du FDC1
                MoveMotorByFDC1(msg.data[0]); 
                break;
            }
        }
        /*msg.id = 200;
        msg.len = 0;
        msg.format = CANStandard;
        msg.type = CANData;
        can.write(msg);
        ThisThread::sleep_for(1s);*/
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

void configureMode(uint8_t mode)
{
    switch (mode)
    {
    case 0: // full step
        M0 = 0;
        M1 = 0;
        M2 = 0;
        break;
    case 1: // half step
        M0 = 1;
        M1 = 0;
        M2 = 0;
        break;
    case 2: // eighth step
        M0 = 0;
        M1 = 1;
        M2 = 0;
        break;
    case 3: // sixteenth step
        M0 = 1;
        M1 = 1;
        M2 = 0;
        break;
    case 4: // eighth step
        M0 = 0;
        M1 = 0;
        M2 = 1;
        break;
    case 5: // quarter step
        M0 = 1;
        M1 = 0;
        M2 = 1;
        break;
    case 6: // half step
        M0 = 0;
        M1 = 1;
        M2 = 1;
        break;
    case 7: // full step
        M0 = 1;
        M1 = 1;
        M2 = 1;
        break;
    }
    can.write(CANMessage(CONFIGURATION_CMD_ID, "0xFF", 1)); // configure mode
    printf("mode %d\n", mode);
}

void moveMotor(uint16_t nombrePas, uint8_t vitesse, uint8_t direction)
{
    stepper(nombrePas, 0, 0, 0, direction, vitesse);
    can.write(CANMessage(DEPLACEMENT_CMD_ID, "0x1F", 1)); // consideration of the action
    can.write(CANMessage(DEPLACEMENT_CMD_ID, "0x2F", 1)); // action taken
}

void controlerAlimentation(uint8_t etat)
{
    if (etat == 0)
    {
        STBY = 0;
    }
    else
    {
        STBY = 1;
    }
    can.write(CANMessage(ALIMENTATION_CMD_ID, "0x00", 1)); // action taken
}

void position_FDC1(int FDC1)
{
    CANMessage msg;
    if(FDC1 == 1)
    {
        can.write(CANMessage(POSITIONFDC1_CMD_ID, "0x00", 1)); // FDC1 activé
        printf("FDC1 activé\n");
    }

    if(FDC1 == 0)
    {
        can.write(CANMessage(POSITIONFDC1_CMD_ID, "0xFF", 1)); // FDC1 non activé
        printf("FDC1 non activé\n");
    }
    MoveMotorByFDC1(FDC1);
}

void MoveMotorByFDC1(int FDC1)
{
    if(FDC1 == 1)
    {
        moveMotor(0,0,0);
        can.write(CANMessage(FDC1_CMD_ID, "0x00", 1)); // le moteur ne tourne plus
    }
    else
    {
        moveMotor(1000,0,1);
        can.write(CANMessage(FDC1_CMD_ID, "0x00", 1)); // le moteur tourne
    }
}