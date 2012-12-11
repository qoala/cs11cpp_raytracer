/* vector_test.cc
 *
 * gtest Unit Test Suite for the Vector<E,DIM> class template
 */

#include "vector.hh"
#include "sstream"
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

/*
struct Vector3FTest : public Test
{
  // Initialization
  virtual void SetUp()
  {
    v0 = Vector3F();
    v1 = {1, -2.5, 3};
    v2 = {-1, -0.2, -2};
    v3 = {3, 0, 4};
    v4 = {1, 1, 0};
  }

  // virtual void TearDown() {}
};
*/

// Verify that subscripting access works
TEST(Vector3FTest, SubscriptAccess)
{
  Vector3F v0 = Vector3F();

  // Assign some values
  v0[0] = 1;
  v0[1] = 2.5;
  v0[2] = -5.7;

  // Retrieve the values
  EXPECT_FLOAT_EQ(1, v0[0]);
  EXPECT_FLOAT_EQ(2.5, v0[1]);
  EXPECT_FLOAT_EQ(-5.7, v0[2]);
}

// Verify that subscripting access fails on out of bounds
TEST(Vector3FTest, OutOfBoundsAssertion)
{
  Vector3F v0 = Vector3F();

  EXPECT_DEATH(v0[-1], "Assertion");
  EXPECT_DEATH(v0[3], "Assertion");
}

// Verify that default constructor actually makes zeros
TEST(Vector3FTest, DefaultCtor)
{
  Vector3F v0 = Vector3F();
  EXPECT_EQ(0, v0[0]);
  EXPECT_EQ(0, v0[1]);
  EXPECT_EQ(0, v0[2]);
}

// Verify that construction via initializer list works
TEST(Vector3FTest, ListCtor)
{
  Vector3F v1 = {1, -2.5, 3};
  EXPECT_EQ(1, v1[0]);
  EXPECT_EQ(-2.5, v1[1]);
  EXPECT_EQ(3, v1[2]);
}

// Verify that list construction fails on improperly sized lists
// Need subfunctions, as list constructors break the gtest macro
void build_2vector_in_Vector3F()
{
  Vector3F v= {0, 1};
  cout << v; // should not reach this line
}
void build_4vector_in_Vector3F()
{
  Vector3F v= {0, 1, 2, 3};
  cout << v; // should not reach this line
}
TEST(Vector3FTest, ListCtorAssertion)
{
  Vector3F v;

  EXPECT_DEATH(build_2vector_in_Vector3F(), "Assertion");
  EXPECT_DEATH(build_4vector_in_Vector3F(), "Assertion");
}

TEST(Vector3FTest, ArithmeticAdd)
{
  // Test compound assignment + addition
  Vector3F v1 = {1, -2.5, 3};
  Vector3F v2 = {-1, -0.2, -2};

  Vector3F &assign_result = (v1 += v2);

  // Verify that v1 is the assign_result of v1 + v2
  EXPECT_FLOAT_EQ(0,    v1[0]);
  EXPECT_FLOAT_EQ(-2.7, v1[1]);
  EXPECT_FLOAT_EQ(1,    v1[2]);

  // Verify that returned value is in fact v1
  EXPECT_EQ(&v1, &assign_result);

  // Now test straight addition
  v1 = {1, -2.5, 3};
  Vector3F result = v1 + v2;

  EXPECT_FLOAT_EQ(0,    result[0]);
  EXPECT_FLOAT_EQ(-2.7, result[1]);
  EXPECT_FLOAT_EQ(1,    result[2]);
}

TEST(Vector3FTest, ArithmeticSub)
{
  // Test compound assignment + subtraction
  Vector3F v1 = {1, -2.5, 3};
  Vector3F v2 = {-1, -0.2, -2};

  Vector3F &assign_result = (v1 -= v2);

  // Verify that v1 is the assign_result of v1 - v2
  EXPECT_FLOAT_EQ(2,    v1[0]);
  EXPECT_FLOAT_EQ(-2.3, v1[1]);
  EXPECT_FLOAT_EQ(5,    v1[2]);

  // Verify that returned value is in fact v1
  EXPECT_EQ(&v1, &assign_result);

  // Now test straight subtraction
  v1 = {1, -2.5, 3};
  Vector3F result = v1 - v2;

  EXPECT_FLOAT_EQ(2,    result[0]);
  EXPECT_FLOAT_EQ(-2.3, result[1]);
  EXPECT_FLOAT_EQ(5,    result[2]);
}

