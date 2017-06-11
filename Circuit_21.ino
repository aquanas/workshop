#include <CurieBLE.h>

BLEPeripheral blePeripheral;
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLEUnsignedCharCharacteristic switchCharacteristic("19B10000-E8F2-537E-4F6C-D104768A1214",BLERead | BLEWrite);     

const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);

  blePeripheral.setLocalName("101 Board");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);

  switchCharacteristic.setValue(0);

  blePeripheral.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  BLECentral central = blePeripheral.central();

  if (central) {

    while(central.connected()) {

      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()) {
          digitalWrite(ledPin, HIGH);
        }
        else {
          digitalWrite(ledPin, LOW);
        
          }
        }
      }
    }
  }

