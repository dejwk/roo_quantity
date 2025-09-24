#include "roo_quantity/volume.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Volume, ConversionSi) {
  Volume v = VolumeInCubicMeters(1.5f);
  EXPECT_FLOAT_EQ(1.5f, v.inCubicMeters());
  EXPECT_FLOAT_EQ(1500.0f, v.inCubicDecimeters());
  EXPECT_FLOAT_EQ(1500000.0f, v.inCubicCentimeters());
  EXPECT_FLOAT_EQ(1500000000.0f, v.inCubicMillimeters());
  EXPECT_FLOAT_EQ(1500000000000000000.0f, v.inCubicMicrometers());
  EXPECT_FLOAT_EQ(0.0000000015f, v.inCubicKilometers());
  EXPECT_FLOAT_EQ(1500.0f, v.inLiters());
  EXPECT_FLOAT_EQ(1.5f, v.inCubicMeters());
}

TEST(Volume, ConversionNonSi) {
  Volume v = VolumeInCubicMeters(1.0f);
  EXPECT_FLOAT_EQ(1.0f, v.inCubicMeters());
  EXPECT_FLOAT_EQ(61023.744095f, v.inCubicInches());

  v = VolumeInCubicMeters(2.5f);
  EXPECT_FLOAT_EQ(152559.3602375f, v.inCubicInches());
}

TEST(Volume, Comparison) {
  EXPECT_TRUE(VolumeInCubicMeters(1.0f) < VolumeInCubicMeters(2.0f));
  EXPECT_TRUE(VolumeInCubicMeters(2.0f) > VolumeInCubicMeters(1.0f));
  EXPECT_TRUE(VolumeInCubicMeters(1.0f) <= VolumeInCubicMeters(1.0f));
  EXPECT_TRUE(VolumeInCubicMeters(1.0f) >= VolumeInCubicMeters(1.0f));
  EXPECT_TRUE(VolumeInCubicMeters(1.0f) == VolumeInCubicMeters(1.0f));
  EXPECT_TRUE(VolumeInCubicMeters(1.0f) != VolumeInCubicMeters(2.0f));
}

TEST(Volume, Operators) {
  Volume v1 = VolumeInCubicMeters(1.5f);
  Volume v2 = VolumeInCubicMeters(2.5f);
  Volume v3 = v1 + v2;
  EXPECT_FLOAT_EQ(4.0f, v3.inCubicMeters());

  v3 = v2 - v1;
  EXPECT_FLOAT_EQ(1.0f, v3.inCubicMeters());

  v3 = v1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, v3.inCubicMeters());

  v3 = v2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, v3.inCubicMeters());

  v1 += v2;
  EXPECT_FLOAT_EQ(4.0f, v1.inCubicMeters());
  v1 -= v2;
  EXPECT_FLOAT_EQ(1.5f, v1.inCubicMeters());

  v1 *= 2.0;
  EXPECT_FLOAT_EQ(3.0f, v1.inCubicMeters());
  v1 /= 2.0;
  EXPECT_FLOAT_EQ(1.5f, v1.inCubicMeters());

  float ratio = v2 / v1;
  EXPECT_FLOAT_EQ(5.0f / 3.0f, ratio);

  EXPECT_FLOAT_EQ(
      2.0f,
      (VolumeInCubicMeters(3.0f) / LengthInMeters(1.5f)).inSquareMeters());
  EXPECT_FLOAT_EQ(
      2.0f, (VolumeInCubicMeters(3.0f) / AreaInSquareMeters(1.5f)).inMeters());
}

TEST(Volume, AsString) {
  EXPECT_EQ("1.5 m³", VolumeInCubicMeters(1.5f).asString());
  EXPECT_EQ("1.5 km³", VolumeInCubicKilometers(1.5f).asString());
}

}  // namespace roo_quantity
