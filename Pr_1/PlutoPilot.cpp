// Do not remove the include below
#include "PlutoPilot.h"

// Receiver configuration
void plutoRxConfig(void)
{
    Receiver_Mode(Rx_ESP);
}

// Called once when Pluto starts
void plutoInit(void)
{
    // No initialization required
}

// Called once when Developer Mode is activated
void onLoopStart(void)
{
    FlightMode_Set(THROTTLE_MODE);

    // Print initial status
    Monitor_Println("Flight-status LED: Deactivated");
}

// Main loop
void plutoLoop(void)
{
    int16_t velocityZ = Estimate_Get(Velocity, Z);

    if (velocityZ > 0)
    {
        Set_LED(RED, ON);
        Monitor_Println("When the drone moves upward: Red LED: ON");
    }
    else
    {
        Set_LED(RED, OFF);
        Monitor_Println("When the drone is not moving upward: Red LED: OFF");
    }
}

// Called once when Developer Mode is deactivated
void onLoopFinish(void)
{
    Set_LED(RED, OFF);
    Monitor_Println("Flight-status LED: Deactivated");
}