TEST(Vector3FTest, ArithmeticSMult)
{
  // Test compound assignment + multiplication
  Vector3F v1 = {1, -2.5, 3};

  Vector3F &assign_result = (v1 *= 2);

  // Verify that v1 is the assign_result of v1 * 2
  EXPECT_FLOAT_EQ(2,    v1[0]);
  EXPECT_FLOAT_EQ(-5,   v1[1]);
  EXPECT_FLOAT_EQ(6,    v1[2]);

  // Verify that returned value is in fact v1
  EXPECT_EQ(&v1, &assign_result);

  // Now test straight multiplication
  v1 = {1, -2.5, 3};
  Vector3F result1 = v1 * 2.f;
  Vector3F result2 = 2.f * v1;

  EXPECT_FLOAT_EQ(2,    result1[0]);
  EXPECT_FLOAT_EQ(-5,   result1[1]);
  EXPECT_FLOAT_EQ(6,    result1[2]);

  EXPECT_FLOAT_EQ(2,    result2[0]);
  EXPECT_FLOAT_EQ(-5,   result2[1]);
  EXPECT_FLOAT_EQ(6,    result2[2]);
}

TEST(Vector3FTest, ArithmeticSDiv)
{
  // Test compound assignment + division
  Vector3F v1 = {1, -2.5, 3};

  Vector3F &assign_result = (v1 /= 2);

  // Verify that v1 is the assign_result of v1 / 2
  EXPECT_FLOAT_EQ(0.5,   v1[0]);
  EXPECT_FLOAT_EQ(-1.25, v1[1]);
  EXPECT_FLOAT_EQ(1.5,   v1[2]);

  // Verify that returned value is in fact v1
  EXPECT_EQ(&v1, &assign_result);

  // Now test straight division
  v1 = {1, -2.5, 3};
  Vector3F result = v1 / 2.f;

  EXPECT_FLOAT_EQ(0.5,   result[0]);
  EXPECT_FLOAT_EQ(-1.25, result[1]);
  EXPECT_FLOAT_EQ(1.5,   result[2]);
}

// Test the unary minus operator
TEST(Vector3FTest, UnaryMinus)
{
  Vector3F v1 = {1, -2.5, 3};
  Vector3F v2 = -v1;

  EXPECT_FLOAT_EQ(-1, v2[0]);
  EXPECT_FLOAT_EQ(2.5, v2[1]);
  EXPECT_FLOAT_EQ(-3, v2[2]);
}

// Test the dot product
TEST(Vector3FTest, DotProduct)
{
  // Dot product with all 3 dimensions nonzero
  Vector3F v1 = {1, -2.5, 3};
  Vector3F v2 = {-1, -0.2, -2};

  EXPECT_FLOAT_EQ(-1+0.5-6, dot(v1, v2));

  // Dot product of orthogonal vectors
  Vector3F v3 = {3, 0, 4};
  Vector3F v4 = {0, 2, 0};

  EXPECT_FLOAT_EQ(0, dot(v3, v4));
}

// Test the cross product
TEST(Vector3FTest, CrossProduct)
{
  // Cross product with all 3 dimensions nonzero
  Vector3F v1 = {1, -2.5, 3};
  Vector3F v2 = {-1, -0.2, -2};

  Vector3F result = cross(v1, v2);
  EXPECT_FLOAT_EQ(5.6, result[0]);
  EXPECT_FLOAT_EQ(-1, result[1]);
  EXPECT_FLOAT_EQ(-2.7, result[2]);

  // Cross product of parallel vectors
  Vector3F v3 = {3, 0, 0};
  Vector3F v4 = {1, 0, 0};

  Vector3F parallel_result = cross(v3, v4);

  EXPECT_FLOAT_EQ(0, parallel_result[0]);
  EXPECT_FLOAT_EQ(0, parallel_result[1]);
  EXPECT_FLOAT_EQ(0, parallel_result[2]);

  // Cross product of orthogonal vectors
  Vector3F v5 = {0, 4, 0};

  Vector3F orthog_result = cross(v3, v5);

  EXPECT_FLOAT_EQ(0, orthog_result[0]);
  EXPECT_FLOAT_EQ(0, orthog_result[1]);
  EXPECT_FLOAT_EQ(12, orthog_result[2]);
}

// Test the norm of a vector
TEST(Vector3FTest, NormOfVector)
{
  // Test with all 3 dimensions non-zero;
  Vector3F v1 = {1, -2, 3};
  EXPECT_FLOAT_EQ(sqrt(14), v1.norm());

  // Test an easy one
  Vector3F v2 = {3, 0, 4};
  EXPECT_FLOAT_EQ(5, v2.norm());
  
  // Test another easy one
  Vector3F v3 = {1, 1, 0};
  EXPECT_FLOAT_EQ(sqrt(2), v3.norm());

  // Test a vector that should be 1
  Vector3F v4 = {1/sqrt(2.f), 1/sqrt(2.f), 0};
  EXPECT_FLOAT_EQ(1, v4.norm());
}

// Test normalization of vectors
TEST(Vector3FTest, Normalize)
{
  // Test with all 3 dimensions non-zero;
  Vector3F v1 = {1, -2, 3};
  Vector3F &result1 = v1.normalize();

  EXPECT_FLOAT_EQ(1/sqrt(14.f), v1[0]);
  EXPECT_FLOAT_EQ(-2/sqrt(14.f), v1[1]);
  EXPECT_FLOAT_EQ(3/sqrt(14.f), v1[2]);
  EXPECT_EQ(&v1, &result1);

  // Test an easy one
  Vector3F v2 = {3, 0, 4};
  Vector3F &result2 = v2.normalize();

  EXPECT_FLOAT_EQ(0.6, v2[0]);
  EXPECT_FLOAT_EQ(0, v2[1]);
  EXPECT_FLOAT_EQ(0.8, v2[2]);
  EXPECT_EQ(&v2, &result2);

  // Test another easy one
  Vector3F v3 = {1, 1, 0};
  Vector3F &result3 = v3.normalize();

  EXPECT_FLOAT_EQ(1/sqrt(2.f), v3[0]);
  EXPECT_FLOAT_EQ(1/sqrt(2.f), v3[1]);
  EXPECT_FLOAT_EQ(0, v3[2]);
  EXPECT_EQ(&v3, &result3);

  // Test one that should already be normalized
  Vector3F v4 = {1/sqrt(2.f), 1/sqrt(2.f), 0};
  Vector3F &result4 = v4.normalize();

  EXPECT_FLOAT_EQ(1/sqrt(2.f), v4[0]);
  EXPECT_FLOAT_EQ(1/sqrt(2.f), v4[1]);
  EXPECT_FLOAT_EQ(0, v4[2]);
  EXPECT_EQ(&v4, &result4);

  // Test a 0-length vector
  Vector3F v0 = {0, 0, 0};
  Vector3F &result0 = v0.normalize();

  EXPECT_FLOAT_EQ(0, v0[0]);
  EXPECT_FLOAT_EQ(0, v0[1]);
  EXPECT_FLOAT_EQ(0, v0[2]);
  EXPECT_EQ(&v0, &result0);
}

// Test getting a normalized copy of a Vector
TEST(Vector3FTest, NormalizeCopy)
{
  // Test with all 3 dimensions non-zero;
  Vector3F v1 = {1, -2, 3};
  Vector3F result = v1.get_normalized();

  // Result
  EXPECT_FLOAT_EQ(1/sqrt(14.f), result[0]);
  EXPECT_FLOAT_EQ(-2/sqrt(14.f), result[1]);
  EXPECT_FLOAT_EQ(3/sqrt(14.f), result[2]);

  // Check argument unchanged
  EXPECT_FLOAT_EQ(1, v1[0]);
  EXPECT_FLOAT_EQ(-2, v1[1]);
  EXPECT_FLOAT_EQ(3, v1[2]);
}

// Test reading from input
TEST(Vector3FTest, StreamInput)
{
  // Vectors into which to read values
  Vector3F v1 = Vector3F();

  // String stream of some input
  istringstream iss("( -25 3.5 5e2 )");

  iss >> v1;

  EXPECT_FLOAT_EQ(-25, v1[0]);
  EXPECT_FLOAT_EQ(3.5, v1[1]);
  EXPECT_FLOAT_EQ(500, v1[2]);
}

int main(int argc, char **argv)
{
  // Parse gtest arguments
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
