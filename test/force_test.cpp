#include "roo_quantity/force.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Force, UnitConversion) {
  Force f = ForceInNewtons(1.5f);
  EXPECT_FLOAT_EQ(1.5f, f.inNewtons());
  EXPECT_FLOAT_EQ(0.0015f, f.inKiloNewtons());
  EXPECT_FLOAT_EQ(1500.0f, f.inMilliNewtons());
  EXPECT_FLOAT_EQ(1500000.0f, f.inMicroNewtons());

  f = ForceInKiloNewtons(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, f.inNewtons());

  f = ForceInMilliNewtons(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, f.inNewtons());

  f = ForceInMicroNewtons(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, f.inMilliNewtons());

  f = ForceInNewtons(-2);
  EXPECT_FLOAT_EQ(-2.0f, f.inNewtons());

  f = ForceInKiloNewtons(2);
  EXPECT_FLOAT_EQ(2000.0f, f.inNewtons());

  f = ForceInMegaNewtons(2);
  EXPECT_FLOAT_EQ(2000000.0f, f.inNewtons());

  f = ForceInGigaNewtons(2);
  EXPECT_FLOAT_EQ(2000000000.0f, f.inNewtons());
}

TEST(Force, Comparison) {
  EXPECT_TRUE(ForceInNewtons(1.0f) < ForceInNewtons(2.0f));
  EXPECT_TRUE(ForceInNewtons(2.0f) > ForceInNewtons(1.0f));
  EXPECT_TRUE(ForceInNewtons(1.0f) <= ForceInNewtons(1.0f));
  EXPECT_TRUE(ForceInNewtons(1.0f) >= ForceInNewtons(1.0f));
  EXPECT_TRUE(ForceInNewtons(1.0f) == ForceInNewtons(1.0f));
  EXPECT_TRUE(ForceInNewtons(1.0f) != ForceInNewtons(2.0f));
}

TEST(Force, Operators) {
  Force f1 = ForceInNewtons(1.5f);
  Force f2 = ForceInNewtons(2.5f);

  Force f3 = f1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, f3.inNewtons());

  f3 = 2.0f * f1;
  EXPECT_FLOAT_EQ(3.0f, f3.inNewtons());

  f3 = f2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, f3.inNewtons());

  float ratio = f2 / f1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  f1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, f1.inNewtons());
  f1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, f1.inNewtons());
}

TEST(Force, Reciprocal) {
  Force f = ForceInNewtons(1.5f);
  Length l = LengthInMeters(2.0f);
  Work w = f * l;
  EXPECT_FLOAT_EQ(3.0f, w.inJoules());
  w = l * f;
  EXPECT_FLOAT_EQ(3.0f, w.inJoules());
  f = w / l;
  EXPECT_FLOAT_EQ(1.5f, f.inNewtons());
  l = w / f;
  EXPECT_FLOAT_EQ(2.0f, l.inMeters());
}

TEST(Force, AsString) {
  EXPECT_EQ("1.5 MN", ForceInMegaNewtons(1.5f).asString());
  EXPECT_EQ("1.5 kN", ForceInKiloNewtons(1.5f).asString());
  EXPECT_EQ("1.5 N", ForceInNewtons(1.5f).asString());
  EXPECT_EQ("1.5 mN", ForceInMilliNewtons(1.5f).asString());
  EXPECT_EQ("1.5 µN", ForceInMicroNewtons(1.5f).asString());
  EXPECT_EQ("0 N", ForceInNewtons(0.0f).asString());
  EXPECT_EQ("? N", UnknownForce().asString());
  EXPECT_EQ("-2 N", ForceInNewtons(-2.0f).asString());
}

}  // namespace roo_quantity
