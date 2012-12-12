/*! \file
 *
 * A simple Ray for tracing 3D scenes
 */

#ifndef _RAY_HH__
#define _RAY_HH__

#include "vector.hh"

//! A 3-dimensional ray with origin and direction
class Ray
{
  //! Origin vector
  Vector3F orig;
  //! Direction vector
  Vector3F dir;

  public:
  //! Constructor takes origin and direction vectors
  Ray(const Vector3F &orig, const Vector3F &dir, bool normalize = true);

  /* Accessors */

  //! Accessor for ray origin
  const Vector3F & get_orig() const;
  //! Accessor for ray direction
  const Vector3F & get_dir() const;

  //! Calculate position at point t along ray
  Vector3F get_point_at_t(float t) const;

  //! Reflect Ray off of position with surface normal
  Ray reflect(const Vector3F &p, const Vector3F &n, float DELTA = 0.0001) const;
};

// === Inline Definitions

/* Accessors */
inline const Vector3F & Ray::get_orig() const { return orig; }
inline const Vector3F & Ray::get_dir() const { return dir; }

#endif
