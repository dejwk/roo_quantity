#include "roo_quantity/velocity.h"

namespace roo_quantity {
namespace {

void VelocityToString(Velocity val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m/s", maxlen);
  } else {
    const char* format;
    const char* sign = "";
    float num;
    if (val.inMetersPerSecond() == 0.0f) {
      snprintf(out, maxlen, "0 m/s");
      return;
    }
    if (val.inMetersPerSecond() < 0) {
      sign = "-";
      val = -val;
    }
    if (val >= VelocityInKilometersPerSecond(1.0f)) {
      format = "%s%g km/s";
      num = val.inKilometersPerSecond();
    } else if (val >= VelocityInMetersPerSecond(1.0f)) {
      format = "%s%g m/s";
      num = val.inMetersPerSecond();
    } else if (val >= VelocityInMillimetersPerSecond(1.0f)) {
      format = "%s%g mm/s";
      num = val.inMillimetersPerSecond();
    } else {
      format = "%s%g µm/s";
      num = val.inMicrometersPerSecond();
    }
    snprintf(out, maxlen, format, sign, num);
  }
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Velocity::asString() const {
  char out[16];
  VelocityToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Velocity::asArduinoString() const {
  char out[16];
  VelocityToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Velocity& val) {
  char out[16];
  VelocityToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity