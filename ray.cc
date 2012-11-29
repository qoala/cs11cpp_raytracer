/* ray.cc
 *
 * A 3-dimensional ray with origin and direction
 */

#include "ray.hh"
#include <cassert>



// Constructor
// If normalize is true (the default), dir will be normalized
Ray::Ray(const Vector3F &orig, const Vector3F &dir, bool normalize)
  : orig(orig)
  , dir(normalize ? dir.get_normalized() : dir)
{
  // Check that direction is valid
  assert(dir.norm() > 0);
}

// Get Point Ray reaches at t
// Asserts that (t >= 0)
Vector3F Ray::get_point_at_t(float t) const
{
  // Check that t is valid
  assert(t >= 0);

  // Start from the Ray's origin
  Vector3F result = orig;
  // Translate by t * the direction
  result += dir * t;

  return result;
}
