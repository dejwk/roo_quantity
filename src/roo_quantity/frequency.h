#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/time.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of frequency, internally stored as floating-point Hertz.
class Frequency {
 public:
  // Creates a frequency object representing an 'unknown' frequency.
  Frequency() : frequency_(std::nanf("")) {}

  // Returns the frequency in GigaHertz.
  float inGigaHertz() const { return frequency_ * 0.000000001f; }

  // Returns the frequency in MegaHertz.
  float inMegaHertz() const { return frequency_ * 0.000001f; }

  // Returns the frequency in kiloHertz.
  float inKiloHertz() const { return frequency_ * 0.001f; }

  // Returns the frequency in Hertz.
  float inHertz() const { return frequency_; }

  // Returns the frequency in milliHertz.
  float inMilliHertz() const { return frequency_ * 1000.0f; }

  // Returns the frequency in microHertz.
  float inMicroHertz() const { return frequency_ * 1000000.0f; }

  // Returns whether the object represents an unknown frequency.
  bool isUnknown() const { return std::isnan(frequency_); }

  bool operator<(const Frequency &other) const {
    return frequency_ < other.frequency_;
  }

  bool operator==(const Frequency &other) const {
    return frequency_ == other.frequency_;
  }

  bool operator>(const Frequency &other) const {
    return other.frequency_ < frequency_;
  }

  bool operator<=(const Frequency &other) const {
    return !(other.frequency_ < frequency_);
  }

  bool operator>=(const Frequency &other) const {
    return !(frequency_ < other.frequency_);
  }

  bool operator!=(const Frequency &other) const {
    return !(frequency_ == other.frequency_);
  }

  Frequency &operator*=(float multi) {
    frequency_ *= multi;
    return *this;
  }

  Frequency &operator/=(float div) {
    frequency_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the frequency.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Frequency UnknownFrequency();

  friend Frequency FrequencyInHertz(float);

  explicit Frequency(float frequency) : frequency_(frequency) {}

  // Stored in Hertz.
  float frequency_;
};

inline Frequency FrequencyInHertz(float frequency);

// Returns a frequency object representing an unknown frequency.
inline Frequency UnknownFrequency() { return Frequency(); }

// Returns a frequency object equivalent to the specified frequency
// expressed in gigaHertz.
inline Frequency FrequencyInGigaHertz(float frequency) {
  return FrequencyInHertz(frequency * 1000000000.0f);
}

// Returns a frequency object equivalent to the specified frequency
// expressed in megaHertz.
inline Frequency FrequencyInMegaHertz(float frequency) {
  return FrequencyInHertz(frequency * 1000000.0f);
}

// Returns a frequency object equivalent to the specified frequency
// expressed in kiloHertz.
inline Frequency FrequencyInKiloHertz(float frequency) {
  return FrequencyInHertz(frequency * 1000.0f);
}

// Returns a frequency object equivalent to the specified frequency
// expressed in Hertz.
inline Frequency FrequencyInHertz(float frequency) {
  return Frequency(frequency);
}

// Returns a frequency object equivalent to the specified frequency
// expressed in milliHertz.
inline Frequency FrequencyInMilliHertz(float frequency) {
  return FrequencyInHertz(frequency * 0.001f);
}

// Returns a frequency object equivalent to the specified frequency
// expressed in microHertz.
inline Frequency FrequencyInMicroHertz(float frequency) {
  return FrequencyInHertz(frequency * 0.000001f);
}

inline Frequency operator*(Frequency a, float b) {
  return FrequencyInHertz(a.inHertz() * b);
}

inline Frequency operator*(float a, Frequency b) {
  return FrequencyInHertz(a * b.inHertz());
}

inline Frequency operator/(Frequency a, float b) {
  return FrequencyInHertz(a.inHertz() / b);
}

inline float operator/(Frequency a, Frequency b) {
  return a.inHertz() / b.inHertz();
}

inline Time operator/(float a, Frequency b) {
  return TimeInSeconds(a / b.inHertz());
}

inline Frequency operator/(float a, Time b) {
  return FrequencyInHertz(a / b.inSeconds());
}

}  // namespace roo_quantity