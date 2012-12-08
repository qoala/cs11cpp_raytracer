/* light.hh
 *
 * A simple representation of a Light with position and color
 */

#ifndef _LIGHT_HH__
#define _LIGHT_HH__

#include "vector.hh"
#include "color.hh"

//! A simple colored light
class Light
{
  //! Position of light
  Vector3F position;
  //! Color of light
  Color color;

  public:
  // === Constructors & methods

  //! Constructor with position and color
  Light(Vector3F p, Color c);

  // Accessors
  //! Accessor for light position
  const Vector3F & get_position() const;
  //! Accessor for light color
  const Color & get_color() const;
};

// === Inline function definitions

// Accessors
inline const Vector3F & Light::get_position() const { return position; }
inline const Color & Light::get_color() const { return color; }

#endif
