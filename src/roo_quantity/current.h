#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/charge.h"
#include "roo_quantity/time.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of current, internally stored as floating-point Amperes.
class Current {
 public:
  // Creates a current object representing an 'unknown' current.
  Current() : current_(std::nanf("")) {}

  // Returns the current in megaAmperes.
  float inMegaAmperes() const { return current_ / 1000000.0f; }

  // Returns the current in kiloAmperes.
  float inKiloAmperes() const { return current_ / 1000.0f; }

  // Returns the current in Amperes.
  float inAmperes() const { return current_; }

  // Returns the current in milliAmperes.
  float inMilliAmperes() const { return current_ * 1000.0f; }

  // Returns the current in microAmperes.
  float inMicroAmperes() const { return current_ * 1000000.0f; }

  // Returns whether the object represents an unknown current.
  bool isUnknown() const { return std::isnan(current_); }

  bool operator<(const Current& other) const {
    return current_ < other.current_;
  }

  bool operator==(const Current& other) const {
    return current_ == other.current_;
  }

  bool operator>(const Current& other) const {
    return other.current_ < current_;
  }

  bool operator<=(const Current& other) const {
    return !(other.current_ < current_);
  }

  bool operator>=(const Current& other) const {
    return !(current_ < other.current_);
  }

  bool operator!=(const Current& other) const {
    return !(current_ == other.current_);
  }

  inline Current& operator+=(const Current& other) {
    current_ += other.inAmperes();
    return *this;
  }

  inline Current& operator-=(const Current& other) {
    current_ -= other.inAmperes();
    return *this;
  }

  inline Current& operator*=(float multi) {
    current_ *= multi;
    return *this;
  }

  inline Current& operator/=(float div) {
    current_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the current.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Current UnknownCurrent();

  friend Current CurrentInAmperes(float);

  explicit Current(float current) : current_(current) {}

  // Stored in Amperes.
  float current_;
};

inline Current CurrentInAmperes(float current);

// Returns a current object representing an unknown current.
inline Current UnknownCurrent() { return Current(); }

// Returns a current object equivalent to the specified current
// expressed in megaAmperes.
inline Current CurrentInMegaAmperes(float current) {
  return CurrentInAmperes(current * 1000000.0f);
}

// Returns a current object equivalent to the specified current
// expressed in kiloAmperes.
inline Current CurrentInKiloAmperes(float current) {
  return CurrentInAmperes(current * 1000.0f);
}

// Returns a current object equivalent to the specified current
// expressed in Amperes.
inline Current CurrentInAmperes(float current) { return Current(current); }

// Returns a current object equivalent to the specified current
// expressed in milliAmperes.
inline Current CurrentInMilliAmperes(float current) {
  return CurrentInAmperes(current * 0.001f);
}

// Returns a current object equivalent to the specified current
// expressed in microAmperes.
inline Current CurrentInMicroAmperes(float current) {
  return CurrentInAmperes(current * 0.000001f);
}

inline Current operator+(Current a, Current b) {
  return CurrentInAmperes(a.inAmperes() + b.inAmperes());
}

inline Current operator-(Current a, Current b) {
  return CurrentInAmperes(a.inAmperes() - b.inAmperes());
}

inline Current operator-(Current a) { return CurrentInAmperes(-a.inAmperes()); }

inline Current operator*(Current a, float b) {
  return CurrentInAmperes(a.inAmperes() * b);
}

inline Current operator*(float a, Current b) {
  return CurrentInAmperes(a * b.inAmperes());
}

inline Current operator/(Current a, float b) {
  return CurrentInAmperes(a.inAmperes() / b);
}

inline float operator/(Current a, Current b) {
  return a.inAmperes() / b.inAmperes();
}

// Vs charge.

inline Charge operator*(Current a, Time b) {
  return ChargeInCoulombs(a.inAmperes() * b.inSeconds());
}

inline Charge operator*(Time a, Current b) {
  return ChargeInCoulombs(a.inSeconds() * b.inAmperes());
}

inline Current operator/(Charge a, Time b) {
  return CurrentInAmperes(a.inCoulombs() / b.inSeconds());
}

inline Time operator/(Charge a, Current b) {
  return TimeInSeconds(a.inCoulombs() / b.inAmperes());
}

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Current& val);

}  // namespace roo_quantity