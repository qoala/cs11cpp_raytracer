/* color.cc
 *
 * An RGB float color representation
 */

#include "color.hh"

// Default constructor
Color::Color()
  : r(0), g(0), b(0)
{ }

// 3-Argument Constructor
/*!
 * Takes RGB components separately.
 */
Color::Color(float r, float g, float b)
  : r(r), g(g), b(b)
{ }

/* Element mutators */
/*!
 * \returns This color (for chaining)
 */
Color & Color::set_red(float red) { r = red; return *this; }
/*!
 * \returns This color (for chaining)
 */
Color & Color::set_green(float green) { g = green; return *this; }
/*!
 * \returns This color (for chaining)
 */
Color & Color::set_blue(float blue) { b = blue; return *this; }

/* Arithmetic & Compound Assignment Operators */

/*!
 * \param rhs Other color to add
 * \returns   This color, after adding rhs
 */
Color & Color::operator+=(const Color &rhs)
{
  r += rhs.r;
  g += rhs.g;
  b += rhs.b;
  
  return *this;
}

/*!
 * \param rhs Other color to subtract
 * \returns   This color, after subtracting rhs
 */
Color & Color::operator-=(const Color &rhs)
{
  r -= rhs.r;
  g -= rhs.g;
  b -= rhs.b;
  
  return *this;
}

/*!
 * \param rhs Other color to multiply by
 * \returns   This color, after multiplying by rhs
 */
Color & Color::operator*=(const Color &rhs)
{
  r *= rhs.r;
  g *= rhs.g;
  b *= rhs.b;
  
  return *this;
}

/*!
 * \param other Other color to add
 * \returns     New color, after adding other
 */
const Color Color::operator+(const Color &other) const
{
  Color result = *this;
  return result += other;
}

/*!
 * \param other Other color to subtract
 * \returns     New color, after subtracting other
 */
const Color Color::operator-(const Color &other) const
{
  Color result = *this;
  return result -= other;
}

/*!
 * \param other Other color to multiply by
 * \returns     New color, after multiplying by other
 */
const Color Color::operator*(const Color &other) const
{
  Color result = *this;
  return result *= other;
}

/* Scalar Mult/Div */

/*!
 * \param s Scalar value to multiply by
 * \returns This color, after multiplying by s
 */
Color & Color::operator*=(const float &s)
{
  r *= s;
  g *= s;
  b *= s;
  
  return *this;
}

/*!
 * \param s Scalar value to divide by
 * \returns This color, after dividing by s
 */
Color & Color::operator/=(const float &s)
{
  r /= s;
  g /= s;
  b /= s;
  
  return *this;
}

/*! \relates Color
 * \param c Color to multiply
 * \param s Scalar to multiply by
 * \returns New color, after multiplying by s
 */
const Color operator*(const Color &c, const float &s)
{
  Color result = c;
  return result *= s;
}

/*! \relates Color
 * \param c Color to multiply
 * \param s Scalar to multiply by
 * \returns New color, after multiplying by s
 */
const Color operator*(const float &s, const Color &c)
{
  Color result = c;
  return result *= s;
}

/*! \relates Color
 * \param c Color to multiply
 * \param s Scalar to divide by
 * \returns New color, after dividing by s
 */
const Color operator/(const Color &c, const float &s)
{
  Color result = c;
  return result /= s;
}

/*!
 * \returns This color (for chaining)
 */
Color & Color::clamp()
{
  r = (r < 0) ? 0 : ((r > 1) ? 1 : r);
  g = (g < 0) ? 0 : ((g > 1) ? 1 : g);
  b = (b < 0) ? 0 : ((b > 1) ? 1 : b);

  return *this;
}

// Print operator
/*! \relates Color
 * Writes contents of color to stream,
 * bracketed by parentheses and with components separated by spaces.
 *
 * For example, the default Color will be written as
 * `"( 0 0 0 )"`
 *
 * \param os  ostream to which to write output.
 * \param c   Color to write to stream output.
 */
std::ostream & operator<<(std::ostream &os, const Color &c)
{
  os << "( " << c.get_red() << ' ';
  os << c.get_green() << ' ' << c.get_blue() << " )";

  return os;
}

// Stream-input operator
/*! \relates Vector
 * Reads contents of color from a stream, "( r g b )"
 * bracketed by parentheses and with elements separated by spaces.
 *
 * For example, black can be read as
 * `"( 0 0 0 )"`
 *
 * \param      is  istream from which to read output.
 * \param[out] c   Color to read from stream.
 */
std::istream & operator>>(std::istream &is, Color &c)
{
  // Holding area for read values
  float r;
  float g;
  float b;
  // Char read from stream
  char ch;

  // Check that stream isn't already bad
  if (!is)  return is;

  // Read leading '('
  is >> ch;
  if (ch != '(')
  {
    is.clear(std::ios_base::failbit);
    return is;
  }

  // Read contents
  is >> r >> g >> b;

  // Read trailing ')'
  is >> ch;
  if (ch != ')') is.clear(std::ios_base::failbit);

  if (is) c = Color(r, g, b);

  return is;
}


