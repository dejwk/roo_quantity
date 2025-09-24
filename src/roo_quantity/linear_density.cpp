#include "roo_quantity/linear_density.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void LinearDensityToString(const LinearDensity& val, char* out, int maxlen) {
  sprintf(out, "%.6g/m", maxlen, val.inUnitsPerMeter());
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string LinearDensity::asString() const {
  char out[16];
  LinearDensityToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String LinearDensity::asArduinoString() const {
  char out[16];
  LinearDensityToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os,
                                const LinearDensity& val) {
  char out[16];
  LinearDensityToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity