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

int servoPin = 3;

Servo Servo1;

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
//BLEService servoService("19B10010-E8F2-537E-4F6C-D104768A1214");
//BLEService led3Service("19B10002-E8F2-537E-4F6C-D104768A1214");
//BLEService led4Service("19B10003-E8F2-537E-4F6C-D104768A1214");


// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switch1Characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switch2Characteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switch3Characteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switch4Characteristic("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = 13; // pin to use for the LED
const int pin2 = 11;
const int pin3 = 10;
const int pin4 = 9;

void setup() {
  Servo1.attach(servoPin);
  
  Serial.begin(9600);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
//  pinMode(pin2, OUTPUT);
//  pinMode(pin3, OUTPUT);
//  pinMode(pin4, OUTPUT);
  
  // set advertised local name and service UUID:
  blePeripheral.setLocalName("LED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  //blePeripheral.setLocalName("SERVO");
  //blePeripheral.setAdvertisedServiceUuid(servoService.uuid());


  // add service and characteristic:
  blePeripheral.addAttribute(ledService);
  //blePeripheral.addAttribute(servoService);

  blePeripheral.addAttribute(switch1Characteristic);
  blePeripheral.addAttribute(switch2Characteristic);
  blePeripheral.addAttribute(switch3Characteristic);
  blePeripheral.addAttribute(switch4Characteristic);

  // set the initial value for the characeristic:
  switch1Characteristic.setValue(0);
  switch2Characteristic.setValue(0);
  switch3Characteristic.setValue(0);
  switch4Characteristic.setValue(0);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  //Servo1.write(0);
  //(1000);

  //Servo1.write(90);
  //delay(1000);

  //Servo1.write(180);
  //delay(1000);

  
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
      if (switch1Characteristic.written()) {
        if (switch1Characteristic.value()) {   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          //Servo1.write(180);
        } else {                              // a 0 value
          Serial.println(F("LED off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
          //Servo1.write(0);   
        }
      }

    if (switch2Characteristic.written()) {
        if (switch2Characteristic.value()) {   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          //Servo1.write(180);
        } else {                              // a 0 value
          Serial.println(F("LED off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
          //Servo1.write(0);
       }
      }

      if (switch3Characteristic.written()) {
        if (switch3Characteristic.value()) {   // any value other than 0
         Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
         //Servo1.write(180);
        } else {                              // a 0 value
         Serial.println(F("LED off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
          //Servo1.write(0);
       }
     }

      if (switch4Characteristic.written()) {
        if (switch4Characteristic.value()) {   // any value other than 0
          Serial.println("LED 4 on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          Servo1.write(180);
        } else {                              // a 0 value
          Serial.println(F("LED 4 off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
          Servo1.write(20);
        }
      }
      
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}

