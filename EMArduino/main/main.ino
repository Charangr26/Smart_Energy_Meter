#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

// Define LCD and PZEM objects
LiquidCrystal_I2C lcd(0x27, 20, 4); // Adjust address if needed
SoftwareSerial pzemSerial(10, 11);  // RX = Pin 10, TX = Pin 11
PZEM004Tv30 pzem(pzemSerial);

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Power Tracker ");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000); // Show initializing message for 2 seconds
  lcd.clear();

  // Initialize Serial for debugging
  Serial.begin(9600);
  Serial.println("PZEM Data Logger");
}

void loop() {
  // Read PZEM data
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();

  // Update LCD with PZEM data
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage, 1);
  lcd.print("V  ");

  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.print(current, 2);
  lcd.print("A  ");

  lcd.setCursor(0, 2);
  lcd.print("Power: ");
  lcd.print(power, 0);
  lcd.print("W  ");

  lcd.setCursor(0, 3);
  lcd.print("Energy: ");
  lcd.print(energy, 3);
  lcd.print("kWh");

  // Debug values to Serial Monitor
  Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
  Serial.print("Current: "); Serial.print(current); Serial.println(" A");
  Serial.print("Power: "); Serial.print(power); Serial.println(" W");
  Serial.print("Energy: "); Serial.print(energy); Serial.println(" kWh");
  Serial.println("--------------------");

  delay(2000); // Update interval
}
