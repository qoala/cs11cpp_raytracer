/* sphere.cc
 *
 * A SceneObject representing a Sphere
 */

#ifndef _SPHERE_HH__
#define _SPHERE_HH__

#include "sceneobject.hh"

class Sphere : public SceneObject
{
  // Position of the Sphere's center
  Vector3F center;
  // Radius of the Sphere
  float radius;

  public:

  // Construct a sphere with center c, radius r, and default color
  Sphere(const Vector3F &c, float r);

  // Construct a sphere with center c, radius r, and color col
  Sphere(const Vector3F &c, float r, const Color &col);

  // Accessors for members
  const Vector3F & get_center() const;
  float get_radius() const;

  // Identify all (up to 2) intersections with a ray
  // Takes a ray r
  // Returns the number of intersections [0-2] as a return value
  // Returns into out-parameter t1 the lowest intersection (if at least 1)
  // Returns into out-parameter t2 the higher intersection (if 2)
  // Otherwise t1 and/or t2 will be set to SceneObject::no_intersection
  int get_intersections(const Ray &r, float &t1, float &t2) const;

  // Identify first intersection with a ray
  // (See sceneobject.hh)
  float intersection(const Ray &r) const;

  // Get the normal to the surface at a point p
  // (See sceneobject.hh)
  Vector3F get_normal(const Vector3F &p) const;
};

// === Inline function definitions

// Accessors for members
inline const Vector3F & Sphere::get_center() const { return center; }
inline float Sphere::get_radius() const { return radius; }

#endif
