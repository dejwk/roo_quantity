#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/area.h"
#include "roo_quantity/areic_number.h"
#include "roo_quantity/force.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of pressure, internally stored as floating-point Pascals.
class Pressure {
 public:
  // Creates a pressure object representing an 'unknown' pressure.
  Pressure() : pressure_(std::nanf("")) {}

  // Returns the pressure in GigaPascals.
  float inGigaPascals() const { return pressure_ * 0.000000001f; }

  // Returns the pressure in MegaPascals.
  float inMegaPascals() const { return pressure_ * 0.000001f; }

  // Returns the pressure in bars.
  float inBars() const { return pressure_ * 0.00001f; }

  // Returns the pressure in kiloPascals.
  float inKiloPascals() const { return pressure_ * 0.001f; }

  // Returns the pressure in HectoPascals.
  float inHectoPascals() const { return pressure_ * 0.01f; }

  // Returns the pressure in Pascals.
  float inPascals() const { return pressure_; }

  // Returns the pressure in milliPascals.
  float inMilliPascals() const { return pressure_ * 1000.0f; }

  // Returns the pressure in microPascals.
  float inMicroPascals() const { return pressure_ * 1000000.0f; }

  // Returns the pressure in PSI (pound per square inch).
  float inPSI() const { return pressure_ * 0.0001450377f; }

  // Returns whether the object represents an unknown pressure.
  bool isUnknown() const { return std::isnan(pressure_); }

  bool operator<(const Pressure& other) const {
    return pressure_ < other.pressure_;
  }

  bool operator==(const Pressure& other) const {
    return pressure_ == other.pressure_;
  }

  bool operator>(const Pressure& other) const {
    return other.pressure_ < pressure_;
  }

  bool operator<=(const Pressure& other) const {
    return !(other.pressure_ < pressure_);
  }

  bool operator>=(const Pressure& other) const {
    return !(pressure_ < other.pressure_);
  }

  bool operator!=(const Pressure& other) const {
    return !(pressure_ == other.pressure_);
  }

  inline Pressure& operator+=(const Pressure& other) {
    pressure_ += other.inPascals();
    return *this;
  }

  inline Pressure& operator-=(const Pressure& other) {
    pressure_ -= other.inPascals();
    return *this;
  }

  inline Pressure& operator*=(float multi) {
    pressure_ *= multi;
    return *this;
  }

  inline Pressure& operator/=(float div) {
    pressure_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the pressure.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Pressure UnknownPressure();

  friend Pressure PressureInPascals(float);

  explicit Pressure(float pressure) : pressure_(pressure) {}

  // Stored in Pascals.
  float pressure_;
};

inline Pressure PressureInPascals(float pressure);

// Returns a pressure object representing an unknown pressure.
inline Pressure UnknownPressure() { return Pressure(); }

// Returns a pressure object equivalent to the specified pressure
// expressed in GigaPascals.
inline Pressure PressureInGigaPascals(float pressure) {
  return PressureInPascals(pressure * 1000000000.0f);
}

// Returns a pressure object equivalent to the specified pressure
// expressed in MegaPascals.
inline Pressure PressureInMegaPascals(float pressure) {
  return PressureInPascals(pressure * 1000000.0f);
}

// Returns a pressure object equivalent to the specified pressure
// expressed in bars.
inline Pressure PressureInBars(float pressure) {
  return PressureInPascals(pressure * 100000.0f);
}

// Returns a pressure object equivalent to the specified pressure
// expressed in kiloPascals.
inline Pressure PressureInKiloPascals(float pressure) {
  return PressureInPascals(pressure * 1000.0f);
}

// Returns a pressure object equivalent to the specified pressure
// expressed in hectoPascals.
inline Pressure PressureInHectoPascals(float pressure) {
  return PressureInPascals(pressure * 100.0f);
}

// Returns a pressure object equivalent to the specified pressure
// expressed in Pascals.
inline Pressure PressureInPascals(float pressure) { return Pressure(pressure); }

// Returns a pressure object equivalent to the specified pressure
// expressed in milliPascals.
inline Pressure PressureInMilliPascals(float pressure) {
  return PressureInPascals(pressure * 0.001f);
}

// Returns a pressure object equivalent to the specified pressure
// expressed in microPascals.
inline Pressure PressureInMicroPascals(float pressure) {
  return PressureInPascals(pressure * 0.000001f);
}

// Returns a pressure object equivalent to the specified pressure
// expressed in PSI (pounds per square inch).
inline Pressure PressureInPSI(float pressure) {
  return PressureInPascals(pressure * 6894.7572932f);
}

inline Pressure operator+(Pressure a, Pressure b) {
  return PressureInPascals(a.inPascals() + b.inPascals());
}

inline Pressure operator-(Pressure a, Pressure b) {
  return PressureInPascals(a.inPascals() - b.inPascals());
}

inline Pressure operator-(Pressure a) {
  return PressureInPascals(-a.inPascals());
}

inline Pressure operator*(Pressure a, float b) {
  return PressureInPascals(a.inPascals() * b);
}

inline Pressure operator*(float a, Pressure b) {
  return PressureInPascals(a * b.inPascals());
}

inline Pressure operator/(Pressure a, float b) {
  return PressureInPascals(a.inPascals() / b);
}

inline float operator/(Pressure a, Pressure b) {
  return a.inPascals() / b.inPascals();
}

inline Pressure operator/(Force a, Area b) {
  return PressureInPascals(a.inNewtons() / b.inSquareMeters());
}

inline Pressure operator*(Force a, AreicNumber b) {
  return PressureInPascals(a.inNewtons() * b.inUnitsPerSquareMeter());
}

}  // namespace roo_quantity