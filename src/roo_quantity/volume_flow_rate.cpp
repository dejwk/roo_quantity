#include "roo_quantity/volume_flow_rate.h"

#include <cmath>

namespace roo_quantity {
namespace {

// Selects the display unit by magnitude and formats the signed value.
void VolumeFlowRateToString(const VolumeFlowRate& val, char* out, int maxlen) {
  if (val.isUnknown()) {
    strncpy(out, "? m³/s", maxlen);
  } else {
    const VolumeFlowRate magnitude = VolumeFlowRateInCubicMetersPerSecond(
        std::fabs(val.inCubicMetersPerSecond()));
    const char* format;
    float num;
    if (magnitude >= VolumeFlowRateInCubicMetersPerSecond(1.0f)) {
      format = "%g m³/s";
      num = val.inCubicMetersPerSecond();
    } else if (magnitude >= VolumeFlowRateInLitersPerSecond(1.0f)) {
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
  char out[20];
  VolumeFlowRateToString(*this, out, sizeof(out));
  return out;
}

#endif

#if defined(ARDUINO)

String VolumeFlowRate::asArduinoString() const {
  char out[20];
  VolumeFlowRateToString(*this, out, sizeof(out));
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os,
                                const VolumeFlowRate& val) {
  char out[20];
  VolumeFlowRateToString(val, out, sizeof(out));
  os << out;
  return os;
}

}  // namespace roo_quantity