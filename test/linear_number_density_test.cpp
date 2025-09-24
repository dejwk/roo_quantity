#include "gtest/gtest.h"
#include "roo_quantity/linear_number_density.h"

namespace roo_quantity {

TEST(LinearNumberDensity, ConversionSi) {
  LinearNumberDensity ld = LinearNumberDensityInUnitsPerMeter(1.5f);
  EXPECT_FLOAT_EQ(1.5f, ld.inUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0015f, ld.inKiloUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0000015f, ld.inMegaUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0000000015f, ld.inGigaUnitsPerMeter());
  EXPECT_FLOAT_EQ(1500.0f, ld.inMilliUnitsPerMeter());
  EXPECT_FLOAT_EQ(1500000.0f, ld.inMicroUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.015f, ld.inUnitsPerCentimeter());
  EXPECT_FLOAT_EQ(0.0015f, ld.inUnitsPerMillimeter());
  EXPECT_FLOAT_EQ(1500.0f, ld.inUnitsPerKilometer());

  ld = LinearNumberDensityInKiloUnitsPerMeter(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, ld.inUnitsPerMeter());

  ld = LinearNumberDensityInMilliUnitsPerMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, ld.inUnitsPerMeter());

  ld = LinearNumberDensityInMicroUnitsPerMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, ld.inMilliUnitsPerMeter());

  ld = LinearNumberDensityInUnitsPerCentimeter(2500.0f);
  EXPECT_FLOAT_EQ(250000.0f, ld.inUnitsPerMeter());

  ld = LinearNumberDensityInUnitsPerMillimeter(2500.0f);
  EXPECT_FLOAT_EQ(2500000.0f, ld.inUnitsPerMeter());

  ld = LinearNumberDensityInUnitsPerKilometer(2);
  EXPECT_FLOAT_EQ(0.002f, ld.inUnitsPerMeter());
}

TEST(LinearNumberDensity, ConversionNonSi) {
  LinearNumberDensity ld = LinearNumberDensityInUnitsPerMeter(1.0f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0254f, ld.inUnitsPerInch());
  EXPECT_FLOAT_EQ(0.3048f, ld.inUnitsPerFoot());
  EXPECT_FLOAT_EQ(0.9144f, ld.inUnitsPerYard());

  ld = LinearNumberDensityInUnitsPerInch(0.0254f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());

  ld = LinearNumberDensityInUnitsPerFoot(0.3048f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());

  ld = LinearNumberDensityInUnitsPerYard(0.9144f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());
}

TEST(LinearNumberDensity, Comparison) {
  EXPECT_TRUE(LinearNumberDensityInUnitsPerMeter(1.0f) <
              LinearNumberDensityInUnitsPerMeter(2.0f));
  EXPECT_TRUE(LinearNumberDensityInUnitsPerMeter(2.0f) >
              LinearNumberDensityInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LinearNumberDensityInUnitsPerMeter(1.0f) <=
              LinearNumberDensityInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LinearNumberDensityInUnitsPerMeter(1.0f) >=
              LinearNumberDensityInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LinearNumberDensityInUnitsPerMeter(1.0f) ==
              LinearNumberDensityInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LinearNumberDensityInUnitsPerMeter(1.0f) !=
              LinearNumberDensityInUnitsPerMeter(2.0f));
}

TEST(LinearNumberDensity, Operators) {
  LinearNumberDensity ld1 = LinearNumberDensityInUnitsPerMeter(1.5f);
  LinearNumberDensity ld2 = LinearNumberDensityInUnitsPerMeter(2.5f);

  LinearNumberDensity ld3 = ld1 * 2.0f;
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
  EXPECT_EQ(3.0f, LengthInMeters(6) * LinearNumberDensityInUnitsPerMeter(0.5f));
}

TEST(LinearNumberDensity, AsString) {
  EXPECT_EQ("1.5/m", LinearNumberDensityInUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1500/m", LinearNumberDensityInKiloUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e+06/m",
            LinearNumberDensityInMegaUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e+09/m",
            LinearNumberDensityInGigaUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("0.0015/m",
            LinearNumberDensityInMilliUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e-06/m",
            LinearNumberDensityInMicroUnitsPerMeter(1.5f).asString());
}

}  // namespace roo_quantity