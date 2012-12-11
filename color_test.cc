/* color_test.cc
 *
 * gtest Unit Test Suite for the Color class
 */

#include "color.hh"
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

// Test mutators and accessors for color components
TEST(ColorTest, ComponentAccess)
{
  Color c;

  // Set the components
  Color &result = c.set_red(0.2).set_green(0.5).set_blue(0.7);

  // Access the components
  EXPECT_FLOAT_EQ(0.2, c.get_red());
  EXPECT_FLOAT_EQ(0.5, c.get_green());
  EXPECT_FLOAT_EQ(0.7, c.get_blue());

  // Confirm that return result is *this
  EXPECT_EQ(&c, &result);
}

// Test the constructors
TEST(ColorTest, Constructors)
{
  // Default Constructor
  Color c0 = Color();
  EXPECT_FLOAT_EQ(0, c0.get_red());
  EXPECT_FLOAT_EQ(0, c0.get_green());
  EXPECT_FLOAT_EQ(0, c0.get_blue());

  // Elementwise Constructor
  Color c1 = Color(0.2, 0.5, 0.7);
  EXPECT_FLOAT_EQ(0.2, c1.get_red());
  EXPECT_FLOAT_EQ(0.5, c1.get_green());
  EXPECT_FLOAT_EQ(0.7, c1.get_blue());
}

// Test Color addition (& compound assignment)
TEST(ColorTest, ArithmeticAdd)
{
  // Test compound assignment
  Color c1 = Color(0.2, 0.5, 0.7);
  Color c2 = Color(0.5, 0.2, 0.1);

  Color &assign_result = (c1 += c2);

  // Verify result
  EXPECT_FLOAT_EQ(0.7, c1.get_red());
  EXPECT_FLOAT_EQ(0.7, c1.get_green());
  EXPECT_FLOAT_EQ(0.8, c1.get_blue());

  // Verify return value is *this
  EXPECT_EQ(&c1, &assign_result);

  // Now test straight addition
  c1 = Color(0.2, 0.5, 0.7);
  Color result = c1 + c2;

  EXPECT_FLOAT_EQ(0.7, result.get_red());
  EXPECT_FLOAT_EQ(0.7, result.get_green());
  EXPECT_FLOAT_EQ(0.8, result.get_blue());
}

// Test Color subtraction (& compound assignment)
TEST(ColorTest, ArithmeticSub)
{
  // Test compound assignment
  Color c1 = Color(0.2, 0.5, 0.7);
  Color c2 = Color(0.5, 0.2, 0.1);

  Color &assign_result = (c1 -= c2);

  // Verify result
  EXPECT_FLOAT_EQ(-0.3, c1.get_red());
  EXPECT_FLOAT_EQ(0.3, c1.get_green());
  EXPECT_FLOAT_EQ(0.6, c1.get_blue());

  // Verify return value is *this
  EXPECT_EQ(&c1, &assign_result);

  // Now test straight subtraction
  c1 = Color(0.2, 0.5, 0.7);
  Color result = c1 - c2;

  EXPECT_FLOAT_EQ(-0.3, result.get_red());
  EXPECT_FLOAT_EQ(0.3, result.get_green());
  EXPECT_FLOAT_EQ(0.6, result.get_blue());
}

// Test Color multiplication (& compound assignment)
TEST(ColorTest, ArithmeticMult)
{
  // Test compound assignment
  Color c1 = Color(0.2, 0.5, 0.7);
  Color c2 = Color(0.5, 0.2, 0.1);

  Color &assign_result = (c1 *= c2);

  // Verify result
  EXPECT_FLOAT_EQ(0.1, c1.get_red());
  EXPECT_FLOAT_EQ(0.1, c1.get_green());
  EXPECT_FLOAT_EQ(0.07, c1.get_blue());

  // Verify return value is *this
  EXPECT_EQ(&c1, &assign_result);

  // Now test straight multiplication
  c1 = Color(0.2, 0.5, 0.7);
  Color result = c1 * c2;

  EXPECT_FLOAT_EQ(0.1, result.get_red());
  EXPECT_FLOAT_EQ(0.1, result.get_green());
  EXPECT_FLOAT_EQ(0.07, result.get_blue());
}

