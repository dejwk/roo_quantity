#include "roo_quantity/force.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void ForceToString(const Force& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inNewtons(), "N", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Force::asString() const {
  char out[16];
  ForceToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Force::asArduinoString() const {
  char out[16];
  ForceToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Force& val) {
  char out[16];
  ForceToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity