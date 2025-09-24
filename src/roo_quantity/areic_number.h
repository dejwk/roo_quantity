#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/area.h"
#include "roo_quantity/lineic_number.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of areic number, a reciprocal of area, internally
// stored as floating-point units per square meter.
class AreicNumber {
 public:
  // Creates an areic number object representing an 'unknown'
  // areic number.
  AreicNumber() : areic_number_(std::nanf("")) {}

  // Returns the areic number in GigaUnitsPerSquareMeter.
  float inGigaUnitsPerSquareMeter() const {
    return areic_number_ * 0.000000001f;
  }

  // Returns the areic number in Mega-units per square meter.
  float inMegaUnitsPerSquareMeter() const { return areic_number_ * 0.000001f; }

  // Returns the areic number in kilo-units per square meter.
  float inKiloUnitsPerSquareMeter() const { return areic_number_ * 0.001f; }

  // Returns the areic number in units per square meter.
  float inUnitsPerSquareMeter() const { return areic_number_; }

  // Returns the areic number in milli-units per square meter.
  float inMilliUnitsPerSquareMeter() const { return areic_number_ * 1000.0f; }

  // Returns the areic number in micro-units per square meter.
  float inMicroUnitsPerSquareMeter() const {
    return areic_number_ * 1000000.0f;
  }

  // Returns the areic number in units per square centimeter.
  float inUnitsPerSquareCentimeter() const { return areic_number_ * 0.0001f; }

  // Returns the areic number in units per square millimeter.
  float inUnitsPerSquareMillimeter() const { return areic_number_ * 0.000001f; }

  // Returns the areic number in units per square kilometer.
  float inUnitsPerSquareKilometer() const { return areic_number_ * 1000000.0f; }

  // Returns the areic number in units per square inch.
  float inUnitsPerSquareInch() const { return areic_number_ * 0.00064516f; }

  // Returns the areic number in units per square foot.
  float inUnitsPerSquareFoot() const { return areic_number_ * 0.09290304f; }

  // Returns the areic number in units per square yard.
  float inUnitsPerSquareYard() const { return areic_number_ * 0.83612736f; }

  // Returns whether the object represents an unknown areic number.
  bool isUnknown() const { return std::isnan(areic_number_); }

  bool operator<(const AreicNumber &other) const {
    return areic_number_ < other.areic_number_;
  }

  bool operator==(const AreicNumber &other) const {
    return areic_number_ == other.areic_number_;
  }

  bool operator>(const AreicNumber &other) const {
    return other.areic_number_ < areic_number_;
  }

  bool operator<=(const AreicNumber &other) const {
    return !(other.areic_number_ < areic_number_);
  }

  bool operator>=(const AreicNumber &other) const {
    return !(areic_number_ < other.areic_number_);
  }

  bool operator!=(const AreicNumber &other) const {
    return !(areic_number_ == other.areic_number_);
  }

  AreicNumber &operator*=(float multi) {
    areic_number_ *= multi;
    return *this;
  }

  AreicNumber &operator/=(float div) {
    areic_number_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the areic number.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend AreicNumber UnknownAreicNumber();

  friend AreicNumber AreicNumberInUnitsPerSquareMeter(float);

  explicit AreicNumber(float areic_number) : areic_number_(areic_number) {}

  // Stored in units per square meter.
  float areic_number_;
};

inline AreicNumber AreicNumberInUnitsPerSquareMeter(float areic_number);

// Returns a areic number object representing an unknown
// areic number.
inline AreicNumber UnknownAreicNumber() { return AreicNumber(); }

// Returns a areic number object equivalent to the specified
// areic number expressed in giga-units per square meter.
inline AreicNumber AreicNumberInGigaUnitsPerSquareMeter(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 1000000000.0f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in mega-units per square meter.
inline AreicNumber AreicNumberInMegaUnitsPerSquareMeter(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 1000000.0f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in kilo-units per square meter.
inline AreicNumber AreicNumberInKiloUnitsPerSquareMeter(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 1000.0f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in units per square meter.
inline AreicNumber AreicNumberInUnitsPerSquareMeter(float areic_number) {
  return AreicNumber(areic_number);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in milli-units per square meter.
inline AreicNumber AreicNumberInMilliUnitsPerSquareMeter(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 0.001f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in micro-units per square meter.
inline AreicNumber AreicNumberInMicroUnitsPerSquareMeter(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 0.000001f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in units per square centimeter.
inline AreicNumber AreicNumberInUnitsPerSquareCentimeter(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 10000.0f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in units per square millimeter.
inline AreicNumber AreicNumberInUnitsPerSquareMillimeter(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 1000000.0f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in units per square kilometer.
inline AreicNumber AreicNumberInUnitsPerSquareKilometer(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 0.000001f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in units per square inch.
inline AreicNumber AreicNumberInUnitsPerSquareInch(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 1550.0031000062f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in units per square foot.
inline AreicNumber AreicNumberInUnitsPerSquareFoot(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 10.7639104167f);
}

// Returns a areic number object equivalent to the specified
// areic number expressed in units per square yard.
inline AreicNumber AreicNumberInUnitsPerSquareYard(float areic_number) {
  return AreicNumberInUnitsPerSquareMeter(areic_number * 1.1959900463f);
}

inline AreicNumber operator*(AreicNumber a, float b) {
  return AreicNumberInUnitsPerSquareMeter(a.inUnitsPerSquareMeter() * b);
}

inline AreicNumber operator*(float a, AreicNumber b) {
  return AreicNumberInUnitsPerSquareMeter(a * b.inUnitsPerSquareMeter());
}

inline float operator*(Area a, AreicNumber b) {
  return a.inSquareMeters() * b.inUnitsPerSquareMeter();
}

inline float operator*(AreicNumber a, Area b) {
  return a.inUnitsPerSquareMeter() * b.inSquareMeters();
}

inline LineicNumber operator*(Length a, AreicNumber b) {
  return LineicNumberInUnitsPerMeter(a.inMeters() * b.inUnitsPerSquareMeter());
}

inline LineicNumber operator*(AreicNumber a, Length b) {
  return LineicNumberInUnitsPerMeter(a.inUnitsPerSquareMeter() * b.inMeters());
}

inline AreicNumber operator/(AreicNumber a, float b) {
  return AreicNumberInUnitsPerSquareMeter(a.inUnitsPerSquareMeter() / b);
}

inline float operator/(AreicNumber a, AreicNumber b) {
  return a.inUnitsPerSquareMeter() / b.inUnitsPerSquareMeter();
}

inline Area operator/(float a, AreicNumber b) {
  return AreaInSquareMeters(a / b.inUnitsPerSquareMeter());
}

inline AreicNumber operator/(float a, Area b) {
  return AreicNumberInUnitsPerSquareMeter(a / b.inSquareMeters());
}

}  // namespace roo_quantity