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
#include <vector>

class Scene
{
  // Vector of SceneObject pointers
  std::vector<SceneObject*> objects;

  // Vector of Light pointers
  std::vector<Light*> lights;

  public:
  // === Constructors/Destructors & methods

  // Default constructor creates an empty scene
  Scene();

  // Destructor deletes contained SceneObjects and Lights 
  ~Scene();

  // Add a SceneObject (allocated on heap)
  // Scene takes responsibility for deleting passed object
  void add_object(SceneObject *so);

  // Add a Light (allocated on heap)
  // Scene takes responsibility for deleting passed object
  void add_light(Light *l);
};




#endif
