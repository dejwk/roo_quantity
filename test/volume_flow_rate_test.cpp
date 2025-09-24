#include "roo_quantity/volume_flow_rate.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(VolumeFlowRate, UnitConversionSi) {
  VolumeFlowRate v = VolumeFlowRateInCubicMetersPerSecond(1.5f);
  EXPECT_FLOAT_EQ(1.5f, v.inCubicMetersPerSecond());
  EXPECT_FLOAT_EQ(1500.0f, v.inLitersPerSecond());
  EXPECT_FLOAT_EQ(1500000.0f, v.inMillilitersPerSecond());

  v = VolumeFlowRateInLitersPerSecond(2.0f);
  EXPECT_FLOAT_EQ(0.002f, v.inCubicMetersPerSecond());

  v = VolumeFlowRateInMillilitersPerSecond(2500.0f);
  EXPECT_FLOAT_EQ(0.0025f, v.inCubicMetersPerSecond());

  v = VolumeFlowRateInCubicMetersPerSecond(-2);
  EXPECT_FLOAT_EQ(-2.0f, v.inCubicMetersPerSecond());
}

TEST(VolumeFlowRate, Comparison) {
  EXPECT_TRUE(VolumeFlowRateInCubicMetersPerSecond(1.0f) <
              VolumeFlowRateInCubicMetersPerSecond(2.0f));
  EXPECT_TRUE(VolumeFlowRateInCubicMetersPerSecond(2.0f) >
              VolumeFlowRateInCubicMetersPerSecond(1.0f));
  EXPECT_TRUE(VolumeFlowRateInCubicMetersPerSecond(1.0f) <=
              VolumeFlowRateInCubicMetersPerSecond(1.0f));
  EXPECT_TRUE(VolumeFlowRateInCubicMetersPerSecond(1.0f) >=
              VolumeFlowRateInCubicMetersPerSecond(1.0f));
  EXPECT_TRUE(VolumeFlowRateInCubicMetersPerSecond(1.0f) ==
              VolumeFlowRateInCubicMetersPerSecond(1.0f));
  EXPECT_TRUE(VolumeFlowRateInCubicMetersPerSecond(1.0f) !=
              VolumeFlowRateInCubicMetersPerSecond(2.0f));
}

TEST(VolumeFlowRate, Operators) {
  VolumeFlowRate v1 = VolumeFlowRateInCubicMetersPerSecond(1.5f);
  VolumeFlowRate v2 = VolumeFlowRateInCubicMetersPerSecond(2.5f);
  VolumeFlowRate v3 = v1 + v2;
  EXPECT_FLOAT_EQ(4.0f, v3.inCubicMetersPerSecond());

  v3 = v2 - v1;
  EXPECT_FLOAT_EQ(1.0f, v3.inCubicMetersPerSecond());

  v3 = v1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, v3.inCubicMetersPerSecond());

  v3 = v2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, v3.inCubicMetersPerSecond());

  v1 += v2;
  EXPECT_FLOAT_EQ(4.0f, v1.inCubicMetersPerSecond());
  v1 -= v2;
  EXPECT_FLOAT_EQ(1.5f, v1.inCubicMetersPerSecond());

  v1 *= 2.0;
  EXPECT_FLOAT_EQ(3.0f, v1.inCubicMetersPerSecond());
  v1 /= 2.0;
  EXPECT_FLOAT_EQ(1.5f, v1.inCubicMetersPerSecond());

  EXPECT_FLOAT_EQ(3.0f, (v1 * TimeInSeconds(2.0f)).inCubicMeters());
}

TEST(VolumeFlowRate, AsString) {
  EXPECT_EQ("? m³/s", UnknownVolumeFlowRate().asString());
  EXPECT_EQ("2 m³/s", VolumeFlowRateInCubicMetersPerSecond(2.0f).asString());
  EXPECT_EQ("500 L/s", VolumeFlowRateInLitersPerSecond(500.0f).asString());
  EXPECT_EQ("1.5 mL/s", VolumeFlowRateInMillilitersPerSecond(1.5f).asString());
}

}  // namespace roo_quantity