/* scene.hh
 *
 * A Scene representation listing a combination of SceneObjects and Lights 
 *
 * Lights and SceneObjects passed in are dynamically allocated,
 * and the Scene object takes responsibility for cleaning them up
 */

#ifndef _SCENE_HH__
#define _SCENE_HH__

#include "sceneobject.hh"
#include "light.hh"
#include "camera.hh"
#include "ray.hh"
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>

//! Boost Shared Pointer to SceneObject
typedef boost::shared_ptr<SceneObject> SPSceneObject;
//! Boost Shared Pointer to Light
typedef boost::shared_ptr<Light> SPLight;

class Scene
{
  // Vector of SceneObject pointers
  std::vector<SPSceneObject> objects;

  // Vector of Light pointers
  std::vector<SPLight> lights;

  public:
  // === Constructors/Destructors & methods

  // Default constructor creates an empty scene
  Scene();

  // Add a SceneObject (allocated on heap)
  // Scene takes responsibility for deleting passed object
  void add_object(SPSceneObject so);

  // Add a Light (allocated on heap)
  // Scene takes responsibility for deleting passed object
  void add_light(SPLight l);


  // Trace a ray, returning the color of the traced ray.
  // Returns black if no intersection
  Color trace_ray(const Ray &r) const;

  // Identify the closest object along a ray
  // Returns the closest object
  // Stores the intersection value in output parameter t
  // If no intersection, sets t to SceneObject::no_intersection
  // and returns NULL
  SPSceneObject find_closest_object(const Ray &r, float &t) const;

  // Render this Scene using a provided Camera and given image size
  // Writes output in ppm format to ostream os
  void render(const Camera &cam, int img_size, std::ostream &os) const;
};




#endif
