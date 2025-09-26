// This example demonstrates how to use and convert units of motion.

#include <Arduino.h>

#include "roo_logging.h"
#include "roo_quantity.h"

using namespace roo_quantity;

void setup() { Serial.begin(9600); }

void loop() {
  // You can create quantities with different units, using the provided factory
  // functions. Here, we create a velocity between 0.0 and 199.9 m/s.
  Velocity v = VelocityInMetersPerSecond(rand() % 2000 / 10.0f);

  // The library integrates with roo_logging, so you can use LOG(INFO) to
  // print out quantities conveniently. The default formatting is in SI units,
  // and it prints out an automatically selected unit based on the value.
  LOG(INFO) << "Default formatting: " << v;

  // You can extract numeric values in different units.
  Serial.printf("In m/s: %.2f\n", v.inMetersPerSecond());
  Serial.printf("In km/h: %.2f\n", v.inKilometersPerHour());
  Serial.printf("In mph: %.2f\n", v.inMilesPerHour());
  Serial.printf("In knots: %.2f\n", v.inKnots());

  // For convenience, you may with to use 'auto' for quantity type when using
  // factory functions, as they make the type obvious from the function name.
  auto t = TimeInSeconds(10);

  // Compiler protects us from mixing incompatible quantities. The following
  // won't compile:
  // auto err = v + t;

  // But when we combine quantities correctly, everything works.
  Length l = v * t;  // Distance traveled in 10 seconds.

  // When you use asArduinoString(), or asString(), the library prints out the
  // value with an automatically selected unit.
  Serial.printf("Distance traveled in %s: %s\n", t.asArduinoString().c_str(),
                l.asArduinoString().c_str());
  delay(1000);
}
