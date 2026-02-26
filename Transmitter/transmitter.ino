// --- LASER TRANSMITTER ---
const int LASER_PIN = 3;
const int BIT_DELAY = 50; // Milliseconds per bit (adjust if needed)

void setup() {
  pinMode(LASER_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Transmitter Ready. Type a message:");
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    transmitChar(data);
  }
}

void transmitChar(char c) {
  // Start bit (Laser ON) to tell receiver a character is coming
  digitalWrite(LASER_PIN, HIGH);
  delay(BIT_DELAY);

  // Transmit 8 bits (ASCII to Binary)
  for (int i = 0; i < 8; i++) {
    int bitValue = bitRead(c, i); // Read bit by bit
    digitalWrite(LASER_PIN, bitValue);
    delay(BIT_DELAY);
  }

  // Stop bit (Laser OFF)
  digitalWrite(LASER_PIN, LOW);
  delay(BIT_DELAY * 2); // Extra pause between characters
}
