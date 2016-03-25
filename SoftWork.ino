/*
   Copyright (c) 2015 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <CurieBle.h>
#include <Servo.h>

Servo Servo1;

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
//BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic servoCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int pin1 = 10; // pin to use for the LED
const int pin2 = 12;
const int pin3 = 11;
int servoPin = 3;

void setup() {
  Serial.begin(9600);
  Servo1.attach(servoPin);

  // set LED pin to output mode
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("LED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(ledService);
  //blePeripheral.addAttribute(switchCharacteristic);
  blePeripheral.addAttribute(servoCharacteristic);

  // set the initial value for the characeristic:

  servoCharacteristic.setValue(2);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      //Servo1.write(20);                //will turn the servo to 20 degrees initially
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:

     if(servoCharacteristic.written()) {
      
      if(servoCharacteristic.value() == 2) {
        Serial.println("Servo 180");      //will turn the servo 180 degrees
        Servo1.write(180);
      } else if (servoCharacteristic.value() == 22) {
        Servo1.write(20);
      } 
      if(servoCharacteristic.value() == 3) {
        Serial.println("TV on");
        digitalWrite(pin1, LOW);
      } else if (servoCharacteristic.value() == 33) {
        digitalWrite(pin1, HIGH);
      } 
      if(servoCharacteristic.value() == 4) {
        Serial.println("Light1 on");
        digitalWrite(pin2, LOW);
      } else if (servoCharacteristic.value() == 44) {
        digitalWrite(pin2, HIGH);
      } 
      if(servoCharacteristic.value() == 5) {
        Serial.println("Light2 on");
        digitalWrite(pin3, LOW);
      } else if (servoCharacteristic.value() == 55) {
        digitalWrite(pin3, HIGH);
      }
     }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}


