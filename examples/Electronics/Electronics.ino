#include <Arduino.h>

#include "roo_logging.h"
#include "roo_quantity.h"
#include "roo_quantity/capacitance.h"
#include "roo_quantity/resistance.h"
#include "roo_quantity/voltage.h"

using namespace roo_quantity;

void setup() { Serial.begin(9600); }

void loop() {
  // Random voltage between 0 and 5V.
  Voltage u = VoltageInVolts(rand() % 500 / 100.0f);
  Serial.printf("Voltage: %s\n", u.asString().c_str());
  // Random current between 0 and 50 mA.
  Current i = CurrentInMilliAmperes(rand() % 50);
  Serial.printf("Current: %s\n", i.asString().c_str());
  Serial.printf("Power: %s\n", (u * i).asString().c_str());
  Serial.printf("Resistance: %s\n", (u / i).asString().c_str());

  // Random capacitance between 0 and 4.7uF.
  Capacitance c = CapacitanceInMicroFarads(rand() % 470 / 100.0f);
  Serial.printf("Capacitance: %s\n", c.asString().c_str());
  Serial.printf("Charge at voltage %s: %s %s\n", u.asString().c_str(),
                (c * u).asString().c_str());

  delay(1000);
}
