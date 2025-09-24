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

// Representation of work, internally stored as floating-point Joules.
class Work {
 public:
  // Creates a work object representing an 'unknown' work.
  Work() : work_(std::nanf("")) {}

  // Returns the work in kilojoules.
  float inKiloJoules() const { return work_ / 1000.0f; }

  // Returns the work in joules.
  float inJoules() const { return work_; }

  // Returns the work in millijoules.
  float inMilliJoules() const { return work_ * 1000.0f; }

  // Returns the work in microjoules.
  float inMicroJoules() const { return work_ * 1000000.0f; }

  // Returns whether the object represents an unknown work.
  bool isUnknown() const { return std::isnan(work_); }

  bool operator<(const Work& other) const { return work_ < other.work_; }

  bool operator==(const Work& other) const { return work_ == other.work_; }

  bool operator>(const Work& other) const { return other.work_ < work_; }

  bool operator<=(const Work& other) const { return !(other.work_ < work_); }

  bool operator>=(const Work& other) const { return !(work_ < other.work_); }

  bool operator!=(const Work& other) const { return !(work_ == other.work_); }

  inline Work& operator+=(const Work& other) {
    work_ += other.inJoules();
    return *this;
  }

  inline Work& operator-=(const Work& other) {
    work_ -= other.inJoules();
    return *this;
  }

  inline Work& operator*=(float multi) {
    work_ *= multi;
    return *this;
  }

  inline Work& operator/=(float div) {
    work_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the work.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Work UnknownWork();

  friend Work WorkInJoules(float);

  explicit Work(float work) : work_(work) {}

  // Stored in joules.
  float work_;
};

inline Work WorkInJoules(float work);

// Returns a work object representing an unknown work.
inline Work UnknownWork() { return Work(); }

// Returns a work object equivalent to the specified work
// expressed in gigaJoules.
inline Work WorkInGigaJoules(float work) {
  return WorkInJoules(work * 1000000000.0f);
}

// Returns a work object equivalent to the specified work
// expressed in megaJoules.
inline Work WorkInMegaJoules(float work) {
  return WorkInJoules(work * 1000000.0f);
}

// Returns a work object equivalent to the specified work
// expressed in kiloJoules.
inline Work WorkInKiloJoules(float work) {
  return WorkInJoules(work * 1000.0f);
}

// Returns a work object equivalent to the specified work
// expressed in Joules.
inline Work WorkInJoules(float work) { return Work(work); }

// Returns a work object equivalent to the specified work
// expressed in milliJoules.
inline Work WorkInMilliJoules(float work) {
  return WorkInJoules(work / 1000.0f);
}

// Returns a work object equivalent to the specified work
// expressed in microJoules.
inline Work WorkInMicroJoules(float work) {
  return WorkInJoules(work / 1000000.0f);
}

inline Work operator+(Work a, Work b) {
  return WorkInJoules(a.inJoules() + b.inJoules());
}

inline Work operator-(Work a, Work b) {
  return WorkInJoules(a.inJoules() - b.inJoules());
}

inline Work operator-(Work a) { return WorkInJoules(-a.inJoules()); }

inline Work operator*(Work a, float b) {
  return WorkInJoules(a.inJoules() * b);
}

inline Work operator*(float a, Work b) {
  return WorkInJoules(a * b.inJoules());
}

inline Work operator/(Work a, float b) {
  return WorkInJoules(a.inJoules() / b);
}

inline float operator/(Work a, Work b) { return a.inJoules() / b.inJoules(); }

}  // namespace roo_quantity