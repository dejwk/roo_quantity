#include "roo_quantity/temperature.h"

ROO_FLAG(char, roo_quantity_default_temperature_unit, 'C');

namespace roo_quantity {
namespace {

void TemperatureToString(const Temperature& t, char* out, int maxlen) {
  switch (GET_ROO_FLAG(roo_quantity_default_temperature_unit)) {
    case 'F': {
      if (t.isUnknown()) {
        snprintf(out, maxlen, "?°F");
      } else {
        snprintf(out, maxlen, "%g°F", t.degFahrenheit());
      }
      break;
    }
    case 'K': {
      if (t.isUnknown()) {
        snprintf(out, maxlen, "?°K");
      } else {
        snprintf(out, maxlen, "%g°K", t.degKelvin());
      }
      break;
    }
    default: {
      if (t.isUnknown()) {
        snprintf(out, maxlen, "?°C");
      } else {
        snprintf(out, maxlen, "%g°C", t.degCelcius());
      }
    }
  }
}

void TemperatureDeltaToString(const TemperatureDelta& dt, char* out, int maxlen) {
  switch (GET_ROO_FLAG(roo_quantity_default_temperature_unit)) {
    case 'F': {
      if (dt.isUnknown()) {
        snprintf(out, maxlen, "?°F");
      } else {
        snprintf(out, maxlen, "%g°F", dt.degFahrenheit());
      }
      break;
    }
    case 'K': {
      if (dt.isUnknown()) {
        snprintf(out, maxlen, "?°K");
      } else {
        snprintf(out, maxlen, "%g°K", dt.degKelvin());
      }
      break;
    }
    default: {
      if (dt.isUnknown()) {
        snprintf(out, maxlen, "?°C");
      } else {
        snprintf(out, maxlen, "%g°C", dt.degCelcius());
      }
    }
  }
}
}  // namespace

#if defined(ESP32) || defined(ESP8266) || defined(__linux__)

std::string Temperature::asString() const {
  char out[16];
  TemperatureToString(*this, out, 16);
  return out;
}

std::string TemperatureDelta::asString() const {
  char out[16];
  TemperatureDeltaToString(*this, out, 16);
  return out;
}

#endif

#if defined(ARDUINO)

String Temperature::asArduinoString() const {
  char out[16];
  TemperatureToString(*this, out, 16);
  return out;
}

String TemperatureDelta::asArduinoString() const {
  char out[16];
  TemperatureDeltaToString(*this, out, 16);
  return out;
}

#endif

roo_logging::Stream& operator<<(roo_logging::Stream& os, const Temperature& t) {
  char out[16];
  TemperatureToString(t, out, 16);
  os << out;
  return os;
}

roo_logging::Stream& operator<<(roo_logging::Stream& os, const TemperatureDelta& dt) {
  char out[16];
  TemperatureDeltaToString(dt, out, 16);
  os << out;
  return os;
}

}  // namespace roo_quantity