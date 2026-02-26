// --- LASER RECEIVER ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SENSOR_PIN = 2;
const int BIT_DELAY = 50; // Must match the transmitter!

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Awaiting Signal:");
  lcd.setCursor(0, 1);
}

void loop() {
  // Wait for the Start bit
  // Note: Most light sensor modules output LOW when light is detected.
  // If yours outputs HIGH, change 'LOW' to 'HIGH' in the while loop condition.
  while (digitalRead(SENSOR_PIN) == HIGH) {
    // Idle, waiting for laser to hit the sensor
  }

  // Delay half a bit period to sample in the middle of the pulse
  delay(BIT_DELAY + (BIT_DELAY / 2));

  char receivedChar = 0;

  // Read the 8 data bits
  for (int i = 0; i < 8; i++) {
    int bitValue = digitalRead(SENSOR_PIN);

    // Invert the reading if your sensor outputs LOW when light hits it
    if (bitValue == LOW) {
      bitWrite(receivedChar, i, 1);
    } else {
      bitWrite(receivedChar, i, 0);
    }

    delay(BIT_DELAY);
  }

  // Print to Serial Monitor and LCD
  Serial.print(receivedChar);
  lcd.print(receivedChar);

  // Simple logic to wrap text on the 16x2 screen
  static int cursorCount = 0;
  cursorCount++;
  if (cursorCount > 15) {
    lcd.clear();
    lcd.setCursor(0, 0);
    cursorCount = 0;
  }
}
