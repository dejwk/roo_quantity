#include "gtest/gtest.h"
#include "roo_quantity.h"

namespace roo_quantity {
namespace {

template <typename Quantity>
class QuantityComparison : public testing::Test {};

using QuantityTypes =
    testing::Types<Area, AreicNumber, Capacitance, Charge, Current, Force,
                   Frequency, Length, LineicNumber, Mass, Power, Pressure,
                   Resistance, Temperature, TemperatureDelta, Time, Velocity,
                   Voltage, Volume, VolumeFlowRate, VolumicNumber, Work>;

TYPED_TEST_SUITE(QuantityComparison, QuantityTypes);

// Verifies that unknown quantities are unordered across all quantity types.
TYPED_TEST(QuantityComparison, UnknownValuesAreUnordered) {
  const TypeParam first;
  const TypeParam second;
  EXPECT_FALSE(first <= second);
  EXPECT_FALSE(first >= second);
}

// Verifies that an unknown reading cannot satisfy an inclusive threshold in
// either operand position.
TEST(QuantityComparison, UnknownReadingDoesNotMeetThresholds) {
  const Temperature unknown;
  const Temperature threshold = TemperatureDegCelcius(60.0f);
  EXPECT_FALSE(unknown <= threshold);
  EXPECT_FALSE(unknown >= threshold);
  EXPECT_FALSE(threshold <= unknown);
  EXPECT_FALSE(threshold >= unknown);
}

}  // namespace
}  // namespace roo_quantity
