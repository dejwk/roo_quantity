#include "roo_quantity/length.h"

namespace roo_quantity {
namespace {

void LengthToString(const Length& val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m", maxlen);
  } else {
    const char* format;
    float num;
    if (val > LengthInMeters(1000.0f)) {
      format = "%g km";
      num = val.inKilometers();
    } else if (val > LengthInMeters(1.0f)) {
      format = "%g m";
      num = val.inMeters();
    } else if (val > LengthInCentimeters(10.0f)) {
      format = "%g cm";
      num = val.inCentimeters();
    } else if (val > LengthInMillimeters(1.0f)) {
      format = "%g mm";
      num = val.inMillimeters();
    } else {
      format = "%g µm";
      num = val.inMicrometers();
    }
    snprintf(out, maxlen, format, num);
  }
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Length::asString() const {
  char out[16];
  LengthToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Length::asArduinoString() const {
  char out[16];
  LengthToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Length& val) {
  char out[16];
  LengthToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity