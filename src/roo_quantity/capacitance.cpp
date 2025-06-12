#include "roo_quantity/capacitance.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void CapacitanceToString(const Capacitance& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inFarads(), "F", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Capacitance::asString() const {
  char out[16];
  CapacitanceToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Capacitance::asArduinoString() const {
  char out[16];
  CapacitanceToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Capacitance& val) {
  char out[16];
  CapacitanceToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity