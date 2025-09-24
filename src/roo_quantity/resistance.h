#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/current.h"
#include "roo_quantity/voltage.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of resistance, internally stored as floating-point Ohms.
class Resistance {
 public:
  // Creates a resistance object representing an 'unknown' resistance.
  Resistance() : resistance_(std::nanf("")) {}

  // Returns the resistance in GigaOhms.
  float inGigaOhms() const { return resistance_ * 0.000000001f; }

  // Returns the resistance in MegaOhms.
  float inMegaOhms() const { return resistance_ * 0.000001f; }

  // Returns the resistance in kiloOhms.
  float inKiloOhms() const { return resistance_ * 0.001f; }

  // Returns the resistance in Ohms.
  float inOhms() const { return resistance_; }

  // Returns the resistance in milliOhms.
  float inMilliOhms() const { return resistance_ * 1000.0f; }

  // Returns the resistance in microOhms.
  float inMicroOhms() const { return resistance_ * 1000000.0f; }

  // Returns the resistance in nanoOhms.
  float inNanoOhms() const { return resistance_ * 1000000000.0f; }

  // Returns whether the object represents an unknown resistance.
  bool isUnknown() const { return std::isnan(resistance_); }

  bool operator<(const Resistance& other) const {
    return resistance_ < other.resistance_;
  }

  bool operator==(const Resistance& other) const {
    return resistance_ == other.resistance_;
  }

  bool operator>(const Resistance& other) const {
    return other.resistance_ < resistance_;
  }

  bool operator<=(const Resistance& other) const {
    return !(other.resistance_ < resistance_);
  }

  bool operator>=(const Resistance& other) const {
    return !(resistance_ < other.resistance_);
  }

  bool operator!=(const Resistance& other) const {
    return !(resistance_ == other.resistance_);
  }

  inline Resistance& operator+=(const Resistance& other) {
    resistance_ += other.inOhms();
    return *this;
  }

  inline Resistance& operator-=(const Resistance& other) {
    resistance_ -= other.inOhms();
    return *this;
  }

  inline Resistance& operator*=(float multi) {
    resistance_ *= multi;
    return *this;
  }

  inline Resistance& operator/=(float div) {
    resistance_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the resistance.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Resistance UnknownResistance();

  friend Resistance ResistanceInOhms(float);

  explicit Resistance(float resistance) : resistance_(resistance) {}

  // Stored in Ohms.
  float resistance_;
};

inline Resistance ResistanceInOhms(float resistance);

// Returns a resistance object representing an unknown resistance.
inline Resistance UnknownResistance() { return Resistance(); }

// Returns a resistance object equivalent to the specified resistance
// expressed in GigaOhms.
inline Resistance ResistanceInGigaOhms(float resistance) {
  return ResistanceInOhms(resistance * 1000000000.0f);
}

// Returns a resistance object equivalent to the specified resistance
// expressed in MegaOhms.
inline Resistance ResistanceInMegaOhms(float resistance) {
  return ResistanceInOhms(resistance * 1000000.0f);
}

// Returns a resistance object equivalent to the specified resistance
// expressed in kiloOhms.
inline Resistance ResistanceInKiloOhms(float resistance) {
  return ResistanceInOhms(resistance * 1000.0f);
}

// Returns a resistance object equivalent to the specified resistance
// expressed in Ohms.
inline Resistance ResistanceInOhms(float resistance) {
  return Resistance(resistance);
}

// Returns a resistance object equivalent to the specified resistance
// expressed in milliOhms.
inline Resistance ResistanceInMilliOhms(float resistance) {
  return ResistanceInOhms(resistance * 0.001f);
}

// Returns a resistance object equivalent to the specified resistance
// expressed in microOhms.
inline Resistance ResistanceInMicroOhms(float resistance) {
  return ResistanceInOhms(resistance * 0.000001f);
}

// Returns a resistance object equivalent to the specified resistance
// expressed in microOhms.
inline Resistance ResistanceInNanoOhms(float resistance) {
  return ResistanceInOhms(resistance * 0.000000001f);
}

inline Resistance operator+(Resistance a, Resistance b) {
  return ResistanceInOhms(a.inOhms() + b.inOhms());
}

inline Resistance operator-(Resistance a, Resistance b) {
  return ResistanceInOhms(a.inOhms() - b.inOhms());
}

inline Resistance operator-(Resistance a) {
  return ResistanceInOhms(-a.inOhms());
}

inline Resistance operator*(Resistance a, float b) {
  return ResistanceInOhms(a.inOhms() * b);
}

inline Resistance operator*(float a, Resistance b) {
  return ResistanceInOhms(a * b.inOhms());
}

inline Resistance operator/(Resistance a, float b) {
  return ResistanceInOhms(a.inOhms() / b);
}

inline float operator/(Resistance a, Resistance b) {
  return a.inOhms() / b.inOhms();
}

// Vs Ohm's law.

inline Voltage operator*(Resistance a, Current b) {
  return VoltageInVolts(a.inOhms() * b.inAmperes());
}

inline Voltage operator*(Current a, Resistance b) {
  return VoltageInVolts(a.inAmperes() * b.inOhms());
}

inline Resistance operator/(Voltage a, Current b) {
  return ResistanceInOhms(a.inVolts() / b.inAmperes());
}

inline Current operator/(Voltage a, Resistance b) {
  return CurrentInAmperes(a.inVolts() / b.inOhms());
}

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Resistance& val);

}  // namespace roo_quantity