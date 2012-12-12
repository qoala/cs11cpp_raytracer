/* cylinder.hh
 *
 * A SceneObject representing a Cylinder
 */

#ifndef _CYLINDER_HH__
#define _CYLINDER_HH__

#include "sceneobject.hh"

//! A SceneObject representing a cylinder
class Cylinder: public SceneObject
{
  //! Position of the Cylinder's center
  Vector3F center;
  //! Long axis direction of the Cylinder (normalized)
  Vector3F axis;
  //! Radius of the Cylinder
  float radius;
  //! Height of the Cylinder
  float height;

  public:

  //! Construct a cylinder with default color & reflectivity
  Cylinder(const Vector3F &c, const Vector3F &a, float r, float h);

  //! Construct a cylinder with default reflectivity
  Cylinder(const Vector3F &c, const Vector3F &a, float r, float h,
           const Color &col);

  //! Construct a cylinder
  Cylinder(const Vector3F &c, const Vector3F &a, float r, float h,
           const Color &col, float ref);

  // Accessors for members
  //! Accessor for cylinder center
  const Vector3F & get_center() const;
  //! Accessor for cylinder axis
  const Vector3F & get_axis() const;
  //! Accessor for cylinder radius
  float get_radius() const;
  //! Accessor for cylinder height
  float get_height() const;

  //! Identify all (up to 2) intersections with a ray
  int get_intersections(const Ray &r, float &t1, float &t2) const;

  // Identify first intersection with a ray
  // (See sceneobject.hh)
  float intersection(const Ray &r) const;

  // Get the normal to the surface at a point p
  // (See sceneobject.hh)
  Vector3F get_normal(const Vector3F &p) const;
};

/*! \relates Cylinder
 * \brief Function to read a Cylinder from an input stream
 */
SPSceneObject read_Cylinder(std::istream &is);

// === Inline function definitions

// Accessors for members
inline const Vector3F & Cylinder::get_center() const { return center; }
inline const Vector3F & Cylinder::get_axis() const { return axis; }
inline float Cylinder::get_radius() const { return radius; }
inline float Cylinder::get_height() const { return height; }

#endif
