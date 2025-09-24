#include "roo_quantity/time.h"

namespace roo_quantity {
namespace {

void TimeToString(Time val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? s", maxlen);
  } else {
    const char* format;
    const char* sign = "";
    float num;
    if (val.inSeconds() == 0.0f) {
      snprintf(out, maxlen, "0 s");
      return;
    }
    if (val.inSeconds() < 0) {
      sign = "-";
      val = -val;
    }
    if (val >= TimeInSeconds(1.0f)) {
      format = "%s%g s";
      num = val.inSeconds();
    } else if (val >= TimeInMilliseconds(1.0f)) {
      format = "%s%g ms";
      num = val.inMilliseconds();
    } else if (val >= TimeInMicroseconds(1.0f)) {
      format = "%s%g µs";
      num = val.inMicroseconds();
    } else {
      format = "%s%g ns";
      num = val.inNanoseconds();
    }
    snprintf(out, maxlen, format, sign, num);
  }
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Time::asString() const {
  char out[16];
  TimeToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Time::asArduinoString() const {
  char out[16];
  TimeToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Time& val) {
  char out[16];
  TimeToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity