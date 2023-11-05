/*
  WriteSingleField
  
  Description: Writes a value to a channel on ThingSpeak every 20 seconds.
  
  Hardware: ESP32 based boards
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
  - Requires installation of EPS32 core. See https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md for details. 
  - Select the target hardware from the Tools->Board menu
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/

#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#define serial_komunikasi Serial1

char ssid[] = "TexasKost";   // your network SSID (name) 
char pass[] = "wisnuudahkerja";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 2332106;
const char * myWriteAPIKey = "QS56H9IHAQ6WUP36";
String datamasuk = Serial1.readString();

// Initialize our values
String myStatus = "";

void setup() {
  Serial.begin(115200);  //Initialize serial
  serial_komunikasi.begin(9600, SERIAL_8N1, 27, 26);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  String data = Serial1.readString();
  
// String Sensor1 = data.substring(0, 3); // Mengambil karakter dari indeks 7 hingga 11
// String Sensor2 = data.substring(4, 7); // Mengambil karakter dari indeks 7 hingga 11
// String Sensor3 = data.substring(7, 13); // Mengambil karakter dari indeks 7 hingga 11
// String Sensor4 = data.substring(13, 18); // Mengambil karakter dari indeks 7 hingga 11
// String Sensor5 = data.substring(18, 21); // Mengambil karakter dari indeks 7 hingga 11

// String data = "Sensor1:254,Sensor2:312345678,Sensor3:200";
int sensor1StartIndex = data.indexOf("sensor1:") + 8; // Panjang "Sensor1:" adalah 8 karakter
int sensor1EndIndex = data.indexOf(",sensor2");
String value1 = data.substring(sensor1StartIndex, sensor1EndIndex);

int sensor2StartIndex = data.indexOf("sensor2:") + 8; // Panjang "Sensor1:" adalah 8 karakter
int sensor2EndIndex = data.indexOf(",sensor3");
String value2 = data.substring(sensor2StartIndex, sensor2EndIndex);

int sensor3StartIndex = data.indexOf("sensor3:") + 8; // Panjang "Sensor1:" adalah 8 karakter
int sensor3EndIndex = data.indexOf(",sensor4");
String value3 = data.substring(sensor3StartIndex, sensor3EndIndex);

int sensor4StartIndex = data.indexOf("sensor4:") + 8; // Panjang "Sensor1:" adalah 8 karakter
int sensor4EndIndex = data.indexOf(",sensor5");
String value4 = data.substring(sensor4StartIndex, sensor4EndIndex);

int sensor5StartIndex = data.indexOf("sensor5:") + 8; // Panjang "Sensor1:" adalah 8 karakter
int sensor5EndIndex = data.indexOf(",sensor6");
String value5 = data.substring(sensor5StartIndex, sensor5EndIndex);
// String value5 = data.substring(data.indexOf("sensor5:")+8;

  // set the fields with the values
  ThingSpeak.setField(1, value1);
  ThingSpeak.setField(2, value2);
  ThingSpeak.setField(3, value3);
  ThingSpeak.setField(4, value4);
  ThingSpeak.setField(5, value5);

  // set the status
  ThingSpeak.setStatus(myStatus);
  
Serial.print("sensor1:" + value1);
Serial.print("sensor2:" + value2);
Serial.print("sensor3:" + value3);
Serial.print("sensor4:" + value4);
Serial.print("sensor5:" + value5);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000); // Wait 20 seconds to update the channel again
}

