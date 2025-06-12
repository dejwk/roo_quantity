#pragma once

#include <cmath>

namespace roo_quantity {

void FormatSimpleSiValue(float val, const char* base_unit, char* out,
                         int maxlen);

}  // namespace roo_quantity