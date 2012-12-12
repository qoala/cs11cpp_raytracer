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
#include <cfloat>
#include <cmath>

using namespace std;

// Default constructor creates an empty scene
Scene::Scene()
  : objects()
  , lights()
{ }

// Add a SceneObject (allocated on heap)
// Scene takes responsibility for deleting passed object
void Scene::add_object(SPSceneObject so)
{
  assert(so != NULL);
  objects.push_back(so);
}

// Add a Light (allocated on heap)
// Scene takes responsibility for deleting passed object
void Scene::add_light(SPLight l)
{
  assert(l != NULL);
  lights.push_back(l);
}


// Trace a ray
/*!
 * \param r         Ray to trace for SceneObjects
 * \param max_depth Maximum remaining number of intersections allowed
 *                  (Defaults to 6)
 * \returns         the Color along the traced ray, or black if no intersection.
 */
Color Scene::trace_ray(const Ray &r, unsigned int max_depth) const
{
  // Color of ray initially black
  // Color of the surface based on lighting
  Color c = Color(0, 0, 0);

  // Position of nearest intersection
  float t;
  // Pointer to closest object
  SPSceneObject so = find_closest_object(r, t);

  // Return if no intersection
  if (t == SceneObject::no_intersection)
    return c;


  // Position of intersection point
  Vector3F pos = r.get_point_at_t(t);

  // Surface normal of object at point
  Vector3F n = so->get_normal(pos);

  // Surface color of object
  const Color &so_c = so->get_surface_color();

  for (unsigned int i = 0; i < lights.size(); ++i)
  {
    // Normalized vector from intersection to light
    Vector3F v_l = lights[i]->get_position() - pos;
    v_l.normalize();

    // Filter light color with surface color and angle of incidence
    c += lights[i]->get_color() * so_c * fmax(dot(n, v_l), 0);
  }

  c.clamp();

  // Surface reflectivity
  float so_r = so->get_surface_reflectivity();
  if (so_r != 0 && max_depth > 0)
  {
    // Color based on reflection
    Color reflect_c = trace_ray(r.reflect(pos, n), max_depth - 1);

    return so_r * reflect_c + ((1 - so_r) * c);
  }
  else
    return c;
}

/*!
 * \param[in]  r  Ray to trace along
 * \param[out] t  Intersection point along ray, or SceneObject::no_intersection
 * \returns A shared pointer to the closest object, NULL if no intersection
 */
SPSceneObject Scene::find_closest_object(const Ray &r, float &t) const
{
  // Pointer to closest object yet found
  SPSceneObject closest = SPSceneObject();
  // Position of nearest intersection (start from max float value)
  t = FLT_MAX;

  for (unsigned int i = 0; i < objects.size(); ++i)
  {
    // Get intersection of Object & Ray
    float intxn = objects[i]->intersection(r);

    if (intxn != SceneObject::no_intersection && intxn < t)
    {
      t = intxn;
      closest = objects[i];
    }
  }

  if (closest == NULL)
    t = SceneObject::no_intersection;

  return closest;
}

/*!
 * \param cam       Camera from which to render the scene
 * \param img_size  Pixel dimensions of image (Only square images supported)
 * \param os        Output stream to write image in ppm format
 */
void Scene::render(const Camera &cam, int img_size, ostream &os) const
{
  // Maximum integer value for colors
  static int MAX_C = 255;

  // Header of a PPM file
  os << "P3 " << img_size << ' ' << img_size << ' ' << MAX_C << endl;

  // Iterate through pixels of image
  for (int y = 0; y < img_size; ++y)
  {
    for (int x = 0; x < img_size; ++x)
    {
      // Get ray and color for pixel
      Ray r = cam.get_ray_for_pixel(x, y, img_size);
      Color c = trace_ray(r);

      // Output for each pixel
      os << int(c.get_red() * MAX_C + 0.5) << ' ';
      os << int(c.get_green() * MAX_C + 0.5) << ' ';
      os << int(c.get_blue() * MAX_C + 0.5) << endl;
    }
  }
}



