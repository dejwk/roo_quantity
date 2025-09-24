#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/area.h"
#include "roo_quantity/linear_number_density.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of surface number density, a reciprocal of area, internally
// stored as floating-point units per square meter.
class SurfaceNumberDensity {
 public:
  // Creates a surface number density object representing an 'unknown'
  // surface number density.
  SurfaceNumberDensity() : surface_number_density_(std::nanf("")) {}

  // Returns the surface number density in GigaUnitsPerSquareMeter.
  float inGigaUnitsPerSquareMeter() const {
    return surface_number_density_ * 0.000000001f;
  }

  // Returns the surface number density in Mega-units per square meter.
  float inMegaUnitsPerSquareMeter() const {
    return surface_number_density_ * 0.000001f;
  }

  // Returns the surface number density in kilo-units per square meter.
  float inKiloUnitsPerSquareMeter() const {
    return surface_number_density_ * 0.001f;
  }

  // Returns the surface number density in units per square meter.
  float inUnitsPerSquareMeter() const { return surface_number_density_; }

  // Returns the surface number density in milli-units per square meter.
  float inMilliUnitsPerSquareMeter() const {
    return surface_number_density_ * 1000.0f;
  }

  // Returns the surface number density in micro-units per square meter.
  float inMicroUnitsPerSquareMeter() const {
    return surface_number_density_ * 1000000.0f;
  }

  // Returns the surface number density in units per square centimeter.
  float inUnitsPerSquareCentimeter() const {
    return surface_number_density_ * 0.0001f;
  }

  // Returns the surface number density in units per square millimeter.
  float inUnitsPerSquareMillimeter() const {
    return surface_number_density_ * 0.000001f;
  }

  // Returns the surface number density in units per square kilometer.
  float inUnitsPerSquareKilometer() const {
    return surface_number_density_ * 1000000.0f;
  }

  // Returns the surface number density in units per square inch.
  float inUnitsPerSquareInch() const {
    return surface_number_density_ * 0.00064516f;
  }

  // Returns the surface number density in units per square foot.
  float inUnitsPerSquareFoot() const {
    return surface_number_density_ * 0.09290304f;
  }

  // Returns the surface number density in units per square yard.
  float inUnitsPerSquareYard() const {
    return surface_number_density_ * 0.83612736f;
  }

  // Returns whether the object represents an unknown surface number density.
  bool isUnknown() const { return std::isnan(surface_number_density_); }

  bool operator<(const SurfaceNumberDensity &other) const {
    return surface_number_density_ < other.surface_number_density_;
  }

  bool operator==(const SurfaceNumberDensity &other) const {
    return surface_number_density_ == other.surface_number_density_;
  }

  bool operator>(const SurfaceNumberDensity &other) const {
    return other.surface_number_density_ < surface_number_density_;
  }

  bool operator<=(const SurfaceNumberDensity &other) const {
    return !(other.surface_number_density_ < surface_number_density_);
  }

  bool operator>=(const SurfaceNumberDensity &other) const {
    return !(surface_number_density_ < other.surface_number_density_);
  }

  bool operator!=(const SurfaceNumberDensity &other) const {
    return !(surface_number_density_ == other.surface_number_density_);
  }

  SurfaceNumberDensity &operator*=(float multi) {
    surface_number_density_ *= multi;
    return *this;
  }

  SurfaceNumberDensity &operator/=(float div) {
    surface_number_density_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the surface_number_density.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend SurfaceNumberDensity UnknownSurfaceNumberDensity();

  friend SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareMeter(float);

  explicit SurfaceNumberDensity(float surface_number_density)
      : surface_number_density_(surface_number_density) {}

  // Stored in units per square meter.
  float surface_number_density_;
};

inline SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareMeter(
    float surface_number_density);

// Returns a surface number density object representing an unknown
// surface number density.
inline SurfaceNumberDensity UnknownSurfaceNumberDensity() {
  return SurfaceNumberDensity();
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in giga-units per square meter.
inline SurfaceNumberDensity SurfaceNumberDensityInGigaUnitsPerSquareMeter(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   1000000000.0f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in mega-units per square meter.
inline SurfaceNumberDensity SurfaceNumberDensityInMegaUnitsPerSquareMeter(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   1000000.0f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in kilo-units per square meter.
inline SurfaceNumberDensity SurfaceNumberDensityInKiloUnitsPerSquareMeter(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   1000.0f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in units per square meter.
inline SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareMeter(
    float surface_number_density) {
  return SurfaceNumberDensity(surface_number_density);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in milli-units per square meter.
inline SurfaceNumberDensity SurfaceNumberDensityInMilliUnitsPerSquareMeter(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   0.001f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in micro-units per square meter.
inline SurfaceNumberDensity SurfaceNumberDensityInMicroUnitsPerSquareMeter(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   0.000001f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in units per square centimeter.
inline SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareCentimeter(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   10000.0f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in units per square millimeter.
inline SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareMillimeter(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   1000000.0f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in units per square kilometer.
inline SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareKilometer(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   0.000001f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in units per square inch.
inline SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareInch(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   1550.0031000062f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in units per square foot.
inline SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareFoot(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   10.7639104167f);
}

// Returns a surface number density object equivalent to the specified
// surface number density expressed in units per square yard.
inline SurfaceNumberDensity SurfaceNumberDensityInUnitsPerSquareYard(
    float surface_number_density) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(surface_number_density *
                                                   1.1959900463f);
}

inline SurfaceNumberDensity operator*(SurfaceNumberDensity a, float b) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(a.inUnitsPerSquareMeter() *
                                                   b);
}

inline SurfaceNumberDensity operator*(float a, SurfaceNumberDensity b) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(a *
                                                   b.inUnitsPerSquareMeter());
}

inline float operator*(Area a, SurfaceNumberDensity b) {
  return a.inSquareMeters() * b.inUnitsPerSquareMeter();
}

inline float operator*(SurfaceNumberDensity a, Area b) {
  return a.inUnitsPerSquareMeter() * b.inSquareMeters();
}

inline LinearNumberDensity operator*(Length a, SurfaceNumberDensity b) {
  return LinearNumberDensityInUnitsPerMeter(a.inMeters() *
                                            b.inUnitsPerSquareMeter());
}

inline LinearNumberDensity operator*(SurfaceNumberDensity a, Length b) {
  return LinearNumberDensityInUnitsPerMeter(a.inUnitsPerSquareMeter() *
                                            b.inMeters());
}

inline SurfaceNumberDensity operator/(SurfaceNumberDensity a, float b) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(a.inUnitsPerSquareMeter() /
                                                   b);
}

inline float operator/(SurfaceNumberDensity a, SurfaceNumberDensity b) {
  return a.inUnitsPerSquareMeter() / b.inUnitsPerSquareMeter();
}

inline Area operator/(float a, SurfaceNumberDensity b) {
  return AreaInSquareMeters(a / b.inUnitsPerSquareMeter());
}

inline SurfaceNumberDensity operator/(float a, Area b) {
  return SurfaceNumberDensityInUnitsPerSquareMeter(a / b.inSquareMeters());
}

}  // namespace roo_quantity