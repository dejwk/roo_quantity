#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/time.h"
#include "roo_quantity/volume.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of volume flow rate, internally stored as floating-point
// cubic meters per second.
class VolumeFlowRate {
 public:
  // Creates a volume flow rate object representing an 'unknown' volume flow
  // rate.
  VolumeFlowRate() : volume_flow_rate_(std::nanf("")) {}

  // Returns the volume flow rate in cubic meters per second.
  float inCubicMetersPerSecond() const { return volume_flow_rate_; }

  // Returns the volume flow rate in liters per second.
  float inLitersPerSecond() const { return volume_flow_rate_ * 1000.0f; }

  // Returns the volume flow rate in milliliters per second.
  float inMillilitersPerSecond() const {
    return volume_flow_rate_ * 1000000.0f;
  }

  // Returns the volume flow rate in milliliters per second.
  float inMilliLitersPerSecond() const {
    return volume_flow_rate_ * 1000000.0f;
  }

  // Returns whether the object represents an unknown volume flow rate.
  bool isUnknown() const { return std::isnan(volume_flow_rate_); }

  bool operator<(const VolumeFlowRate& other) const {
    return volume_flow_rate_ < other.volume_flow_rate_;
  }

  bool operator==(const VolumeFlowRate& other) const {
    return volume_flow_rate_ == other.volume_flow_rate_;
  }

  bool operator>(const VolumeFlowRate& other) const {
    return other.volume_flow_rate_ < volume_flow_rate_;
  }

  bool operator<=(const VolumeFlowRate& other) const {
    return !(other.volume_flow_rate_ < volume_flow_rate_);
  }

  bool operator>=(const VolumeFlowRate& other) const {
    return !(volume_flow_rate_ < other.volume_flow_rate_);
  }

  bool operator!=(const VolumeFlowRate& other) const {
    return !(volume_flow_rate_ == other.volume_flow_rate_);
  }

  inline VolumeFlowRate& operator+=(const VolumeFlowRate& other) {
    volume_flow_rate_ += other.inCubicMetersPerSecond();
    return *this;
  }

  inline VolumeFlowRate& operator-=(const VolumeFlowRate& other) {
    volume_flow_rate_ -= other.inCubicMetersPerSecond();
    return *this;
  }

  inline VolumeFlowRate& operator*=(float multi) {
    volume_flow_rate_ *= multi;
    return *this;
  }

  inline VolumeFlowRate& operator/=(float div) {
    volume_flow_rate_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the volume flow rate.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend VolumeFlowRate UnknownVolumeFlowRate();

  friend VolumeFlowRate VolumeFlowRateInCubicMetersPerSecond(float);

  explicit VolumeFlowRate(float volume_flow_rate)
      : volume_flow_rate_(volume_flow_rate) {}

  // Stored in cubic meters per second.
  float volume_flow_rate_;
};

inline VolumeFlowRate VolumeFlowRateInCubicMetersPerSecond(
    float volume_flow_rate);

// Returns a volume flow rate object representing an unknown volume flow rate.
inline VolumeFlowRate UnknownVolumeFlowRate() { return VolumeFlowRate(); }

// Returns a volume flow rate object equivalent to the specified volume flow
// rate expressed in cubic meters per second.
inline VolumeFlowRate VolumeFlowRateInCubicMetersPerSecond(
    float volume_flow_rate) {
  return VolumeFlowRate(volume_flow_rate);
}

// Returns a volume flow rate object equivalent to the specified volume flow
// rate expressed in liters per second.
inline VolumeFlowRate VolumeFlowRateInLitersPerSecond(float volume_flow_rate) {
  return VolumeFlowRateInCubicMetersPerSecond(volume_flow_rate * 0.001f);
}

// Returns a volume flow rate object equivalent to the specified volume flow
// rate expressed in milliliters per second.
inline VolumeFlowRate VolumeFlowRateInMillilitersPerSecond(
    float volume_flow_rate) {
  return VolumeFlowRateInCubicMetersPerSecond(volume_flow_rate * 0.000001f);
}

inline VolumeFlowRate operator+(VolumeFlowRate a, VolumeFlowRate b) {
  return VolumeFlowRateInCubicMetersPerSecond(a.inCubicMetersPerSecond() +
                                              b.inCubicMetersPerSecond());
}

inline VolumeFlowRate operator-(VolumeFlowRate a, VolumeFlowRate b) {
  return VolumeFlowRateInCubicMetersPerSecond(a.inCubicMetersPerSecond() -
                                              b.inCubicMetersPerSecond());
}

inline VolumeFlowRate operator-(VolumeFlowRate a) {
  return VolumeFlowRateInCubicMetersPerSecond(-a.inCubicMetersPerSecond());
}

inline VolumeFlowRate operator*(VolumeFlowRate a, float b) {
  return VolumeFlowRateInCubicMetersPerSecond(a.inCubicMetersPerSecond() * b);
}

inline VolumeFlowRate operator*(float a, VolumeFlowRate b) {
  return VolumeFlowRateInCubicMetersPerSecond(a * b.inCubicMetersPerSecond());
}

inline Volume operator*(VolumeFlowRate a, Time b) {
  return VolumeInCubicMeters(a.inCubicMetersPerSecond() * b.inSeconds());
}

inline Volume operator*(Time a, VolumeFlowRate b) {
  return VolumeInCubicMeters(a.inSeconds() * b.inCubicMetersPerSecond());
}

inline VolumeFlowRate operator/(VolumeFlowRate a, float b) {
  return VolumeFlowRateInCubicMetersPerSecond(a.inCubicMetersPerSecond() / b);
}

inline float operator/(VolumeFlowRate a, VolumeFlowRate b) {
  return a.inCubicMetersPerSecond() / b.inCubicMetersPerSecond();
}

inline VolumeFlowRate operator/(Volume a, Time b) {
  return VolumeFlowRateInCubicMetersPerSecond(a.inCubicMeters() /
                                              b.inSeconds());
}

}  // namespace roo_quantity