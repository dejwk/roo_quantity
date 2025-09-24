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

// Representation of linear_number_density, a reciprocal of length, internally
// stored as floating-point units per meter.
class LinearNumberDensity {
 public:
  // Creates a linear number density object representing an 'unknown'
  // linear number density.
  LinearNumberDensity() : linear_number_density_(std::nanf("")) {}

  // Returns the linear number density in GigaUnitsPerMeter.
  float inGigaUnitsPerMeter() const {
    return linear_number_density_ * 0.000000001f;
  }

  // Returns the linear number density in Mega-units per meter.
  float inMegaUnitsPerMeter() const {
    return linear_number_density_ * 0.000001f;
  }

  // Returns the linear number density in kilo-units per meter.
  float inKiloUnitsPerMeter() const { return linear_number_density_ * 0.001f; }

  // Returns the linear number density in units per meter.
  float inUnitsPerMeter() const { return linear_number_density_; }

  // Returns the linear number density in milli-units per meter.
  float inMilliUnitsPerMeter() const {
    return linear_number_density_ * 1000.0f;
  }

  // Returns the linear number density in micro-units per meter.
  float inMicroUnitsPerMeter() const {
    return linear_number_density_ * 1000000.0f;
  }

  // Returns the linear number density in units per centimeter.
  float inUnitsPerCentimeter() const { return linear_number_density_ * 0.01f; }

  // Returns the linear number density in units per millimeter.
  float inUnitsPerMillimeter() const { return linear_number_density_ * 0.001f; }

  // Returns the linear number density in units per kilometer.
  float inUnitsPerKilometer() const { return linear_number_density_ * 1000.0f; }

  // Returns the linear number density in units per inch (DPI).
  float inUnitsPerInch() const { return linear_number_density_ * 0.0254f; }

  // Returns the linear number density in units per inch (DPI).
  float inDPI() const { return inUnitsPerInch(); }

  // Returns the linear number density in units per foot.
  float inUnitsPerFoot() const { return linear_number_density_ * 0.3048f; }

  // Returns the linear number density in units per yard.
  float inUnitsPerYard() const { return linear_number_density_ * 0.9144f; }

  // Returns whether the object represents an unknown linear number density.
  bool isUnknown() const { return std::isnan(linear_number_density_); }

  bool operator<(const LinearNumberDensity &other) const {
    return linear_number_density_ < other.linear_number_density_;
  }

  bool operator==(const LinearNumberDensity &other) const {
    return linear_number_density_ == other.linear_number_density_;
  }

  bool operator>(const LinearNumberDensity &other) const {
    return other.linear_number_density_ < linear_number_density_;
  }

  bool operator<=(const LinearNumberDensity &other) const {
    return !(other.linear_number_density_ < linear_number_density_);
  }

  bool operator>=(const LinearNumberDensity &other) const {
    return !(linear_number_density_ < other.linear_number_density_);
  }

  bool operator!=(const LinearNumberDensity &other) const {
    return !(linear_number_density_ == other.linear_number_density_);
  }

  LinearNumberDensity &operator*=(float multi) {
    linear_number_density_ *= multi;
    return *this;
  }

  LinearNumberDensity &operator/=(float div) {
    linear_number_density_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the linear number density.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend LinearNumberDensity UnknownLinearNumberDensity();

  friend LinearNumberDensity LinearNumberDensityInUnitsPerMeter(float);

  explicit LinearNumberDensity(float linear_number_density)
      : linear_number_density_(linear_number_density) {}

  // Stored in units per meter.
  float linear_number_density_;
};

inline LinearNumberDensity LinearNumberDensityInUnitsPerMeter(
    float linear_number_density);

// Returns a linear number density object representing an unknown
// linear number density.
inline LinearNumberDensity UnknownLinearNumberDensity() {
  return LinearNumberDensity();
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in giga-units per meter.
inline LinearNumberDensity LinearNumberDensityInGigaUnitsPerMeter(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density *
                                            1000000000.0f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in mega-units per meter.
inline LinearNumberDensity LinearNumberDensityInMegaUnitsPerMeter(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density * 1000000.0f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in kilo-units per meter.
inline LinearNumberDensity LinearNumberDensityInKiloUnitsPerMeter(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density * 1000.0f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in units per meter.
inline LinearNumberDensity LinearNumberDensityInUnitsPerMeter(
    float linear_number_density) {
  return LinearNumberDensity(linear_number_density);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in milli-units per meter.
inline LinearNumberDensity LinearNumberDensityInMilliUnitsPerMeter(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density * 0.001f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in micro-units per meter.
inline LinearNumberDensity LinearNumberDensityInMicroUnitsPerMeter(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density * 0.000001f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in units per centimeter.
inline LinearNumberDensity LinearNumberDensityInUnitsPerCentimeter(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density * 100.0f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in units per millimeter.
inline LinearNumberDensity LinearNumberDensityInUnitsPerMillimeter(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density * 1000.0f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in units per kilometer.
inline LinearNumberDensity LinearNumberDensityInUnitsPerKilometer(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density * 0.001f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in units per inch.
inline LinearNumberDensity LinearNumberDensityInUnitsPerInch(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density *
                                            39.37007874f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in units per foot.
inline LinearNumberDensity LinearNumberDensityInUnitsPerFoot(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density *
                                            3.280839895f);
}

// Returns a linear number density object equivalent to the specified
// linear number density expressed in units per yard.
inline LinearNumberDensity LinearNumberDensityInUnitsPerYard(
    float linear_number_density) {
  return LinearNumberDensityInUnitsPerMeter(linear_number_density *
                                            1.0936132983f);
}

inline LinearNumberDensity operator*(LinearNumberDensity a, float b) {
  return LinearNumberDensityInUnitsPerMeter(a.inUnitsPerMeter() * b);
}

inline LinearNumberDensity operator*(float a, LinearNumberDensity b) {
  return LinearNumberDensityInUnitsPerMeter(a * b.inUnitsPerMeter());
}

inline float operator*(Length a, LinearNumberDensity b) {
  return a.inMeters() * b.inUnitsPerMeter();
}

inline float operator*(LinearNumberDensity a, Length b) {
  return a.inUnitsPerMeter() * b.inMeters();
}

inline LinearNumberDensity operator/(LinearNumberDensity a, float b) {
  return LinearNumberDensityInUnitsPerMeter(a.inUnitsPerMeter() / b);
}

inline float operator/(LinearNumberDensity a, LinearNumberDensity b) {
  return a.inUnitsPerMeter() / b.inUnitsPerMeter();
}

inline Length operator/(float a, LinearNumberDensity b) {
  return LengthInMeters(a / b.inUnitsPerMeter());
}

inline LinearNumberDensity operator/(float a, Length b) {
  return LinearNumberDensityInUnitsPerMeter(a / b.inMeters());
}

}  // namespace roo_quantity