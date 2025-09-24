#include "roo_quantity/area.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Area, ConversionSi) {
  Area a = AreaInSquareMeters(1.5f);
  EXPECT_FLOAT_EQ(1.5f, a.inSquareMeters());
  EXPECT_FLOAT_EQ(150.0f, a.inSquareDecimeters());
  EXPECT_FLOAT_EQ(15000.0f, a.inSquareCentimeters());
  EXPECT_FLOAT_EQ(1500000.0f, a.inSquareMillimeters());
  EXPECT_FLOAT_EQ(1500000000000.0f, a.inSquareMicrometers());
  EXPECT_FLOAT_EQ(0.0000015f, a.inSquareKilometers());
  EXPECT_FLOAT_EQ(0.000015f, a.inHectares());
  EXPECT_FLOAT_EQ(0.015f, a.inAres());
}

TEST(Area, ConversionNonSi) {
  Area a = AreaInSquareMeters(1.0f);
  EXPECT_FLOAT_EQ(1.0f, a.inSquareMeters());
  EXPECT_FLOAT_EQ(0.000247105f, a.inAcres());
  EXPECT_FLOAT_EQ(1550.0031f, a.inSquareInches());

  a = AreaInSquareMeters(2500.0f);
  EXPECT_FLOAT_EQ(0.6177625f, a.inAcres());
  EXPECT_FLOAT_EQ(3875007.75f, a.inSquareInches());
}

TEST(Area, Comparison) {
  EXPECT_TRUE(AreaInSquareMeters(1.0f) < AreaInSquareMeters(2.0f));
  EXPECT_TRUE(AreaInSquareMeters(2.0f) > AreaInSquareMeters(1.0f));
  EXPECT_TRUE(AreaInSquareMeters(1.0f) <= AreaInSquareMeters(1.0f));
  EXPECT_TRUE(AreaInSquareMeters(1.0f) >= AreaInSquareMeters(1.0f));
  EXPECT_TRUE(AreaInSquareMeters(1.0f) == AreaInSquareMeters(1.0f));
  EXPECT_TRUE(AreaInSquareMeters(1.0f) != AreaInSquareMeters(2.0f));
}

TEST(Area, Operators) {
  Area a1 = AreaInSquareMeters(1.5f);
  Area a2 = AreaInSquareMeters(2.5f);
  Area a3 = a1 + a2;
  EXPECT_FLOAT_EQ(4.0f, a3.inSquareMeters());

  a3 = a2 - a1;
  EXPECT_FLOAT_EQ(1.0f, a3.inSquareMeters());

  a3 = a1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, a3.inSquareMeters());

  a3 = a2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, a3.inSquareMeters());

  a1 += a2;
  EXPECT_FLOAT_EQ(4.0f, a1.inSquareMeters());
  a1 -= a2;
  EXPECT_FLOAT_EQ(1.5f, a1.inSquareMeters());

  a1 *= 2.0;
  EXPECT_FLOAT_EQ(3.0f, a1.inSquareMeters());
  a1 /= 2.0;
  EXPECT_FLOAT_EQ(1.5f, a1.inSquareMeters());

  EXPECT_FLOAT_EQ(0.6f, a1 / a2);
}

TEST(Area, AsString) {
  EXPECT_EQ("1.5 m²", AreaInSquareMeters(1.5f).asString());
  EXPECT_EQ("1.5 km²", AreaInSquareKilometers(1.5f).asString());
}

}  // namespace roo_quantity