#include "gtest/gtest.h"
#include "roo_quantity/current.h"

namespace roo_quantity {

TEST(Current, UnitConversionSi) {
  Current c = CurrentInAmperes(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inAmperes());
  EXPECT_FLOAT_EQ(0.0015f, c.inKiloAmperes());
  EXPECT_FLOAT_EQ(1500.0f, c.inMilliAmperes());
  EXPECT_FLOAT_EQ(1500000.0f, c.inMicroAmperes());

  c = CurrentInKiloAmperes(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, c.inAmperes());

  c = CurrentInMilliAmperes(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inAmperes());

  c = CurrentInMicroAmperes(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMilliAmperes());

  c = CurrentInAmperes(-2);
  EXPECT_FLOAT_EQ(-2.0f, c.inAmperes());
}

TEST(Current, Comparison) {
  EXPECT_TRUE(CurrentInAmperes(1.0f) < CurrentInAmperes(2.0f));
  EXPECT_TRUE(CurrentInAmperes(2.0f) > CurrentInAmperes(1.0f));
  EXPECT_TRUE(CurrentInAmperes(1.0f) <= CurrentInAmperes(1.0f));
  EXPECT_TRUE(CurrentInAmperes(1.0f) >= CurrentInAmperes(1.0f));
  EXPECT_TRUE(CurrentInAmperes(1.0f) == CurrentInAmperes(1.0f));
  EXPECT_TRUE(CurrentInAmperes(1.0f) != CurrentInAmperes(2.0f));
}

TEST(Current, Operators) {
  Current c1 = CurrentInAmperes(1.5f);
  Current c2 = CurrentInAmperes(2.5f);

  Current c3 = c1 + c2;
  EXPECT_FLOAT_EQ(4.0f, c3.inAmperes());

  c3 = c2 - c1;
  EXPECT_FLOAT_EQ(1.0f, c3.inAmperes());

  c1 += c2;
  EXPECT_FLOAT_EQ(4.0f, c1.inAmperes());
  c1 -= c2;
  EXPECT_FLOAT_EQ(1.5f, c1.inAmperes());

  c3 = c1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, c3.inAmperes());

  c3 = 2.0f * c1;
  EXPECT_FLOAT_EQ(3.0f, c3.inAmperes());

  c3 = c2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, c3.inAmperes());

  float ratio = c2 / c1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  c1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, c1.inAmperes());
  c1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, c1.inAmperes());
}

TEST(Current, VsCharge) {
  Current i = CurrentInAmperes(2.0f);
  Time t = TimeInSeconds(0.5f);
  Charge c = i * t;
  EXPECT_FLOAT_EQ(1.0f, c.inCoulombs());
  c = t * i;
  EXPECT_FLOAT_EQ(1.0f, c.inCoulombs());
  i = c / t;
  EXPECT_FLOAT_EQ(2.0f, i.inAmperes());
  t = c / i;
  EXPECT_FLOAT_EQ(0.5f, t.inSeconds());
}

TEST(Current, AsString) {
  EXPECT_EQ("15.5 MA", CurrentInMegaAmperes(15.5f).asString());
  EXPECT_EQ("15.5 kA", CurrentInKiloAmperes(15.5f).asString());
  EXPECT_EQ("1.5 A", CurrentInAmperes(1.5f).asString());
  EXPECT_EQ("15.5 mA", CurrentInAmperes(0.0155f).asString());
  EXPECT_EQ("150.3 µA", CurrentInAmperes(0.0001503f).asString());
  EXPECT_EQ("20 nA", CurrentInAmperes(0.00000002f).asString());
  EXPECT_EQ("? A", UnknownCurrent().asString());
  EXPECT_EQ("-2 A", CurrentInAmperes(-2).asString());
  EXPECT_EQ("0 A", CurrentInAmperes(0).asString());
}

}  // namespace roo_quantity
