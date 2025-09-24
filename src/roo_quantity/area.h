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

// Representation of area, internally stored as floating-point square meters.
class Area {
 public:
  // Creates a area object representing an 'unknown' area.
  Area() : area_(std::nanf("")) {}

  // Returns the area in square kilometers.
  float inSquareKilometers() const { return area_ * 0.000001f; }

  // Returns the area in hectares.
  float inHectares() const { return area_ * 0.00001f; }

  // Returns the area in ares.
  float inAres() const { return area_ * 0.01f; }

  // Returns the area in square meters.
  float inSquareMeters() const { return area_; }

  // Returns the area in square decimeters.
  float inSquareDecimeters() const { return area_ * 100.0f; }

  // Returns the area in square centimeters.
  float inSquareCentimeters() const { return area_ * 10000.0f; }

  // Returns the area in square millimeters.
  float inSquareMillimeters() const { return area_ * 1000000.0f; }

  // Returns the area in square micrometers.
  float inSquareMicrometers() const { return area_ * 1000000000000.0f; }

  // Returns the area in acres.
  float inAcres() const { return area_ * 0.000247105f; }

  // Returns the area in square inches.
  float inSquareInches() const { return area_ * 1550.0031f; }

  // Returns whether the object represents an unknown area.
  bool isUnknown() const { return std::isnan(area_); }

  bool operator<(const Area &other) const { return area_ < other.area_; }

  bool operator==(const Area &other) const { return area_ == other.area_; }

  bool operator>(const Area &other) const { return other.area_ < area_; }

  bool operator<=(const Area &other) const { return !(other.area_ < area_); }

  bool operator>=(const Area &other) const { return !(area_ < other.area_); }

  bool operator!=(const Area &other) const { return !(area_ == other.area_); }

  inline Area &operator+=(const Area &other) {
    area_ += other.inSquareMeters();
    return *this;
  }

  inline Area &operator-=(const Area &other) {
    area_ -= other.inSquareMeters();
    return *this;
  }

  inline Area &operator*=(float multi) {
    area_ *= multi;
    return *this;
  }

  inline Area &operator/=(float div) {
    area_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the area.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Area UnknownArea();

  friend Area AreaInSquareMeters(float);

  explicit Area(float area) : area_(area) {}

  // Stored in meters.
  float area_;
};

inline Area AreaInSquareMeters(float area);

// Returns a area object representing an unknown area.
inline Area UnknownArea() { return Area(); }

// Returns a area object equivalent to the specified area
// expressed in square kilometers.
inline Area AreaInSquareKilometers(float area) {
  return AreaInSquareMeters(area * 1000000.0f);
}

// Returns a area object equivalent to the specified area
// expressed in hectares.
inline Area AreaInHectares(float area) {
  return AreaInSquareMeters(area * 10000.0f);
}

// Returns a area object equivalent to the specified area
// expressed in ares.
inline Area AreaInAres(float area) { return AreaInSquareMeters(area * 100.0f); }

// Returns a area object equivalent to the specified area
// expressed in square meters.
inline Area AreaInSquareMeters(float area) { return Area(area); }

// Returns a area object equivalent to the specified area
// expressed in square decimeters.
inline Area AreaInSquareDecimeters(float area) {
  return AreaInSquareMeters(area * 0.01f);
}

// Returns a area object equivalent to the specified area
// expressed in square centimeters.
inline Area AreaInSquareCentimeters(float area) {
  return AreaInSquareMeters(area * 0.0001f);
}

// Returns a area object equivalent to the specified area
// expressed in square millimeters.
inline Area AreaInSquareMillimeters(float area) {
  return AreaInSquareMeters(area * 0.000001f);
}

// Returns a area object equivalent to the specified area
// expressed in square micrometers.
inline Area AreaInSquareMicrometers(float area) {
  return AreaInSquareMeters(area * 0.000000000001f);
}

// Returns a area object equivalent to the specified area
// expressed in acres.
inline Area AreaInAcres(float area) {
  return AreaInSquareMeters(area * 4046.86f);
}

// Returns a area object equivalent to the specified area
// expressed in acres.
inline Area AreaInSquareInches(float area) {
  return AreaInSquareMeters(area * 0.00064516f);
}

inline Area operator+(Area a, Area b) {
  return AreaInSquareMeters(a.inSquareMeters() + b.inSquareMeters());
}

inline Area operator-(Area a, Area b) {
  return AreaInSquareMeters(a.inSquareMeters() - b.inSquareMeters());
}

inline Area operator-(Area a) {
  return AreaInSquareMeters(-a.inSquareMeters());
}

inline Area operator*(Area a, float b) {
  return AreaInSquareMeters(a.inSquareMeters() * b);
}

inline Area operator*(float a, Area b) {
  return AreaInSquareMeters(a * b.inSquareMeters());
}

inline Area operator/(Area a, float b) {
  return AreaInSquareMeters(a.inSquareMeters() / b);
}

inline float operator/(Area a, Area b) {
  return a.inSquareMeters() / b.inSquareMeters();
}

inline Area operator*(Length a, Length b) {
  return AreaInSquareMeters(a.inMeters() * b.inMeters());
}

inline Length operator/(Area a, Length b) {
  return LengthInMeters(a.inSquareMeters() / b.inMeters());
}

roo_logging::Stream &operator<<(roo_logging::Stream &os, const Area &val);

}  // namespace roo_quantity