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

// Representation of length, internally stored as floating-point meters.
class Length {
 public:
  // Creates a length object representing an 'unknown' length.
  Length() : length_(std::nanf("")) {}

  // Returns the length in kilometers.
  float inKilometers() const { return length_ * 0.001f; }

  // Returns the length in meters.
  float inMeters() const { return length_; }

  // Returns the length in decimeters.
  float inDecimeters() const { return length_ * 10.0f; }

  // Returns the length in centimeters.
  float inCentimeters() const { return length_ * 100.0f; }

  // Returns the length in millimeters.
  float inMillimeters() const { return length_ * 1000.0f; }

  // Returns the length in micrometers.
  float inMicrometers() const { return length_ * 1000000.0f; }

  // Returns the length in nanometers.
  float inNanometers() const { return length_ * 1000000000.0f; }

  // Returns the length in inches.
  float inInches() const { return length_ * 39.37007874f; }

  // Returns the length in feet.
  float inFeet() const { return length_ * 3.280839895f; }

  // Returns the length in yards.
  float inYards() const { return length_ * 1.0936132983f; }

  // Returns the length in light years.
  float inLightYears() const { return length_ * 1.057000834E-16f; }

  // Returns whether the object represents an unknown length.
  bool isUnknown() const { return std::isnan(length_); }

  bool operator<(const Length& other) const { return length_ < other.length_; }

  bool operator==(const Length& other) const {
    return length_ == other.length_;
  }

  bool operator>(const Length& other) const { return other.length_ < length_; }

  bool operator<=(const Length& other) const {
    return !(other.length_ < length_);
  }

  bool operator>=(const Length& other) const {
    return !(length_ < other.length_);
  }

  bool operator!=(const Length& other) const {
    return !(length_ == other.length_);
  }

  inline Length& operator+=(const Length& other) {
    length_ += other.inMeters();
    return *this;
  }

  inline Length& operator-=(const Length& other) {
    length_ -= other.inMeters();
    return *this;
  }

  inline Length& operator*=(float multi) {
    length_ *= multi;
    return *this;
  }

  inline Length& operator/=(float div) {
    length_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the length.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Length UnknownLength();

  friend Length LengthInMeters(float);

  explicit Length(float length) : length_(length) {}

  // Stored in meters.
  float length_;
};

inline Length LengthInMeters(float length);

// Returns a length object representing an unknown length.
inline Length UnknownLength() { return Length(); }

// Returns a length object equivalent to the specified length
// expressed in kilometers.
inline Length LengthInKilometers(float length) {
  return LengthInMeters(length * 1000.0f);
}

// Returns a length object equivalent to the specified length
// expressed in meters.
inline Length LengthInMeters(float length) { return Length(length); }

// Returns a length object equivalent to the specified length
// expressed in centimeters.
inline Length LengthInDecimeters(float length) {
  return LengthInMeters(length * 0.1f);
}

// Returns a length object equivalent to the specified length
// expressed in centimeters.
inline Length LengthInCentimeters(float length) {
  return LengthInMeters(length * 0.01f);
}

// Returns a length object equivalent to the specified length
// expressed in millimeters.
inline Length LengthInMillimeters(float length) {
  return LengthInMeters(length * 0.001f);
}

// Returns a length object equivalent to the specified length
// expressed in micrometers.
inline Length LengthInMicrometers(float length) {
  return LengthInMeters(length * 0.000001f);
}

// Returns a length object equivalent to the specified length
// expressed in nanometers.
inline Length LengthInNanometers(float length) {
  return LengthInMeters(length * 0.000000001f);
}

// Returns a length object equivalent to the specified length
// expressed in inches.
inline Length LengthInInches(float length) {
  return LengthInMeters(length * 0.0254f);
}

// Returns a length object equivalent to the specified length
// expressed in feet.
inline Length LengthInFeet(float length) {
  return LengthInMeters(length * 0.3048f);
}

// Returns a length object equivalent to the specified length
// expressed in yards.
inline Length LengthInYards(float length) {
  return LengthInMeters(length * 0.9144f);
}

// Returns a length object equivalent to the specified length
// expressed in light years.
inline Length LengthInLightYears(float length) {
  return LengthInMeters(length * 9460730472580044.0f);
}

inline Length operator+(Length a, Length b) {
  return LengthInMeters(a.inMeters() + b.inMeters());
}

inline Length operator-(Length a, Length b) {
  return LengthInMeters(a.inMeters() - b.inMeters());
}

inline Length operator-(Length a) { return LengthInMeters(-a.inMeters()); }

inline Length operator*(Length a, float b) {
  return LengthInMeters(a.inMeters() * b);
}

inline Length operator*(float a, Length b) {
  return LengthInMeters(a * b.inMeters());
}

inline Length operator/(Length a, float b) {
  return LengthInMeters(a.inMeters() / b);
}

inline float operator/(Length a, Length b) {
  return a.inMeters() / b.inMeters();
}

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Length& val);

}  // namespace roo_quantity