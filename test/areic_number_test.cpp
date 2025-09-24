#include "roo_quantity/areic_number.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(AreicNumber, ConversionSi) {
  AreicNumber snd = AreicNumberInUnitsPerSquareMeter(1.5f);
  EXPECT_FLOAT_EQ(1.5f, snd.inUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.0015f, snd.inKiloUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.0000015f, snd.inMegaUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.0000000015f, snd.inGigaUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(1500.0f, snd.inMilliUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(1500000.0f, snd.inMicroUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.00015f, snd.inUnitsPerSquareCentimeter());
  EXPECT_FLOAT_EQ(0.0000015f, snd.inUnitsPerSquareMillimeter());
  EXPECT_FLOAT_EQ(1500000.0f, snd.inUnitsPerSquareKilometer());

  snd = AreicNumberInKiloUnitsPerSquareMeter(2.0f);
  EXPECT_FLOAT_EQ(2000.0f, snd.inUnitsPerSquareMeter());

  snd = AreicNumberInMilliUnitsPerSquareMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, snd.inUnitsPerSquareMeter());

  snd = AreicNumberInMicroUnitsPerSquareMeter(2500.0f);
  EXPECT_FLOAT_EQ(2.5f, snd.inMilliUnitsPerSquareMeter());

  snd = AreicNumberInUnitsPerSquareCentimeter(2500.0f);
  EXPECT_FLOAT_EQ(25000000.0f, snd.inUnitsPerSquareMeter());

  snd = AreicNumberInUnitsPerSquareMillimeter(2500.0f);
  EXPECT_FLOAT_EQ(2500000000.0f, snd.inUnitsPerSquareMeter());

  snd = AreicNumberInUnitsPerSquareKilometer(2);
  EXPECT_FLOAT_EQ(0.000002f, snd.inUnitsPerSquareMeter());
}

TEST(AreicNumber, ConversionNonSi) {
  AreicNumber snd = AreicNumberInUnitsPerSquareMeter(1.0f);
  EXPECT_FLOAT_EQ(1.0f, snd.inUnitsPerSquareMeter());
  EXPECT_FLOAT_EQ(0.00064516f, snd.inUnitsPerSquareInch());
  EXPECT_FLOAT_EQ(0.09290304f, snd.inUnitsPerSquareFoot());
  EXPECT_FLOAT_EQ(0.83612736f, snd.inUnitsPerSquareYard());

  snd = AreicNumberInUnitsPerSquareInch(0.00064516f);
  EXPECT_FLOAT_EQ(1.0f, snd.inUnitsPerSquareMeter());

  snd = AreicNumberInUnitsPerSquareFoot(0.09290304f);
  EXPECT_FLOAT_EQ(1.0f, snd.inUnitsPerSquareMeter());

  snd = AreicNumberInUnitsPerSquareYard(0.83612736f);
  EXPECT_FLOAT_EQ(1.0f, snd.inUnitsPerSquareMeter());
}

TEST(AreicNumber, Comparison) {
  EXPECT_TRUE(AreicNumberInUnitsPerSquareMeter(1.0f) <
              AreicNumberInUnitsPerSquareMeter(2.0f));
  EXPECT_TRUE(AreicNumberInUnitsPerSquareMeter(2.0f) >
              AreicNumberInUnitsPerSquareMeter(1.0f));
  EXPECT_TRUE(AreicNumberInUnitsPerSquareMeter(1.0f) <=
              AreicNumberInUnitsPerSquareMeter(1.0f));
  EXPECT_TRUE(AreicNumberInUnitsPerSquareMeter(1.0f) >=
              AreicNumberInUnitsPerSquareMeter(1.0f));
  EXPECT_TRUE(AreicNumberInUnitsPerSquareMeter(1.0f) ==
              AreicNumberInUnitsPerSquareMeter(1.0f));
  EXPECT_TRUE(AreicNumberInUnitsPerSquareMeter(1.0f) !=
              AreicNumberInUnitsPerSquareMeter(2.0f));
}

TEST(AreicNumber, Operators) {
  AreicNumber snd1 = AreicNumberInUnitsPerSquareMeter(1.5f);
  AreicNumber snd2 = AreicNumberInUnitsPerSquareMeter(2.5f);

  AreicNumber snd3 = snd1 * 2.0f;
  EXPECT_FLOAT_EQ(3.0f, snd3.inUnitsPerSquareMeter());

  snd3 = 2.0f * snd1;
  EXPECT_FLOAT_EQ(3.0f, snd3.inUnitsPerSquareMeter());

  snd3 = snd2 / 2.0f;
  EXPECT_FLOAT_EQ(1.25f, snd3.inUnitsPerSquareMeter());

  float ratio = snd2 / snd1;
  EXPECT_FLOAT_EQ(1.6666666f, ratio);

  Area a1 = 2.0f / snd1;
  EXPECT_FLOAT_EQ(1.3333333f, a1.inSquareMeters());

  AreicNumber snd4 = 2.0f / a1;
  EXPECT_FLOAT_EQ(1.5f, snd4.inUnitsPerSquareMeter());

  snd2 *= 2.0f;
  EXPECT_FLOAT_EQ(5.0f, snd2.inUnitsPerSquareMeter());
  snd2 /= 2.0f;
  EXPECT_FLOAT_EQ(2.5f, snd2.inUnitsPerSquareMeter());
}

TEST(AreicNumber, Reciprocal) {
  Area a = AreaInSquareMeters(2.0f);
  AreicNumber snd = AreicNumberInUnitsPerSquareMeter(0.5f);
  EXPECT_FLOAT_EQ(1.0f, (a * snd));
  EXPECT_FLOAT_EQ(1.0f, (snd * a));
  EXPECT_FLOAT_EQ(4.0f, (2.0f / snd).inSquareMeters());
  EXPECT_FLOAT_EQ(1.0f, (2.0f / a).inUnitsPerSquareMeter());
}

TEST(AreicNumber, AsString) {
  EXPECT_EQ("1.5/m²", AreicNumberInUnitsPerSquareMeter(1.5f).asString());
  EXPECT_EQ("1.5e-06/m²",
            AreicNumberInUnitsPerSquareKilometer(1.5f).asString());
}

}  // namespace roo_quantity