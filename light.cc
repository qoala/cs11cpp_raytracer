/* light.cc
 *
 * A simple representation of a Light with position and color
 */

#include "light.hh"

Light::Light(Vector3F p, Color c)
  : position(p)
  , color(c)
{ }
