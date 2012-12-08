/* light.cc
 *
 * A simple representation of a Light with position and color
 */

#include "light.hh"

/*!
 * \param p Position vector of the light
 * \param c Color of the light
 */
Light::Light(Vector3F p, Color c)
  : position(p)
  , color(c)
{ }
