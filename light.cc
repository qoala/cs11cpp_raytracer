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

/*! \relates Light
 * Reads a Light from the provided input stream in the format:
 * "position color"
 *
 * With the read formats for Vectors & Colors, this looks like:
 * "(x y z) [r g b]"
 *
 * \param is  Input stream from which to read a new Plane
 * \returns   Pointer to a new Light, or NULL if reading failed
 */
SPLight read_Light(std::istream &is)
{
  // Check if stream is already bad
  if (!is) return SPLight();

  Vector3F p;
  Color c;

  // Read components
  is >> p;
  is >> c;

  if (is)
  {
    SPLight sl(new Light(p, c));

    return sl;
  }
  else
  {
    return SPLight();
  }
}
