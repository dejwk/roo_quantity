#include "roo_quantity/resistance.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Resistance, UnitConversionSi) {
  Resistance c = ResistanceInOhms(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inOhms());
  EXPECT_FLOAT_EQ(0.0000000015f, c.inGigaOhms());
  EXPECT_FLOAT_EQ(0.0000015f, c.inMegaOhms());
  EXPECT_FLOAT_EQ(0.0015f, c.inKiloOhms());
  EXPECT_FLOAT_EQ(1500.0f, c.inMilliOhms());
  EXPECT_FLOAT_EQ(1500000.0f, c.inMicroOhms());

  c = ResistanceInGigaOhms(2.0f);
  EXPECT_FLOAT_EQ(2000000000.0f, c.inOhms());

  c = ResistanceInMegaOhms(2.0f);
  EXPECT_FLOAT_EQ(2000000.0f, c.inOhms());

  c = ResistanceInKiloOhms(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, c.inOhms());

  c = ResistanceInMilliOhms(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inOhms());

  c = ResistanceInMicroOhms(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMilliOhms());

  c = ResistanceInOhms(-2);
  EXPECT_FLOAT_EQ(-2.0f, c.inOhms());
}

TEST(Resistance, Comparison) {
  EXPECT_TRUE(ResistanceInOhms(1.0f) < ResistanceInOhms(2.0f));
  EXPECT_TRUE(ResistanceInOhms(2.0f) > ResistanceInOhms(1.0f));
  EXPECT_TRUE(ResistanceInOhms(1.0f) <= ResistanceInOhms(1.0f));
  EXPECT_TRUE(ResistanceInOhms(1.0f) >= ResistanceInOhms(1.0f));
  EXPECT_TRUE(ResistanceInOhms(1.0f) == ResistanceInOhms(1.0f));
  EXPECT_TRUE(ResistanceInOhms(1.0f) != ResistanceInOhms(2.0f));
}

TEST(Resistance, Operators) {
  Resistance c1 = ResistanceInOhms(1.5f);
  Resistance c2 = ResistanceInOhms(2.5f);

  Resistance c3 = c1 + c2;
  EXPECT_FLOAT_EQ(4.0f, c3.inOhms());

  c3 = c2 - c1;
  EXPECT_FLOAT_EQ(1.0f, c3.inOhms());

  c1 += c2;
  EXPECT_FLOAT_EQ(4.0f, c1.inOhms());
  c1 -= c2;
  EXPECT_FLOAT_EQ(1.5f, c1.inOhms());

  c3 = c1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, c3.inOhms());

  c3 = 2.0f * c1;
  EXPECT_FLOAT_EQ(3.0f, c3.inOhms());

  c3 = c2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, c3.inOhms());

  float ratio = c2 / c1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  c1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, c1.inOhms());
  c1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, c1.inOhms());
}

TEST(Resistance, OhmsLaw) {
  Resistance r = ResistanceInOhms(4.0f);
  Current i = CurrentInAmperes(2.0f);
  Voltage v = r * i;
  EXPECT_FLOAT_EQ(8.0f, v.inVolts());
  v = i * r;
  EXPECT_FLOAT_EQ(8.0f, v.inVolts());
  i = v / r;
  EXPECT_FLOAT_EQ(2.0f, i.inAmperes());
  r = v / i;
  EXPECT_FLOAT_EQ(4.0f, r.inOhms());
}

TEST(Resistance, AsString) {
  EXPECT_EQ("15.5 GΩ", ResistanceInGigaOhms(15.5f).asString());
  EXPECT_EQ("15.5 MΩ", ResistanceInMegaOhms(15.5f).asString());
  EXPECT_EQ("15.5 kΩ", ResistanceInKiloOhms(15.5f).asString());
  EXPECT_EQ("1.5 Ω", ResistanceInOhms(1.5f).asString());
  EXPECT_EQ("15.5 mΩ", ResistanceInOhms(0.0155f).asString());
  EXPECT_EQ("150.3 µΩ", ResistanceInOhms(0.0001503f).asString());
  EXPECT_EQ("20 nΩ", ResistanceInOhms(0.00000002f).asString());
  EXPECT_EQ("? Ω", UnknownResistance().asString());
  EXPECT_EQ("-2 Ω", ResistanceInOhms(-2).asString());
  EXPECT_EQ("0 Ω", ResistanceInOhms(0).asString());
}

}  // namespace roo_quantity
