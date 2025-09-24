#include "roo_quantity/length.h"

namespace roo_quantity {
namespace {

void LengthToString(Length val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m", maxlen);
  } else {
    const char* format;
    const char* sign = "";
    float num;
    if (val.inMeters() == 0.0f) {
      snprintf(out, maxlen, "0 m");
      return;
    }
    if (val.inMeters() < 0) {
      sign = "-";
      val = -val;
    }
    if (val >= LengthInMeters(1000.0f)) {
      format = "%s%g km";
      num = val.inKilometers();
    } else if (val >= LengthInMeters(1.0f)) {
      format = "%s%g m";
      num = val.inMeters();
    } else if (val >= LengthInCentimeters(10.0f)) {
      format = "%s%g cm";
      num = val.inCentimeters();
    } else if (val >= LengthInMillimeters(1.0f)) {
      format = "%s%g mm";
      num = val.inMillimeters();
    } else if (val >= LengthInMicrometers(1.0f)) {
      format = "%s%g µm";
      num = val.inMicrometers();
    } else {
      format = "%s%g nm";
      num = val.inNanometers();
    }
    snprintf(out, maxlen, format, sign, num);
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