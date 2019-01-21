
#include <Wire.h>
#include <DS3231.h>
#include <CytronEZMP3.h>

const int BUTTON = 5;
int val = 0;
int oldval = 0;
int trackNum = 1;
int is_night = 0;
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

int isNight(){
  dt = clock.getDateTime();
  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  if (dt.hour > 17){
    return 1;
  }
  return 0;
}

void loop () {
  val = digitalRead(BUTTON);
  oldval = val;
  while(val == HIGH){
    digitalWrite(13, HIGH);
    if (oldval != val) {
    Serial.println("on");
    }
    trackNum = random(3);
    is_night = isNight();
    Serial.println(is_night);
    if (is_night == 0) {
      mp3.playTrackFromFolder(1, trackNum);
      Serial.println("Now playing folder 1 track " + (String)mp3.getTrackNo());
    }
    if (is_night == 1) {
      mp3.playTrackFromFolder(2, trackNum);
      Serial.println("Now playing folder 2 track " + (String)mp3.getTrackNo());
    }
   
    delay(4000);
    val = digitalRead(BUTTON);
    Serial.println("while last");
    Serial.println(val);
  }
  if (oldval != val) {
    digitalWrite(13, LOW);
    Serial.println("off");
    }
}
