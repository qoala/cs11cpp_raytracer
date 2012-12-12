/*! \file
 * \brief A simple ray tracer program
 *
 * Draws 3 spheres over a plane, writing in PPM format to std out
 */

#include "scene.hh"
#include "plane.hh"
#include "sphere.hh"
#include "cylinder.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;
using namespace boost;

/*!
 * Reads a scene from the given input stream
 *
 * Each line of input should describe a different component of the scene.
 * A line starts with the type of component being described, followed by
 * the relevant construction for that component.  These are as follows:
 *
 * - camera (position vector) (look at vector) (up vector)
 * - light (position vector) [color]
 * - plane  distance_from_orign (normal vector) [color]
 * - sphere (center position vector) radius [color]
 *
 * Vectors are in the format "(x y z)"
 * and Colors are in the format "[r g b]"
 *
 * If multiple Camera lines are provided, only the last is used.
 * At least one camera must be defined.
 *
 * Empty lines are ignored, as are comment lines which begin with "#".
 * The pound sign must be the first character on the line.
 *
 * \param[in]  is         An input stream to read.  Reading stops at EOF.
 * \param[in]  readFuncs  A mapping of names to a function that takes an
 *                        istream and returns SPSceneObjects
 * \param[out] scn        Scene containing described objects
 * \param[out] cam        Camera read from scene
 * \returns               true if input reaches EOF successfully.
 */
bool read_Scene(istream &is, map<string, SceneObjectReader> readFuncs,
           Scene &scn, Camera &cam)
{
  // Create an empty scene
  scn = Scene();

  // Create a blank camera
  cam = Camera();

  // Success flag (continue reading lines after error, to identify all errors)
  bool success = true;

  // Loop through lines in input
  string line;
  int ln = 0;
  for (getline(is, line); is.good(); getline(is, line))
  {
    // Increment line #
    ++ln;

    // Check for comment line
    if (line.length() == 0 || line[0] == '#') continue;

    // Create a string stream to read the line
    istringstream iss(line);

    // Read in the next component type
    string type;
    iss >> type;

    // Check for empty line
    if (!iss) continue;

    if (readFuncs.find(type) != readFuncs.end())
    {
      // New object to read
      SPSceneObject obj;

      // Read object using appropriate function
      obj = readFuncs[type](iss);

      if (obj == NULL)
      {
        success = false;
        cerr << "Error: Couldn't read " << type << " on line " << ln << endl;
      }
      else
      {
        scn.add_object(obj);
      }
    }
    else if (type == "light")
    {
      // New light to read
      SPLight l;

      l = read_Light(iss);

      if (l == NULL)
      {
        success = false;
        cerr << "Error: Couldn't read light on line " << ln << endl;
      }
      else
      {
        scn.add_light(l);
      }
    }
    else if (type == "camera")
    {
      cam = read_Camera(iss);

      if (!cam.valid())
      {
        success = false;
        cerr << "Error: Couldn't read camera (or invalid camera) on line ";
        cerr << ln << endl;
      }
    }
    else
    {
      success = false;
      cerr << "Error: Unrecognized type \"" << type << "\" on line " << ln;
      cerr << endl;
    }

  }

  return success;
}

/*!
 * Read a scene description on std in and render it in ppm format on std out.
 *
 * For formatting, see \ref read_Scene;
 */
int main()
{
  // Map of type names to SceneObjectReader functions
  map<string, SceneObjectReader> readFuncs;

  // Add types to the mapping
  readFuncs["plane"] = read_Plane;
  readFuncs["sphere"] = read_Sphere;
  readFuncs["cylinder"] = read_Cylinder;

  // Read the scene in from std in description
  Scene scn;
  Camera cam;

  if(!read_Scene(cin, readFuncs, scn, cam))
  {
    cerr << "Parsing of scene description failed." << endl;
  }
  else
  {
    // Render the scene to std out
    scn.render(cam, 500, cout);
  }

}
