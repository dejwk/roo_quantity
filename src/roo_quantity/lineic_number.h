#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/length.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of lineic number, a reciprocal of length, internally
// stored as floating-point units per meter.
class LineicNumber {
 public:
  // Creates a lineic number object representing an 'unknown'
  // lineic number.
  LineicNumber() : lineic_number_(std::nanf("")) {}

  // Returns the lineic number in GigaUnitsPerMeter.
  float inGigaUnitsPerMeter() const { return lineic_number_ * 0.000000001f; }

  // Returns the lineic number in Mega-units per meter.
  float inMegaUnitsPerMeter() const { return lineic_number_ * 0.000001f; }

  // Returns the lineic number in kilo-units per meter.
  float inKiloUnitsPerMeter() const { return lineic_number_ * 0.001f; }

  // Returns the lineic number in units per meter.
  float inUnitsPerMeter() const { return lineic_number_; }

  // Returns the lineic number in milli-units per meter.
  float inMilliUnitsPerMeter() const { return lineic_number_ * 1000.0f; }

  // Returns the lineic number in micro-units per meter.
  float inMicroUnitsPerMeter() const { return lineic_number_ * 1000000.0f; }

  // Returns the lineic number in units per centimeter.
  float inUnitsPerCentimeter() const { return lineic_number_ * 0.01f; }

  // Returns the lineic number in units per millimeter.
  float inUnitsPerMillimeter() const { return lineic_number_ * 0.001f; }

  // Returns the lineic number in units per kilometer.
  float inUnitsPerKilometer() const { return lineic_number_ * 1000.0f; }

  // Returns the lineic number in units per inch (DPI).
  float inUnitsPerInch() const { return lineic_number_ * 0.0254f; }

  // Returns the lineic number in units per inch (DPI).
  float inDPI() const { return inUnitsPerInch(); }

  // Returns the lineic number in units per foot.
  float inUnitsPerFoot() const { return lineic_number_ * 0.3048f; }

  // Returns the lineic number in units per yard.
  float inUnitsPerYard() const { return lineic_number_ * 0.9144f; }

  // Returns whether the object represents an unknown lineic number.
  bool isUnknown() const { return std::isnan(lineic_number_); }

  bool operator<(const LineicNumber &other) const {
    return lineic_number_ < other.lineic_number_;
  }

  bool operator==(const LineicNumber &other) const {
    return lineic_number_ == other.lineic_number_;
  }

  bool operator>(const LineicNumber &other) const {
    return other.lineic_number_ < lineic_number_;
  }

  bool operator<=(const LineicNumber &other) const {
    return !(other.lineic_number_ < lineic_number_);
  }

  bool operator>=(const LineicNumber &other) const {
    return !(lineic_number_ < other.lineic_number_);
  }

  bool operator!=(const LineicNumber &other) const {
    return !(lineic_number_ == other.lineic_number_);
  }

  LineicNumber &operator*=(float multi) {
    lineic_number_ *= multi;
    return *this;
  }

  LineicNumber &operator/=(float div) {
    lineic_number_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the lineic number.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend LineicNumber UnknownLineicNumber();

  friend LineicNumber LineicNumberInUnitsPerMeter(float);

  explicit LineicNumber(float lineic_number) : lineic_number_(lineic_number) {}

  // Stored in units per meter.
  float lineic_number_;
};

inline LineicNumber LineicNumberInUnitsPerMeter(float lineic_number);

// Returns a lineic number object representing an unknown
// lineic number.
inline LineicNumber UnknownLineicNumber() { return LineicNumber(); }

// Returns a lineic number object equivalent to the specified
// lineic number expressed in giga-units per meter.
inline LineicNumber LineicNumberInGigaUnitsPerMeter(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 1000000000.0f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in mega-units per meter.
inline LineicNumber LineicNumberInMegaUnitsPerMeter(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 1000000.0f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in kilo-units per meter.
inline LineicNumber LineicNumberInKiloUnitsPerMeter(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 1000.0f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in units per meter.
inline LineicNumber LineicNumberInUnitsPerMeter(float lineic_number) {
  return LineicNumber(lineic_number);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in milli-units per meter.
inline LineicNumber LineicNumberInMilliUnitsPerMeter(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 0.001f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in micro-units per meter.
inline LineicNumber LineicNumberInMicroUnitsPerMeter(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 0.000001f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in units per centimeter.
inline LineicNumber LineicNumberInUnitsPerCentimeter(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 100.0f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in units per millimeter.
inline LineicNumber LineicNumberInUnitsPerMillimeter(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 1000.0f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in units per kilometer.
inline LineicNumber LineicNumberInUnitsPerKilometer(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 0.001f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in units per inch.
inline LineicNumber LineicNumberInUnitsPerInch(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 39.37007874f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in units per foot.
inline LineicNumber LineicNumberInUnitsPerFoot(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 3.280839895f);
}

// Returns a lineic number object equivalent to the specified
// lineic number expressed in units per yard.
inline LineicNumber LineicNumberInUnitsPerYard(float lineic_number) {
  return LineicNumberInUnitsPerMeter(lineic_number * 1.0936132983f);
}

inline LineicNumber operator*(LineicNumber a, float b) {
  return LineicNumberInUnitsPerMeter(a.inUnitsPerMeter() * b);
}

inline LineicNumber operator*(float a, LineicNumber b) {
  return LineicNumberInUnitsPerMeter(a * b.inUnitsPerMeter());
}

inline float operator*(Length a, LineicNumber b) {
  return a.inMeters() * b.inUnitsPerMeter();
}

inline float operator*(LineicNumber a, Length b) {
  return a.inUnitsPerMeter() * b.inMeters();
}

inline LineicNumber operator/(LineicNumber a, float b) {
  return LineicNumberInUnitsPerMeter(a.inUnitsPerMeter() / b);
}

inline float operator/(LineicNumber a, LineicNumber b) {
  return a.inUnitsPerMeter() / b.inUnitsPerMeter();
}

inline Length operator/(float a, LineicNumber b) {
  return LengthInMeters(a / b.inUnitsPerMeter());
}

inline LineicNumber operator/(float a, Length b) {
  return LineicNumberInUnitsPerMeter(a / b.inMeters());
}

}  // namespace roo_quantity