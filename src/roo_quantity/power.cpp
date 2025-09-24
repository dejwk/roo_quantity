#include "roo_quantity/power.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void PowerToString(const Power& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inWatts(), "W", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Power::asString() const {
  char out[16];
  PowerToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Power::asArduinoString() const {
  char out[16];
  PowerToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Power& val) {
  char out[16];
  PowerToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity