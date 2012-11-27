/* intersect_test.cc
 *
 * gtest test suite to test intersection between Rays and various SceneObjects
 *
 * NOT all inclusive or complete on any tested class
 * though should test all code paths within intersection code
 */

#include "ray.hh"
#include "sphere.hh"
#include "plane.hh"
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

// === Sphere intersection() & get_intersections()

// Ray and its opposite extend through sphere's interior, 2 intersections
// (Ray points at sphere)
TEST(SphereTest, Through2Intersections)
{
  // Sphere for straight-on intersections
  Sphere s1 = Sphere(Vector3F({2, 0, 0}), 1);
  // Sphere for oblique intersections
  Sphere s2 = Sphere(Vector3F({2, 1, 0}), sqrt(2));

  // Ray pointing at spheres
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Nearest intersection tests:
  EXPECT_FLOAT_EQ(1., s1.intersection(r));
  EXPECT_FLOAT_EQ(1., s2.intersection(r));

  // All intersection tests:
  float t1, t2;

  EXPECT_EQ(2, s1.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(1., t1);
  EXPECT_FLOAT_EQ(3., t2);

  EXPECT_EQ(2, s2.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(1., t1);
  EXPECT_FLOAT_EQ(3., t2);
}

// Ray and its opposite extend through sphere's interior, 1 intersection
// (Ray originates inside sphere)
TEST(SphereTest, Through1Intersections)
{
  // Sphere for straight-on intersections
  Sphere s1 = Sphere(Vector3F({0, 0, 0}), 1);
  // Sphere for oblique intersections
  Sphere s2 = Sphere(Vector3F({0, 1, 0}), sqrt(2));

  // Ray inside spheres
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Nearest intersection tests:
  EXPECT_FLOAT_EQ(1., s1.intersection(r));
  EXPECT_FLOAT_EQ(1., s2.intersection(r));

  // All intersection tests:
  float t1, t2;

  EXPECT_EQ(1, s1.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(1., t1);
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t2);

  EXPECT_EQ(1, s2.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(1., t1);
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t2);
}

// Ray and its opposite extend through sphere's interior, 0 intersections
// (Ray points away from sphere)
TEST(SphereTest, Through0Intersections)
{
  // Sphere for straight-on intersections
  Sphere s1 = Sphere(Vector3F({-2, 0, 0}), 1);
  // Sphere for oblique intersections
  Sphere s2 = Sphere(Vector3F({-2, 1, 0}), sqrt(2));

  // Ray pointing away from spheres
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Nearest intersection tests:
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, s1.intersection(r));
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, s2.intersection(r));

  // All intersection tests:
  float t1, t2;

  EXPECT_EQ(0, s1.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t1);
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t2);

  EXPECT_EQ(0, s2.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t1);
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t2);
}

// Ray and its opposite are tangent to sphere, 1 intersection
// (Ray passes beside sphere)
TEST(SphereTest, TangentIntersection)
{
  // Sphere for straight-on intersections
  Sphere s1 = Sphere(Vector3F({1, 1, 0}), 1);

  // Ray tangent to spheres
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Nearest intersection tests:
  EXPECT_FLOAT_EQ(1., s1.intersection(r));

  // All intersection tests:
  float t1, t2;

  EXPECT_EQ(1, s1.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(1., t1);
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t2);
}

// Ray and its opposite are tangent to sphere, 1 intersection at t=0
// (Ray starts beside sphere)
TEST(SphereTest, TangentIntersectionAt0)
{
  // Sphere for straight-on intersections
  Sphere s1 = Sphere(Vector3F({0, 1, 0}), 1);

  // Ray tangent to spheres
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Nearest intersection tests:
  EXPECT_FLOAT_EQ(0., s1.intersection(r));

  // All intersection tests:
  float t1, t2;

  EXPECT_EQ(1, s1.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(0., t1);
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t2);
}

// Ray and its opposite are tangent to sphere, 0 intersections
// (Opposite of Ray passes beside sphere)
TEST(SphereTest, TangentMiss)
{
  // Sphere for straight-on intersections
  Sphere s1 = Sphere(Vector3F({-1, 1, 0}), 1);

  // Ray tangent to spheres
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Nearest intersection tests:
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, s1.intersection(r));

  // All intersection tests:
  float t1, t2;

  EXPECT_EQ(0, s1.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t1);
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t2);
}

// Ray and its opposite both completely miss sphere, 0 intersections
TEST(SphereTest, Miss)
{
  // Sphere for straight-on intersections
  Sphere s1 = Sphere(Vector3F({0, 3, 4}), 1);

  // Ray tangent to spheres
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Nearest intersection tests:
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, s1.intersection(r));

  // All intersection tests:
  float t1, t2;

  EXPECT_EQ(0, s1.get_intersections(r, t1, t2));
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t1);
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, t2);
}

// === Plane intersection()

// Ray intersects plane
TEST(PlaneTest, Intersection)
{
  // Plane for straight-on intersection
  Plane p1 = Plane(1, Vector3F({-1, 0, 0}));
  // Plane for oblique intersection
  Plane p2 = Plane(sqrt(2)/2, Vector3F({-1, -1, 0}));

  // Ray pointing at planes
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Intersection test
  EXPECT_FLOAT_EQ(1., p1.intersection(r));
  EXPECT_FLOAT_EQ(1., p2.intersection(r));
}

// Ray points away from plane
TEST(PlaneTest, Miss)
{
  // Plane for straight-on intersection
  Plane p1 = Plane(-1, Vector3F({-1, 0, 0}));
  // Plane for oblique intersection
  Plane p2 = Plane(-sqrt(2)/2, Vector3F({-1, -1, 0}));

  // Ray pointing away from planes
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Intersection test
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, p1.intersection(r));
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, p2.intersection(r));
}

// Ray is tangent to plane, miss until infinity
TEST(PlaneTest, TangentMiss)
{
  Plane p1 = Plane(-1, Vector3F({0, -1, 0}));

  // Ray tangent to plane
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Intersection test
  EXPECT_FLOAT_EQ(SceneObject::no_intersection, p1.intersection(r));
}

// Ray is tangent to plane, but touching
TEST(PlaneTest, TangentIntersection)
{
  Plane p1 = Plane(0, Vector3F({0, -1, 0}));

  // Ray tangent to plane
  Ray r = Ray(Vector3F({0, 0, 0}), Vector3F({1, 0, 0}));

  // Intersection test
  EXPECT_FLOAT_EQ(0., p1.intersection(r));
}

int main(int argc, char **argv)
{
  // Parse gtest arguments
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
