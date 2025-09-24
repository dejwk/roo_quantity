#include "roo_quantity/volumic_number.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void VolumicNumberToString(const VolumicNumber& val, char* out, int maxlen) {
  snprintf(out, maxlen, "%.6g/m³", val.inUnitsPerCubicMeter());
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string VolumicNumber::asString() const {
  char out[16];
  VolumicNumberToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String VolumicNumber::asArduinoString() const {
  char out[16];
  VolumicNumberToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os,
                                const VolumicNumber& val) {
  char out[16];
  VolumicNumberToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity