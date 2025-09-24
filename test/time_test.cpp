#include "roo_quantity/time.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Time, Conversion) {
  Time t = TimeInSeconds(1.5f);
  EXPECT_FLOAT_EQ(1.5f, t.inSeconds());
  EXPECT_FLOAT_EQ(1500.0f, t.inMilliseconds());
  EXPECT_FLOAT_EQ(1500000.0f, t.inMicroseconds());
  EXPECT_FLOAT_EQ(1500000000.0f, t.inNanoseconds());

  t = TimeInHours(2.0f);
  EXPECT_FLOAT_EQ(7200.0f, t.inSeconds());

  t = TimeInMinutes(12.0f);
  EXPECT_FLOAT_EQ(720.0f, t.inSeconds());

  t = TimeInMilliseconds(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, t.inSeconds());

  t = TimeInMicroseconds(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, t.inMilliseconds());

  t = TimeInNanoseconds(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, t.inMicroseconds());

  t = TimeInSeconds(-2);
  EXPECT_FLOAT_EQ(-2.0f, t.inSeconds());
}

TEST(Time, Comparison) {
  EXPECT_TRUE(TimeInSeconds(1.0f) < TimeInSeconds(2.0f));
  EXPECT_TRUE(TimeInSeconds(2.0f) > TimeInSeconds(1.0f));
  EXPECT_TRUE(TimeInSeconds(1.0f) <= TimeInSeconds(1.0f));
  EXPECT_TRUE(TimeInSeconds(1.0f) >= TimeInSeconds(1.0f));
  EXPECT_TRUE(TimeInSeconds(1.0f) == TimeInSeconds(1.0f));
  EXPECT_TRUE(TimeInSeconds(1.0f) != TimeInSeconds(2.0f));
}

TEST(Time, Operators) {
  Time t1 = TimeInSeconds(1.5f);
  Time t2 = TimeInSeconds(2.5f);
  Time t3 = t1 + t2;
  EXPECT_FLOAT_EQ(4.0f, t3.inSeconds());

  t3 = t2 - t1;
  EXPECT_FLOAT_EQ(1.0f, t3.inSeconds());

  t3 = t1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, t3.inSeconds());

  t3 = 2.0f * t1;
  EXPECT_FLOAT_EQ(3.0f, t3.inSeconds());

  t3 = t2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, t3.inSeconds());

  float f = t2 / t1;
  EXPECT_FLOAT_EQ(5.0f / 3.0f, f);
}

TEST(Time, AsString) {
  EXPECT_EQ("1.5 s", TimeInSeconds(1.5f).asString());
  EXPECT_EQ("500 ms", TimeInSeconds(0.5f).asString());
  EXPECT_EQ("150.3 µs", TimeInSeconds(0.0001503f).asString());
  EXPECT_EQ("20 ns", TimeInSeconds(0.00000002f).asString());
  EXPECT_EQ("? s", UnknownTime().asString());
  EXPECT_EQ("-2 s", TimeInSeconds(-2).asString());
  EXPECT_EQ("0 s", TimeInSeconds(0).asString());
}

}  // namespace roo_quantity
