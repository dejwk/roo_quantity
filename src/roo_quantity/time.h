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

// Representation of elapsed, internally stored as floating-point seconds.
class Time {
 public:
  // Creates a time object representing an 'unknown' time.
  Time() : time_(std::nanf("")) {}

  // Returns the time in seconds.
  float inSeconds() const { return time_; }

  // Returns the time in milliseconds.
  float inMilliseconds() const { return time_ * 1000.0f; }

  // Returns the time in microseconds.
  float inMicroseconds() const { return time_ * 1000000.0f; }

  // Returns the time in nanoseconds.
  float inNanoseconds() const { return time_ * 1000000000.0f; }

  // Returns whether the object represents an unknown time.
  bool isUnknown() const { return std::isnan(time_); }

  bool operator<(const Time &other) const { return time_ < other.time_; }

  bool operator==(const Time &other) const {
    return time_ == other.time_;
  }

  bool operator>(const Time &other) const { return other.time_ < time_; }

  bool operator<=(const Time &other) const {
    return !(other.time_ < time_);
  }

  bool operator>=(const Time &other) const {
    return !(time_ < other.time_);
  }

  bool operator!=(const Time &other) const {
    return !(time_ == other.time_);
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the time.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Time UnknownTime();

  friend Time TimeInSeconds(float);

  explicit Time(float time) : time_(time) {}

  // Stored in seconds.
  float time_;
};

inline Time TimeInSeconds(float time);

// Returns a time object representing an unknown time.
inline Time UnknownTime() { return Time(); }

// Returns a time object equivalent to the specified time
// expressed in seconds.
inline Time TimeInSeconds(float time) { return Time(time); }

// Returns a time object equivalent to the specified time
// expressed in milliseconds.
inline Time TimeInMilliseconds(float time) {
  return TimeInSeconds(time * 0.001f);
}

// Returns a time object equivalent to the specified time
// expressed in microseconds.
inline Time TimeInMicroseconds(float time) {
  return TimeInSeconds(time * 0.000001f);
}

// Returns a time object equivalent to the specified time
// expressed in nanoseconds.
inline Time TimeInNanoseconds(float time) {
  return TimeInSeconds(time * 0.000000001f);
}

inline Time operator+(Time a, Time b) {
  return TimeInSeconds(a.inSeconds() + b.inSeconds());
}

inline Time operator*(Time a, float b) {
  return TimeInSeconds(a.inSeconds() * b);
}

inline Time operator*(float a, Time b) {
  return TimeInSeconds(a * b.inSeconds());
}

inline Time operator/(Time a, float b) {
  return TimeInSeconds(a.inSeconds() / b);
}

inline float operator/(Time a, Time b) {
  return a.inSeconds() / b.inSeconds();
}

}  // namespace roo_quantity