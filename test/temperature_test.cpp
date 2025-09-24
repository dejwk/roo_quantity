#include "roo_quantity/temperature.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Temperature, Conversion) {
  Temperature t = TemperatureDegCelcius(25.0f);
  EXPECT_FLOAT_EQ(25.0f, t.degCelcius());
  EXPECT_FLOAT_EQ(298.15f, t.degKelvin());
  EXPECT_FLOAT_EQ(77.0f, t.degFahrenheit());

  t = TemperatureDegKelvin(300.0f);
  EXPECT_FLOAT_EQ(26.85f, t.degCelcius());

  t = TemperatureDegFahrenheit(77.0f);
  EXPECT_FLOAT_EQ(25.0f, t.degCelcius());

  t = TemperatureDegCelcius(-10.0f);
  EXPECT_FLOAT_EQ(-10.0f, t.degCelcius());
  EXPECT_FLOAT_EQ(263.15f, t.degKelvin());
  EXPECT_FLOAT_EQ(14.0f, t.degFahrenheit());
}

TEST(Temperature, Comparison) {
  EXPECT_TRUE(TemperatureDegCelcius(20.0f) < TemperatureDegCelcius(30.0f));
  EXPECT_TRUE(TemperatureDegCelcius(30.0f) > TemperatureDegCelcius(20.0f));
  EXPECT_TRUE(TemperatureDegCelcius(20.0f) <= TemperatureDegCelcius(20.0f));
  EXPECT_TRUE(TemperatureDegCelcius(20.0f) >= TemperatureDegCelcius(20.0f));
  EXPECT_TRUE(TemperatureDegCelcius(20.0f) == TemperatureDegCelcius(20.0f));
  EXPECT_TRUE(TemperatureDegCelcius(20.0f) != TemperatureDegCelcius(30.0f));
}

TEST(Temperature, Operators) {
  Temperature t1 = TemperatureDegCelcius(20.0f);
  Temperature t2 = TemperatureDegCelcius(30.0f);
  TemperatureDelta dt1 = TemperatureDeltaDegCelcius(5.0f);
  TemperatureDelta dt2 = TemperatureDeltaDegCelcius(10.0f);

  Temperature t3 = t1 + dt1;
  EXPECT_FLOAT_EQ(25.0f, t3.degCelcius());

  t3 = t2 - dt2;
  EXPECT_FLOAT_EQ(20.0f, t3.degCelcius());

  t3 = dt1 + t1;
  EXPECT_FLOAT_EQ(25.0f, t3.degCelcius());

  TemperatureDelta dt3 = dt1 + dt2;
  EXPECT_FLOAT_EQ(15.0f, dt3.degCelcius());

  dt3 = t2 - t1;
  EXPECT_FLOAT_EQ(10.0f, dt3.degCelcius());

  dt3 = dt1 * 2.0f;
  EXPECT_FLOAT_EQ(10.0f, dt3.degCelcius());

  dt3 = 2.0f * dt1;
  EXPECT_FLOAT_EQ(10.0f, dt3.degCelcius());

  dt3 = dt2 / 2.0f;
  EXPECT_FLOAT_EQ(5.0f, dt3.degCelcius());

  dt1 *= 2.0f;
  EXPECT_FLOAT_EQ(10.0f, dt1.degCelcius());
  dt1 /= 2.0f;
  EXPECT_FLOAT_EQ(5.0f, dt1.degCelcius());

  t1 += dt1;
  EXPECT_FLOAT_EQ(25.0f, t1.degCelcius());
  t1 -= dt1;
  EXPECT_FLOAT_EQ(20.0f, t1.degCelcius());

  dt1 = -dt1;
  EXPECT_FLOAT_EQ(-5.0f, dt1.degCelcius());

  dt2 = dt2 + dt1;
  EXPECT_FLOAT_EQ(5.0f, dt2.degCelcius());
}

TEST(Temperature, String) {
  EXPECT_EQ("25°C", TemperatureDegCelcius(25.0f).asString());
}

}  // namespace roo_quantity