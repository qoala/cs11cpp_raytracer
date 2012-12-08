/* plane.hh
 *
 * A SceneObject that represents an infinite plane
 */

#ifndef _PLANE_HH__
#define _PLANE_HH__

#include "sceneobject.hh"

//! A SceneObject that represents an infinite plane
class Plane : public SceneObject
{
  //! Distance from origin
  float dist;
  //! Surface normal of plane
  Vector3F norm;

  public:

  // === Constructors & methods

  //! Construct infinite plane with default color
  Plane(float d, const Vector3F &n);

  //! Construct infinite plane
  Plane(float d, const Vector3F &n, const Color &c);

  //! Accessor for distance from origin
  float get_dist() const;
  //! Accessor for surface normal
  const Vector3F & get_norm() const;

  // Identify first intersection with a ray
  // (See sceneobject.hh)
  float intersection(const Ray &r) const;

  // Get the normal to the surface at a point p
  // (See sceneobject.hh)
  Vector3F get_normal(const Vector3F &p) const;
};

// === Inline function definitions

// Accessors for members
inline float Plane::get_dist() const { return dist; }
inline const Vector3F & Plane::get_norm() const { return norm; }

#endif
