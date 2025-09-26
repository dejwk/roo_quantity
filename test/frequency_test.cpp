#include "roo_quantity/frequency.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Frequency, ConversionSi) {
  Frequency f = FrequencyInHertz(1.5f);
  EXPECT_FLOAT_EQ(1.5f, f.inHertz());
  EXPECT_FLOAT_EQ(0.0015f, f.inKiloHertz());
  EXPECT_FLOAT_EQ(1500.0f, f.inMilliHertz());
  EXPECT_FLOAT_EQ(1500000.0f, f.inMicroHertz());

  f = FrequencyInKiloHertz(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, f.inHertz());

  f = FrequencyInMilliHertz(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, f.inHertz());

  f = FrequencyInMicroHertz(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, f.inMilliHertz());

  f = FrequencyInHertz(-2);
  EXPECT_FLOAT_EQ(-2.0f, f.inHertz());

  f = FrequencyInKiloHertz(2);
  EXPECT_FLOAT_EQ(2000.0f, f.inHertz());

  f = FrequencyInMegaHertz(2);
  EXPECT_FLOAT_EQ(2000000.0f, f.inHertz());

  f = FrequencyInGigaHertz(2);
  EXPECT_FLOAT_EQ(2000000000.0f, f.inHertz());
}

TEST(Frequency, ConversionNonSi) {
  Frequency f = FrequencyInRPM(60.0f);
  EXPECT_FLOAT_EQ(1.0f, f.inHertz());
  EXPECT_FLOAT_EQ(60.0f, f.inRevolutionsPerMinute());
  EXPECT_FLOAT_EQ(60.0f, f.inRPM());
  EXPECT_FLOAT_EQ(2.0f * M_PI, f.inRadiansPerSecond());

  f = FrequencyInRadiansPerSecond(2.0f * M_PI);
  EXPECT_FLOAT_EQ(1.0f, f.inHertz());
  EXPECT_FLOAT_EQ(60.0f, f.inRevolutionsPerMinute());
  EXPECT_FLOAT_EQ(60.0f, f.inRPM());
}

TEST(Frequency, Comparison) {
  EXPECT_TRUE(FrequencyInHertz(1.0f) < FrequencyInHertz(2.0f));
  EXPECT_TRUE(FrequencyInHertz(2.0f) > FrequencyInHertz(1.0f));
  EXPECT_TRUE(FrequencyInHertz(1.0f) <= FrequencyInHertz(1.0f));
  EXPECT_TRUE(FrequencyInHertz(1.0f) >= FrequencyInHertz(1.0f));
  EXPECT_TRUE(FrequencyInHertz(1.0f) == FrequencyInHertz(1.0f));
  EXPECT_TRUE(FrequencyInHertz(1.0f) != FrequencyInHertz(2.0f));
}

TEST(Frequency, Operators) {
  Frequency f1 = FrequencyInHertz(1.5f);
  Frequency f2 = FrequencyInHertz(2.5f);

  Frequency f3 = f1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, f3.inHertz());

  f3 = 2.0f * f1;
  EXPECT_FLOAT_EQ(3.0f, f3.inHertz());

  f3 = f2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, f3.inHertz());

  float ratio = f2 / f1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  Time t1 = 2.0f / f1;
  EXPECT_FLOAT_EQ(1.3333333f, t1.inSeconds());

  Frequency f4 = 2.0f / t1;
  EXPECT_FLOAT_EQ(1.5f, f4.inHertz());

  f2 *= 2.0f;
  EXPECT_FLOAT_EQ(5.0f, f2.inHertz());
  f2 /= 2.0f;
  EXPECT_FLOAT_EQ(2.5f, f2.inHertz());

  EXPECT_EQ(3.0f, TimeInSeconds(6) * FrequencyInHertz(0.5f));
  EXPECT_EQ(3.0f, FrequencyInHertz(0.5f) * TimeInSeconds(6));
}

TEST(Frequency, String) {
  EXPECT_EQ("1.5 Hz", FrequencyInHertz(1.5f).asString());
  EXPECT_EQ("1.5 kHz", FrequencyInKiloHertz(1.5f).asString());
  EXPECT_EQ("1.5 MHz", FrequencyInMegaHertz(1.5f).asString());
  EXPECT_EQ("1.5 GHz", FrequencyInGigaHertz(1.5f).asString());
  EXPECT_EQ("1.5 mHz", FrequencyInMilliHertz(1.5f).asString());
  EXPECT_EQ("1.5 µHz", FrequencyInMicroHertz(1.5f).asString());
  EXPECT_EQ("? Hz", Frequency().asString());
}

}  // namespace roo_quantity
