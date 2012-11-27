/* ray.hh
 *
 * A 3-dimensional ray with origin and direction
 */

#ifndef _RAY_HH__
#define _RAY_HH__

#include "vector.hh"


class Ray
{
  // Origin
  Vector3F orig;
  // Direction
  Vector3F dir;

  public:
  // Constructor
  // If normalize is true (the default), dir will be normalized
  // Asserts that direction dir has nonzero norm
  Ray(const Vector3F &orig, const Vector3F &dir, bool normalize = true);

  // Accessors
  const Vector3F & get_orig() const;
  const Vector3F & get_dir() const;

  // Get Point Ray reaches at T
  // Asserts that (t >= 0)
  Vector3F get_point_at_T(float t);
};

// === Inline Definitions

// Accessors
inline const Vector3F & Ray::get_orig() const { return orig; }
inline const Vector3F & Ray::get_dir() const { return dir; }

#endif
