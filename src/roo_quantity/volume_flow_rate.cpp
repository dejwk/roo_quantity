#include "roo_quantity/volume_flow_rate.h"

namespace roo_quantity {
namespace {

void VolumeFlowRateToString(const VolumeFlowRate& val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m³/s", maxlen);
  } else {
    const char* format;
    float num;
    if (val > VolumeFlowRateInCubicMetersPerSecond(1.0f)) {
      format = "%g m³/s";
      num = val.inCubicMetersPerSecond();
    } else if (val > VolumeFlowRateInLitersPerSecond(1.0f)) {
      format = "%g L/s";
      num = val.inLitersPerSecond();
    } else {
      format = "%g mL/s";
      num = val.inMillilitersPerSecond();
    }
    snprintf(out, maxlen, format, num);
  }
}

}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string VolumeFlowRate::asString() const {
  char out[16];
  VolumeFlowRateToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String VolumeFlowRate::asArduinoString() const {
  char out[16];
  VolumeFlowRateToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const VolumeFlowRate& val) {
  char out[16];
  VolumeFlowRateToString(val, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity