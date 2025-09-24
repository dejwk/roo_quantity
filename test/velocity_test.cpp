#include "roo_quantity/velocity.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Velocity, UnitConversionSi) {
  Velocity c = VelocityInMetersPerSecond(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inMetersPerSecond());
  EXPECT_FLOAT_EQ(0.0015f, c.inKilometersPerSecond());
  EXPECT_FLOAT_EQ(1500.0f, c.inMillimetersPerSecond());
  EXPECT_FLOAT_EQ(1500000.0f, c.inMicrometersPerSecond());

  c = VelocityInKilometersPerSecond(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, c.inMetersPerSecond());

  c = VelocityInMillimetersPerSecond(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMetersPerSecond());

  c = VelocityInMicrometersPerSecond(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMillimetersPerSecond());

  c = VelocityInMetersPerSecond(-2);
  EXPECT_FLOAT_EQ(-2.0f, c.inMetersPerSecond());
}

TEST(Velocity, UnitConversionImperial) {
  Velocity c = VelocityInMetersPerSecond(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inMetersPerSecond());
  EXPECT_FLOAT_EQ(3.3554044381f, c.inMilesPerHour());
  EXPECT_FLOAT_EQ(2.9157667387f, c.inKnots());

  c = VelocityInMph(2.0f);
  EXPECT_FLOAT_EQ(0.89408f, c.inMetersPerSecond());
}

TEST(Velocity, Comparison) {
  EXPECT_TRUE(VelocityInMetersPerSecond(1.0f) <
              VelocityInMetersPerSecond(2.0f));
  EXPECT_TRUE(VelocityInMetersPerSecond(2.0f) >
              VelocityInMetersPerSecond(1.0f));
  EXPECT_TRUE(VelocityInMetersPerSecond(1.0f) <=
              VelocityInMetersPerSecond(1.0f));
  EXPECT_TRUE(VelocityInMetersPerSecond(1.0f) >=
              VelocityInMetersPerSecond(1.0f));
  EXPECT_TRUE(VelocityInMetersPerSecond(1.0f) ==
              VelocityInMetersPerSecond(1.0f));
  EXPECT_TRUE(VelocityInMetersPerSecond(1.0f) !=
              VelocityInMetersPerSecond(2.0f));
}

TEST(Velocity, Operators) {
  Velocity c1 = VelocityInMetersPerSecond(1.5f);
  Velocity c2 = VelocityInMetersPerSecond(2.5f);

  Velocity c3 = c1 + c2;
  EXPECT_FLOAT_EQ(4.0f, c3.inMetersPerSecond());

  c3 = c2 - c1;
  EXPECT_FLOAT_EQ(1.0f, c3.inMetersPerSecond());

  c1 += c2;
  EXPECT_FLOAT_EQ(4.0f, c1.inMetersPerSecond());
  c1 -= c2;
  EXPECT_FLOAT_EQ(1.5f, c1.inMetersPerSecond());

  c3 = c1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, c3.inMetersPerSecond());

  c3 = 2.0f * c1;
  EXPECT_FLOAT_EQ(3.0f, c3.inMetersPerSecond());

  c3 = c2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, c3.inMetersPerSecond());

  float ratio = c2 / c1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  c1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, c1.inMetersPerSecond());
  c1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, c1.inMetersPerSecond());
}

TEST(Velocity, VsLength) {
  Velocity p = VelocityInMetersPerSecond(2.0f);
  Time t = TimeInSeconds(3.0f);
  Length l = p * t;
  EXPECT_FLOAT_EQ(6.0f, l.inMeters());
  l = t * p;
  EXPECT_FLOAT_EQ(6.0f, l.inMeters());
  p = l / t;
  EXPECT_FLOAT_EQ(2.0f, p.inMetersPerSecond());
  t = l / p;
  EXPECT_FLOAT_EQ(3.0f, t.inSeconds());
}

TEST(Velocity, AsString) {
  EXPECT_EQ("15.5 km/s", VelocityInKilometersPerSecond(15.5f).asString());
  EXPECT_EQ("1.5 m/s", VelocityInMetersPerSecond(1.5f).asString());
  EXPECT_EQ("15.5 mm/s", VelocityInMetersPerSecond(0.0155f).asString());
  EXPECT_EQ("150.3 µm/s", VelocityInMetersPerSecond(0.0001503f).asString());
  EXPECT_EQ("? m/s", UnknownVelocity().asString());
  EXPECT_EQ("-2 m/s", VelocityInMetersPerSecond(-2).asString());
  EXPECT_EQ("0 m/s", VelocityInMetersPerSecond(0).asString());
}

}  // namespace roo_quantity
