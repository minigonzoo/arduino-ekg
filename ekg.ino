const int ekgPin = A0;         // EKG-Signal
const int leadOffPos = 10;     // Lead-Off +
const int leadOffNeg = 11;     // Lead-Off -
unsigned long lastBeatTime = 0;
unsigned long lastSampleTime = 0;
int bpm = 0;
bool beatDetected = false;

void setup() {
  Serial.begin(9600);
  pinMode(leadOffPos, INPUT);
  pinMode(leadOffNeg, INPUT);
}

void loop() {
  if (digitalRead(leadOffPos) == HIGH || digitalRead(leadOffNeg) == HIGH) {
    Serial.println("!");  
  } else {
    int signal = analogRead(ekgPin);
    Serial.println(signal);  

 
    if (signal > 550 && !beatDetected) {
      beatDetected = true;
      unsigned long currentTime = millis();
      unsigned long interval = currentTime - lastBeatTime;
      if (interval > 300) {  
        bpm = 60000 / interval;
        lastBeatTime = currentTime;
      }
    }

    if (signal < 520) {
      beatDetected = false;
    }
  }

  delay(1);
}
