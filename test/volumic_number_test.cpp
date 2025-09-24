#include "roo_quantity/volumic_number.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(VolumicNumber, ConversionSi) {
  VolumicNumber vnd = VolumicNumberInUnitsPerCubicMeter(1.5f);
  EXPECT_FLOAT_EQ(1.5f, vnd.inUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(0.0015f, vnd.inKiloUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(0.0000015f, vnd.inMegaUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(0.0000000015f, vnd.inGigaUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(1500.0f, vnd.inMilliUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(1500000.0f, vnd.inMicroUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(0.0015f, vnd.inUnitsPerLiter());
  EXPECT_FLOAT_EQ(0.0000015f, vnd.inUnitsPerCubicCentimeter());
  EXPECT_FLOAT_EQ(0.0000000015f, vnd.inUnitsPerCubicMillimeter());
  EXPECT_FLOAT_EQ(1500000000.0f, vnd.inUnitsPerCubicKilometer());

  vnd = VolumicNumberInKiloUnitsPerCubicMeter(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, vnd.inUnitsPerCubicMeter());

  vnd = VolumicNumberInMilliUnitsPerCubicMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, vnd.inUnitsPerCubicMeter());

  vnd = VolumicNumberInMicroUnitsPerCubicMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, vnd.inMilliUnitsPerCubicMeter());

  vnd = VolumicNumberInUnitsPerCubicCentimeter(2500.0f);
  EXPECT_FLOAT_EQ(2500000000.0f, vnd.inUnitsPerCubicMeter());

  vnd = VolumicNumberInUnitsPerCubicMillimeter(2500.0f);
  EXPECT_FLOAT_EQ(2500000000000.0f, vnd.inUnitsPerCubicMeter());

  vnd = VolumicNumberInUnitsPerCubicKilometer(2);
  EXPECT_FLOAT_EQ(0.000000002f, vnd.inUnitsPerCubicMeter());

  vnd = VolumicNumberInUnitsPerLiter(2.5f);
  EXPECT_FLOAT_EQ(2500.0f, vnd.inUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(2.5f, vnd.inUnitsPerLiter());
}

TEST(VolumicNumber, ConversionNonSi) {
  VolumicNumber vnd = VolumicNumberInUnitsPerCubicMeter(1.0f);
  EXPECT_FLOAT_EQ(1.0f, vnd.inUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(1.6387064E-5f, vnd.inUnitsPerCubicInch());
  EXPECT_FLOAT_EQ(0.0283168466f, vnd.inUnitsPerCubicFoot());
  EXPECT_FLOAT_EQ(0.764554858f, vnd.inUnitsPerCubicYard());

  vnd = VolumicNumberInUnitsPerCubicInch(1.6387064E-5f);
  EXPECT_FLOAT_EQ(1.0f, vnd.inUnitsPerCubicMeter());

  vnd = VolumicNumberInUnitsPerCubicFoot(0.0283168466f);
  EXPECT_FLOAT_EQ(1.0f, vnd.inUnitsPerCubicMeter());

  vnd = VolumicNumberInUnitsPerCubicYard(0.764554858f);
  EXPECT_FLOAT_EQ(1.0f, vnd.inUnitsPerCubicMeter());
}

TEST(VolumicNumber, Comparison) {
  EXPECT_TRUE(VolumicNumberInUnitsPerCubicMeter(1.0f) <
              VolumicNumberInUnitsPerCubicMeter(2.0f));
  EXPECT_TRUE(VolumicNumberInUnitsPerCubicMeter(2.0f) >
              VolumicNumberInUnitsPerCubicMeter(1.0f));
  EXPECT_TRUE(VolumicNumberInUnitsPerCubicMeter(1.0f) <=
              VolumicNumberInUnitsPerCubicMeter(2.0f));
  EXPECT_TRUE(VolumicNumberInUnitsPerCubicMeter(2.0f) >=
              VolumicNumberInUnitsPerCubicMeter(1.0f));
  EXPECT_TRUE(VolumicNumberInUnitsPerCubicMeter(1.0f) ==
              VolumicNumberInUnitsPerCubicMeter(1.0f));
  EXPECT_TRUE(VolumicNumberInUnitsPerCubicMeter(1.0f) !=
              VolumicNumberInUnitsPerCubicMeter(2.0f));
}

TEST(VolumicNumber, Operators) {
  VolumicNumber vnd1 = VolumicNumberInUnitsPerCubicMeter(1.0f);
  VolumicNumber vnd2 = VolumicNumberInUnitsPerCubicMeter(2.0f);

  EXPECT_FLOAT_EQ(2.0f, (vnd1 * 2.0f).inUnitsPerCubicMeter());
  EXPECT_FLOAT_EQ(1.0f, (vnd2 / 2.0f).inUnitsPerCubicMeter());

  vnd1 *= 3.0f;
  EXPECT_FLOAT_EQ(3.0f, vnd1.inUnitsPerCubicMeter());

  vnd1 /= 3.0f;
  EXPECT_FLOAT_EQ(1.0f, vnd1.inUnitsPerCubicMeter());

  EXPECT_FLOAT_EQ(3.0f, (3.0f * vnd1).inUnitsPerCubicMeter());
}

TEST(VolumicNumber, Reciprocal) {
  Volume vol = VolumeInCubicMeters(2.0f);
  VolumicNumber vnd = VolumicNumberInUnitsPerCubicMeter(0.5f);
  EXPECT_FLOAT_EQ(1.0f, (vol * vnd));
  EXPECT_FLOAT_EQ(1.0f, (vnd * vol));

  vol = 6.0f / vnd;
  EXPECT_FLOAT_EQ(12.0f, vol.inCubicMeters());
}

TEST(VolumicNumber, AsString) {
  EXPECT_EQ("1.5/m³", VolumicNumberInUnitsPerCubicMeter(1.5f).asString());
  EXPECT_EQ("1.5e-09/m³",
            VolumicNumberInUnitsPerCubicKilometer(1.5f).asString());
}

}  // namespace roo_quantity
