#include "roo_quantity/pressure.h"

namespace roo_quantity {
namespace {

void PressureToString(const Pressure& val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m", maxlen);
  } else {
    const char* format;
    float num;
    if (val > PressureInMegaPascals(2.0f)) {
      format = "%g MPa";
      num = val.inMegaPascals();
    } else if (val > PressureInBars(1.0f)) {
      format = "%g bar";
      num = val.inBars();
    } else if (val > PressureInHectoPascals(2000.0f)) {
      format = "%g kPa";
      num = val.inKiloPascals();
    } else if (val > PressureInHectoPascals(500.0f)) {
      format = "%g hPa";
      num = val.inBars();
    } else if (val > PressureInPascals(1.0f)) {
      format = "%g Pa";
      num = val.inPascals();
    } else if (val > PressureInMilliPascals(1.0f)) {
      format = "%g mPa";
      num = val.inMilliPascals();
    } else {
      format = "%g µPa";
      num = val.inMicroPascals();
    }
    snprintf(out, maxlen, format, num);
  }
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Pressure::asString() const {
  char out[16];
  PressureToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Pressure::asArduinoString() const {
  char out[16];
  PressureToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Pressure& val) {
  char out[16];
  PressureToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity