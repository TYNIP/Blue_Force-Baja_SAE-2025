#include <SPI.h>
#include <LoRa.h>

// Módulo LoRa (SX1278)
#define NSS 5    
#define RST 14   
#define DIO0 26  

#ifdef TRANSMITTER
  #define POT_PIN 34  
#endif

void setup() {
  Serial.begin(115200);
  while (!Serial);  

  SPI.begin();

  LoRa.setPins(NSS, RST, DIO0);

  Serial.println("Iniciando LoRa...");
  if (!LoRa.begin(915E6)) {  
    Serial.println("Error al iniciar LoRa");
    while (1); 
  }

  #ifdef TRANSMITTER
    Serial.println("Modo TRANSMISOR");
  #endif

  #ifdef RECEIVER
    Serial.println("Modo RECEPTOR");
  #endif
}

void loop() {
  #ifdef TRANSMITTER
    int potValue = analogRead(POT_PIN);

    LoRa.beginPacket();
    LoRa.write(potValue);  
    LoRa.endPacket();

    Serial.print("Valor del potenciómetro enviado: ");
    Serial.println(potValue);

    delay(1000);
  #endif

  #ifdef RECEIVER
    int packetSize = LoRa.parsePacket();
    Serial.println(packetSize);
    if (packetSize) {
      String received = "";
      while (LoRa.available()) {
        received += (char)LoRa.read();
      }
      Serial.print("Valor recibido: ");
      Serial.println(received);
    }

    Serial.println("Receptor - Ayuda no jala :c");
    delay(1000);
  #endif
}
