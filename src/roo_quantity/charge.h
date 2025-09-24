#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of charge, internally stored as floating-point Coulombs.
class Charge {
 public:
  // Creates a charge object representing an 'unknown' charge.
  Charge() : charge_(std::nanf("")) {}

  // Returns the charge in kiloCoulombs.
  float inKiloCoulombs() const { return charge_ / 1000.0f; }

  // Returns the charge in Coulombs.
  float inCoulombs() const { return charge_; }

  // Returns the charge in milliCoulombs.
  float inMilliCoulombs() const { return charge_ * 1000.0f; }

  // Returns the charge in microCoulombs.
  float inMicroCoulombs() const { return charge_ * 1000000.0f; }

  // Returns whether the object represents an unknown charge.
  bool isUnknown() const { return std::isnan(charge_); }

  bool operator<(const Charge& other) const { return charge_ < other.charge_; }

  bool operator==(const Charge& other) const {
    return charge_ == other.charge_;
  }

  bool operator>(const Charge& other) const { return other.charge_ < charge_; }

  bool operator<=(const Charge& other) const {
    return !(other.charge_ < charge_);
  }

  bool operator>=(const Charge& other) const {
    return !(charge_ < other.charge_);
  }

  bool operator!=(const Charge& other) const {
    return !(charge_ == other.charge_);
  }

  inline Charge& operator+=(const Charge& other) {
    charge_ += other.inCoulombs();
    return *this;
  }

  inline Charge& operator-=(const Charge& other) {
    charge_ -= other.inCoulombs();
    return *this;
  }

  inline Charge& operator*=(float multi) {
    charge_ *= multi;
    return *this;
  }

  inline Charge& operator/=(float div) {
    charge_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the charge.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Charge UnknownCharge();

  friend Charge ChargeInCoulombs(float);

  explicit Charge(float charge) : charge_(charge) {}

  // Stored in Coulombs.
  float charge_;
};

inline Charge ChargeInCoulombs(float charge);

// Returns a charge object representing an unknown charge.
inline Charge UnknownCharge() { return Charge(); }

// Returns a charge object equivalent to the specified charge
// expressed in kiloCoulombs.
inline Charge ChargeInKiloCoulombs(float charge) {
  return ChargeInCoulombs(charge * 1000.0f);
}

// Returns a charge object equivalent to the specified charge
// expressed in Coulombs.
inline Charge ChargeInCoulombs(float charge) { return Charge(charge); }

// Returns a charge object equivalent to the specified charge
// expressed in milliCoulombs.
inline Charge ChargeInMilliCoulombs(float charge) {
  return ChargeInCoulombs(charge * 0.001f);
}

// Returns a charge object equivalent to the specified charge
// expressed in microCoulombs.
inline Charge ChargeInMicroCoulombs(float charge) {
  return ChargeInCoulombs(charge * 0.000001f);
}

inline Charge operator+(Charge a, Charge b) {
  return ChargeInCoulombs(a.inCoulombs() + b.inCoulombs());
}

inline Charge operator-(Charge a, Charge b) {
  return ChargeInCoulombs(a.inCoulombs() - b.inCoulombs());
}

inline Charge operator-(Charge a) { return ChargeInCoulombs(-a.inCoulombs()); }

inline Charge operator*(Charge a, float b) {
  return ChargeInCoulombs(a.inCoulombs() * b);
}

inline Charge operator*(float a, Charge b) {
  return ChargeInCoulombs(a * b.inCoulombs());
}

inline Charge operator/(Charge a, float b) {
  return ChargeInCoulombs(a.inCoulombs() / b);
}

inline float operator/(Charge a, Charge b) {
  return a.inCoulombs() / b.inCoulombs();
}

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Charge& val);

}  // namespace roo_quantity