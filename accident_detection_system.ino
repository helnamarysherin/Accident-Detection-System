#define TILT_SENSOR 2
#define CANCEL_BUTTON 7
#define BUZZER 8
#define LED 9

bool accidentDetected = false;
unsigned long accidentTime = 0;

void setup() {
  pinMode(TILT_SENSOR, INPUT_PULLUP);
  pinMode(CANCEL_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  Serial.println("System Ready");
}

void loop() {

  // Detect accident (only once)
  if (!accidentDetected && digitalRead(TILT_SENSOR) == LOW) {
    accidentDetected = true;
    accidentTime = millis();

    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);

    Serial.println("🚨 ACCIDENT DETECTED");
  }

  // Cancel false alarm
  if (accidentDetected && digitalRead(CANCEL_BUTTON) == LOW) {
    resetSystem("❌ Alert Cancelled");
  }

  // Auto stop after 5 seconds
  if (accidentDetected && millis() - accidentTime >= 5000) {
    resetSystem("📨 Emergency Alert Sent");
  }
}

void resetSystem(String message) {
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);
  accidentDetected = false;

  Serial.println(message);
  delay(1000); // debounce safety
}
