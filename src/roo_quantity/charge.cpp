#include "roo_quantity/charge.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void ChargeToString(const Charge& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inCoulombs(), "A", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Charge::asString() const {
  char out[16];
  ChargeToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Charge::asArduinoString() const {
  char out[16];
  ChargeToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Charge& val) {
  char out[16];
  ChargeToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity