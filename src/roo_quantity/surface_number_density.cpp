#include "roo_quantity/surface_number_density.h"

#include "roo_quantity/si.h"

namespace roo_quantity {
namespace {

void SurfaceNumberDensityToString(const SurfaceNumberDensity& val, char* out,
                                  int maxlen) {
  sprintf(out, "%.6g/m²", maxlen, val.inUnitsPerSquareMeter());
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string SurfaceNumberDensity::asString() const {
  char out[16];
  SurfaceNumberDensityToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String SurfaceNumberDensity::asArduinoString() const {
  char out[16];
  SurfaceNumberDensityToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os,
                                const SurfaceNumberDensity& val) {
  char out[16];
  SurfaceNumberDensityToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity