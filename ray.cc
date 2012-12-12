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

// Reflect Ray
/*!
 * \param p Position of intersection with reflective object
 * \param n Surface normal of object at point of intersection
 *          (must be normalized)
 * \param DELTA delta by which to offset origin,
 *              preventing intersection with the same object again.
 *              (defaults to 0.0001)
 * \returns Reflected ray originating from just past p.
 */
Ray Ray::reflect(const Vector3F &p, const Vector3F &n, float DELTA) const
{
  // New direction negates component in direction of n
  Vector3F new_dir = dir + 2.f * project(-dir, n);

  // New origin offset from intersection point
  Vector3F new_orig = p + new_dir * DELTA;

  return Ray(new_orig, new_dir);
}
