#include <Wire.h>
#include <DS3231.h>
#include <CytronEZMP3.h>

int distance = 0;
int oldDistance = 0;
int trackNum = 1;
int is_night = 0;
int trig = 8;
int echo = 9;
CytronEZMP3 mp3;
DS3231 clock;
RTCDateTime dt;



void setup () {

  //  pinMode(BUTTON, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
  // Initialize DS3231
  Serial.println("Initialize DS3231");;
  clock.begin();
  //
  //  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);

  if (!mp3.begin(2, 3))
  {
    Serial.println("Init failed");
    while (1);
  }
  mp3.setVolume(25);
  Serial.print("Device: ");
  Serial.println(mp3.getCurrentDevice() == 1 ? "U-Disk" : "microSD");

  Serial.print("Total files: ");
  Serial.println(mp3.getTotalFiles());
}

float isClose() {
  digitalWrite(trig, LOW);
  delayMicroseconds(1);

  digitalWrite(trig, HIGH);
  delayMicroseconds(11);

  digitalWrite(trig, LOW);
  int t = pulseIn(echo, HIGH);
  float distance = t * 0.017;
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 30) {
    return 1;
  } else {
    return 0;
  }
}

int isNight() {
  dt = clock.getDateTime();
  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  if (dt.hour > 17) {
    return 1;
  }
  return 0;
}

void loop () {
  distance = isClose();
  oldDistance = distance;

  while (distance == 1) {
    digitalWrite(13, HIGH);

    if (oldDistance != distance) {
      Serial.println("on");
    }
    trackNum = 1 + random(2);
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

    delay(3000);
    distance = isClose();
  }
  if (oldDistance != distance) {
    digitalWrite(13, LOW);
    Serial.println("off");
  }
}
