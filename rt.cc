/*! \file
 * \brief A simple ray tracer program
 *
 * Draws 3 spheres over a plane, writing in PPM format to std out
 */

#include "scene.hh"
#include "plane.hh"
#include "sphere.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;
using namespace boost;

int main()
{
  // Map of type names to SceneObjectReader functions
  map<string, SceneObjectReader> readFuncs;

  // Add types to the mapping
  readFuncs["plane"] = read_Plane;
  readFuncs["sphere"] = read_Sphere;

  // Create an empty scene
  Scene scn = Scene();

  // Create some objects & lights and give them to the Scene
  {
    SPSceneObject pln = SPSceneObject(new Plane(0, Vector3F({0, 1, 0}),
                                                Color(0.5, 0, 0.5)));
    SPSceneObject s1 = SPSceneObject(new Sphere(Vector3F({-1.2, 0.5, 0}),
                                                0.5, Color(1, 0, 0)));
    SPSceneObject s2 = SPSceneObject(new Sphere(Vector3F({0, 0.5, 0}),
                                                0.5, Color(0, 1, 0)));
    SPSceneObject s3 = SPSceneObject(new Sphere(Vector3F({1.2, 0.5, 0}),
                                                0.5, Color(0, 0, 1)));

    SPLight l1 = SPLight(new Light(Vector3F({-10, 10, 5}),
                                   Color(0.8, 0.8, 0.8)));
    SPLight l2 = SPLight(new Light(Vector3F({5, 3, 5}),
                                   Color(0.3, 0.3, 0.3)));

    /*
    // Test reading planes
    istringstream iss("0 (0 1 0) [0.5 0 0.5]");
    scn.add_object(read_Plane(iss));
    */

    /*
    // Test reading spheres
    istringstream iss("(-1.2 0.5 0) 0.5 [1 0 0]");
    scn.add_object(read_Sphere(iss));
    */

    /*
    // Test reading lights
    istringstream iss("(-10 10 5) [0.8 0.8 0.8]");
    scn.add_light(read_Light(iss));
    */

    scn.add_object(pln);
    scn.add_object(s1);
    scn.add_object(s2);
    scn.add_object(s3);

    scn.add_light(l1);
    scn.add_light(l2);
  }

  /*
  // Create a camera to render the scene from
  Camera cam = Camera(Vector3F({-1.5, 1, 3}),   // Position
                      Vector3F({-0.3, 0.5, 0}), // Look-at target
                      Vector3F({0, 1, 0}));     // Up
  */
  // Test reading cameras
  istringstream iss("(-1.5 1 3) (-.3 .5 0) (0 1 0)");
  Camera cam = read_Camera(iss);

  // Render the scene to std out
  scn.render(cam, 500, cout);

}
