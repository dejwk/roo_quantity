#pragma once

#include <cmath>

namespace roo_quantity {

/// Formats a value with an SI prefix and base unit.
///
/// Writes a null-terminated string into `out` with at most `maxlen` bytes.
void FormatSimpleSiValue(float val, const char* base_unit, char* out,
                         int maxlen);

}  // namespace roo_quantity