#include "roo_quantity/volume.h"

#include <cmath>

namespace roo_quantity {
namespace {

// Selects the display unit by magnitude and formats the signed value.
void VolumeToString(const Volume& val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m³", maxlen);
  } else {
    const Volume magnitude =
        VolumeInCubicMeters(std::fabs(val.inCubicMeters()));
    const char* format;
    float num;
    if (magnitude >= VolumeInCubicKilometers(1.0f)) {
      format = "%g km³";
      num = val.inCubicKilometers();
    } else if (magnitude >= VolumeInCubicMeters(1.0f)) {
      format = "%g m³";
      num = val.inCubicMeters();
    } else if (magnitude >= VolumeInCubicDecimeters(1.0f)) {
      format = "%g dm³";
      num = val.inCubicDecimeters();
    } else if (magnitude >= VolumeInMilliliters(1.0f)) {
      format = "%g ml";
      num = val.inMilliliters();
    } else if (magnitude >= VolumeInCubicMillimeters(1.0f)) {
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
  char out[20];
  VolumeToString(*this, out, sizeof(out));
  return out;
}

#endif

#if defined(ARDUINO)

String Volume::asArduinoString() const {
  char out[20];
  VolumeToString(*this, out, sizeof(out));
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Volume& val) {
  char out[20];
  VolumeToString(val, out, sizeof(out));
  os << out;
  return os;
}

}  // namespace roo_quantity