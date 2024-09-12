#include <Arduino.h>

// Define the GPIO pins
#define BUTTON_PIN_1 12
#define BUTTON_PIN_2 14
#define ROT_POT_1 13
#define MOTOR_OUT_1 22
#define MOTOR_OUT_2 23

// PWM properties
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8
#define PWM_CHANNEL_1 0
#define PWM_CHANNEL_2 1

// Global variables
int dutyCycle = 0;

void setup() {
  Serial.begin(115200);
  
  // Set pin modes
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(ROT_POT_1, INPUT);
  
  // Configure PWM for both motor control pins
  ledcSetup(PWM_CHANNEL_1, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_2, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(MOTOR_OUT_1, PWM_CHANNEL_1);
  ledcAttachPin(MOTOR_OUT_2, PWM_CHANNEL_2);
  
  // Initialize motor pins to LOW (motor off)
  ledcWrite(PWM_CHANNEL_1, 0);
  ledcWrite(PWM_CHANNEL_2, 0);
}

void loop() {
  // Read buttons (active low due to INPUT_PULLUP)
  bool button1Pressed = !digitalRead(BUTTON_PIN_1);
  bool button2Pressed = !digitalRead(BUTTON_PIN_2);
  
  // Read potentiometer and map to duty cycle (0-255)
  int potValue = analogRead(ROT_POT_1);
  dutyCycle = map(potValue, 0, 4095, 0, 255);
  
  // Motor control logic
  if (button1Pressed && !button2Pressed) {
    // Forward direction
    ledcWrite(PWM_CHANNEL_1, dutyCycle);
    ledcWrite(PWM_CHANNEL_2, 0);
    Serial.println("Motor Forward");
  } else if (button2Pressed && !button1Pressed) {
    // Reverse direction
    ledcWrite(PWM_CHANNEL_1, 0);
    ledcWrite(PWM_CHANNEL_2, dutyCycle);
    Serial.println("Motor Reverse");
  } else {
    // Stop motor when no button is pressed or both are pressed
    ledcWrite(PWM_CHANNEL_1, 0);
    ledcWrite(PWM_CHANNEL_2, 0);
    Serial.println("Motor OFF");
  }
  
  // Print debug information
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print(", Duty Cycle: ");
  Serial.println(dutyCycle);
  
  delay(100);  // Small delay to prevent serial flooding
}

// Write all GPIO Pins available on an ESP-32 Devkit 
// =======================================================|
// GPIO0: ADC2_1, Touch1, Boot (OD/IE/WPD)
// GPIO1: U0TXD, Serial TX (OD/IE/WPU)
// GPIO2: ADC2_2, Touch2 (OD/IE/WPD)
// GPIO3: U0RXD, Serial RX (OD/IE/WPU)
// GPIO4: ADC2_0, Touch0 (OD/IE/WPD)
// GPIO5: VSPI SS (OD/IE)
// -------------------------------------------------------|
// !!! GPIO6-GPIO11: Flash Memory (NOT USABLE as GPIO)
// -------------------------------------------------------|
// GPIO12: ADC2_5, RTC (OD/IE/WPD)
// GPIO13: ADC2_4, Touch4, RTC (OD/IE/WPU)
// GPIO14: ADC2_6, Touch6, RTC (OD/IE/WPU)
// GPIO15: ADC2_3, Touch3, RTC, MTDO, HSPI SS (OD/IE/WPU)
// -------------------------------------------------------|
// GPIO16: (OD/IE)
// GPIO17: (OD/IE)
// -------------------------------------------------------|
// GPIO18: VSPI CLK (OD/IE)
// GPIO19: VSPI MISO (OD/IE)
// GPIO21: Wire SDA (OD/IE)
// GPIO22: Wire SCL (OD/IE)
// GPIO23: VSPI MOSI (OD/IE)
// -------------------------------------------------------|
// GPIO25: DAC_1, ADC2_8, RTC (OD/IE)
// GPIO26: DAC_2, ADC2_9, RTC (OD/IE)
// GPIO27: ADC2_7, Touch7, RTC (OD/IE)
// GPIO32: ADC1_4, Touch9, RTC (OD/IE)
// GPIO33: ADC1_5, Touch8, RTC (OD/IE)
// -------------------------------------------------------|
// GPIO34: ADC1_6, RTC (Input only)
// GPIO35: ADC1_7, RTC (Input only)
// GPIO36: ADC1_0, RTC (Input only)
// GPIO39: ADC1_3, RTC (Input only)
// =======================================================|
// Note: OD = Output Disable, IE = Input Enable
// WPU = Weak Pull-up, WPD = Weak Pull-down
// RTC = RTC Power Domain (VDD3P3_RTC)
// =======================================================|