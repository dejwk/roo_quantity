#include "roo_quantity/area.h"

namespace roo_quantity {
namespace {

void AreaToString(const Area& val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m²", maxlen);
  } else {
    const char* format;
    float num;
    if (val > AreaInSquareKilometers(1.0f)) {
      format = "%g km²";
      num = val.inSquareKilometers();
    } else if (val > AreaInHectares(1.0f)) {
      format = "%g ha";
      num = val.inHectares();
    } else if (val > AreaInSquareMeters(1.0f)) {
      format = "%g m²";
      num = val.inSquareMeters();
    } else if (val > AreaInSquareDecimeters(1.0f)) {
      format = "%g dm²";
      num = val.inSquareDecimeters();
    } else if (val > AreaInSquareMillimeters(1.0f)) {
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
  char out[16];
  AreaToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Area::asArduinoString() const {
  char out[16];
  AreaToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Area& val) {
  char out[16];
  AreaToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity