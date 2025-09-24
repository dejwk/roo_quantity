#include "roo_quantity/mass.h"

namespace roo_quantity {
namespace {

void MassToString(Mass val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? kg", maxlen);
  } else {
    const char* format;
    const char* sign = "";
    float num;
    if (val.inKg() == 0.0f) {
      snprintf(out, maxlen, "0 kg");
      return;
    }
    if (val.inKg() < 0) {
      sign = "-";
      val = -val;
    }
    if (val >= MassInTons(1.0f)) {
      format = "%s%g t";
      num = val.inTons();
    } else if (val >= MassInKilograms(1.0f)) {
      format = "%s%g kg";
      num = val.inKilograms();
    } else if (val >= MassInGrams(1.0f)) {
      format = "%s%g g";
      num = val.inGrams();
    } else if (val >= MassInMilligrams(1.0f)) {
      format = "%s%g mg";
      num = val.inMilligrams();
    } else {
      format = "%s%g µg";
      num = val.inMicrograms();
    }
    snprintf(out, maxlen, format, sign, num);
  }
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Mass::asString() const {
  char out[16];
  MassToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Mass::asArduinoString() const {
  char out[16];
  MassToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Mass& val) {
  char out[16];
  MassToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity