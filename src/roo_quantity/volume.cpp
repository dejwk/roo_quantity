#include "roo_quantity/volume.h"

namespace roo_quantity {
namespace {

void VolumeToString(const Volume& val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m³", maxlen);
  } else {
    const char* format;
    float num;
    if (val > VolumeInCubicKilometers(1.0f)) {
      format = "%g km³";
      num = val.inCubicKilometers();
    } else if (val > VolumeInCubicMeters(1.0f)) {
      format = "%g m³";
      num = val.inCubicMeters();
    } else if (val > VolumeInCubicDecimeters(1.0f)) {
      format = "%g dm³";
      num = val.inCubicDecimeters();
    } else if (val > VolumeInMilliliters(1.0f)) {
      format = "%g ml";
      num = val.inMilliliters();
    } else if (val > VolumeInCubicMillimeters(1.0f)) {
      format = "%g mm³";
      num = val.inCubicMillimeters();
    } else {
      format = "%g µm³";
      num = val.inCubicMicrometers();
    }
    snprintf(out, maxlen, format, num);
  }
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Volume::asString() const {
  char out[16];
  VolumeToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Volume::asArduinoString() const {
  char out[16];
  VolumeToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Volume& val) {
  char out[16];
  VolumeToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity