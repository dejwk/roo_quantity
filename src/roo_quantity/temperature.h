#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_time.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

ROO_DECLARE_FLAG(char, roo_quantity_default_temperature_unit);

namespace roo_quantity {

class Temperature;
class TemperatureDelta;

// Representation of a temperature, internally stored as floating-point Celsius
// degrees.
class Temperature {
 public:
  // Creates a temperature object representing an 'unknown' temperature.
  Temperature() : tempC_(std::nanf("")) {}

  // Returns the temperature in degrees Celcius.
  float degCelcius() const { return tempC_; }

  // Returns the temperature in degrees Kelvin.
  float degKelvin() const { return tempC_ + 273.15; }

  // Returns the temperature in degrees Fahrenheit.
  float degFahrenheit() const { return tempC_ * 1.8 + 32.0; }

  // Returns whether the object represents an unknown temperature.
  bool isUnknown() const { return std::isnan(tempC_); }

  bool operator<(const Temperature &other) const {
    return tempC_ < other.tempC_;
  }

  bool operator==(const Temperature &other) const {
    return tempC_ == other.tempC_;
  }

  bool operator>(const Temperature &other) const {
    return other.tempC_ < tempC_;
  }

  bool operator<=(const Temperature &other) const {
    return !(other.tempC_ < tempC_);
  }

  bool operator>=(const Temperature &other) const {
    return !(tempC_ < other.tempC_);
  }

  bool operator!=(const Temperature &other) const {
    return !(tempC_ == other.tempC_);
  }

  inline Temperature &operator+=(const TemperatureDelta &other);
  inline Temperature &operator-=(const TemperatureDelta &other);

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the temperature, using the unit
  // defined by the 'roo_temperature_default_unit' flag.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Temperature UnknownTemperature();

  friend Temperature TemperatureDegCelcius(float);
  friend Temperature TemperatureDegKelvin(float);
  friend Temperature TemperatureDegFahrenheit(float);

  explicit Temperature(float tempC) : tempC_(tempC) {}

  // Using Celsius for the internal representation, so that integer C
  // temperatures (particularly, zero) behave well when compared for equality.
  float tempC_;
};

class TemperatureDelta {
 public:
  // Creates a temperature delta object representing an 'unknown' temperature
  // delta.
  TemperatureDelta() : tempC_(std::nanf("")) {}

  // Returns the temperature delta in degrees Celcius.
  float degCelcius() const { return tempC_; }

  // Returns the temperature delta in degrees Kelvin.
  float degKelvin() const { return tempC_ + 273.15; }

  // Returns the temperature delta in degrees Fahrenheit.
  float degFahrenheit() const { return tempC_ * 1.8 + 32.0; }

  // Returns whether the object represents an unknown temperature delta.
  bool isUnknown() const { return std::isnan(tempC_); }

  bool operator<(const TemperatureDelta &other) const {
    return tempC_ < other.tempC_;
  }

  bool operator==(const TemperatureDelta &other) const {
    return tempC_ == other.tempC_;
  }

  bool operator>(const TemperatureDelta &other) const {
    return other.tempC_ < tempC_;
  }

  bool operator<=(const TemperatureDelta &other) const {
    return !(other.tempC_ < tempC_);
  }

  bool operator>=(const TemperatureDelta &other) const {
    return !(tempC_ < other.tempC_);
  }

  bool operator!=(const TemperatureDelta &other) const {
    return !(tempC_ == other.tempC_);
  }

  inline TemperatureDelta &operator+=(const TemperatureDelta &other) {
    tempC_ += other.degCelcius();
    return *this;
  }

  inline TemperatureDelta &operator-=(const TemperatureDelta &other) {
    tempC_ -= other.degCelcius();
    return *this;
  }

  inline TemperatureDelta &operator*=(float multi) {
    tempC_ *= multi;
    return *this;
  }

  inline TemperatureDelta &operator/=(float div) {
    tempC_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the temperature delta, using the unit
  // defined by the 'roo_temperature_default_unit' flag.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend TemperatureDelta UnknownTemperatureDelta();

  friend TemperatureDelta TemperatureDeltaDegCelcius(float);
  friend TemperatureDelta TemperatureDeltaDegKelvin(float);
  friend TemperatureDelta TemperatureDeltaDegFahrenheit(float);

  explicit TemperatureDelta(float tempC) : tempC_(tempC) {}

  // Using Celsius (equivalent to Kelvin) for the internal delta representation.
  float tempC_;
};

roo_logging::Stream &operator<<(roo_logging::Stream &os, const Temperature &t);
roo_logging::Stream &operator<<(roo_logging::Stream &os,
                                const TemperatureDelta &t);

// Returns a temperature object representing an unknown temperature.
inline Temperature UnknownTemperature() { return Temperature(); }

// Returns a temperature object equivalent to the specified temperature
// expressed in Celcius degrees.
inline Temperature TemperatureDegCelcius(float tempC) {
  return Temperature(tempC);
}

// Returns a temperature object equivalent to the specified temperature
// expressed in Kelvin degrees.
//
// Due to floating-point rounding errors, and since the temperature is
// internally stored in Celcius degrees, generally,
// DegKelvin(x).degKelvin() != x.
inline Temperature TemperatureDegKelvin(float tempK) {
  return Temperature(tempK - 273.15);
}

// Returns a temperature object approximately equal to the specified temperature
// expressed in Fahrenheit degrees.
//
// Due to floating-point rounding errors, and since the temperature is
// internally stored in Celcius degrees, generally,
// DegFahrenheit(x).degFahrenheit() != x.
inline Temperature TemperatureDegFahrenheit(float tempF) {
  return TemperatureDegCelcius((tempF - 32.0) / 1.8);
}

// Returns a temperature object representing an unknown temperature delta.
inline TemperatureDelta UnknownTemperatureDelta() { return TemperatureDelta(); }

// Returns a temperature delta object equivalent to the specified temperature
// expressed in Celcius degrees.
inline TemperatureDelta TemperatureDeltaDegCelcius(float tempC) {
  return TemperatureDelta(tempC);
}

// Returns a temperature delta object equivalent to the specified temperature
// delta expressed in Kelvin degrees. It is in fact equivalent to
// TemperatureDeltaDegCelcius.
inline TemperatureDelta TemperatureDeltaDegKelvin(float tempK) {
  return TemperatureDelta(tempK);
}

// Returns a temperature delta object approximately equal to the specified
// temperature delta expressed in Fahrenheit degrees.
//
// Due to floating-point rounding errors, and since the temperature is
// internally stored in Celcius degrees, generally,
// DegFahrenheit(x).degFahrenheit() != x.
inline TemperatureDelta TemperatureDeltaDegFahrenheit(float tempF) {
  return TemperatureDeltaDegCelcius(tempF / 1.8);
}

inline Temperature &Temperature::operator+=(const TemperatureDelta &other) {
  tempC_ += other.degCelcius();
  return *this;
}

inline Temperature &Temperature::operator-=(const TemperatureDelta &other) {
  tempC_ -= other.degCelcius();
  return *this;
}

inline Temperature operator+(Temperature a, TemperatureDelta b) {
  return TemperatureDegCelcius(a.degCelcius() + b.degCelcius());
}

inline Temperature operator-(Temperature a, TemperatureDelta b) {
  return TemperatureDegCelcius(a.degCelcius() - b.degCelcius());
}

inline Temperature operator+(TemperatureDelta a, Temperature b) {
  return TemperatureDegCelcius(a.degCelcius() + b.degCelcius());
}

inline TemperatureDelta operator+(TemperatureDelta a, TemperatureDelta b) {
  return TemperatureDeltaDegCelcius(a.degCelcius() + b.degCelcius());
}

inline TemperatureDelta operator-(TemperatureDelta a, TemperatureDelta b) {
  return TemperatureDeltaDegCelcius(a.degCelcius() - b.degCelcius());
}

inline TemperatureDelta operator-(TemperatureDelta a) {
  return TemperatureDeltaDegCelcius(-a.degCelcius());
}

inline TemperatureDelta operator-(Temperature a, Temperature b) {
  return TemperatureDeltaDegCelcius(a.degCelcius() - b.degCelcius());
}

inline TemperatureDelta operator*(TemperatureDelta a, float b) {
  return TemperatureDeltaDegCelcius(a.degCelcius() * b);
}

inline TemperatureDelta operator*(float a, TemperatureDelta b) {
  return TemperatureDeltaDegCelcius(a * b.degCelcius());
}

inline TemperatureDelta operator/(TemperatureDelta a, float b) {
  return TemperatureDeltaDegCelcius(a.degCelcius() / b);
}

}  // namespace roo_quantity