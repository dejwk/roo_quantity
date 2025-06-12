#include "roo_quantity/si.h"

#include <cmath>
#include <cstdio>

namespace roo_quantity {

void FormatSimpleSiValue(float val, const char* base_unit, char* out,
                         int maxlen) {
  if (isnanf(val)) {
    snprintf(out, maxlen, "? %s", base_unit);
  } else {
    const char* prefix;
    float num;
    if (val > 1000000000000000.0f) {
      prefix = "P";
      val *= 0.000000000000001;
    } else if (val > 1000000000000.0f) {
      prefix = "T";
      val *= 0.000000000001;
    } else if (val > 1000000000.0f) {
      prefix = "G";
      val *= 0.000000001;
    } else if (val > 1000000.0f) {
      prefix = "M";
      val *= 0.000001;
    } else if (val > 1000.0f) {
      prefix = "k";
      val *= 0.001;
    } else if (val > 1.0f) {
      prefix = "";
    } else if (val > 0.001f) {
      prefix = "m";
      val *= 1000.0f;
    } else if (val > 0.000001f) {
      prefix = "µ";
      val *= 1000000.0f;
    } else if (val > 0.000000001f) {
      prefix = "n";
      val *= 1000000000.0f;
    } else {
      prefix = "p";
      val *= 1000000000000.0f;
    }
    snprintf(out, maxlen, "%g %s%s", val, prefix, base_unit);
  }
}

}  // namespace roo_quantity