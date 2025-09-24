#include "roo_quantity/frequency.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void FrequencyToString(const Frequency& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inHertz(), "Hz", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Frequency::asString() const {
  char out[16];
  FrequencyToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Frequency::asArduinoString() const {
  char out[16];
  FrequencyToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Frequency& val) {
  char out[16];
  FrequencyToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity