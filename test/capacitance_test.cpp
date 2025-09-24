#include "roo_quantity/capacitance.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Capacitance, UnitConversionSi) {
  Capacitance c = CapacitanceInFarads(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inFarads());
  EXPECT_FLOAT_EQ(0.0015f, c.inKiloFarads());
  EXPECT_FLOAT_EQ(1500.0f, c.inMilliFarads());
  EXPECT_FLOAT_EQ(1500000.0f, c.inMicroFarads());
  EXPECT_FLOAT_EQ(1500000000.0f, c.inNanoFarads());
  EXPECT_FLOAT_EQ(1500000000000.0f, c.inPicoFarads());

  c = CapacitanceInKiloFarads(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, c.inFarads());

  c = CapacitanceInMilliFarads(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inFarads());

  c = CapacitanceInMicroFarads(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMilliFarads());

  c = CapacitanceInNanoFarads(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMicroFarads());

  c = CapacitanceInPicoFarads(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inNanoFarads());

  c = CapacitanceInFarads(-2);
  EXPECT_FLOAT_EQ(-2.0f, c.inFarads());
}

TEST(Capacitance, Comparison) {
  EXPECT_TRUE(CapacitanceInFarads(1.0f) < CapacitanceInFarads(2.0f));
  EXPECT_TRUE(CapacitanceInFarads(2.0f) > CapacitanceInFarads(1.0f));
  EXPECT_TRUE(CapacitanceInFarads(1.0f) <= CapacitanceInFarads(1.0f));
  EXPECT_TRUE(CapacitanceInFarads(1.0f) >= CapacitanceInFarads(1.0f));
  EXPECT_TRUE(CapacitanceInFarads(1.0f) == CapacitanceInFarads(1.0f));
  EXPECT_TRUE(CapacitanceInFarads(1.0f) != CapacitanceInFarads(2.0f));
}

TEST(Capacitance, Operators) {
  Capacitance c1 = CapacitanceInFarads(1.5f);
  Capacitance c2 = CapacitanceInFarads(2.5f);

  Capacitance c3 = c1 + c2;
  EXPECT_FLOAT_EQ(4.0f, c3.inFarads());

  c3 = c2 - c1;
  EXPECT_FLOAT_EQ(1.0f, c3.inFarads());

  c1 += c2;
  EXPECT_FLOAT_EQ(4.0f, c1.inFarads());
  c1 -= c2;
  EXPECT_FLOAT_EQ(1.5f, c1.inFarads());

  c3 = c1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, c3.inFarads());

  c3 = 2.0f * c1;
  EXPECT_FLOAT_EQ(3.0f, c3.inFarads());

  c3 = c2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, c3.inFarads());

  float ratio = c2 / c1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  c1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, c1.inFarads());
  c1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, c1.inFarads());
}

TEST(Capacitance, VsCharge) {
  Capacitance c = CapacitanceInFarads(2.0f);
  Voltage v = VoltageInVolts(3.0f);
  Charge q = c * v;
  EXPECT_FLOAT_EQ(6.0f, q.inCoulombs());
  q = v * c;
  EXPECT_FLOAT_EQ(6.0f, q.inCoulombs());
  c = q / v;
  EXPECT_FLOAT_EQ(2.0f, c.inFarads());
  v = q / c;
  EXPECT_FLOAT_EQ(3.0f, v.inVolts());
}

TEST(Capacitance, AsString) {
  EXPECT_EQ("1.5 F", CapacitanceInFarads(1.5f).asString());
  EXPECT_EQ("15.5 mF", CapacitanceInFarads(0.0155f).asString());
  EXPECT_EQ("150.3 µF", CapacitanceInFarads(0.0001503f).asString());
  EXPECT_EQ("20 nF", CapacitanceInFarads(0.00000002f).asString());
  EXPECT_EQ("20 pF", CapacitanceInFarads(0.00000000002f).asString());
  EXPECT_EQ("? F", UnknownCapacitance().asString());
  EXPECT_EQ("-2 F", CapacitanceInFarads(-2).asString());
  EXPECT_EQ("0 F", CapacitanceInFarads(0).asString());
}

}  // namespace roo_quantity
