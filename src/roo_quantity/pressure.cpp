#include "roo_quantity/pressure.h"

namespace roo_quantity {
namespace {

void PressureToString(Pressure val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m", maxlen);
  } else {
    const char* format;
    const char* sign = "";
    float num;
    if (val.inPascals() == 0.0f) {
      snprintf(out, maxlen, "0 Pa");
      return;
    }
    if (val.inPascals() < 0) {
      sign = "-";
      val = -val;
    }
    if (val >= PressureInGigaPascals(1.0f)) {
      format = "%s%g GPa";
      num = val.inGigaPascals();
    } else if (val >= PressureInMegaPascals(2.0f)) {
      format = "%s%g MPa";
      num = val.inMegaPascals();
    } else if (val >= PressureInBars(0.1f)) {
      format = "%s%g bar";
      num = val.inBars();
    // } else if (val >= PressureInHectoPascals(1100.0f)) {
    //   format = "%s%g kPa";
    //   num = val.inKiloPascals();
    // } else if (val >= PressureInHectoPascals(800.0f)) {
    //   format = "%s%g hPa";
    //   num = val.inHectoPascals();
    } else if (val >= PressureInKiloPascals(1.0f)) {
      format = "%s%g kPa";
      num = val.inKiloPascals();
    } else if (val >= PressureInPascals(1.0f)) {
      format = "%s%g Pa";
      num = val.inPascals();
    } else if (val >= PressureInMilliPascals(1.0f)) {
      format = "%s%g mPa";
      num = val.inMilliPascals();
    } else {
      format = "%s%g µPa";
      num = val.inMicroPascals();
    }
    snprintf(out, maxlen, format, sign, num);
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