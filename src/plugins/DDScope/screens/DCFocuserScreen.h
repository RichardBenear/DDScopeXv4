// =====================================================
// DCFocuserScreen.h

#ifndef DCFOCUSER_S_H
#define DCFOCUSER_S_H

#include <Arduino.h>
class Display;

class DCFocuserScreen : public Display {
  public:
    void draw();
    bool touchPoll(uint16_t px, uint16_t py);
    void updateFocuserButtons();
    void updateFocuserStatus();
    bool focuserButStateChange();
    
  private:
    void focInit();
    void focChangeDirection();
    void focMove(int numPulses, int pulseWidth);
    void updateFocPosition();

    // UI flags
    bool redrawBut = false;
    bool focMovingIn = true; // default assumption
    bool gotoSetpoint = false;
    bool focGoToHalf = false;
    bool setPoint = false;
    bool decSpeed = false;
    bool incSpeed = false;
    bool incMoveCt = false;
    bool decMoveCt = false;
    bool setZero = false;
    bool setMax = false;
    bool focReset = false;

    // calibration - state flags
    bool revFocuser = false ;
    bool inwardCalState = true; // start with inward calibration
    bool calibActive ;
    bool focGoToActive ;

    // motion parameters
    int focMoveSpeed = 300; // pulse width in microsec
    int focMoveDistance = 5; // probably need to start with 5
    int moveDistance = 0;

    // position tracking
    int  focPosition     = 0;
    int  focTarget       = 0;
    int  focDeltaMove    = 0;
    int  focMaxPosition  = 0;
    int  focMinPosition  = 0;
    int  setPointTarget  = 0;

    // Valid flags
    bool isZeroed   = false;  // set true in Set Zero and min-cal step
    bool isMaxKnown = false;  // set true in Set Max and max-cal step
    bool setPointValid = false; // set true when Set Goto Pt pressed
};

extern DCFocuserScreen dcFocuserScreen;

#endif
