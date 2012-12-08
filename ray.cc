/* ray.cc
 *
 * A 3-dimensional ray with origin and direction
 */

#include "ray.hh"
#include <cassert>



// Constructor takes origin and direction vectors
/*!
 * Asserts that dir.norm() is nonzero.
 *
 * \param orig      Position vector for ray's origin
 * \param dir       Direction vector for ray
 * \param normalize Optional flag which normalizes dir if true (the default)
 */
Ray::Ray(const Vector3F &orig, const Vector3F &dir, bool normalize)
  : orig(orig)
  , dir(normalize ? dir.get_normalized() : dir)
{
  // Check that direction is valid
  assert(dir.norm() > 0);
}

// Get Point Ray reaches at t
/*!
 * Asserts that t is non-negative.
 * \param t A non-negative value to evaluate the ray at
 * \returns A position vector of the ray's position at point t
 */
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
