#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/areic_number.h"
#include "roo_quantity/volume.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of volumic number, a reciprocal of area, internally
// stored as floating-point units per cubic meter.
class VolumicNumber {
 public:
  // Creates an volumic number object representing an 'unknown'
  // volumic number.
  VolumicNumber() : volumic_number_(std::nanf("")) {}

  // Returns the volumic number in GigaUnitsPerCubicMeter.
  float inGigaUnitsPerCubicMeter() const {
    return volumic_number_ * 0.000000001f;
  }

  // Returns the volumic number in Mega-units per cubic meter.
  float inMegaUnitsPerCubicMeter() const { return volumic_number_ * 0.000001f; }

  // Returns the volumic number in kilo-units per cubic meter.
  float inKiloUnitsPerCubicMeter() const { return volumic_number_ * 0.001f; }

  // Returns the volumic number in units per cubic meter.
  float inUnitsPerCubicMeter() const { return volumic_number_; }

  // Returns the volumic number in milli-units per cubic meter.
  float inMilliUnitsPerCubicMeter() const { return volumic_number_ * 1000.0f; }

  // Returns the volumic number in micro-units per cubic meter.
  float inMicroUnitsPerCubicMeter() const {
    return volumic_number_ * 1000000.0f;
  }

  // Returns the volumic number in units per cubic decimeter (liter).
  float inUnitsPerCubicDecimeter() const { return volumic_number_ * 0.001f; }

  // Returns the volumic number in units per cubic decimeter (liter).
  float inUnitsPerLiter() const { return inUnitsPerCubicDecimeter(); }

  // Returns the volumic number in units per cubic centimeter.
  float inUnitsPerCubicCentimeter() const {
    return volumic_number_ * 0.000001f;
  }

  // Returns the volumic number in units per cubic millimeter.
  float inUnitsPerCubicMillimeter() const {
    return volumic_number_ * 0.000000001f;
  }

  // Returns the volumic number in units per cubic kilometer.
  float inUnitsPerCubicKilometer() const {
    return volumic_number_ * 1000000000.0f;
  }

  // Returns the volumic number in units per cubic inch.
  float inUnitsPerCubicInch() const { return volumic_number_ * 1.6387064E-5f; }

  // Returns the volumic number in units per cubic foot.
  float inUnitsPerCubicFoot() const { return volumic_number_ * 0.0283168466f; }

  // Returns the volumic number in units per cubic yard.
  float inUnitsPerCubicYard() const { return volumic_number_ * 0.764554858f; }

  // Returns whether the object represents an unknown volumic number.
  bool isUnknown() const { return std::isnan(volumic_number_); }

  bool operator<(const VolumicNumber &other) const {
    return volumic_number_ < other.volumic_number_;
  }

  bool operator==(const VolumicNumber &other) const {
    return volumic_number_ == other.volumic_number_;
  }

  bool operator>(const VolumicNumber &other) const {
    return other.volumic_number_ < volumic_number_;
  }

  bool operator<=(const VolumicNumber &other) const {
    return !(other.volumic_number_ < volumic_number_);
  }

  bool operator>=(const VolumicNumber &other) const {
    return !(volumic_number_ < other.volumic_number_);
  }

  bool operator!=(const VolumicNumber &other) const {
    return !(volumic_number_ == other.volumic_number_);
  }

  VolumicNumber &operator*=(float multi) {
    volumic_number_ *= multi;
    return *this;
  }

