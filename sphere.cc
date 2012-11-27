/* sphere.cc
 *
 * A SceneObject representing a Sphere
 */

#include "sphere.hh"
#include <cassert>
#include <cmath>

using namespace std;

// Construct a sphere with center c, radius r, and default color
Sphere::Sphere(const Vector3F &c, float r)
  : center(c)
  , radius(r)
{ }

// Construct a sphere with center c, radius r, and color col
Sphere::Sphere(const Vector3F &c, float r, const Color &col)
  : SceneObject(col)
  , center(c)
  , radius(r)
{ }

// Identify all (up to 2) intersections with a ray
// Takes a ray r
// Returns the number of intersections [0-2] as a return value
// Returns into out-parameter t1 the lowest intersection (if at least 1)
// Returns into out-parameter t2 the higher intersection (if 2)
// Otherwise t1 and/or t2 will be set to SceneObject::no_intersection
int Sphere::get_intersections(const Ray &r, float &t1, float &t2) const
{
  // Set up the terms of the quadratic equation a*t^2 + b*t + c == 0
  float a = r.get_dir().norm_sq();
  float b = 2 * (dot(r.get_orig(), r.get_dir()) - dot(r.get_dir(), center));
  float c = r.get_orig().norm_sq() + center.norm_sq()
            - 2 * dot(r.get_orig(), center) - radius * radius;

  // The discriminant
  float disc = b*b - 4 * a * c;

  if (disc > 0)
  {
    // 2 solutions, though one or both might be negative
    t1 = (-b - sqrt(disc)) / (2 * a);
    t2 = (-b + sqrt(disc)) / (2 * a);

    if (t2 < 0)
    {
      // No valid intersections
      t1 = no_intersection;
      t2 = no_intersection;
      return 0;
    }
    if (t1 < 0)
    {
      // Only one valid intersection
      t1 = t2;
      t2 = no_intersection;
      return 1;
    }
    // Both valid intersections
    return 2;
  }
  else if (disc == 0)
  {
    // 1 solution, though it might be negative
    t2 = no_intersection;

    // a is positive, t is nonnegative iff b is nonnpositive
    if (b <= 0)
    {
      t1 = -b / (2 * a);
      return 1;
    }
    else
    {
      t1 = no_intersection;
      return 0;
    }
  }
  else if (disc < 0)
  {
    // 0 solutions
    t1 = no_intersection;
    t2 = no_intersection;
    return 0;
  }
  else // disc is NaN? Something broke
  {
    assert((disc > 0) || (disc == 0) || (disc < 0));
  }

  // Reached if assertions disabled
  t1 = no_intersection;
  t2 = no_intersection;
  return 0;
}

// Identify first intersection with a ray
// (See sceneobject.hh)
float Sphere::intersection(const Ray &r) const
{
  float t1, t2;

  // Get the intersections
  get_intersections(r, t1, t2);

  // Only care about the first intersection,
  // which will already be flagged if there are none
  return t1;
}

// Get the normal to the surface at a point p
// (See sceneobject.hh)
Vector3F Sphere::get_normal(const Vector3F &p) const
{
  // Get vector from center to surface point p
  Vector3F result = p - center;

  // normalize the result
  return result.normalize();
}
