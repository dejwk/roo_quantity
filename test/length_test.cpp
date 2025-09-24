#include "roo_quantity/length.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Length, ConversionSi) {
  Length t = LengthInMeters(1.5f);
  EXPECT_FLOAT_EQ(1.5f, t.inMeters());
  EXPECT_FLOAT_EQ(1500.0f, t.inMillimeters());
  EXPECT_FLOAT_EQ(1500000.0f, t.inMicrometers());
  EXPECT_FLOAT_EQ(1500000000.0f, t.inNanometers());

  t = LengthInMillimeters(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, t.inMeters());

  t = LengthInMicrometers(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, t.inMillimeters());

  t = LengthInNanometers(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, t.inMicrometers());

  t = LengthInMeters(-2);
  EXPECT_FLOAT_EQ(-2.0f, t.inMeters());
}

TEST(Length, ConversionNonSi) {
  Length t = LengthInMeters(1.0f);
  EXPECT_FLOAT_EQ(1.0f, t.inMeters());
  EXPECT_FLOAT_EQ(39.37007874f, t.inInches());
  EXPECT_FLOAT_EQ(3.280839895f, t.inFeet());
  EXPECT_FLOAT_EQ(1.057000834E-16f, t.inLightYears());

  t = LengthInInches(25.4f);
  EXPECT_FLOAT_EQ(0.64516f, t.inMeters());

  t = LengthInFeet(3.280839895f);
  EXPECT_FLOAT_EQ(1.0f, t.inMeters());

  t = LengthInYards(1.0936132983f);
  EXPECT_FLOAT_EQ(1.0f, t.inMeters());

  t = LengthInLightYears(1.057000834E-16f);
  EXPECT_FLOAT_EQ(1.0f, t.inMeters());
}

TEST(Length, Comparison) {
  EXPECT_TRUE(LengthInMeters(1.0f) < LengthInMeters(2.0f));
  EXPECT_TRUE(LengthInMeters(2.0f) > LengthInMeters(1.0f));
  EXPECT_TRUE(LengthInMeters(1.0f) <= LengthInMeters(1.0f));
  EXPECT_TRUE(LengthInMeters(1.0f) >= LengthInMeters(1.0f));
  EXPECT_TRUE(LengthInMeters(1.0f) == LengthInMeters(1.0f));
  EXPECT_TRUE(LengthInMeters(1.0f) != LengthInMeters(2.0f));
}

TEST(Length, Operators) {
  Length t1 = LengthInMeters(1.5f);
  Length t2 = LengthInMeters(2.5f);
  Length t3 = t1 + t2;
  EXPECT_FLOAT_EQ(4.0f, t3.inMeters());

  t3 = t2 - t1;
  EXPECT_FLOAT_EQ(1.0f, t3.inMeters());

  t3 = t1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, t3.inMeters());

  t3 = 2.0f * t1;
  EXPECT_FLOAT_EQ(3.0f, t3.inMeters());

  t3 = t2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, t3.inMeters());

  float f = t2 / t1;
  EXPECT_FLOAT_EQ(5.0f / 3.0f, f);

  t2 += t1;
  EXPECT_FLOAT_EQ(4.0f, t2.inMeters());
  t2 -= t1;
  EXPECT_FLOAT_EQ(2.5f, t2.inMeters());

  t2 *= 2.0f;
  EXPECT_FLOAT_EQ(5.0f, t2.inMeters());
  t2 /= 2.0f;
  EXPECT_FLOAT_EQ(2.5f, t2.inMeters());
}

TEST(Length, AsString) {
  EXPECT_EQ("1.5 m", LengthInMeters(1.5f).asString());
  EXPECT_EQ("15.5 mm", LengthInMeters(0.0155f).asString());
  EXPECT_EQ("50 cm", LengthInMeters(0.5f).asString());
  EXPECT_EQ("150.3 µm", LengthInMeters(0.0001503f).asString());
  EXPECT_EQ("20 nm", LengthInMeters(0.00000002f).asString());
  EXPECT_EQ("? m", UnknownLength().asString());
  EXPECT_EQ("-2 m", LengthInMeters(-2).asString());
  EXPECT_EQ("0 m", LengthInMeters(0).asString());
}

}  // namespace roo_quantity
