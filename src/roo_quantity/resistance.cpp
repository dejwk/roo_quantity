#include "roo_quantity/resistance.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void ResistanceToString(const Resistance& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inOhms(), "Ω", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Resistance::asString() const {
  char out[16];
  ResistanceToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Resistance::asArduinoString() const {
  char out[16];
  ResistanceToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Resistance& val) {
  char out[16];
  ResistanceToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity