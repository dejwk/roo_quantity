#include "roo_quantity/current.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void CurrentToString(const Current& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inAmperes(), "A", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Current::asString() const {
  char out[16];
  CurrentToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Current::asArduinoString() const {
  char out[16];
  CurrentToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Current& val) {
  char out[16];
  CurrentToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity