/* light.hh
 *
 * A simple representation of a Light with position and color
 */

#ifndef _LIGHT_HH__
#define _LIGHT_HH__

#include "vector.hh"
#include "color.hh"

class Light
{
  // Position of light
  Vector3F position;
  // Color of light
  Color color;

  public:
  // === Constructors & methods

  // Constructor takes position and color for Light
  Light(Vector3F p, Color c);

  // Accessors
  const Vector3F & get_position() const;
  const Color & get_color() const;
};

// === Inline function definitions

// Accessors
inline const Vector3F & Light::get_position() const { return position; }
inline const Color & Light::get_color() const { return color; }

#endif
