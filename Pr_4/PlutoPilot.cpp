// Do not remove the include below
#include "PlutoPilot.h"

/**
 * Configures Pluto's receiver to use PPM or default ESP mode; activate the line matching your setup.
 * AUX channel configurations is only for PPM recievers if no custom configureMode function is called this are the default setup
 * ARM mode : Rx_AUX2, range 1300 to 2100
 * ANGLE mode : Rx_AUX2, range 900 to 2100
 * BARO mode : Rx_AUX3, range 1300 to 2100
 * MAG mode : Rx_AUX1, range 900 to 1300
 * HEADFREE mode : Rx_AUX1, range 1300 to 1700
 * DEV mode : Rx_AUX4, range 1500 to 2100
 */
void plutoRxConfig ( void ) {
  // Receiver mode: Uncomment one line for ESP or CAM or PPM setup.
  Receiver_Mode ( Rx_ESP );    // Onboard ESP
  // Receiver_Mode ( Rx_CAM );    // WiFi CAMERA
  // Receiver_Mode ( Rx_PPM );    // PPM based
}

// The setup function is called once at Pluto's hardware startup
void plutoInit ( void ) {
  // Add your hardware initialization code here
}

// The function is called once before plutoLoop when you activate Developer Mode
void onLoopStart ( void ) {
  // do your one time stuffs here
}

Interval sensorPrintInterval;

// The loop function is called in an endless loop
void plutoLoop ( void ) {
  if ( sensorPrintInterval.set ( 1000, true ) ) {
    const double pressure = Sensor_Get ( Barometer, Pressure ) / 100.0;
    const double temperature = Sensor_Get ( Barometer, Temperature ) / 100.0;

    Monitor_Println ( "Pressure: ", pressure, 2 );
    Monitor_Println ( "Temperature: ", temperature, 2 );
  }
}

// The function is called once after plutoLoop when you deactivate Developer Mode
void onLoopFinish ( void ) {
  // do your cleanup stuffs here
}
