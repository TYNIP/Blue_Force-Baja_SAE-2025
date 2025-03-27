#include <Arduino.h>

#ifdef TRANSMITTER
#include "Transmitter.h"
#endif

#ifdef RECEIVER
#include "Receiver.h"
#endif

void setup() {
    Serial.begin(115200);
    while (!Serial);

    #ifdef TRANSMITTER
    setupTransmitter();
    #endif

    #ifdef RECEIVER
    setupReceiver();
    #endif
}

void loop() {
    #ifdef TRANSMITTER
    sendMessage("Esto esta encendido????");
    delay(2000);
    #endif

    #ifdef RECEIVER
    receiveMessage();
    #endif
}
