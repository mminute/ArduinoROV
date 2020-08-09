/******************************************************************************
  TinyGPSPlus_GPS_Shield.ino
  TinyGPS++ Library Example for the SparkFun GPS Logger Shield
  By Jim Lindblom @ SparkFun Electronics
  February 9, 2016
  https://github.com/sparkfun/GPS_Shield

  https://learn.sparkfun.com/tutorials/gps-logger-shield-hookup-guide?_ga=2.258475021.624261004.1561830609-1494020347.1559920172
  /Users/mjennings/Downloads/TinyGPSPlus-1.0.2/src/TinyGPS++.cpp to see the code
  Downloaded from https://github.com/mikalhart/TinyGPSPlus/releases

  See /Tests/GPS/TinyGPSPlusPlusExample/TinyGPSPlusPlusExample.ino for notes
******************************************************************************/

#include <SoftwareSerial.h>
#include <TinyGPS++.h> // Include the TinyGPS++ library
#include <Wire.h>

#define ARDUINO_GPS_RX 9 // GPS TX, Arduino RX pin
#define ARDUINO_GPS_TX 8 // GPS RX, Arduino TX pin
#define DISPLAY_ADDRESS1 0x72 //This is the default address of the OpenLCD
#define GPS_BAUD 9600 // GPS module baud rate. GP3906 defaults to 9600.
#define SERIAL_BAUD 9600
// #define SerialMonitor Serial

SoftwareSerial ssGPS(ARDUINO_GPS_TX, ARDUINO_GPS_RX); // Create a SoftwareSerial
TinyGPSPlus tinyGPS; // Create a TinyGPSPlus object

#define gpsPort ssGPS

void setup() {
  gpsPort.begin(GPS_BAUD);
  Serial.begin(SERIAL_BAUD); //Start serial communication at 9600 for debug statements
  Serial.println("OpenLCD Example Code");

  Wire.begin(); //Join the bus as master
  Wire.beginTransmission(DISPLAY_ADDRESS1);
  Wire.write('|'); //Put LCD into setting mode
  Wire.write('-'); //Send clear display command
  Wire.endTransmission();
}

void loop() {
  // print position, altitude, speed, time/date, and satellites:
  printGPSInfo();

  // "Smart delay" looks for GPS data while the Arduino's not doing anything else
  smartDelay(1000); 
}

void printGPSInfo() {
  // Print latitude, longitude, altitude in feet, course, speed, date, time,
  // and the number of visible satellites.
  // SerialMonitor.print("Lat: "); SerialMonitor.println(tinyGPS.location.lat(), 6);
   i2cSendValue(tinyGPS.location.lat());
   Serial.print("lat: ");
   Serial.println(tinyGPS.location.lat(), 6);
//  i2cSendValue(ARDUINO_GPS_RX);
  // SerialMonitor.print("Long: "); SerialMonitor.println(tinyGPS.location.lng(), 6);
  // SerialMonitor.print("Alt: "); SerialMonitor.println(tinyGPS.altitude.feet());
  // SerialMonitor.print("Course: "); SerialMonitor.println(tinyGPS.course.deg());
  // SerialMonitor.print("Speed: "); SerialMonitor.println(tinyGPS.speed.mph());
  // SerialMonitor.print("Date: "); printDate();
  // SerialMonitor.print("Time: "); printTime();
  // SerialMonitor.print("Sats: "); SerialMonitor.println(tinyGPS.satellites.value());
  // SerialMonitor.println();
}

// This custom version of delay() ensures that the tinyGPS object
// is being "fed". From the TinyGPS++ examples.
static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do
  {
    // If data has come in from the GPS module
    while (gpsPort.available())
      tinyGPS.encode(gpsPort.read()); // Send it to the encode function
    // tinyGPS.encode(char) continues to "load" the tinGPS object with new
    // data coming in from the GPS module. As full NMEA strings begin to come in
    // the tinyGPS library will be able to start parsing them for pertinent info
  } while (millis() - start < ms);
}

// printDate() formats the date into dd/mm/yy.
void printDate() {
  // SerialMonitor.print(tinyGPS.date.day());
  // SerialMonitor.print("/");
  // SerialMonitor.print(tinyGPS.date.month());
  // SerialMonitor.print("/");
  // SerialMonitor.println(tinyGPS.date.year());
}

// printTime() formats the time into "hh:mm:ss", and prints leading 0's
// where they're called for.
void printTime() {
  // SerialMonitor.print(tinyGPS.time.hour());
  // SerialMonitor.print(":");
  // if (tinyGPS.time.minute() < 10) SerialMonitor.print('0');
  // SerialMonitor.print(tinyGPS.time.minute());
  // SerialMonitor.print(":");
  // if (tinyGPS.time.second() < 10) SerialMonitor.print('0');
  // SerialMonitor.println(tinyGPS.time.second());
}

//Given a number, i2cSendValue chops up an integer into four values and sends them out over I2C
void i2cSendValue(int value) {
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1

  Wire.write('|'); //Put LCD into setting mode
  Wire.write('-'); //Send clear display command

  Wire.print("Cycles: ");
  Wire.print(value);
  Serial.println(value, 6);

  Wire.endTransmission(); //Stop I2C transmission
}
