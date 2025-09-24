#include "roo_quantity/lineic_number.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void LineicNumberToString(const LineicNumber& val, char* out,
                           int maxlen) {
  sprintf(out, "%.6g/m", maxlen, val.inUnitsPerMeter());
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string LineicNumber::asString() const {
  char out[16];
  LineicNumberToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String LineicNumber::asArduinoString() const {
  char out[16];
  LineicNumberToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os,
                                const LineicNumber& val) {
  char out[16];
  LineicNumberToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity