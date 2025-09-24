#include "roo_quantity/power.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Power, UnitConversionSi) {
  Power c = PowerInWatts(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inWatts());
  EXPECT_FLOAT_EQ(0.0015f, c.inKiloWatts());
  EXPECT_FLOAT_EQ(1500.0f, c.inMilliWatts());
  EXPECT_FLOAT_EQ(1500000.0f, c.inMicroWatts());

  c = PowerInKiloWatts(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, c.inWatts());

  c = PowerInMilliWatts(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inWatts());

  c = PowerInMicroWatts(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMilliWatts());

  c = PowerInWatts(-2);
  EXPECT_FLOAT_EQ(-2.0f, c.inWatts());
}

TEST(Power, Comparison) {
  EXPECT_TRUE(PowerInWatts(1.0f) < PowerInWatts(2.0f));
  EXPECT_TRUE(PowerInWatts(2.0f) > PowerInWatts(1.0f));
  EXPECT_TRUE(PowerInWatts(1.0f) <= PowerInWatts(1.0f));
  EXPECT_TRUE(PowerInWatts(1.0f) >= PowerInWatts(1.0f));
  EXPECT_TRUE(PowerInWatts(1.0f) == PowerInWatts(1.0f));
  EXPECT_TRUE(PowerInWatts(1.0f) != PowerInWatts(2.0f));
}

TEST(Power, Operators) {
  Power c1 = PowerInWatts(1.5f);
  Power c2 = PowerInWatts(2.5f);

  Power c3 = c1 + c2;
  EXPECT_FLOAT_EQ(4.0f, c3.inWatts());

  c3 = c2 - c1;
  EXPECT_FLOAT_EQ(1.0f, c3.inWatts());

  c1 += c2;
  EXPECT_FLOAT_EQ(4.0f, c1.inWatts());
  c1 -= c2;
  EXPECT_FLOAT_EQ(1.5f, c1.inWatts());

  c3 = c1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, c3.inWatts());

  c3 = 2.0f * c1;
  EXPECT_FLOAT_EQ(3.0f, c3.inWatts());

  c3 = c2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, c3.inWatts());

  float ratio = c2 / c1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  c1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, c1.inWatts());
  c1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, c1.inWatts());
}

TEST(Power, VsWork) {
  Power p = PowerInWatts(2.0f);
  Time t = TimeInSeconds(0.5f);
  Work w = p * t;
  EXPECT_FLOAT_EQ(1.0f, w.inJoules());
  w = t * p;
  EXPECT_FLOAT_EQ(1.0f, w.inJoules());
  p = w / t;
  EXPECT_FLOAT_EQ(2.0f, p.inWatts());
  t = w / p;
  EXPECT_FLOAT_EQ(0.5f, t.inSeconds());
}

TEST(Power, AsString) {
  EXPECT_EQ("15.5 GW", PowerInGigaWatts(15.5f).asString());
  EXPECT_EQ("15.5 MW", PowerInMegaWatts(15.5f).asString());
  EXPECT_EQ("15.5 kW", PowerInKiloWatts(15.5f).asString());
  EXPECT_EQ("1.5 W", PowerInWatts(1.5f).asString());
  EXPECT_EQ("15.5 mW", PowerInWatts(0.0155f).asString());
  EXPECT_EQ("150.3 µW", PowerInWatts(0.0001503f).asString());
  EXPECT_EQ("20 nW", PowerInWatts(0.00000002f).asString());
  EXPECT_EQ("? W", UnknownPower().asString());
  EXPECT_EQ("-2 W", PowerInWatts(-2).asString());
  EXPECT_EQ("0 W", PowerInWatts(0).asString());
}

}  // namespace roo_quantity
