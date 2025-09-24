#include "roo_quantity/linear_density.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(LinearDensity, ConversionSi) {
  LinearDensity ld = LinearDensityInUnitsPerMeter(1.5f);
  EXPECT_FLOAT_EQ(1.5f, ld.inUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0015f, ld.inKiloUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0000015f, ld.inMegaUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0000000015f, ld.inGigaUnitsPerMeter());
  EXPECT_FLOAT_EQ(1500.0f, ld.inMilliUnitsPerMeter());
  EXPECT_FLOAT_EQ(1500000.0f, ld.inMicroUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.015f, ld.inUnitsPerCentimeter());
  EXPECT_FLOAT_EQ(0.0015f, ld.inUnitsPerMillimeter());
  EXPECT_FLOAT_EQ(1500.0f, ld.inUnitsPerKilometer());

  ld = LinearDensityInKiloUnitsPerMeter(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, ld.inUnitsPerMeter());

  ld = LinearDensityInMilliUnitsPerMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, ld.inUnitsPerMeter());

  ld = LinearDensityInMicroUnitsPerMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, ld.inMilliUnitsPerMeter());

  ld = LinearDensityInUnitsPerCentimeter(2500.0f);
  EXPECT_FLOAT_EQ(250000.0f, ld.inUnitsPerMeter());

  ld = LinearDensityInUnitsPerMillimeter(2500.0f);
  EXPECT_FLOAT_EQ(2500000.0f, ld.inUnitsPerMeter());

  ld = LinearDensityInUnitsPerKilometer(2);
  EXPECT_FLOAT_EQ(0.002f, ld.inUnitsPerMeter());
}

TEST(LinearDensity, ConversionNonSi) {
  LinearDensity ld = LinearDensityInUnitsPerMeter(1.0f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0254f, ld.inUnitsPerInch());
  EXPECT_FLOAT_EQ(0.3048f, ld.inUnitsPerFoot());
  EXPECT_FLOAT_EQ(0.9144f, ld.inUnitsPerYard());

  ld = LinearDensityInUnitsPerInch(0.0254f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());

  ld = LinearDensityInUnitsPerFoot(0.3048f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());

  ld = LinearDensityInUnitsPerYard(0.9144f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());
}

TEST(LinearDensity, Comparison) {
  EXPECT_TRUE(LinearDensityInUnitsPerMeter(1.0f) <
              LinearDensityInUnitsPerMeter(2.0f));
  EXPECT_TRUE(LinearDensityInUnitsPerMeter(2.0f) >
              LinearDensityInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LinearDensityInUnitsPerMeter(1.0f) <=
              LinearDensityInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LinearDensityInUnitsPerMeter(1.0f) >=
              LinearDensityInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LinearDensityInUnitsPerMeter(1.0f) ==
              LinearDensityInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LinearDensityInUnitsPerMeter(1.0f) !=
              LinearDensityInUnitsPerMeter(2.0f));
}

TEST(LinearDensity, Operators) {
  LinearDensity ld1 = LinearDensityInUnitsPerMeter(1.5f);
  LinearDensity ld2 = LinearDensityInUnitsPerMeter(2.5f);

  LinearDensity ld3 = ld1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, ld3.inUnitsPerMeter());

  ld3 = 2.0f * ld1;
  EXPECT_FLOAT_EQ(3.0f, ld3.inUnitsPerMeter());

  ld3 = ld2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, ld3.inUnitsPerMeter());

  float ratio = ld2 / ld1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  Length len = LengthInMeters(2.0f);
  float product = len * ld1;
  EXPECT_FLOAT_EQ(3.0f, product);

  product = ld1 * len;
  EXPECT_FLOAT_EQ(3.0f, product);

  len = 6.0f / ld1;
  EXPECT_FLOAT_EQ(4.0f, len.inMeters());

  ld3 = 6.0f / len;
  EXPECT_FLOAT_EQ(1.5f, ld3.inUnitsPerMeter());

  ld2 *= 2.0f;
  EXPECT_FLOAT_EQ(5.0f, ld2.inUnitsPerMeter());
  ld2 /= 2.0f;
  EXPECT_FLOAT_EQ(2.5f, ld2.inUnitsPerMeter());
  EXPECT_EQ(3.0f, LengthInMeters(6) * LinearDensityInUnitsPerMeter(0.5f));
}

TEST(LinearDensity, AsString) {
  EXPECT_EQ("1.5/m", LinearDensityInUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1500/m", LinearDensityInKiloUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e+06/m", LinearDensityInMegaUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e+09/m", LinearDensityInGigaUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("0.0015/m", LinearDensityInMilliUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e-06/m", LinearDensityInMicroUnitsPerMeter(1.5f).asString());
}

}  // namespace roo_quantity