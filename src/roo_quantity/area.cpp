#include "roo_quantity/area.h"

#include <cmath>

namespace roo_quantity {
namespace {

// Selects the display unit by magnitude and formats the signed value.
void AreaToString(const Area& val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m²", maxlen);
  } else {
    const Area magnitude = AreaInSquareMeters(std::fabs(val.inSquareMeters()));
    const char* format;
    float num;
    if (magnitude >= AreaInSquareKilometers(1.0f)) {
      format = "%g km²";
      num = val.inSquareKilometers();
    } else if (magnitude >= AreaInHectares(1.0f)) {
      format = "%g ha";
      num = val.inHectares();
    } else if (magnitude >= AreaInSquareMeters(1.0f)) {
      format = "%g m²";
      num = val.inSquareMeters();
    } else if (magnitude >= AreaInSquareDecimeters(1.0f)) {
      format = "%g dm²";
      num = val.inSquareDecimeters();
    } else if (magnitude >= AreaInSquareMillimeters(1.0f)) {
      format = "%g mm²";
      num = val.inSquareMillimeters();
    } else {
      format = "%g µm²";
      num = val.inSquareMicrometers();
    }
    snprintf(out, maxlen, format, num);
  }
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Area::asString() const {
  char out[20];
  AreaToString(*this, out, sizeof(out));
  return out;
}

#endif

#if defined(ARDUINO)

String Area::asArduinoString() const {
  char out[20];
  AreaToString(*this, out, sizeof(out));
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Area& val) {
  char out[20];
  AreaToString(val, out, sizeof(out));
  os << out;
  return os;
}

}  // namespace roo_quantity