/* color.hh
 *
 * An RGB float color representation
 */

#ifndef _COLOR_HH__
#define _COLOR_HH__

#include <cassert>
#include <iostream>

class Color
{
  /* RGB contents */
  float r;
  float g;
  float b;

  public:

  /* Constructors */

  /* Default constructor
   *
   * initializes with zeros
   */
  Color();

  /* 3-Argument Constructor
   *
   * Takes RGB components separately.
   */
  Color(float r, float g, float b);


  /* Element accessors */
  float get_red() const;
  float get_green() const;
  float get_blue() const;

  /* Element mutators, return *this for chaining */
  Color & set_red(float red);
  Color & set_green(float green);
  Color & set_blue(float blue);

  /* Arithmetic & Compound Assignment Operators */
  Color & operator+=(const Color &rhs);
  Color & operator-=(const Color &rhs);
  Color & operator*=(const Color &rhs);
  const Color operator+(const Color &other) const;
  const Color operator-(const Color &other) const;
  const Color operator*(const Color &other) const;

  /* Scalar Mult/Div */
  Color & operator*=(const float &s);
  Color & operator/=(const float &s);

  /* Clamp this Color to [0,1] on all components */
  Color & clamp();
};


/* Non-member functions */

/* Print operator */
std::ostream & operator<<(std::ostream &os, const Color &v);

/* Scalar Mult/Div */
const Color operator*(const Color &v, const float &s);

const Color operator*(const float &s, const Color &v);

const Color operator/(const Color &v, const float &s);

//// Inline Definitions ////

/* Accessors */
inline float Color::get_red() const { return r; }
inline float Color::get_green() const { return g; }
inline float Color::get_blue() const { return b; }

#endif
