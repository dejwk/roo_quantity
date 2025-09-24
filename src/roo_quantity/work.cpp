#include "roo_quantity/work.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void WorkToString(const Work& val, char* out, int maxlen) {
  FormatSimpleSiValue(val.inJoules(), "J", out, maxlen);
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Work::asString() const {
  char out[16];
  WorkToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Work::asArduinoString() const {
  char out[16];
  WorkToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Work& val) {
  char out[16];
  WorkToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity