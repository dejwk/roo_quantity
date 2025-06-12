#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/area.h"
#include "roo_quantity/length.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of volume, internally stored as floating-point cubic meters.
class Volume {
 public:
  // Creates a volume object representing an 'unknown' volume.
  Volume() : volume_(std::nanf("")) {}

  // Returns the volume in cubic kilometers.
  float inCubicKilometers() const { return volume_ * 0.000000001f; }

  // Returns the volume in cubic meters.
  float inCubicMeters() const { return volume_; }

  // Returns the volume in liters.
  float inLiters() const { return volume_ * 1000.0f; }

  // Returns the volume in liters.
  float inCubicDecimeters() const { return inLiters(); }

  // Returns the volume in milliliters.
  float inMilliliters() const { return volume_ * 1000000.0f; }

  // Returns the volume in milliliters.
  float inCubicCentimeters() const { return inMilliliters(); }

  // Returns the volume in microliters.
  float inMicroliters() const { return volume_ * 1000000000.0f; }

  // Returns the volume in microliters.
  float inCubicMillimeters() const { return inMicroliters(); }

  // Returns the volume in cubic micrometers.
  float inCubicMicrometers() const { return volume_ * 1000000000000000000.0f; }

  // Returns the volume in cubic inches.
  float inCubicInches() const { return volume_ * 61023.744095f; }

  // Returns whether the object represents an unknown volume.
  bool isUnknown() const { return std::isnan(volume_); }

  bool operator<(const Volume &other) const { return volume_ < other.volume_; }

  bool operator==(const Volume &other) const {
    return volume_ == other.volume_;
  }

  bool operator>(const Volume &other) const { return other.volume_ < volume_; }

  bool operator<=(const Volume &other) const {
    return !(other.volume_ < volume_);
  }

  bool operator>=(const Volume &other) const {
    return !(volume_ < other.volume_);
  }

  bool operator!=(const Volume &other) const {
    return !(volume_ == other.volume_);
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the volume.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Volume UnknownVolume();

  friend Volume VolumeInCubicMeters(float);

  explicit Volume(float volume) : volume_(volume) {}

  // Stored in meters.
  float volume_;
};

inline Volume VolumeInCubicMeters(float volume);

// Returns a volume object representing an unknown volume.
inline Volume UnknownVolume() { return Volume(); }

// Returns a volume object equivalent to the specified volume
// expressed in cubic kilometers.
inline Volume VolumeInCubicKilometers(float volume) {
  return VolumeInCubicMeters(volume * 1000000000.0f);
}

// Returns a volume object equivalent to the specified volume
// expressed in cubic meters.
inline Volume VolumeInCubicMeters(float volume) { return Volume(volume); }

// Returns a volume object equivalent to the specified volume
// expressed in liters.
inline Volume VolumeInLiters(float volume) {
  return VolumeInCubicMeters(volume * 0.001f);
}

// Returns a volume object equivalent to the specified volume
// expressed in liters.
inline Volume VolumeInCubicDecimeters(float volume) {
  return VolumeInLiters(volume);
}

// Returns a volume object equivalent to the specified volume
// expressed in milliliters.
inline Volume VolumeInMilliliters(float volume) {
    return VolumeInCubicMeters(volume * 0.000001f);
  }
  
// Returns a volume object equivalent to the specified volume
// expressed in milliliters.
inline Volume VolumeInCubicCentimeters(float volume) {
  return VolumeInMilliliters(volume);
}

// Returns a volume object equivalent to the specified volume
// expressed in cubic millimeters.
inline Volume VolumeInCubicMillimeters(float volume) {
  return VolumeInCubicMeters(volume * 0.000000001f);
}

// Returns a volume object equivalent to the specified volume
// expressed in cubic micrometers.
inline Volume VolumeInCubicMicrometers(float volume) {
  return VolumeInCubicMeters(volume * 0.000000000000000001f);
}

// Returns a volume object equivalent to the specified volume
// expressed in acres.
inline Volume VolumeInCubicInches(float volume) {
  return VolumeInCubicMeters(volume * 1.6387e-5f);
}

inline Volume operator+(Volume a, Volume b) {
  return VolumeInCubicMeters(a.inCubicMeters() + b.inCubicMeters());
}

inline Volume operator*(Volume a, float b) {
  return VolumeInCubicMeters(a.inCubicMeters() * b);
}

inline Volume operator*(float a, Volume b) {
  return VolumeInCubicMeters(a * b.inCubicMeters());
}

inline Volume operator/(Volume a, float b) {
  return VolumeInCubicMeters(a.inCubicMeters() / b);
}

inline float operator/(Volume a, Volume b) {
  return a.inCubicMeters() / b.inCubicMeters();
}

inline Volume operator*(Length a, Area b) {
  return VolumeInCubicMeters(a.inMeters() * b.inSquareMeters());
}

inline Volume operator*(Area a, Length b) {
  return VolumeInCubicMeters(a.inSquareMeters() * b.inMeters());
}

inline Area operator/(Volume a, Length b) {
  return AreaInSquareMeters(a.inCubicMeters() / b.inMeters());
}

inline Length operator/(Volume a, Area b) {
  return LengthInMeters(a.inCubicMeters() / b.inSquareMeters());
}

}  // namespace roo_quantity