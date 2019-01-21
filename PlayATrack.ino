/******************************************************************************
PlayATrack.ino
Cytron EasyMP3 Shield Library example sketch
Created by Ng Beng Chet @ Cytron Technologies Sdn Bhd 
Original Creation Date: Mar 10, 2016
https://github.com/CytronTechnologies/CytronWiFiShield

Modified from DFPlayer_Mini_Mp3 Library examples
Credit to lisper <lisper.li@dfrobot.com> @ DFRobot
Original Creation Date: May 30, 2014
https://github.com/DFRobot/DFPlayer-Mini-mp3

!!! Description Here !!!

Development environment specifics:
  IDE: Arduino 1.6.7
  Hardware Platform: Arduino Uno or any other compatible boards
  Cytron EasyMP3 Shield Version: 1.0

Distributed as-is; no warranty is given.
******************************************************************************/
#include <Wire.h>
#include <DS3231.h>
#include <CytronEZMP3.h>

const int BUTTON = 5;
int val = 0;
int oldval = 0;
int trackNum = 1;
CytronEZMP3 mp3;
DS3231 clock;
RTCDateTime dt;

void setup () {

  pinMode(BUTTON,INPUT);
  
  Serial.begin(9600);
 // Initialize DS3231
  Serial.println("Initialize DS3231");;
  clock.begin();
//
//  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);
  
  if(!mp3.begin(2, 3))
  {
    Serial.println("Init failed");
    while(1);
  }
  mp3.setVolume(25);
  Serial.print("Device: ");
  Serial.println(mp3.getCurrentDevice()==1?"U-Disk":"microSD");

  Serial.print("Total files: ");
  Serial.println(mp3.getTotalFiles());
}

int isNight?(){
  dt = clock.getDateTime();
  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
}

void loop () {
  
  val = digitalRead(BUTTON);
  oldval = val;
  while(val == HIGH){
    if (oldval != val) {
    Serial.println("on");
    }
    trackNum = 1 + random(2);
    mp3.playPhysical(trackNum);
    Serial.println("Now playing track " + (String)mp3.getTrackNo());
    delay(2000);
    val = digitalRead(BUTTON);
  }
  if (oldval != val) {
    Serial.println("off");
    }
}




void loop()
{
  dt = clock.getDateTime();

  // For leading zero look to DS3231_dateformat example

  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");

  delay(1000);
}
