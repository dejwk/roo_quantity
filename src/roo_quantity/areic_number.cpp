#include "roo_quantity/areic_number.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void AreicNumberToString(const AreicNumber& val, char* out, int maxlen) {
  sprintf(out, "%.6g/m²", maxlen, val.inUnitsPerSquareMeter());
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string AreicNumber::asString() const {
  char out[16];
  AreicNumberToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String AreicNumber::asArduinoString() const {
  char out[16];
  AreicNumberToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os,
                                const AreicNumber& val) {
  char out[16];
  AreicNumberToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity