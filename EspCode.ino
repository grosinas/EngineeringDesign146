//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String msg;
int TEST = 13;
int OpenPaper = 14;
int OUTPUT1;
int OUTPUT2;
int OUTPUT3;
int INPUT1;
int INPUT2;
int INPUT3;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  msg = "";
  pinMode(TEST, OUTPUT);
  pinMode(OUTPUT1, OUTPUT);
  pinMode(OpenPaper, OUTPUT);
  digitalWrite(OpenPaper, LOW);

  digitalWrite(TEST, LOW);
}

void loop() {

  if (Serial.available()) {
    SerialBT.write(Serial.read());
    digitalWrite(TEST, LOW);

  }
  if (SerialBT.available()) {
    //    msg = SerialBT.readString();
    //    if (msg == "<Open PMD>") {
    //      Serial.write("test");
    //      digitalWrite(TEST, HIGH);
    //    } else if (msg == "<Open Paper>") {
    //      Serial.write("not test");
    //      digitalWrite(TEST, LOW);
    //    }
    msg = SerialBT.readString();
    //Serial.write(SerialBT.read());
    Serial.println(msg);
    if (msg == "<Open PMD>") {
      digitalWrite(TEST, HIGH);
      delay(1000);
      digitalWrite(TEST,LOW);
    } else if (msg == "<Open Other>") {
      digitalWrite(OpenPaper, !digitalRead(OpenPaper));
    }

  }


}
