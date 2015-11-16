#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/adc.h>
// Blink the LED to show we're on
static tBoolean blink_on = true;
static tMotor *motor[2];
static tADC *isensor[2];
static tBoolean read = false;
float k_p=10.0;
// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    float value=0.0f;
    float wallDistance=0.0f;
    SetPin(PIN_F3, blink_on);
    motor[0] = InitializeServoMotor(motor[0],false);
    motor[1] = InitializeServoMotor(motor[0],true);
    isensor[0] = InitializeADC(PIN_D0);
    while (1) {
        // Runtime code can go here
        value = ADCRead(isensor[0]);
        read = value>0.25f;
        if(read)
        {
            SetPin(PIN_F2, false);
            wallDistance=k_p*(0.25f-value);
            Set Motor(motor[0],1.0-wallDistance);
            Set Motor(motor[1],1.0+wallDistance);
        }
        else
        {
            SetPin(PIN_F2, true);
            Set Motor(motor[0],1.0);
            Set Motor(motor[1],1.0);
        }
    }
}
