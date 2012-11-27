/* sceneobject.hh
 *
 * An abstract base class to represent scene objects
 */

#ifndef _SCENEOBJECT_HH__
#define _SCENEOBJECT_HH__

#include "vector.hh"
#include "color.hh"
#include "ray.hh"

class SceneObject
{
  // Surface color
  Color surface_c;

  public:
  // === Constants

  // Return value for no intersection
  static const float no_intersection;


  // === Constructors & methods

  // Default constructor
  // Initializes surface color to gray (0.5, 0.5, 0.5)
  SceneObject();

  // Constructor specifying surface color
  SceneObject(const Color &c);

  // Accessor & Mutator for surface color
  const Color & get_surface_color() const;
  void set_surface_color(const Color &c);

  // Identify first intersection with a ray (Pure-virtual)
  // Returns t value of intersection
  // If no intersection occurs, returns SceneObject::no_intersection
  virtual float intersection(const Ray &r) const = 0;

  // Get the normal to the surface at a point p
  // p is assumed to be on the surface of the SceneObject
  // returns a normalized direction vector
  virtual Vector3F get_normal(const Vector3F &p) const = 0;

  // Get the color at a point p
  // p is assumed to be a point on the surface of the SceneObject
  // By default, returns the general surface color
  virtual Color get_color(const Vector3F &p) const;
};

// === Inline function definitions

// Accessor & Mutator for surface color
inline const Color & SceneObject::get_surface_color() const
{
  return surface_c;
}
inline void SceneObject::set_surface_color(const Color &c)
{
  surface_c = c;
}

#endif