// Test scalar multiplication (& compound assignment)
TEST(ColorTest, ArithmeticSMult)
{
  // Test compound assignment
  Color c1 = Color(0.2, 0.5, 0.7);

  Color &assign_result = (c1 *= 2);

  // Verify result
  EXPECT_FLOAT_EQ(0.4, c1.get_red());
  EXPECT_FLOAT_EQ(1.0, c1.get_green());
  EXPECT_FLOAT_EQ(1.4, c1.get_blue());

  // Verify return value is *this
  EXPECT_EQ(&c1, &assign_result);

  // Now test straight scalar multiplication
  c1 = Color(0.2, 0.5, 0.7);
  Color result1 = c1 * 2;
  Color result2 = 2 * c1;

  EXPECT_FLOAT_EQ(0.4, result1.get_red());
  EXPECT_FLOAT_EQ(1.0, result1.get_green());
  EXPECT_FLOAT_EQ(1.4, result1.get_blue());

  EXPECT_FLOAT_EQ(0.4, result2.get_red());
  EXPECT_FLOAT_EQ(1.0, result2.get_green());
  EXPECT_FLOAT_EQ(1.4, result2.get_blue());
}

// Test scalar multiplication (& compound assignment)
TEST(ColorTest, ArithmeticSDiv)
{
  // Test compound assignment
  Color c1 = Color(0.2, 0.5, 0.7);

  Color &assign_result = (c1 /= 2);

  // Verify result
  EXPECT_FLOAT_EQ(0.1, c1.get_red());
  EXPECT_FLOAT_EQ(.25, c1.get_green());
  EXPECT_FLOAT_EQ(.35, c1.get_blue());

  // Verify return value is *this
  EXPECT_EQ(&c1, &assign_result);

  // Now test straight scalar multiplication
  c1 = Color(0.2, 0.5, 0.7);
  Color result = c1 / 2;

  EXPECT_FLOAT_EQ(0.1, result.get_red());
  EXPECT_FLOAT_EQ(.25, result.get_green());
  EXPECT_FLOAT_EQ(.35, result.get_blue());
}

// Test clamping of colors
TEST(ColorTest, ClampTest)
{
  // All values need correcting
  Color c1 = Color(-3, 1.1, 1.03);
  c1.clamp();
  EXPECT_FLOAT_EQ(0, c1.get_red());
  EXPECT_FLOAT_EQ(1, c1.get_green());
  EXPECT_FLOAT_EQ(1, c1.get_blue());

  // No values need correcting
  Color c2 = Color(0.2, 0.4, 0.7);
  c2.clamp();
  EXPECT_FLOAT_EQ(0.2, c2.get_red());
  EXPECT_FLOAT_EQ(0.4, c2.get_green());
  EXPECT_FLOAT_EQ(0.7, c2.get_blue());

  // Just one value needs correcting after arithmetic
  c2 *= 2;
  c2.clamp();
  EXPECT_FLOAT_EQ(0.4, c2.get_red());
  EXPECT_FLOAT_EQ(0.8, c2.get_green());
  EXPECT_FLOAT_EQ(1.0, c2.get_blue());

  // Don't change zeros
  Color c3 = Color(0, 0, 0);
  c3.clamp();
  EXPECT_FLOAT_EQ(0, c3.get_red());
  EXPECT_FLOAT_EQ(0, c3.get_green());
  EXPECT_FLOAT_EQ(0, c3.get_blue());

  // Don't change zeros
  Color c4 = Color(1, 1, 1);
  c4.clamp();
  EXPECT_FLOAT_EQ(1, c4.get_red());
  EXPECT_FLOAT_EQ(1, c4.get_green());
  EXPECT_FLOAT_EQ(1, c4.get_blue());
}

// Test reading from input
TEST(ColorTest, StreamInput)
{
  // Vectors into which to read values
  Color c = Color();

  // String stream of some input
  istringstream iss("( 0.1 0.5 0.2 )");

  iss >> c;

  EXPECT_FLOAT_EQ(0.1, c.get_red());
  EXPECT_FLOAT_EQ(0.5, c.get_green());
  EXPECT_FLOAT_EQ(0.2, c.get_blue());
}

int main(int argc, char **argv)
{
  // Parse gtest arguments
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
