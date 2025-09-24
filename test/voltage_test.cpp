#include "roo_quantity/voltage.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Voltage, UnitConversionSi) {
  Voltage c = VoltageInVolts(1.5f);
  EXPECT_FLOAT_EQ(1.5f, c.inVolts());
  EXPECT_FLOAT_EQ(0.0015f, c.inKiloVolts());
  EXPECT_FLOAT_EQ(1500.0f, c.inMilliVolts());
  EXPECT_FLOAT_EQ(1500000.0f, c.inMicroVolts());

  c = VoltageInKiloVolts(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, c.inVolts());

  c = VoltageInMilliVolts(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inVolts());

  c = VoltageInMicroVolts(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, c.inMilliVolts());

  c = VoltageInVolts(-2);
  EXPECT_FLOAT_EQ(-2.0f, c.inVolts());
}

TEST(Voltage, Comparison) {
  EXPECT_TRUE(VoltageInVolts(1.0f) < VoltageInVolts(2.0f));
  EXPECT_TRUE(VoltageInVolts(2.0f) > VoltageInVolts(1.0f));
  EXPECT_TRUE(VoltageInVolts(1.0f) <= VoltageInVolts(1.0f));
  EXPECT_TRUE(VoltageInVolts(1.0f) >= VoltageInVolts(1.0f));
  EXPECT_TRUE(VoltageInVolts(1.0f) == VoltageInVolts(1.0f));
  EXPECT_TRUE(VoltageInVolts(1.0f) != VoltageInVolts(2.0f));
}

TEST(Voltage, Operators) {
  Voltage c1 = VoltageInVolts(1.5f);
  Voltage c2 = VoltageInVolts(2.5f);

  Voltage c3 = c1 + c2;
  EXPECT_FLOAT_EQ(4.0f, c3.inVolts());

  c3 = c2 - c1;
  EXPECT_FLOAT_EQ(1.0f, c3.inVolts());

  c1 += c2;
  EXPECT_FLOAT_EQ(4.0f, c1.inVolts());
  c1 -= c2;
  EXPECT_FLOAT_EQ(1.5f, c1.inVolts());

  c3 = c1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, c3.inVolts());

  c3 = 2.0f * c1;
  EXPECT_FLOAT_EQ(3.0f, c3.inVolts());

  c3 = c2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, c3.inVolts());

  float ratio = c2 / c1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  c1 *= 3.0f;
  EXPECT_FLOAT_EQ(4.5f, c1.inVolts());
  c1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.5f, c1.inVolts());
}

TEST(Voltage, VsWork) {
  Voltage p = VoltageInVolts(2.0f);
  Charge q = ChargeInCoulombs(0.5f);
  Work w = p * q;
  EXPECT_FLOAT_EQ(1.0f, w.inJoules());
  w = q * p;
  EXPECT_FLOAT_EQ(1.0f, w.inJoules());
  p = w / q;
  EXPECT_FLOAT_EQ(2.0f, p.inVolts());
  q = w / p;
  EXPECT_FLOAT_EQ(0.5f, q.inCoulombs());
}

TEST(Voltage, VsPower) {
  Voltage v = VoltageInVolts(2.0f);
  Current i = CurrentInAmperes(0.5f);
  Power p = v * i;
  EXPECT_FLOAT_EQ(1.0f, p.inWatts());
  p = i * v;
  EXPECT_FLOAT_EQ(1.0f, p.inWatts());
  v = p / i;
  EXPECT_FLOAT_EQ(2.0f, v.inVolts());
  i = p / v;
  EXPECT_FLOAT_EQ(0.5f, i.inAmperes());
}

TEST(Voltage, AsString) {
  EXPECT_EQ("15.5 kV", VoltageInKiloVolts(15.5f).asString());
  EXPECT_EQ("1.5 V", VoltageInVolts(1.5f).asString());
  EXPECT_EQ("15.5 mV", VoltageInVolts(0.0155f).asString());
  EXPECT_EQ("150.3 µV", VoltageInVolts(0.0001503f).asString());
  EXPECT_EQ("20 nV", VoltageInVolts(0.00000002f).asString());
  EXPECT_EQ("? V", UnknownVoltage().asString());
  EXPECT_EQ("-2 V", VoltageInVolts(-2).asString());
  EXPECT_EQ("0 V", VoltageInVolts(0).asString());
}

}  // namespace roo_quantity
