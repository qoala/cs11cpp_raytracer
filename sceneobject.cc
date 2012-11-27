/* sceneobject.cc
 *
 * An abstract base class to represent scene objects
 */

#include "sceneobject.hh"

// Return value for no intersection
const float SceneObject::no_intersection = -1;

// Default constructor
// Initializes surface color to gray (0.5, 0.5, 0.5)
SceneObject::SceneObject()
  : surface_c(0.5, 0.5, 0.5)
{ }

// Constructor specifying surface color
SceneObject::SceneObject(const Color &c)
  : surface_c(c)
{ }

// Get the color at a point p
// p is assumed to be a point on the surface of the SceneObject
// By default, returns the general surface color
Color SceneObject::get_color(const Vector3F &p) const
{
  return surface_c;
}
