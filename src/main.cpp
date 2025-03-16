#include <Arduino.h>
#include <LoRa.h>

#define NSS 18   // Pin NSS del LoRa
#define RST 14   // Pin Reset del LoRa
#define DIO0 26  // Pin DIO0 del LoRa

#ifdef TRANSMITTER
    #define BUTTON_PIN 12  // GPIO donde está conectado el botón
    int counter = 0;
#endif

void setup() {
    Serial.begin(115200);

    // Configurar LoRa
    LoRa.setPins(NSS, RST, DIO0);
    if (!LoRa.begin(915E6)) {  // 915 MHz (México)
        Serial.println("Error al iniciar LoRa");
        while (1);
    }

    #ifdef TRANSMITTER
        Serial.println("Modo TRANSMISOR");
        pinMode(BUTTON_PIN, INPUT_PULLUP);
    #endif

    #ifdef RECEIVER
        Serial.println("Modo RECEPTOR");
    #endif
}

void loop() {
    #ifdef TRANSMITTER
        if (digitalRead(BUTTON_PIN) == LOW) {
            delay(200);  // Evitar rebotes
            counter++;

            LoRa.beginPacket();
            LoRa.print("Contador: ");
            LoRa.print(counter);
            LoRa.endPacket();

            Serial.print("Mensaje enviado: ");
            Serial.println(counter);
        }
    #endif

    #ifdef RECEIVER
        int packetSize = LoRa.parsePacket();
        if (packetSize) {
            Serial.print("Mensaje recibido: ");
            while (LoRa.available()) {
                Serial.print((char)LoRa.read());
            }
            Serial.println();
        }
    #endif
}
