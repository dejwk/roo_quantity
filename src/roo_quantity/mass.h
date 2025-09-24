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

// Representation of mass, internally stored as floating-point kilograms.
class Mass {
 public:
  // Creates a mass object representing an 'unknown' mass.
  Mass() : mass_(std::nanf("")) {}

  // Returns the mass in metric tonnes.
  float inTons() const { return mass_ * 0.001f; }

  // Returns the mass in kilograms.
  float inKilograms() const { return mass_; }

  float inKg() const { return inKilograms(); }

  // Returns the mass in grams.
  float inGrams() const { return mass_ * 1000.0f; }

  // Returns the mass in milligrams.
  float inMilligrams() const { return mass_ * 1000000.0f; }

  // Returns the mass in micrograms.
  float inMicrograms() const { return mass_ * 1000000000.0f; }

  // Returns the mass in pounds.
  float inPounds() const { return mass_ * 2.2046226218f; }

  // Returns the mass in pounds.
  float inLbs() const { return inPounds(); }

  // Returns whether the object represents an unknown mass.
  bool isUnknown() const { return std::isnan(mass_); }

  bool operator<(const Mass& other) const { return mass_ < other.mass_; }

  bool operator==(const Mass& other) const { return mass_ == other.mass_; }

  bool operator>(const Mass& other) const { return other.mass_ < mass_; }

  bool operator<=(const Mass& other) const { return !(other.mass_ < mass_); }

  bool operator>=(const Mass& other) const { return !(mass_ < other.mass_); }

  bool operator!=(const Mass& other) const { return !(mass_ == other.mass_); }

  inline Mass& operator+=(const Mass& other) {
    mass_ += other.inKg();
    return *this;
  }

  inline Mass& operator-=(const Mass& other) {
    mass_ -= other.inKg();
    return *this;
  }

  inline Mass& operator*=(float multi) {
    mass_ *= multi;
    return *this;
  }

  inline Mass& operator/=(float div) {
    mass_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the mass.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Mass UnknownMass();

  friend Mass MassInKilograms(float);

  explicit Mass(float mass) : mass_(mass) {}

  // Stored in kg.
  float mass_;
};

inline Mass MassInGrams(float mass);

// Returns a mass object representing an unknown mass.
inline Mass UnknownMass() { return Mass(); }

// Returns a mass object equivalent to the specified mass
// expressed in kilograms.
inline Mass MassInKilograms(float mass) { return Mass(mass); }

// Returns a mass object equivalent to the specified mass
// expressed in kilograms.
inline Mass MassInKg(float mass) { return MassInKilograms(mass); }

// Returns a mass object equivalent to the specified mass
// expressed in metric tons.
inline Mass MassInTons(float mass) { return MassInKilograms(mass * 1000.0f); }

// Returns a mass object equivalent to the specified mass
// expressed in grams.
inline Mass MassInGrams(float mass) { return MassInKg(mass * 0.001f); }

// Returns a mass object equivalent to the specified mass
// expressed in milligrams.
inline Mass MassInMilligrams(float mass) {
  return MassInKilograms(mass * 0.000001f);
}

// Returns a mass object equivalent to the specified mass
// expressed in micrograms.
inline Mass MassInMicrograms(float mass) {
  return MassInKg(mass * 0.000000001f);
}

// Returns a mass object equivalent to the specified mass
// expressed in pounds.
inline Mass MassInPounds(float mass) { return MassInKg(mass * 0.45359237f); }

inline Mass MassInLbs(float mass) { return MassInPounds(mass); }

inline Mass operator+(Mass a, Mass b) { return MassInKg(a.inKg() + b.inKg()); }

inline Mass operator-(Mass a, Mass b) { return MassInKg(a.inKg() - b.inKg()); }

inline Mass operator-(Mass a) { return MassInKg(-a.inKg()); }

inline Mass operator*(Mass a, float b) { return MassInKg(a.inKg() * b); }

inline Mass operator*(float a, Mass b) { return MassInKg(a * b.inKg()); }

inline Mass operator/(Mass a, float b) { return MassInKg(a.inKg() / b); }

inline float operator/(Mass a, Mass b) { return a.inKg() / b.inKg(); }

}  // namespace roo_quantity