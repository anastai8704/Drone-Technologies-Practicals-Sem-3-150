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

  Receiver_Config_Arm ( Rx_AUX2, 1300, 2100 );
}

enum FlightSequenceState {
  SEQUENCE_ARM,
  SEQUENCE_TAKEOFF,
  SEQUENCE_LAND,
  SEQUENCE_DISARM,
  SEQUENCE_COMPLETE
};

static FlightSequenceState sequenceState;
static uint32_t sequenceStartTime;

// The setup function is called once at Pluto's hardware startup
void plutoInit ( void ) {
  sequenceState     = SEQUENCE_ARM;
  sequenceStartTime = millis ( );
}

// The function is called once before plutoLoop when you activate Developer Mode
void onLoopStart ( void ) {
  // do your one time stuffs here
}

// The loop function is called in an endless loop
void plutoLoop ( void ) {
  switch ( sequenceState ) {
    case SEQUENCE_ARM:
      if ( Command_Arm ( ) ) {
        sequenceState     = SEQUENCE_TAKEOFF;
        sequenceStartTime = millis ( );
      }
      break;

    case SEQUENCE_TAKEOFF:
      Command_TakeOff ( 180 );
      if ( ( uint32_t ) ( millis ( ) - sequenceStartTime ) >= 8000 ) {
        sequenceState     = SEQUENCE_LAND;
        sequenceStartTime = millis ( );
      }
      break;

    case SEQUENCE_LAND:
      Command_Land ( 95 );
      if ( ( uint32_t ) ( millis ( ) - sequenceStartTime ) >= 7000 ) {
        sequenceState     = SEQUENCE_DISARM;
      }
      break;

    case SEQUENCE_DISARM:
      if ( Command_DisArm ( ) ) {
        sequenceState = SEQUENCE_COMPLETE;
      }
      break;

    case SEQUENCE_COMPLETE:
      break;
  }
}

// The function is called once after plutoLoop when you deactivate Developer Mode
void onLoopFinish ( void ) {
  // do your cleanup stuffs here
}
