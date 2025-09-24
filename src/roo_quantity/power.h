#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/time.h"
#include "roo_quantity/work.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of power, internally stored as floating-point Watts.
class Power {
 public:
  // Creates a power object representing an 'unknown' power.
  Power() : power_(std::nanf("")) {}

  // Returns the power in gigaWatts.
  float inGigaWatts() const { return power_ / 1000000000.0f; }

  // Returns the power in megaWatts.
  float inMegaWatts() const { return power_ / 1000000.0f; }

  // Returns the power in kiloWatts.
  float inKiloWatts() const { return power_ / 1000.0f; }

  // Returns the power in Watts.
  float inWatts() const { return power_; }

  // Returns the power in milliWatts.
  float inMilliWatts() const { return power_ * 1000.0f; }

  // Returns the power in microWatts.
  float inMicroWatts() const { return power_ * 1000000.0f; }

  // Returns whether the object represents an unknown power.
  bool isUnknown() const { return std::isnan(power_); }

  bool operator<(const Power& other) const { return power_ < other.power_; }

  bool operator==(const Power& other) const { return power_ == other.power_; }

  bool operator>(const Power& other) const { return other.power_ < power_; }

  bool operator<=(const Power& other) const { return !(other.power_ < power_); }

  bool operator>=(const Power& other) const { return !(power_ < other.power_); }

  bool operator!=(const Power& other) const {
    return !(power_ == other.power_);
  }

  inline Power& operator+=(const Power& other) {
    power_ += other.inWatts();
    return *this;
  }

  inline Power& operator-=(const Power& other) {
    power_ -= other.inWatts();
    return *this;
  }

  inline Power& operator*=(float multi) {
    power_ *= multi;
    return *this;
  }

  inline Power& operator/=(float div) {
    power_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the power.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Power UnknownPower();

  friend Power PowerInWatts(float);

  explicit Power(float power) : power_(power) {}

  // Stored in Watts.
  float power_;
};

inline Power PowerInWatts(float power);

// Returns a power object representing an unknown power.
inline Power UnknownPower() { return Power(); }

// Returns a power object equivalent to the specified power
// expressed in gigaWatts.
inline Power PowerInGigaWatts(float power) {
  return PowerInWatts(power * 1000000000.0f);
}

// Returns a power object equivalent to the specified power
// expressed in megaWatts.
inline Power PowerInMegaWatts(float power) {
  return PowerInWatts(power * 1000000.0f);
}

// Returns a power object equivalent to the specified power
// expressed in kiloWatts.
inline Power PowerInKiloWatts(float power) {
  return PowerInWatts(power * 1000.0f);
}

// Returns a power object equivalent to the specified power
// expressed in Watts.
inline Power PowerInWatts(float power) { return Power(power); }

// Returns a power object equivalent to the specified power
// expressed in milliWatts.
inline Power PowerInMilliWatts(float power) {
  return PowerInWatts(power * 0.001f);
}

// Returns a power object equivalent to the specified power
// expressed in microWatts.
inline Power PowerInMicroWatts(float power) {
  return PowerInWatts(power * 0.000001f);
}

inline Power operator+(Power a, Power b) {
  return PowerInWatts(a.inWatts() + b.inWatts());
}

inline Power operator-(Power a, Power b) {
  return PowerInWatts(a.inWatts() - b.inWatts());
}

inline Power operator-(Power a) { return PowerInWatts(-a.inWatts()); }

inline Power operator*(Power a, float b) {
  return PowerInWatts(a.inWatts() * b);
}

inline Power operator*(float a, Power b) {
  return PowerInWatts(a * b.inWatts());
}

inline Power operator/(Power a, float b) {
  return PowerInWatts(a.inWatts() / b);
}

inline float operator/(Power a, Power b) { return a.inWatts() / b.inWatts(); }

// Power vs work.

inline Work operator*(Power a, Time b) {
  return WorkInJoules(a.inWatts() * b.inSeconds());
}

inline Work operator*(Time a, Power b) {
  return WorkInJoules(a.inSeconds() * b.inWatts());
}

inline Power operator/(Work w, Time b) {
  return PowerInWatts(w.inJoules() / b.inSeconds());
}

inline Time operator/(Work w, Power b) {
  return TimeInSeconds(w.inJoules() / b.inWatts());
}

}  // namespace roo_quantity