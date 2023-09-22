/* Stepper  Motor Library v1.0
 * Copyright (c) 2017 Armand Coetzer
 * s213293048@nmmu.ac.za
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
#ifndef Stepper_H
#define Stepper_H
 
#include "mbed.h"
 
/** Class library for a Stepper Motor to be able to Select amount of steps,set the time interval between steps, run stepper motor freely and stop the stepper motor.
 *
 * Example:
 * @code
 * #include "mbed.h"                                           //include the mbed APIs and other libraries
 * #include "Stepper.h"                                        //include the Stepper librariy
 *
 * Stepper stepper (PE_4, PE_5, PE_6, PE_7);                   //Initialize bus pins
 *
 * int main() 
 * {
 *
 *    while(1)                                               //Enter infinite while loop
 *    {
 *       stepper.Interval(0.1);                              //Choosing time interval between steps(control speed)
 *       stepper.Direction(true);                            //Choosing direction. true = Clockwise, false = Anticlockwise
 *       stepper.Run();                                      //Makes the stepper run continuously
 *       wait(5);                                            //mbed's wait function, wait 5 sec.
 *       stepper.Direction(false); 
 *       wait(5);   
 *       stepper.Stop();                                     //To make stepper stop
 *       wait(5);     
 *    }                   
 * }
 * @endcode
 */
 
class Stepper {
  public:
    /** Create a Stepper motor object connected to the specified pins. 
    * @param coil1 MCU Output Pin for coil1.
    * @param coil2 MCU Output Pin for coil2.
    * @param coil3 MCU Output Pin for coil3.
    * @param coil4 MCU Output Pin for coil4.
    */
    Stepper(PinName Coil1, PinName Coil2, PinName Coil3, PinName Coil4);
    
    /** Makes the stepper run continuously.
    * @param 
    *     None
    */
    void Run();
    
    /** To make stepper stop.
    * @param 
    *     None
    */
    void Stop();
    
     /** Setting direction of the stepper motor, Clockwise or Anticlockwise.
    * @param 
    *     boolean slection to select direction. true = Clockwise, false = Anticlockwise
    */
    void Direction(bool dir);
    
     /** Choosing time interval between steps(control speed).
    * @param 
    *     A float value to set the time between steps.
    * @return
    *     None
    */
    void Interval(float sec);
    
    /** Selct amount of steps the stpper motor should turn.
    * @param 
    *     interger value to select the amount of steps.
    * @return
    *     None
    */
    void Step(int steps);

  private:
  
    void stepper_isr();
    
    BusOut _Coils;
    Timer timer;
    Ticker ticker;
    float secinter;
    float lastsecinter;
    uint8_t StepDir;
    uint8_t stepper_steps[4];
    int8_t stepcount;
    uint8_t Prevtime;
    uint8_t run;
    uint8_t stepincr;   
    uint8_t stepping;
    uint8_t Steps;
};
 
#endif
