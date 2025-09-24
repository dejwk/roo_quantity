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

// Representation of linear_density, internally stored as floating-point
// units per meter.
class LinearDensity {
 public:
  // Creates a linear_density object representing an 'unknown' linear_density.
  LinearDensity() : linear_density_(std::nanf("")) {}

  // Returns the linear_density in GigaUnitsPerMeter.
  float inGigaUnitsPerMeter() const { return linear_density_ * 0.000000001f; }

  // Returns the linear_density in Mega-units per meter.
  float inMegaUnitsPerMeter() const { return linear_density_ * 0.000001f; }

  // Returns the linear_density in kilo-units per meter.
  float inKiloUnitsPerMeter() const { return linear_density_ * 0.001f; }

  // Returns the linear_density in units per meter.
  float inUnitsPerMeter() const { return linear_density_; }

  // Returns the linear_density in milli-units per meter.
  float inMilliUnitsPerMeter() const { return linear_density_ * 1000.0f; }

  // Returns the linear_density in micro-units per meter.
  float inMicroUnitsPerMeter() const { return linear_density_ * 1000000.0f; }

  // Returns the linear_density in units per centimeter.
  float inUnitsPerCentimeter() const { return linear_density_ * 0.01f; }

  // Returns the linear_density in units per millimeter.
  float inUnitsPerMillimeter() const { return linear_density_ * 0.001f; }

  // Returns the linear_density in units per kilometer.
  float inUnitsPerKilometer() const { return linear_density_ * 1000.0f; }

  // Returns the linear_density in units per inch (DPI).
  float inUnitsPerInch() const { return linear_density_ * 0.0254f; }

  // Returns the linear_density in units per inch (DPI).
  float inDPI() const { return inUnitsPerInch(); }

  // Returns the linear_density in units per foot.
  float inUnitsPerFoot() const { return linear_density_ * 0.3048f; }

  // Returns the linear_density in units per yard.
  float inUnitsPerYard() const { return linear_density_ * 0.9144f; }

  // Returns whether the object represents an unknown linear_density.
  bool isUnknown() const { return std::isnan(linear_density_); }

  bool operator<(const LinearDensity &other) const {
    return linear_density_ < other.linear_density_;
  }

  bool operator==(const LinearDensity &other) const {
    return linear_density_ == other.linear_density_;
  }

  bool operator>(const LinearDensity &other) const {
    return other.linear_density_ < linear_density_;
  }

  bool operator<=(const LinearDensity &other) const {
    return !(other.linear_density_ < linear_density_);
  }

  bool operator>=(const LinearDensity &other) const {
    return !(linear_density_ < other.linear_density_);
  }

  bool operator!=(const LinearDensity &other) const {
    return !(linear_density_ == other.linear_density_);
  }

  LinearDensity &operator*=(float multi) {
    linear_density_ *= multi;
    return *this;
  }

  LinearDensity &operator/=(float div) {
    linear_density_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the linear_density.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend LinearDensity UnknownLinearDensity();

  friend LinearDensity LinearDensityInUnitsPerMeter(float);

  explicit LinearDensity(float linear_density)
      : linear_density_(linear_density) {}

  // Stored in UnitsPerMeter.
  float linear_density_;
};

inline LinearDensity LinearDensityInUnitsPerMeter(float linear_density);

// Returns a linear_density object representing an unknown linear_density.
inline LinearDensity UnknownLinearDensity() { return LinearDensity(); }

// Returns a linear_density object equivalent to the specified linear_density
// expressed in giga-units per meter.
inline LinearDensity LinearDensityInGigaUnitsPerMeter(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 1000000000.0f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in mega-units per meter.
inline LinearDensity LinearDensityInMegaUnitsPerMeter(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 1000000.0f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in kilo-units per meter.
inline LinearDensity LinearDensityInKiloUnitsPerMeter(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 1000.0f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in units per meter.
inline LinearDensity LinearDensityInUnitsPerMeter(float linear_density) {
  return LinearDensity(linear_density);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in milli-units per meter.
inline LinearDensity LinearDensityInMilliUnitsPerMeter(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 0.001f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in micro-units per meter.
inline LinearDensity LinearDensityInMicroUnitsPerMeter(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 0.000001f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in units per centimeter.
inline LinearDensity LinearDensityInUnitsPerCentimeter(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 100.0f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in units per millimeter.
inline LinearDensity LinearDensityInUnitsPerMillimeter(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 1000.0f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in units per kilometer.
inline LinearDensity LinearDensityInUnitsPerKilometer(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 0.001f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in units per inch.
inline LinearDensity LinearDensityInUnitsPerInch(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 39.37007874f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in units per foot.
inline LinearDensity LinearDensityInUnitsPerFoot(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 3.280839895f);
}

// Returns a linear_density object equivalent to the specified linear_density
// expressed in units per yard.
inline LinearDensity LinearDensityInUnitsPerYard(float linear_density) {
  return LinearDensityInUnitsPerMeter(linear_density * 1.0936132983f);
}

inline LinearDensity operator*(LinearDensity a, float b) {
  return LinearDensityInUnitsPerMeter(a.inUnitsPerMeter() * b);
}

inline LinearDensity operator*(float a, LinearDensity b) {
  return LinearDensityInUnitsPerMeter(a * b.inUnitsPerMeter());
}

inline float operator*(Length a, LinearDensity b) {
  return a.inMeters() * b.inUnitsPerMeter();
}

inline float operator*(LinearDensity a, Length b) {
  return a.inUnitsPerMeter() * b.inMeters();
}

inline LinearDensity operator/(LinearDensity a, float b) {
  return LinearDensityInUnitsPerMeter(a.inUnitsPerMeter() / b);
}

inline float operator/(LinearDensity a, LinearDensity b) {
  return a.inUnitsPerMeter() / b.inUnitsPerMeter();
}

inline Length operator/(float a, LinearDensity b) {
  return LengthInMeters(a / b.inUnitsPerMeter());
}

inline LinearDensity operator/(float a, Length b) {
  return LinearDensityInUnitsPerMeter(a / b.inMeters());
}

}  // namespace roo_quantity