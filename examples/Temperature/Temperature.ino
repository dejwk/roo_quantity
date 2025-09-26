#include <Arduino.h>

#include "roo_logging.h"
#include "roo_quantity.h"

using namespace roo_quantity;

void setup() { Serial.begin(9600); }

void loop() {
  // Random temperature between -15.0C and +35.0C.
  Temperature temp = TemperatureDegCelcius(rand() % 500 / 10.0 - 15.0f);
  Serial.printf("Temperature: %s\n", temp.asArduinoString().c_str());
  Serial.println("In Celsius: " + String(temp.degCelcius()));
  Serial.println("In Kelvin: " + String(temp.degKelvin()));
  Serial.println("In Fahrenheit: " + String(temp.degFahrenheit()));

  // Quantity can also be 'unknown'.
  Serial.println("Unknown temperature: " +
                 UnknownTemperature().asArduinoString());

  // When you calculate temperature differences, the result is a
  // TemperatureDelta.
  TemperatureDelta d1 =
      TemperatureDegCelcius(25.0f) - TemperatureDegCelcius(22.0f);
  Serial.printf("Temperature delta 1: %s\n", d1.asString().c_str());

  // You can also create a TemperatureDelta directly.
  TemperatureDelta d2 = TemperatureDeltaDegCelcius(5.0f);
  Serial.printf("Temperature delta 2: %s\n", d2.asString().c_str());

  // You cannot add two Temperature objects (temperatures are absolute),
  // but you can add a TemperatureDelta to a Temperature (or to another delta).
  Temperature new_temp = temp + d1 + d2;
  Serial.printf("New temperature: %s\n", new_temp.asString().c_str());

  delay(1000);
}
