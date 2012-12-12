/* sceneobject.hh
 *
 * An abstract base class to represent scene objects
 */

#ifndef _SCENEOBJECT_HH__
#define _SCENEOBJECT_HH__

#include "vector.hh"
#include "color.hh"
#include "ray.hh"
#include <boost/shared_ptr.hpp>

//! An abstract base class representing an object in a scene
class SceneObject
{
  //! Surface color
  Color surface_c;

  //! Surface reflectivity
  /*!
   * Ranges from 0 to 1, with 0 being completely unreflective,
   * and 1 being completely reflective.
   */
  float surface_r;

  public:
  // === Constants

  //! Return value for no intersection
  static const float no_intersection;


  // === Constructors & methods

  //! Default constructor (Surface color initialized to gray (0.5, 0.5, 0.5))
  SceneObject();

  //! Constructor specifying surface color and reflectivity
  SceneObject(const Color &c, float r = 0);

  //! Accessor for surface color
  const Color & get_surface_color() const;
  //! Accessor for surface reflectivity
  float get_surface_reflectivity() const;
  //! Mutator to set surface color
  void set_surface_color(const Color &c);
  //! Mutator to set surface reflectivity
  void set_surface_reflectivity(float r);

  //! Identify first intersection with a ray
  /*!
   * \returns The t value of the nearest intersection
   *          or SceneObject::no_intersection if there was none.
   */
  virtual float intersection(const Ray &r) const = 0;

  //! Get the surface normal at a point p
  /*!
   * \param p A point assumed to be on the object's surface
   * \returns A normalized direction vector for the surface normal
   */
  virtual Vector3F get_normal(const Vector3F &p) const = 0;

  //! Get the surface color at a point p
  /*!
   * By default, returns the object's surface color.
   * \param p A point assumed to be on the object's surface
   * \returns The color of the surface point
   */
  virtual Color get_color(const Vector3F &p) const;
};

//! Boost Shared Pointer to SceneObject
typedef boost::shared_ptr<SceneObject> SPSceneObject;

//! Function type which reads an istream and produces a scene object
typedef SPSceneObject (*SceneObjectReader)(std::istream &is);

// === Inline function definitions

// Accessor & Mutator for surface color & reflectivity
inline const Color & SceneObject::get_surface_color() const
{
  return surface_c;
}
inline void SceneObject::set_surface_color(const Color &c)
{
  surface_c = c;
}
inline float SceneObject::get_surface_reflectivity() const
{
  return surface_r;
}
inline void SceneObject::set_surface_reflectivity(float r)
{
  surface_r = r;
}

#endif
