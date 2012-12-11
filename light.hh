/* light.hh
 *
 * A simple representation of a Light with position and color
 */

#ifndef _LIGHT_HH__
#define _LIGHT_HH__

#include "vector.hh"
#include "color.hh"
#include <boost/shared_ptr.hpp>

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

//! Boost Shared Pointer to Light
typedef boost::shared_ptr<Light> SPLight;

/*! \relates Light
 * \brief Function to read a Light from an input stream
 */
SPLight read_Light(std::istream &is);

// === Inline function definitions

// Accessors
inline const Vector3F & Light::get_position() const { return position; }
inline const Color & Light::get_color() const { return color; }

#endif
