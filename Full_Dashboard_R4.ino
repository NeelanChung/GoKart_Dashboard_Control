#include "config.h"
#include "buttons.h"
#include "lcd.h"
#include "Sensors.h"

// Debounced buttons
DebouncedButton btnTemp, btnBatt, btn3, btn4;

// Current UI mode
unsigned int mode = MODE_OTHER;

// Draw the chosen screen exactly once on entry
static void enterMode(unsigned int m) {
  mode = m;
  switch (m) {
    case MODE_TEMPERATURE: drawTemperatureScreen(); break;
    case MODE_BATTERY:     drawBatteryScreen();     break;
    case MODE_SPEED:       drawSpeedScreen();       break;
    case MODE_OTHER:       drawOtherScreen();       break;
  }
}

void setup() {
  Serial.begin(115200);
  initLCD();

  initButton(btnTemp, PIN_BTN_TEMP, DEBOUNCE_MS);
  initButton(btnBatt, PIN_BTN_BATT, DEBOUNCE_MS);
  initButton(btn3,    PIN_BTN_SPEED,    DEBOUNCE_MS);
  initButton(btn4,    PIN_BTN_4,    DEBOUNCE_MS);

  enterMode(MODE_OTHER); // default screen
}

void loop() {
  // Button presses change mode and draw screen once
  if (updateButton(btnTemp)) { enterMode(MODE_TEMPERATURE); Serial.println("Temp"); }
  if (updateButton(btnBatt)) { enterMode(MODE_BATTERY);     Serial.println("Batt"); }
  if (updateButton(btn3))    { enterMode(MODE_SPEED);       Serial.println("Speed"); }
  if (updateButton(btn4))    { enterMode(MODE_OTHER);       Serial.println("Other"); }

  // Per-mode periodic work (animations, incremental updates)
  switch(mode){
    case MODE_TEMPERATURE: 

    break; 

    case MODE_BATTERY: 

    break; 

    case MODE_SPEED: 
    noInterrupts();
    unsigned int dtUs = deltaT; 
    interrupts(); 

    drawSpeedVals(calculateSpeed(dtUs, RADIUS), calculateRPM(dtUs)); 
    break; 
  }

  if(analogRead(POT_THROTTLE) > THRESHOLD)
  {
    digitalWrite(PIN_MOTOR, HIGH); 
  }
}
