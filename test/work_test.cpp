#include "roo_quantity/work.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Work, UnitConversion) {
  Work w = WorkInJoules(1.5f);
  EXPECT_FLOAT_EQ(1.5f, w.inJoules());
  EXPECT_FLOAT_EQ(0.0015f, w.inKiloJoules());
  EXPECT_FLOAT_EQ(1500.0f, w.inMilliJoules());
  EXPECT_FLOAT_EQ(1500000.0f, w.inMicroJoules());

  w = WorkInKiloJoules(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, w.inJoules());

  w = WorkInMilliJoules(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, w.inJoules());

  w = WorkInMicroJoules(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, w.inMilliJoules());

  w = WorkInJoules(-2);
  EXPECT_FLOAT_EQ(-2.0f, w.inJoules());

  w = WorkInKiloJoules(2);
  EXPECT_FLOAT_EQ(2000.0f, w.inJoules());

  w = WorkInMegaJoules(2);
  EXPECT_FLOAT_EQ(2000000.0f, w.inJoules());

  w = WorkInGigaJoules(2);
  EXPECT_FLOAT_EQ(2000000000.0f, w.inJoules());
}

TEST(Work, Comparison) {
  EXPECT_TRUE(WorkInJoules(1.0f) < WorkInJoules(2.0f));
  EXPECT_TRUE(WorkInJoules(2.0f) > WorkInJoules(1.0f));
  EXPECT_TRUE(WorkInJoules(1.0f) <= WorkInJoules(1.0f));
  EXPECT_TRUE(WorkInJoules(1.0f) >= WorkInJoules(1.0f));
  EXPECT_TRUE(WorkInJoules(1.0f) == WorkInJoules(1.0f));
  EXPECT_TRUE(WorkInJoules(1.0f) != WorkInJoules(2.0f));
}

TEST(Work, Operators) {
  Work w1 = WorkInJoules(1.5f);
  Work w2 = WorkInJoules(2.5f);

  Work w3 = w1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, w3.inJoules());

  w3 = 2.0f * w1;
  EXPECT_FLOAT_EQ(3.0f, w3.inJoules());

  w3 = w2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, w3.inJoules());

  float ratio = w2 / w1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  w1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, w1.inJoules());
  w1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, w1.inJoules());
}

TEST(Work, AsString) {
  EXPECT_EQ("1.5 GJ", WorkInGigaJoules(1.5f).asString());
  EXPECT_EQ("1.5 MJ", WorkInMegaJoules(1.5f).asString());
  EXPECT_EQ("1.5 kJ", WorkInKiloJoules(1.5f).asString());
  EXPECT_EQ("1.5 J", WorkInJoules(1.5f).asString());
  EXPECT_EQ("1.5 mJ", WorkInMilliJoules(1.5f).asString());
  EXPECT_EQ("1.5 µJ", WorkInMicroJoules(1.5f).asString());
  EXPECT_EQ("0 J", WorkInJoules(0.0f).asString());
  EXPECT_EQ("? J", UnknownWork().asString());
  EXPECT_EQ("-2 J", WorkInJoules(-2).asString());
}

}  // namespace roo_quantity
