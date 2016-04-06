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
BLEService ledService("C7FEE205-E355-4370-B690-6B28B4C15EC6"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int pin1 = 2; // pin to use for the LED
const int pin2 = 3;
const int pin3 = 4;
const int pin4 = 5;
const int pin5 = 6;
const int pin6 = 7;
const int pin7 = 8;
const int pin8 = 9;


void setup() {
  Serial.begin(9600);
  Servo1.attach(pin4);
  Servo1.write(140);
  // set LED pin to output mode
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  
  //pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("Switches");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);

  // set the initial value for the characeristic:

  switchCharacteristic.setValue(0);

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
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:

     if(switchCharacteristic.written()) {
      if(switchCharacteristic.value() == 1) {
        Serial.println("Channel1 on");
        digitalWrite(pin1, HIGH);
      } else if (switchCharacteristic.value() == 11) {
        digitalWrite(pin1, LOW);
      } 
      if(switchCharacteristic.value() == 2) {
        Serial.println("Channel2 on");
        digitalWrite(pin2, HIGH);
      } else if (switchCharacteristic.value() == 22) {
        digitalWrite(pin2, LOW);
      } 
      if(switchCharacteristic.value() == 3) {
        Serial.println("Channel3 on");
        digitalWrite(pin3, HIGH);
      } else if (switchCharacteristic.value() == 33) {
        digitalWrite(pin3, LOW);
      }
       if(switchCharacteristic.value() == 4) {
        Serial.println("Channel4 on");
        Servo1.write(140);
        //digitalWrite(pin4, HIGH);
      } else if (switchCharacteristic.value() == 44) {
        Servo1.write(10);
        //digitalWrite(pin4, LOW);
      }
       if(switchCharacteristic.value() == 5) {
        Serial.println("Channel5 on");
        digitalWrite(pin5, HIGH);
      } else if (switchCharacteristic.value() == 55) {
        digitalWrite(pin5, LOW);
      }
       if(switchCharacteristic.value() == 6) {
        Serial.println("Channel6 on");
        digitalWrite(pin6, HIGH);
      } else if (switchCharacteristic.value() == 66) {
        digitalWrite(pin6, LOW);
      }
       if(switchCharacteristic.value() == 7) {
        Serial.println("Channel7 on");
        digitalWrite(pin7, HIGH);
      } else if (switchCharacteristic.value() == 77) {
        digitalWrite(pin7, LOW);
      }
       if(switchCharacteristic.value() == 8) {
        Serial.println("Channel8 on");
        digitalWrite(pin8, HIGH);
      } else if (switchCharacteristic.value() == 88) {
        digitalWrite(pin8, LOW);
      }    
     }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}


