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

// Representation of force, internally stored as floating-point Newtons.
class Force {
 public:
  // Creates a force object representing an 'unknown' force.
  Force() : force_(std::nanf("")) {}

  // Returns the force in kiloNewtons.
  float inKiloNewtons() const { return force_ / 1000.0f; }

  // Returns the force in Newtons.
  float inNewtons() const { return force_; }

  // Returns the force in milliNewtons.
  float inMilliNewtons() const { return force_ * 1000.0f; }

  // Returns the force in microNewtons.
  float inMicroNewtons() const { return force_ * 1000000.0f; }

  // Returns whether the object represents an unknown force.
  bool isUnknown() const { return std::isnan(force_); }

  bool operator<(const Force &other) const { return force_ < other.force_; }

  bool operator==(const Force &other) const {
    return force_ == other.force_;
  }

  bool operator>(const Force &other) const { return other.force_ < force_; }

  bool operator<=(const Force &other) const {
    return !(other.force_ < force_);
  }

  bool operator>=(const Force &other) const {
    return !(force_ < other.force_);
  }

  bool operator!=(const Force &other) const {
    return !(force_ == other.force_);
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the force.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Force UnknownForce();

  friend Force ForceInNewtons(float);

  explicit Force(float force) : force_(force) {}

  // Stored in Newtons.
  float force_;
};

inline Force ForceInNewtons(float force);

// Returns a force object representing an unknown force.
inline Force UnknownForce() { return Force(); }

// Returns a force object equivalent to the specified force
// expressed in kiloNewtons.
inline Force ForceInKiloNewtons(float force) {
  return ForceInNewtons(force * 1000.0f);
}

// Returns a force object equivalent to the specified force
// expressed in Newtons.
inline Force ForceInNewtons(float force) { return Force(force); }

// Returns a force object equivalent to the specified force
// expressed in milliNewtons.
inline Force ForceInMilliNewtons(float force) {
  return ForceInNewtons(force / 1000.0f);
}

// Returns a force object equivalent to the specified force
// expressed in microNewtons.
inline Force ForceInMicroNewtons(float force) {
  return ForceInNewtons(force / 1000000.0f);
}

inline Force operator+(Force a, Force b) {
  return ForceInNewtons(a.inNewtons() + b.inNewtons());
}

inline Force operator*(Force a, float b) {
  return ForceInNewtons(a.inNewtons() * b);
}

inline Force operator*(float a, Force b) {
  return ForceInNewtons(a * b.inNewtons());
}

inline Force operator/(Force a, float b) {
  return ForceInNewtons(a.inNewtons() / b);
}

inline float operator/(Force a, Force b) {
  return a.inNewtons() / b.inNewtons();
}

}  // namespace roo_quantity