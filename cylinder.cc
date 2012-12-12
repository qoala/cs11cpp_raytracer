/* cylinder.cc
 *
 * A SceneObject representing a Cylinder
 */

#include "cylinder.hh"
#include "sphere.hh"
#include <cassert>
#include <cmath>

using namespace std;

// Construct a cylinder with default color & reflectivity
/*!
 * \param c   Position vector of cylinder's center
 * \param a   Direction of long axis (Must be non-zero)
 * \param r   Radius of cylinder
 * \param h   Height of cylinder
 */
Cylinder::Cylinder(const Vector3F &c, const Vector3F &a, float r, float h)
  : center(c)
  , axis(a)
  , radius(r)
  , height(h)
{
  assert(axis.norm() > 0);
}

// Construct a cylinder with default reflectivity
/*!
 * \param c   Position vector of cylinder's center
 * \param a   Direction of long axis (Must be non-zero)
 * \param r   Radius of cylinder
 * \param h   Height of cylinder
 * \param col Surface color of cylinder
 */
Cylinder::Cylinder(const Vector3F &c, const Vector3F &a, float r, float h,
                   const Color &col)
  : SceneObject(col)
  , center(c)
  , axis(a.get_normalized())
  , radius(r)
  , height(h)
{
  assert(axis.norm() > 0);
}

// Construct a Cylinder
/*!
 * \param c   Position vector of cylinder's center
 * \param a   Direction of long axis (Must be non-zero)
 * \param r   Radius of cylinder
 * \param h   Height of cylinder
 * \param col Surface color of cylinder
 * \param ref Surface reflectivity of cylinder
 */
Cylinder::Cylinder(const Vector3F &c, const Vector3F &a, float r, float h,
                   const Color &col, float ref)
  : SceneObject(col, ref)
  , center(c)
  , axis(a.get_normalized())
  , radius(r)
  , height(h)
{
  assert(axis.norm() > 0);
}

// Identify all (up to 2) intersections with a ray
/*!
 * \param[in]  r  The ray to test for intersection
 * \param[out] t1 The nearest intersection (if at least 1)
 *                or SceneObject::no_intersection
 * \param[out] t2 The further intersection (if 2)
 *                or SceneObject::no_intersection
 * \returns       The number of intersections (0 - 2, inclusive)
 */
int Cylinder::get_intersections(const Ray &r, float &t1, float &t2) const
{
  // Projection of center, ray origin, and ray direction along axis
  Vector3F c_par = project(center, axis);
  Vector3F p_par = project(r.get_orig(), axis);
  Vector3F d_par = project(r.get_dir(), axis);

  // Check that ray is capable of hitting cylinder
  if ((r.get_dir() - d_par).norm_sq() == 0)
  {
    t1 = no_intersection;
    t2 = no_intersection;
    return 0;
  }

  // Imaginary sphere to test intersections
  Sphere sph = Sphere(center - c_par, radius);

  // Imaginary ray projected into the cylinder's X-section plane
  // NOT normalized, so that t values transform correctly
  Ray r_proj = Ray(r.get_orig() - p_par, r.get_dir() - d_par, false);

  // Get intersections
  int count = sph.get_intersections(r_proj, t1, t2);

  // Check that intersections are within height of the cylinder

  // Check the 2nd intersection
  if ((count == 2) && ((p_par - c_par + d_par * t2).norm() > height / 2))
  {
    // Intersection misses height
    t2 = no_intersection;
    --count;
  }

  if ((count >= 1) && ((p_par - c_par + d_par * t1).norm() > height / 2))
  {
    // Intersection misses height
    t1 = t2;
    t2 = no_intersection;
    --count;
  }

  return count;
}

// Identify first intersection with a ray
// (See sceneobject.hh)
float Cylinder::intersection(const Ray &r) const
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
Vector3F Cylinder::get_normal(const Vector3F &p) const
{
  // Get vector from center to surface point p
  Vector3F offset = p - center;

  // Remove component along axis
  Vector3F result = offset - project(offset, axis);

  // normalize the result
  return result.normalize();
}

/*! \relates Cylinder
 * Reads a Cylinder from the provided input stream in the format:
 * "center radius color"
 *
 * With the read formats for Vectors & Colors, this looks like:
 * "(x y z) radius [r g b]"
 *
 * \param is  Input stream from which to read a new Plane
 * \returns   Pointer to a new Cylinder, or NULL if reading failed
 */
SPSceneObject read_Cylinder(std::istream &is)
{
  // Check if stream is already bad
  if (!is) return SPSceneObject();

  Vector3F pos;
  Vector3F axis;
  float r;
  float h;
  Color c;
  float ref;

  // Read components
  is >> pos;
  is >> axis;
  is >> r;
  is >> h;
  is >> c;
  is >> ref;

  if (is)
  {
    SPSceneObject sso(new Cylinder(pos, axis, r, h, c, ref));

    return sso;
  }
  else
  {
    return SPSceneObject();
  }
}
