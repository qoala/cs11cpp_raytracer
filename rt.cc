/*! \file
 * \brief A simple ray tracer program
 *
 * Draws 3 spheres over a plane, writing in PPM format to std out
 */

#include "scene.hh"
#include "plane.hh"
#include "sphere.hh"
#include <iostream>

using namespace std;
using namespace boost;

int main()
{
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

    scn.add_object(pln);
    scn.add_object(s1);
    scn.add_object(s2);
    scn.add_object(s3);

    scn.add_light(l1);
    scn.add_light(l2);
  }

  // Create a camera to render the scene from
  Camera cam = Camera(Vector3F({-1.5, 1, 3}),   // Position
                      Vector3F({-0.3, 0.5, 0}), // Look-at target
                      Vector3F({0, 1, 0}));     // Up

  // Render the scene to std out
  scn.render(cam, 500, cout);

}
