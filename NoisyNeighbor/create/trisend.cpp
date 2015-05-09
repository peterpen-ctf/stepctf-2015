#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = 0;

    char* tri_state = argv[1];

    if (wiringPiSetup () == -1) return 1;
    printf("sending tri_state[%s]\n", tri_state);
    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableTransmit(PIN);

    mySwitch.sendTriState(tri_state);

    return 0;
}
