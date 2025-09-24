#pragma once

#include <cmath>

#include "roo_flags.h"
#include "roo_logging.h"
#include "roo_quantity/current.h"
#include "roo_quantity/time.h"
#include "roo_quantity/voltage.h"

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
#include <string>
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace roo_quantity {

// Representation of capacitance, internally stored as floating-point Farads.
class Capacitance {
 public:
  // Creates a capacitance object representing an 'unknown' capacitance.
  Capacitance() : capacitance_(std::nanf("")) {}

  // Returns the capacitance in kiloFarads.
  float inKiloFarads() const { return capacitance_ * 0.001f; }

  // Returns the capacitance in Farads.
  float inFarads() const { return capacitance_; }

  // Returns the capacitance in milliFarads.
  float inMilliFarads() const { return capacitance_ * 1000.0f; }

  // Returns the capacitance in microFarads.
  float inMicroFarads() const { return capacitance_ * 1000000.0f; }

  // Returns the capacitance in nanoFarads.
  float inNanoFarads() const { return capacitance_ * 1000000000.0f; }

  // Returns the capacitance in picoFarads.
  float inPicoFarads() const { return capacitance_ * 1000000000000.0f; }

  // Returns whether the object represents an unknown capacitance.
  bool isUnknown() const { return std::isnan(capacitance_); }

  bool operator<(const Capacitance& other) const {
    return capacitance_ < other.capacitance_;
  }

  bool operator==(const Capacitance& other) const {
    return capacitance_ == other.capacitance_;
  }

  bool operator>(const Capacitance& other) const {
    return other.capacitance_ < capacitance_;
  }

  bool operator<=(const Capacitance& other) const {
    return !(other.capacitance_ < capacitance_);
  }

  bool operator>=(const Capacitance& other) const {
    return !(capacitance_ < other.capacitance_);
  }

  bool operator!=(const Capacitance& other) const {
    return !(capacitance_ == other.capacitance_);
  }

  inline Capacitance& operator+=(const Capacitance& other) {
    capacitance_ += other.inFarads();
    return *this;
  }

  inline Capacitance& operator-=(const Capacitance& other) {
    capacitance_ -= other.inFarads();
    return *this;
  }

  inline Capacitance& operator*=(float multi) {
    capacitance_ *= multi;
    return *this;
  }

  inline Capacitance& operator/=(float div) {
    capacitance_ /= div;
    return *this;
  }

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)
  // Returns the string representation of the capacitance.
  std::string asString() const;
#endif

#if defined(ARDUINO)
  String asArduinoString() const;
#endif

 private:
  friend Capacitance UnknownCapacitance();

  friend Capacitance CapacitanceInFarads(float);

  explicit Capacitance(float capacitance) : capacitance_(capacitance) {}

  // Stored in Farads.
  float capacitance_;
};

inline Capacitance CapacitanceInFarads(float capacitance);

// Returns a capacitance object representing an unknown capacitance.
inline Capacitance UnknownCapacitance() { return Capacitance(); }

// Returns a capacitance object equivalent to the specified capacitance
// expressed in kiloFarads.
inline Capacitance CapacitanceInKiloFarads(float capacitance) {
  return CapacitanceInFarads(capacitance * 1000.0f);
}

// Returns a capacitance object equivalent to the specified capacitance
// expressed in Farads.
inline Capacitance CapacitanceInFarads(float capacitance) {
  return Capacitance(capacitance);
}

// Returns a capacitance object equivalent to the specified capacitance
// expressed in milliFarads.
inline Capacitance CapacitanceInMilliFarads(float capacitance) {
  return CapacitanceInFarads(capacitance * 0.001f);
}

// Returns a capacitance object equivalent to the specified capacitance
// expressed in microFarads.
inline Capacitance CapacitanceInMicroFarads(float capacitance) {
  return CapacitanceInFarads(capacitance * 0.000001f);
}

// Returns a capacitance object equivalent to the specified capacitance
// expressed in nanoFarads.
inline Capacitance CapacitanceInNanoFarads(float capacitance) {
  return CapacitanceInFarads(capacitance * 0.000000001f);
}

// Returns a capacitance object equivalent to the specified capacitance
// expressed in picoFarads.
inline Capacitance CapacitanceInPicoFarads(float capacitance) {
  return CapacitanceInFarads(capacitance * 0.000000000001f);
}

inline Capacitance operator+(Capacitance a, Capacitance b) {
  return CapacitanceInFarads(a.inFarads() + b.inFarads());
}

inline Capacitance operator-(Capacitance a, Capacitance b) {
  return CapacitanceInFarads(a.inFarads() - b.inFarads());
}

inline Capacitance operator-(Capacitance a) {
  return CapacitanceInFarads(-a.inFarads());
}

inline Capacitance operator*(Capacitance a, float b) {
  return CapacitanceInFarads(a.inFarads() * b);
}

inline Capacitance operator*(float a, Capacitance b) {
  return CapacitanceInFarads(a * b.inFarads());
}

inline Capacitance operator/(Capacitance a, float b) {
  return CapacitanceInFarads(a.inFarads() / b);
}

inline float operator/(Capacitance a, Capacitance b) {
  return a.inFarads() / b.inFarads();
}

// Vs charge.

inline Charge operator*(Capacitance a, Voltage b) {
  return ChargeInCoulombs(a.inFarads() * b.inVolts());
}

inline Charge operator*(Voltage a, Capacitance b) {
  return ChargeInCoulombs(a.inVolts() * b.inFarads());
}

inline Capacitance operator/(Charge a, Voltage b) {
  return CapacitanceInFarads(a.inCoulombs() / b.inVolts());
}

inline Voltage operator/(Charge a, Capacitance b) {
  return VoltageInVolts(a.inCoulombs() / b.inFarads());
}

roo_logging::Stream& operator<<(roo_logging::Stream& os,
                                const Capacitance& val);

}  // namespace roo_quantity