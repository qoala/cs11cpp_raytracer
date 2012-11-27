/* scene.cc
 *
 * A Scene representation listing a combination of Lights and SceneObjects
 *
 * Lights and SceneObjects passed in are dynamically allocated,
 * and the Scene object takes responsibility for cleaning them up
 */

#include "scene.hh"
#include <algorithm>
#include <functional>

using namespace std;

// Default constructor creates an empty scene
Scene::Scene()
  : objects()
  , lights()
{ }

// Helper functions for destructor
// Function to delete SceneObjects
static void delete_object(SceneObject *so) { delete so; }
// Function to delete Lights
static void delete_light(Light *l) { delete l; }

// Destructor deletes contained SceneObjects and Lights 
Scene::~Scene()
{
  // Delete SceneObjects
  for_each(objects.begin(), objects.end(), ptr_fun(delete_object));

  // Delete Lights
  for_each(lights.begin(), lights.end(), ptr_fun(delete_light));
}

// Add a SceneObject (allocated on heap)
// Scene takes responsibility for deleting passed object
void add_object(SceneObject *so)
{
}

// Add a Light (allocated on heap)
// Scene takes responsibility for deleting passed object
void add_light(Light *l)
{
}


