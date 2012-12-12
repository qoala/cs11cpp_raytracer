/* sphere.cc
 *
 * A SceneObject representing a Sphere
 */

#include "sphere.hh"
#include <cassert>
#include <cmath>

using namespace std;

// Construct a sphere with center c, radius r, and default color & reflectivity
/*!
 * \param c   Position vector of sphere's center
 * \param r   Radius of sphere
 */
Sphere::Sphere(const Vector3F &c, float r)
  : center(c)
  , radius(r)
{ }

// Construct a sphere with center c, radius r, color col, and default reflect.
/*!
 * \param c   Position vector of sphere's center
 * \param r   Radius of sphere
 * \param col Surface color of sphere
 */
Sphere::Sphere(const Vector3F &c, float r, const Color &col)
  : SceneObject(col)
  , center(c)
  , radius(r)
{ }

// Construct a Sphere
/*!
 * \param c   Position vector of sphere's center
 * \param r   Radius of sphere
 * \param col Surface color of sphere
 * \param ref Surface reflectivity of sphere
 */
Sphere::Sphere(const Vector3F &c, float r, const Color &col, float ref)
  : SceneObject(col, ref)
  , center(c)
  , radius(r)
{ }

// Identify all (up to 2) intersections with a ray
/*!
 * \param[in]  r  The ray to test for intersection
 * \param[out] t1 The nearest intersection (if at least 1)
 *                or SceneObject::no_intersection
 * \param[out] t2 The further intersection (if 2)
 *                or SceneObject::no_intersection
 * \returns       The number of intersections (0 - 2, inclusive)
 */
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

/*! \relates Sphere
 * Reads a Sphere from the provided input stream in the format:
 * "center radius color"
 *
 * With the read formats for Vectors & Colors, this looks like:
 * "(x y z) radius [r g b]"
 *
 * \param is  Input stream from which to read a new Plane
 * \returns   Pointer to a new Sphere, or NULL if reading failed
 */
SPSceneObject read_Sphere(std::istream &is)
{
  // Check if stream is already bad
  if (!is) return SPSceneObject();

  Vector3F pos;
  float r;
  Color c;
  float ref;

  // Read components
  is >> pos;
  is >> r;
  is >> c;
  is >> ref;

  if (is)
  {
    SPSceneObject sso(new Sphere(pos, r, c, ref));

    return sso;
  }
  else
  {
    return SPSceneObject();
  }
}
