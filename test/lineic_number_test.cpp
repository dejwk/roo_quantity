#include "roo_quantity/lineic_number.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(LineicNumber, ConversionSi) {
  LineicNumber ld = LineicNumberInUnitsPerMeter(1.5f);
  EXPECT_FLOAT_EQ(1.5f, ld.inUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0015f, ld.inKiloUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0000015f, ld.inMegaUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0000000015f, ld.inGigaUnitsPerMeter());
  EXPECT_FLOAT_EQ(1500.0f, ld.inMilliUnitsPerMeter());
  EXPECT_FLOAT_EQ(1500000.0f, ld.inMicroUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.015f, ld.inUnitsPerCentimeter());
  EXPECT_FLOAT_EQ(0.0015f, ld.inUnitsPerMillimeter());
  EXPECT_FLOAT_EQ(1500.0f, ld.inUnitsPerKilometer());

  ld = LineicNumberInKiloUnitsPerMeter(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, ld.inUnitsPerMeter());

  ld = LineicNumberInMilliUnitsPerMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, ld.inUnitsPerMeter());

  ld = LineicNumberInMicroUnitsPerMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, ld.inMilliUnitsPerMeter());

  ld = LineicNumberInUnitsPerCentimeter(2500.0f);
  EXPECT_FLOAT_EQ(250000.0f, ld.inUnitsPerMeter());

  ld = LineicNumberInUnitsPerMillimeter(2500.0f);
  EXPECT_FLOAT_EQ(2500000.0f, ld.inUnitsPerMeter());

  ld = LineicNumberInUnitsPerKilometer(2);
  EXPECT_FLOAT_EQ(0.002f, ld.inUnitsPerMeter());
}

TEST(LineicNumber, ConversionNonSi) {
  LineicNumber ld = LineicNumberInUnitsPerMeter(1.0f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());
  EXPECT_FLOAT_EQ(0.0254f, ld.inUnitsPerInch());
  EXPECT_FLOAT_EQ(0.3048f, ld.inUnitsPerFoot());
  EXPECT_FLOAT_EQ(0.9144f, ld.inUnitsPerYard());

  ld = LineicNumberInUnitsPerInch(0.0254f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());

  ld = LineicNumberInUnitsPerFoot(0.3048f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());

  ld = LineicNumberInUnitsPerYard(0.9144f);
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());
}

TEST(LineicNumber, Comparison) {
  EXPECT_TRUE(LineicNumberInUnitsPerMeter(1.0f) <
              LineicNumberInUnitsPerMeter(2.0f));
  EXPECT_TRUE(LineicNumberInUnitsPerMeter(2.0f) >
              LineicNumberInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LineicNumberInUnitsPerMeter(1.0f) <=
              LineicNumberInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LineicNumberInUnitsPerMeter(1.0f) >=
              LineicNumberInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LineicNumberInUnitsPerMeter(1.0f) ==
              LineicNumberInUnitsPerMeter(1.0f));
  EXPECT_TRUE(LineicNumberInUnitsPerMeter(1.0f) !=
              LineicNumberInUnitsPerMeter(2.0f));
}

TEST(LineicNumber, Operators) {
  LineicNumber ld1 = LineicNumberInUnitsPerMeter(1.5f);
  LineicNumber ld2 = LineicNumberInUnitsPerMeter(2.5f);

  LineicNumber ld3 = ld1 * 2.0f;
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
  EXPECT_EQ(3.0f, LengthInMeters(6) * LineicNumberInUnitsPerMeter(0.5f));
}

TEST(LineicNumber, Reciprocal) {
  Length len = LengthInMeters(2.0f);
  LineicNumber ld = LineicNumberInUnitsPerMeter(0.5f);
  EXPECT_FLOAT_EQ(1.0f, (len * ld));
  EXPECT_FLOAT_EQ(1.0f, (ld * len));

  len = 4.0f / ld;
  EXPECT_FLOAT_EQ(8.0f, len.inMeters());

  ld = 8.0f / len;
  EXPECT_FLOAT_EQ(1.0f, ld.inUnitsPerMeter());
}

TEST(LineicNumber, AsString) {
  EXPECT_EQ("1.5/m", LineicNumberInUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1500/m", LineicNumberInKiloUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e+06/m", LineicNumberInMegaUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e+09/m", LineicNumberInGigaUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("0.0015/m", LineicNumberInMilliUnitsPerMeter(1.5f).asString());
  EXPECT_EQ("1.5e-06/m", LineicNumberInMicroUnitsPerMeter(1.5f).asString());
}

}  // namespace roo_quantity