  VolumicNumber &operator/=(float div) {
    volumic_number_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the volumic number.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend VolumicNumber UnknownVolumicNumber();

  friend VolumicNumber VolumicNumberInUnitsPerCubicMeter(float);

  explicit VolumicNumber(float volumic_number)
      : volumic_number_(volumic_number) {}

  // Stored in units per cubic meter.
  float volumic_number_;
};

inline VolumicNumber VolumicNumberInUnitsPerCubicMeter(float volumic_number);

// Returns a volumic number object representing an unknown
// volumic number.
inline VolumicNumber UnknownVolumicNumber() { return VolumicNumber(); }

// Returns a volumic number object equivalent to the specified
// volumic number expressed in giga-units per cubic meter.
inline VolumicNumber VolumicNumberInGigaUnitsPerCubicMeter(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 1000000000.0f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in mega-units per cubic meter.
inline VolumicNumber VolumicNumberInMegaUnitsPerCubicMeter(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 1000000.0f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in kilo-units per cubic meter.
inline VolumicNumber VolumicNumberInKiloUnitsPerCubicMeter(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 1000.0f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic meter.
inline VolumicNumber VolumicNumberInUnitsPerCubicMeter(float volumic_number) {
  return VolumicNumber(volumic_number);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in milli-units per cubic meter.
inline VolumicNumber VolumicNumberInMilliUnitsPerCubicMeter(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 0.001f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in micro-units per cubic meter.
inline VolumicNumber VolumicNumberInMicroUnitsPerCubicMeter(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 0.000001f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic decimeter (liter).
inline VolumicNumber VolumicNumberInUnitsPerCubicDecimeter(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 1000.0f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic decimeter (liter).
inline VolumicNumber VolumicNumberInUnitsPerLiter(float volumic_number) {
  return VolumicNumberInUnitsPerCubicDecimeter(volumic_number);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic centimeter.
inline VolumicNumber VolumicNumberInUnitsPerCubicCentimeter(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 1000000.0f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic millimeter.
inline VolumicNumber VolumicNumberInUnitsPerCubicMillimeter(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 1000000000.0f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic kilometer.
inline VolumicNumber VolumicNumberInUnitsPerCubicKilometer(
    float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 0.000000001f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic inch.
inline VolumicNumber VolumicNumberInUnitsPerCubicInch(float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 61023.744094732f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic foot.
inline VolumicNumber VolumicNumberInUnitsPerCubicFoot(float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 35.3146667215f);
}

// Returns a volumic number object equivalent to the specified
// volumic number expressed in units per cubic yard.
inline VolumicNumber VolumicNumberInUnitsPerCubicYard(float volumic_number) {
  return VolumicNumberInUnitsPerCubicMeter(volumic_number * 1.3079506193f);
}

inline VolumicNumber operator*(VolumicNumber a, float b) {
  return VolumicNumberInUnitsPerCubicMeter(a.inUnitsPerCubicMeter() * b);
}

inline VolumicNumber operator*(float a, VolumicNumber b) {
  return VolumicNumberInUnitsPerCubicMeter(a * b.inUnitsPerCubicMeter());
}

inline float operator*(Volume a, VolumicNumber b) {
  return a.inCubicMeters() * b.inUnitsPerCubicMeter();
}

inline float operator*(VolumicNumber a, Volume b) {
  return a.inUnitsPerCubicMeter() * b.inCubicMeters();
}

inline LineicNumber operator*(Length a, VolumicNumber b) {
  return LineicNumberInUnitsPerMeter(a.inMeters() * b.inUnitsPerCubicMeter());
}

inline LineicNumber operator*(VolumicNumber a, Length b) {
  return LineicNumberInUnitsPerMeter(a.inUnitsPerCubicMeter() * b.inMeters());
}

inline VolumicNumber operator/(VolumicNumber a, float b) {
  return VolumicNumberInUnitsPerCubicMeter(a.inUnitsPerCubicMeter() / b);
}

inline float operator/(VolumicNumber a, VolumicNumber b) {
  return a.inUnitsPerCubicMeter() / b.inUnitsPerCubicMeter();
}

inline Volume operator/(float a, VolumicNumber b) {
  return VolumeInCubicMeters(a / b.inUnitsPerCubicMeter());
}

inline VolumicNumber operator/(float a, Volume b) {
  return VolumicNumberInUnitsPerCubicMeter(a / b.inCubicMeters());
}

}  // namespace roo_quantity