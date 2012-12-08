/*! \file
 * A simple Color class
 */

#ifndef _COLOR_HH__
#define _COLOR_HH__

#include <cassert>
#include <iostream>

//! An RGB float color representation
class Color
{
  // === RGB contents
  //! Red component
  float r;
  //! Green component
  float g;
  //! Blue component
  float b;

  public:

  // === Constructors

  //! Default constructor (Initializes with all zeros)
  Color();

  //! 3-Argument Constructor
  Color(float r, float g, float b);


  /* Element accessors */
  //! Accessor for red component
  float get_red() const;
  //! Accessor for green component
  float get_green() const;
  //! Accessor for blue component
  float get_blue() const;

  /* Element mutators, return *this for chaining */
  //! Mutator to set the red component
  Color & set_red(float red);
  //! Mutator to set the green component
  Color & set_green(float green);
  //! Mutator to set the blue component
  Color & set_blue(float blue);

  /* Arithmetic & Compound Assignment Operators */
  //! Compound Assignment with addition
  Color & operator+=(const Color &rhs);
  //! Compound Assignment with subtraction
  Color & operator-=(const Color &rhs);
  //! Compound Assignment with color multiplication
  Color & operator*=(const Color &rhs);
  //! Binary addition operator
  const Color operator+(const Color &other) const;
  //! Binary subtraction operator
  const Color operator-(const Color &other) const;
  //! Binary Color multiplication operator
  const Color operator*(const Color &other) const;

  /* Scalar Mult/Div */
  //! Compound Assignment with scalar multiplication
  Color & operator*=(const float &s);
  //! Compound Assignment with scalar division
  Color & operator/=(const float &s);

  //! Clamp this color to [0,1] on all components
  Color & clamp();
};


// === Non-member functions

/*! \relates Color
 * \brief Print operator
 */
std::ostream & operator<<(std::ostream &os, const Color &c);

/* Scalar Mult/Div */

/*! \relates Color
 * \brief Scalar multiplication binary operator
 */
const Color operator*(const Color &c, const float &s);

/*! \relates Color
 * \brief Scalar multiplication binary operator
 */
const Color operator*(const float &s, const Color &c);

/*! \relates Color
 * \brief Scalar division binary operator
 */
const Color operator/(const Color &c, const float &s);

// === Inline Definitions

/* Accessors */
inline float Color::get_red() const { return r; }
inline float Color::get_green() const { return g; }
inline float Color::get_blue() const { return b; }

#endif
