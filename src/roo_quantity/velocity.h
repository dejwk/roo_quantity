#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/length.h"
#include "roo_quantity/time.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of velocity, internally stored as floating-point meters per
// second.
class Velocity {
 public:
  // Creates a velocity object representing an 'unknown' velocity.
  Velocity() : velocity_(std::nanf("")) {}

  // Returns the velocity in kilometers per second.
  float inKilometersPerSecond() const { return velocity_ * 0.001f; }

  // Returns the velocity in kilometers per hour.
  float inKilometersPerHour() const { return velocity_ * 3.6f; }

  // Returns the velocity in kilometers per hour.
  float inKph() const { return inKilometersPerHour(); }

  // Returns the velocity in meters per second.
  float inMetersPerSecond() const { return velocity_; }

  // Returns the velocity in millimeters per second.
  float inMillimetersPerSecond() const { return velocity_ * 1000.0f; }

  // Returns the velocity in micrometers per second.
  float inMicrometersPerSecond() const { return velocity_ * 1000000.0f; }

  // Returns the velocity in miles per hour.
  float inMilesPerHour() const { return velocity_ * 2.2369362921f; }

  // Returns the velocity in miles per hour.
  float inMph() const { return inMilesPerHour(); }

  float inKnots() const { return velocity_ * 1.9438444924f; }

  // Returns whether the object represents an unknown velocity.
  bool isUnknown() const { return std::isnan(velocity_); }

  bool operator<(const Velocity& other) const {
    return velocity_ < other.velocity_;
  }

  bool operator==(const Velocity& other) const {
    return velocity_ == other.velocity_;
  }

  bool operator>(const Velocity& other) const {
    return other.velocity_ < velocity_;
  }

  bool operator<=(const Velocity& other) const {
    return !(other.velocity_ < velocity_);
  }

  bool operator>=(const Velocity& other) const {
    return !(velocity_ < other.velocity_);
  }

  bool operator!=(const Velocity& other) const {
    return !(velocity_ == other.velocity_);
  }

  inline Velocity& operator+=(const Velocity& other) {
    velocity_ += other.inMetersPerSecond();
    return *this;
  }

  inline Velocity& operator-=(const Velocity& other) {
    velocity_ -= other.inMetersPerSecond();
    return *this;
  }

  inline Velocity& operator*=(float multi) {
    velocity_ *= multi;
    return *this;
  }

  inline Velocity& operator/=(float div) {
    velocity_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the velocity.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Velocity UnknownVelocity();

  friend Velocity VelocityInMetersPerSecond(float);

  explicit Velocity(float velocity) : velocity_(velocity) {}

  // Stored in MetersPerSecond.
  float velocity_;
};

inline Velocity VelocityInMetersPerSecond(float velocity);

// Returns a velocity object representing an unknown velocity.
inline Velocity UnknownVelocity() { return Velocity(); }

// Returns a velocity object equivalent to the specified velocity
// expressed in kilometers per second.
inline Velocity VelocityInKilometersPerSecond(float velocity) {
  return VelocityInMetersPerSecond(velocity * 1000.0f);
}

// Returns a velocity object equivalent to the specified velocity
// expressed in meters per second.
inline Velocity VelocityInMetersPerSecond(float velocity) {
  return Velocity(velocity);
}

// Returns a velocity object equivalent to the specified velocity
// expressed in millimeters per second.
inline Velocity VelocityInMillimetersPerSecond(float velocity) {
  return VelocityInMetersPerSecond(velocity * 0.001f);
}

// Returns a velocity object equivalent to the specified velocity
// expressed in micrometers per second.
inline Velocity VelocityInMicrometersPerSecond(float velocity) {
  return VelocityInMetersPerSecond(velocity * 0.000001f);
}

// Returns a velocity object equivalent to the specified velocity
// expressed in kilometers per hour.
inline Velocity VelocityInKilometersPerHour(float velocity) {
  return VelocityInMetersPerSecond(velocity * 0.2777777778f);
}

inline Velocity VelocityInKph(float velocity) {
  return VelocityInKilometersPerHour(velocity);
}

// Returns a velocity object equivalent to the specified velocity
// expressed in miles per hour.
inline Velocity VelocityInMilesPerHour(float velocity) {
  return VelocityInMetersPerSecond(velocity * 0.44704f);
}

inline Velocity VelocityInMph(float velocity) {
  return VelocityInMilesPerHour(velocity);
}

inline Velocity operator+(Velocity a, Velocity b) {
  return VelocityInMetersPerSecond(a.inMetersPerSecond() +
                                   b.inMetersPerSecond());
}

inline Velocity operator-(Velocity a, Velocity b) {
  return VelocityInMetersPerSecond(a.inMetersPerSecond() -
                                   b.inMetersPerSecond());
}

inline Velocity operator-(Velocity a) {
  return VelocityInMetersPerSecond(-a.inMetersPerSecond());
}

inline Velocity operator*(Velocity a, float b) {
  return VelocityInMetersPerSecond(a.inMetersPerSecond() * b);
}

inline Velocity operator*(float a, Velocity b) {
  return VelocityInMetersPerSecond(a * b.inMetersPerSecond());
}

inline Velocity operator/(Velocity a, float b) {
  return VelocityInMetersPerSecond(a.inMetersPerSecond() / b);
}

inline float operator/(Velocity a, Velocity b) {
  return a.inMetersPerSecond() / b.inMetersPerSecond();
}

// Vs time.

inline Length operator*(Velocity a, Time b) {
  return LengthInMeters(a.inMetersPerSecond() * b.inSeconds());
}

inline Length operator*(Time a, Velocity b) {
  return LengthInMeters(a.inSeconds() * b.inMetersPerSecond());
}

inline Velocity operator/(Length a, Time b) {
  return VelocityInMetersPerSecond(a.inMeters() / b.inSeconds());
}

inline Time operator/(Length a, Velocity b) {
  return TimeInSeconds(a.inMeters() / b.inMetersPerSecond());
}

}  // namespace roo_quantity