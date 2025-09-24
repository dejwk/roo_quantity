#include "roo_quantity/si.h"

#include "gtest/gtest.h"

namespace roo_quantity {

TEST(Si, FormatSimpleValue) {
  char out[64];
  FormatSimpleSiValue(0.0f, "A", out, 64);
  EXPECT_STREQ("0 A", out);

  FormatSimpleSiValue(0.032f, "A", out, 64);
  EXPECT_STREQ("32 mA", out);

  FormatSimpleSiValue(0.0324f, "A", out, 64);
  EXPECT_STREQ("32.4 mA", out);

  FormatSimpleSiValue(1243.3f, "V", out, 64);
  EXPECT_STREQ("1.2433 kV", out);

  FormatSimpleSiValue(0.0000047f, "F", out, 64);
  EXPECT_STREQ("4.7 µF", out);

  FormatSimpleSiValue(0.000000001f, "F", out, 64);
  EXPECT_STREQ("1 nF", out);

  FormatSimpleSiValue(0.0000000000022f, "F", out, 64);
  EXPECT_STREQ("2.2 pF", out);

  FormatSimpleSiValue(0.0000000000000068f, "F", out, 64);
  EXPECT_STREQ("0.0068 pF", out);

  FormatSimpleSiValue(1000000.0f, "Pa", out, 64);
  EXPECT_STREQ("1 MPa", out);

  FormatSimpleSiValue(54300000000.0f, "J", out, 64);
  EXPECT_STREQ("54.3 GJ", out);

  FormatSimpleSiValue(54300000000000.0f, "W", out, 64);
  EXPECT_STREQ("54.3 TW", out);

  FormatSimpleSiValue(54300000000000000.0f, "W", out, 64);
  EXPECT_STREQ("54.3 PW", out);

  FormatSimpleSiValue(54300000000000000000.0f, "W", out, 64);
  EXPECT_STREQ("54300 PW", out);

  FormatSimpleSiValue(0.003333f, "m", out, 64);
  EXPECT_STREQ("3.333 mm", out);
}

TEST(Si, FormatSimpleValueNegative) {
  char out[64];
  FormatSimpleSiValue(-0.032f, "A", out, 64);
  EXPECT_STREQ("-32 mA", out);

  FormatSimpleSiValue(-543222.0f, "V", out, 64);
  EXPECT_STREQ("-543.222 kV", out);
}

TEST(Si, FormatSimpleValueNaN) {
  char out[64];
  FormatSimpleSiValue(0.0f / 0.0f, "A", out, 64);
  EXPECT_STREQ("? A", out);
}

TEST(Si, FormatSimpleValueInf) {
  char out[64];
  FormatSimpleSiValue(5.0f / 0.0f, "A", out, 64);
  EXPECT_STREQ("∞ A", out);

  FormatSimpleSiValue(-5.0f / 0.0f, "A", out, 64);
  EXPECT_STREQ("-∞ A", out);
}

}  // namespace roo_quantity