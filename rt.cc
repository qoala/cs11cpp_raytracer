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

int main()
{
  Scene scn = Scene();

  // Create some objects & lights and give them to the Scene
  {
    Plane *pln = new Plane(0, Vector3F({0, 1, 0}), Color(0.5, 0, 0.5));
    Sphere *s1 = new Sphere(Vector3F({-1.2, 0.5, 0}), 0.5, Color(1, 0, 0));
    Sphere *s2 = new Sphere(Vector3F({0, 0.5, 0}), 0.5, Color(0, 1, 0));
    Sphere *s3 = new Sphere(Vector3F({1.2, 0.5, 0}), 0.5, Color(0, 0, 1));

    Light *l1 = new Light(Vector3F({-10, 10, 5}), Color(0.8, 0.8, 0.8));
    Light *l2 = new Light(Vector3F({5, 3, 5}), Color(0.3, 0.3, 0.3));

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
