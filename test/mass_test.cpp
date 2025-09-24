#include "roo_quantity/mass.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Mass, UnitConversionSi) {
  Mass c = MassInKg(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inKg());
  EXPECT_FLOAT_EQ(0.0015f, c.inTons());
  EXPECT_FLOAT_EQ(1500.0f, c.inGrams());
  EXPECT_FLOAT_EQ(1500000.0f, c.inMilligrams());
  EXPECT_FLOAT_EQ(1500000000.0f, c.inMicrograms());

  c = MassInTons(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, c.inKg());

  c = MassInGrams(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inKilograms());

  c = MassInMilligrams(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inGrams());

  c = MassInMicrograms(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMilligrams());

  c = MassInKilograms(-2);
  EXPECT_FLOAT_EQ(-2.0f, c.inKg());
}

TEST(Mass, UnitConversionImperial) {
  Mass c = MassInKg(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inKg());
  EXPECT_FLOAT_EQ(3.30693393f, c.inLbs());

  c = MassInLbs(2.0f);
  EXPECT_FLOAT_EQ(0.90718474f, c.inKg());
}

TEST(Mass, Comparison) {
  EXPECT_TRUE(MassInKg(1.0f) < MassInKg(2.0f));
  EXPECT_TRUE(MassInKg(2.0f) > MassInKg(1.0f));
  EXPECT_TRUE(MassInKg(1.0f) <= MassInKg(1.0f));
  EXPECT_TRUE(MassInKg(1.0f) >= MassInKg(1.0f));
  EXPECT_TRUE(MassInKg(1.0f) == MassInKg(1.0f));
  EXPECT_TRUE(MassInKg(1.0f) != MassInKg(2.0f));
}

TEST(Mass, Operators) {
  Mass c1 = MassInKg(1.5f);
  Mass c2 = MassInKg(2.5f);
  Mass c3 = c1 + c2;
  EXPECT_FLOAT_EQ(4.0f, c3.inKg());
  c3 = c2 - c1;
  EXPECT_FLOAT_EQ(1.0f, c3.inKg());
  c1 += c2;
  EXPECT_FLOAT_EQ(4.0f, c1.inKg());
  c1 -= c2;
  EXPECT_FLOAT_EQ(1.5f, c1.inKg());
  c3 = c1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, c3.inKg());
  c3 = 2.0f * c1;
  EXPECT_FLOAT_EQ(3.0f, c3.inKg());
  c3 = c2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, c3.inKg());
  float ratio = c2 / c1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);
  c1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, c1.inKg());
  c1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, c1.inKg());
}

TEST(Mass, AsString) {
  EXPECT_EQ("15.5 kg", MassInKg(15.5f).asString());
  EXPECT_EQ("1.5 t", MassInTons(1.5f).asString());
  EXPECT_EQ("15.5 mg", MassInGrams(0.0155f).asString());
  EXPECT_EQ("150.3 µg", MassInGrams(0.0001503f).asString());
  EXPECT_EQ("? kg", UnknownMass().asString());
  EXPECT_EQ("-2 kg", MassInKg(-2).asString());
  EXPECT_EQ("0 kg", MassInKg(0).asString());
}

}  // namespace roo_quantity
