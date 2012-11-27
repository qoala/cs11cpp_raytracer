/* plane.cc
 *
 * A SceneObject that represents an infinite plane
 */

#include "plane.hh"

// Construct infinite plane
// with distance d, surface normal n, and default color
Plane::Plane(float d, const Vector3F &n)
  : dist(d)
  , norm(n.get_normalized())
{ }

// Construct infinite plane
// with distance d, surface normal n, and color c
Plane::Plane(float d, const Vector3F &n, const Color &c)
  : SceneObject(c)
  , dist(d)
  , norm(n.get_normalized())
{ }

// Identify first intersection with a ray
// (See sceneobject.hh)
float Plane::intersection(const Ray &r) const
{
  float numerator   = dot(r.get_orig(), norm) + dist;
  float denominator = dot(r.get_dir(), norm);

  // Test for Ray parallel to Plane
  if (denominator == 0)
  {
    if (numerator == 0)
    {
      // (0/0) Ray originates on Plane
      return 0;
    }
    else
    {
      // (x/0) parallel Ray will never intersect
      return no_intersection;
    }
  }

  float result = -numerator / denominator;

  // Check for no intersection
  if (result < 0)
    result = no_intersection;

  return result;
}

// Get the normal to the surface at a point p
// (See sceneobject.hh)
Vector3F Plane::get_normal(const Vector3F &p) const
{
  // Surface normal is constant over an infinite plane
  return norm;
}
