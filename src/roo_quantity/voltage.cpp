#include "roo_quantity/voltage.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void VoltageToString(const Voltage& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inVolts(), "V", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Voltage::asString() const {
  char out[16];
  VoltageToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Voltage::asArduinoString() const {
  char out[16];
  VoltageToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Voltage& val) {
  char out[16];
  VoltageToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity