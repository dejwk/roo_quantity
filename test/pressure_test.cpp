#include "roo_quantity/pressure.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Pressure, UnitConversionSi) {
  Pressure p = PressureInPascals(1.5f);
  EXPECT_FLOAT_EQ(1.5f, p.inPascals());
  EXPECT_FLOAT_EQ(0.0015f, p.inKiloPascals());
  EXPECT_FLOAT_EQ(1500.0f, p.inMilliPascals());
  EXPECT_FLOAT_EQ(1500000.0f, p.inMicroPascals());
  EXPECT_FLOAT_EQ(0.0000015f, p.inMegaPascals());
  EXPECT_FLOAT_EQ(0.0000000015f, p.inGigaPascals());
  EXPECT_FLOAT_EQ(0.000015f, p.inBars());
  EXPECT_FLOAT_EQ(0.015f, p.inHectoPascals());

  p = PressureInKiloPascals(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, p.inPascals());

  p = PressureInMilliPascals(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, p.inPascals());

  p = PressureInMicroPascals(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, p.inMilliPascals());

  p = PressureInPascals(-2);
  EXPECT_FLOAT_EQ(-2.0f, p.inPascals());

  p = PressureInKiloPascals(2);
  EXPECT_FLOAT_EQ(2000.0f, p.inPascals());

  p = PressureInMegaPascals(2);
  EXPECT_FLOAT_EQ(2000000.0f, p.inPascals());

  p = PressureInGigaPascals(2);
  EXPECT_FLOAT_EQ(2000000000.0f, p.inPascals());
}

TEST(Pressure, UnitConversionNonSi) {
  Pressure p = PressureInPascals(1.0f);
  EXPECT_FLOAT_EQ(1.0f, p.inPascals());
  EXPECT_FLOAT_EQ(0.0001450377f, p.inPSI());

  p = PressureInPascals(2.5f);
  EXPECT_FLOAT_EQ(0.00036259425f, p.inPSI());
}

TEST(Pressure, Comparison) {
  EXPECT_TRUE(PressureInPascals(1.0f) < PressureInPascals(2.0f));
  EXPECT_TRUE(PressureInPascals(2.0f) > PressureInPascals(1.0f));
  EXPECT_TRUE(PressureInPascals(1.0f) <= PressureInPascals(1.0f));
  EXPECT_TRUE(PressureInPascals(1.0f) >= PressureInPascals(1.0f));
  EXPECT_TRUE(PressureInPascals(1.0f) == PressureInPascals(1.0f));
  EXPECT_TRUE(PressureInPascals(1.0f) != PressureInPascals(2.0f));
}

TEST(Pressure, Operators) {
  Pressure p1 = PressureInPascals(1.5f);
  Pressure p2 = PressureInPascals(2.5f);

  Pressure p3 = p1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, p3.inPascals());

  p3 = 2.0f * p1;
  EXPECT_FLOAT_EQ(3.0f, p3.inPascals());

  p3 = p2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, p3.inPascals());

  float ratio = p2 / p1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  p1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, p1.inPascals());
  p1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, p1.inPascals());

  p3 = p1 + p2;
  EXPECT_FLOAT_EQ(4.0f, p3.inPascals());

  p3 = p2 - p1;
  EXPECT_FLOAT_EQ(1.0f, p3.inPascals());

  p1 += p2;
  EXPECT_FLOAT_EQ(4.0f, p1.inPascals());
  p1 -= p2;
  EXPECT_FLOAT_EQ(1.5f, p1.inPascals());
}

TEST(Pressure, AsString) {
  EXPECT_EQ("1.5 Pa", PressureInPascals(1.5f).asString());
  EXPECT_EQ("1.5 kPa", PressureInKiloPascals(1.5f).asString());
  EXPECT_EQ("32 MPa", PressureInMegaPascals(32.0f).asString());
  EXPECT_EQ("15 bar", PressureInMegaPascals(1.5f).asString());
  EXPECT_EQ("1.5 GPa", PressureInGigaPascals(1.5f).asString());
  EXPECT_EQ("2.5 bar", PressureInBars(2.5f).asString());
  EXPECT_EQ("1.2 bar", PressureInHectoPascals(1200.0f).asString());
  EXPECT_EQ("1 bar", PressureInPascals(100000.0f).asString());
  EXPECT_EQ("0.3 bar", PressureInBars(0.3f).asString());
}

}  // namespace roo_quantity
