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
    // Deactivate default flight-status LED behaviour
    FlightMode_Set(THROTTLE_MODE);

    // Initially turn both LEDs OFF
    Set_LED(RED, OFF);
    Set_LED(GREEN, OFF);
}

// Main loop
void plutoLoop(void)
{
    int16_t velocityZ = Estimate_Get(Velocity, Z);

    // Drone moving upward
    if (velocityZ > 0)
    {
        Set_LED(RED, ON);
        Set_LED(GREEN, OFF);
    }
    // Drone moving downward
    else if (velocityZ < 0)
    {
        Set_LED(RED, OFF);
        Set_LED(GREEN, ON);
    }
    // Drone is not moving vertically
    else
    {
        Set_LED(RED, OFF);
        Set_LED(GREEN, OFF);
    }
}

// Called once when Developer Mode is deactivated
void onLoopFinish(void)
{
    Set_LED(RED, OFF);
    Set_LED(GREEN, OFF);
}