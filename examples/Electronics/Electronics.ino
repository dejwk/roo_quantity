#include <Arduino.h>

#include "roo_logging.h"
#include "roo_quantity.h"

using namespace roo_quantity;

void setup() { Serial.begin(9600); }

void loop() {
  // Random voltage between 0 and 5V.
  Voltage u = VoltageInVolts(rand() % 500 / 100.0f);
  Serial.println("Voltage: " + u.asArduinoString());

  // Random current between 0 and 50 mA.
  Current i = CurrentInMilliAmperes(rand() % 50);
  Serial.println("Current: " + i.asArduinoString());
  Serial.println("Power: " + (u * i).asArduinoString());
  Serial.println("Resistance: " + (u / i).asArduinoString());

  // What if the current was 500 times lower?
  i /= 500;
  Serial.println("New current: " + i.asArduinoString());
  Serial.println("New power: " + (u * i).asArduinoString());
  Serial.println("New resistance: " + (u / i).asArduinoString());

  // Random capacitance between 0 and 4.7µF.
  Capacitance c = CapacitanceInNanoFarads(rand() % 4700);
  Serial.println("Capacitance " + c.asArduinoString());
  Serial.printf("Charge at %s: %s %s\n", u.asString().c_str(),
                (c * u).asString().c_str());

  delay(1000);
}
