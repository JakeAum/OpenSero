#include <Arduino.h>

// Define the GPIO pin for the button
#define BUTTON_PIN_1 12 
#define BUTTON_PIN_2 14 

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
}

void loop() {

  int b1 = digitalRead(BUTTON_PIN_1);
  int b2 = digitalRead(BUTTON_PIN_2);

  Serial.print(b1);
  Serial.print(" ");
  Serial.println(b2);
  delayMicroseconds(10);

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