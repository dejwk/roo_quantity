#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/current.h"
#include "roo_quantity/power.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of voltage, internally stored as floating-point Volts.
class Voltage {
 public:
  // Creates a voltage object representing an 'unknown' voltage.
  Voltage() : voltage_(std::nanf("")) {}

  // Returns the voltage in kiloVolts.
  float inKiloVolts() const { return voltage_ * 0.001f; }

  // Returns the voltage in Volts.
  float inVolts() const { return voltage_; }

  // Returns the voltage in milliVolts.
  float inMilliVolts() const { return voltage_ * 1000.0f; }

  // Returns the voltage in microVolts.
  float inMicroVolts() const { return voltage_ * 1000000.0f; }

  // Returns whether the object represents an unknown voltage.
  bool isUnknown() const { return std::isnan(voltage_); }

  bool operator<(const Voltage& other) const {
    return voltage_ < other.voltage_;
  }

  bool operator==(const Voltage& other) const {
    return voltage_ == other.voltage_;
  }

  bool operator>(const Voltage& other) const {
    return other.voltage_ < voltage_;
  }

  bool operator<=(const Voltage& other) const {
    return !(other.voltage_ < voltage_);
  }

  bool operator>=(const Voltage& other) const {
    return !(voltage_ < other.voltage_);
  }

  bool operator!=(const Voltage& other) const {
    return !(voltage_ == other.voltage_);
  }

  inline Voltage& operator+=(const Voltage& other) {
    voltage_ += other.inVolts();
    return *this;
  }

  inline Voltage& operator-=(const Voltage& other) {
    voltage_ -= other.inVolts();
    return *this;
  }

  inline Voltage& operator*=(float multi) {
    voltage_ *= multi;
    return *this;
  }

  inline Voltage& operator/=(float div) {
    voltage_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the voltage.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Voltage UnknownVoltage();

  friend Voltage VoltageInVolts(float);

  explicit Voltage(float voltage) : voltage_(voltage) {}

  // Stored in Volts.
  float voltage_;
};

inline Voltage VoltageInVolts(float voltage);

// Returns a voltage object representing an unknown voltage.
inline Voltage UnknownVoltage() { return Voltage(); }

// Returns a voltage object equivalent to the specified voltage
// expressed in kiloVolts.
inline Voltage VoltageInKiloVolts(float voltage) {
  return VoltageInVolts(voltage * 1000.0f);
}

// Returns a voltage object equivalent to the specified voltage
// expressed in Volts.
inline Voltage VoltageInVolts(float voltage) { return Voltage(voltage); }

// Returns a voltage object equivalent to the specified voltage
// expressed in milliVolts.
inline Voltage VoltageInMilliVolts(float voltage) {
  return VoltageInVolts(voltage * 0.001f);
}

// Returns a voltage object equivalent to the specified voltage
// expressed in microVolts.
inline Voltage VoltageInMicroVolts(float voltage) {
  return VoltageInVolts(voltage * 0.000001f);
}

inline Voltage operator+(Voltage a, Voltage b) {
  return VoltageInVolts(a.inVolts() + b.inVolts());
}

inline Voltage operator-(Voltage a, Voltage b) {
  return VoltageInVolts(a.inVolts() - b.inVolts());
}

inline Voltage operator-(Voltage a) { return VoltageInVolts(-a.inVolts()); }

inline Voltage operator*(Voltage a, float b) {
  return VoltageInVolts(a.inVolts() * b);
}

inline Voltage operator*(float a, Voltage b) {
  return VoltageInVolts(a * b.inVolts());
}

inline Voltage operator/(Voltage a, float b) {
  return VoltageInVolts(a.inVolts() / b);
}

inline float operator/(Voltage a, Voltage b) {
  return a.inVolts() / b.inVolts();
}

// Vs power.

inline Power operator*(Voltage a, Current b) {
  return PowerInWatts(a.inVolts() * b.inAmperes());
}

inline Power operator*(Current a, Voltage b) {
  return PowerInWatts(a.inAmperes() * b.inVolts());
}

inline Voltage operator/(Power a, Current b) {
  return VoltageInVolts(a.inWatts() / b.inAmperes());
}

inline Current operator/(Power a, Voltage b) {
  return CurrentInAmperes(a.inWatts() / b.inVolts());
}

// Vs work.

inline Work operator*(Voltage a, Charge b) {
  return WorkInJoules(a.inVolts() * b.inCoulombs());
}

inline Work operator*(Charge a, Voltage b) {
  return WorkInJoules(a.inCoulombs() * b.inVolts());
}

inline Voltage operator/(Work a, Charge b) {
  return VoltageInVolts(a.inJoules() / b.inCoulombs());
}

inline Charge operator/(Work a, Voltage b) {
  return ChargeInCoulombs(a.inJoules() / b.inVolts());
}

}  // namespace roo_quantity