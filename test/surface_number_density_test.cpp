#include "roo_quantity/surface_number_density.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(SurfaceNumberDensity, ConversionSi) {
  SurfaceNumberDensity snd = SurfaceNumberDensityInUnitsPerSquareMeter(1.5f);
  EXPECT_FLOAT_EQ(1.5f, snd.inUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.0015f, snd.inKiloUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.0000015f, snd.inMegaUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.0000000015f, snd.inGigaUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(1500.0f, snd.inMilliUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(1500000.0f, snd.inMicroUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.00015f, snd.inUnitsPerSquareCentimeter());
  EXPECT_FLOAT_EQ(0.0000015f, snd.inUnitsPerSquareMillimeter());
  EXPECT_FLOAT_EQ(1500000.0f, snd.inUnitsPerSquareKilometer());

  snd = SurfaceNumberDensityInKiloUnitsPerSquareMeter(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, snd.inUnitsPerSquareMeter());

  snd = SurfaceNumberDensityInMilliUnitsPerSquareMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, snd.inUnitsPerSquareMeter());

  snd = SurfaceNumberDensityInMicroUnitsPerSquareMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, snd.inMilliUnitsPerSquareMeter());

  snd = SurfaceNumberDensityInUnitsPerSquareCentimeter(2500.0f);
  EXPECT_FLOAT_EQ(25000000.0f, snd.inUnitsPerSquareMeter());

  snd = SurfaceNumberDensityInUnitsPerSquareMillimeter(2500.0f);
  EXPECT_FLOAT_EQ(2500000000.0f, snd.inUnitsPerSquareMeter());

  snd = SurfaceNumberDensityInUnitsPerSquareKilometer(2);
  EXPECT_FLOAT_EQ(0.000002f, snd.inUnitsPerSquareMeter());
}

TEST(SurfaceNumberDensity, ConversionNonSi) {
  SurfaceNumberDensity snd = SurfaceNumberDensityInUnitsPerSquareMeter(1.0f);
  EXPECT_FLOAT_EQ(1.0f, snd.inUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.00064516f, snd.inUnitsPerSquareInch());
  EXPECT_FLOAT_EQ(0.09290304f, snd.inUnitsPerSquareFoot());
  EXPECT_FLOAT_EQ(0.83612736f, snd.inUnitsPerSquareYard());

  snd = SurfaceNumberDensityInUnitsPerSquareInch(0.00064516f);
  EXPECT_FLOAT_EQ(1.0f, snd.inUnitsPerSquareMeter());

  snd = SurfaceNumberDensityInUnitsPerSquareFoot(0.09290304f);
  EXPECT_FLOAT_EQ(1.0f, snd.inUnitsPerSquareMeter());

  snd = SurfaceNumberDensityInUnitsPerSquareYard(0.83612736f);
  EXPECT_FLOAT_EQ(1.0f, snd.inUnitsPerSquareMeter());
}

TEST(SurfaceNumberDensity, Comparison) {
  EXPECT_TRUE(SurfaceNumberDensityInUnitsPerSquareMeter(1.0f) <
              SurfaceNumberDensityInUnitsPerSquareMeter(2.0f));
  EXPECT_TRUE(SurfaceNumberDensityInUnitsPerSquareMeter(2.0f) >
              SurfaceNumberDensityInUnitsPerSquareMeter(1.0f));
  EXPECT_TRUE(SurfaceNumberDensityInUnitsPerSquareMeter(1.0f) <=
              SurfaceNumberDensityInUnitsPerSquareMeter(1.0f));
  EXPECT_TRUE(SurfaceNumberDensityInUnitsPerSquareMeter(1.0f) >=
              SurfaceNumberDensityInUnitsPerSquareMeter(1.0f));
  EXPECT_TRUE(SurfaceNumberDensityInUnitsPerSquareMeter(1.0f) ==
              SurfaceNumberDensityInUnitsPerSquareMeter(1.0f));
  EXPECT_TRUE(SurfaceNumberDensityInUnitsPerSquareMeter(1.0f) !=
              SurfaceNumberDensityInUnitsPerSquareMeter(2.0f));
}

TEST(SurfaceNumberDensity, Operators) {
  SurfaceNumberDensity snd1 = SurfaceNumberDensityInUnitsPerSquareMeter(1.5f);
  SurfaceNumberDensity snd2 = SurfaceNumberDensityInUnitsPerSquareMeter(2.5f);

  SurfaceNumberDensity snd3 = snd1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, snd3.inUnitsPerSquareMeter());

  snd3 = 2.0f * snd1;
  EXPECT_FLOAT_EQ(3.0f, snd3.inUnitsPerSquareMeter());

  snd3 = snd2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, snd3.inUnitsPerSquareMeter());

  float ratio = snd2 / snd1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  Area a1 = 2.0f / snd1;
  EXPECT_FLOAT_EQ(1.3333333f, a1.inSquareMeters());

  SurfaceNumberDensity snd4 = 2.0f / a1;
  EXPECT_FLOAT_EQ(1.5f, snd4.inUnitsPerSquareMeter());

  snd2 *= 2.0f;
  EXPECT_FLOAT_EQ(5.0f, snd2.inUnitsPerSquareMeter());
  snd2 /= 2.0f;
  EXPECT_FLOAT_EQ(2.5f, snd2.inUnitsPerSquareMeter());
}

TEST(SurfaceNumberDensity, Reciprocal) {
  Area a = AreaInSquareMeters(2.0f);
  SurfaceNumberDensity snd = SurfaceNumberDensityInUnitsPerSquareMeter(0.5f);
  EXPECT_FLOAT_EQ(1.0f, (a * snd));
  EXPECT_FLOAT_EQ(1.0f, (snd * a));
  EXPECT_FLOAT_EQ(4.0f, (2.0f / snd).inSquareMeters());
  EXPECT_FLOAT_EQ(1.0f, (2.0f / a).inUnitsPerSquareMeter());
}

TEST(SurfaceNumberDensity, AsString) {
  EXPECT_EQ("1.5/m²",
            SurfaceNumberDensityInUnitsPerSquareMeter(1.5f).asString());
  EXPECT_EQ("1.5e-06/m²",
            SurfaceNumberDensityInUnitsPerSquareKilometer(1.5f).asString());
}

}  // namespace roo_quantity