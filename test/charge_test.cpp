#include "roo_quantity/charge.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Charge, UnitConversionSi) {
  Charge c = ChargeInCoulombs(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inCoulombs());
  EXPECT_FLOAT_EQ(0.0015f, c.inKiloCoulombs());
  EXPECT_FLOAT_EQ(1500.0f, c.inMilliCoulombs());
  EXPECT_FLOAT_EQ(1500000.0f, c.inMicroCoulombs());

  c = ChargeInKiloCoulombs(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, c.inCoulombs());

  c = ChargeInMilliCoulombs(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inCoulombs());

  c = ChargeInMicroCoulombs(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMilliCoulombs());

  c = ChargeInCoulombs(-2);
  EXPECT_FLOAT_EQ(-2.0f, c.inCoulombs());
}

TEST(Charge, Comparison) {
  EXPECT_TRUE(ChargeInCoulombs(1.0f) < ChargeInCoulombs(2.0f));
  EXPECT_TRUE(ChargeInCoulombs(2.0f) > ChargeInCoulombs(1.0f));
  EXPECT_TRUE(ChargeInCoulombs(1.0f) <= ChargeInCoulombs(1.0f));
  EXPECT_TRUE(ChargeInCoulombs(1.0f) >= ChargeInCoulombs(1.0f));
  EXPECT_TRUE(ChargeInCoulombs(1.0f) == ChargeInCoulombs(1.0f));
  EXPECT_TRUE(ChargeInCoulombs(1.0f) != ChargeInCoulombs(2.0f));
}

TEST(Charge, Operators) {
  Charge c1 = ChargeInCoulombs(1.5f);
  Charge c2 = ChargeInCoulombs(2.5f);

  Charge c3 = c1 + c2;
  EXPECT_FLOAT_EQ(4.0f, c3.inCoulombs());

  c3 = c2 - c1;
  EXPECT_FLOAT_EQ(1.0f, c3.inCoulombs());

  c1 += c2;
  EXPECT_FLOAT_EQ(4.0f, c1.inCoulombs());
  c1 -= c2;
  EXPECT_FLOAT_EQ(1.5f, c1.inCoulombs());

  c3 = c1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, c3.inCoulombs());

  c3 = 2.0f * c1;
  EXPECT_FLOAT_EQ(3.0f, c3.inCoulombs());

  c3 = c2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, c3.inCoulombs());

  float ratio = c2 / c1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  c1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, c1.inCoulombs());
  c1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, c1.inCoulombs());
}

TEST(Charge, AsString) {
  EXPECT_EQ("1.5 C", ChargeInCoulombs(1.5f).asString());
  EXPECT_EQ("15.5 kC", ChargeInKiloCoulombs(15.5f).asString());
  EXPECT_EQ("15.5 mC", ChargeInCoulombs(0.0155f).asString());
  EXPECT_EQ("150.3 µC", ChargeInCoulombs(0.0001503f).asString());
  EXPECT_EQ("20 nC", ChargeInCoulombs(0.00000002f).asString());
  EXPECT_EQ("? C", UnknownCharge().asString());
  EXPECT_EQ("-2 C", ChargeInCoulombs(-2).asString());
  EXPECT_EQ("0 C", ChargeInCoulombs(0).asString());
}

}  // namespace roo_quantity
