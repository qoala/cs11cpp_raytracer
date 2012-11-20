/* color.cc
 *
 * An RGB float color representation
 */

#include "color.hh"

/* Default constructor */
Color::Color()
  : r(0), g(0), b(0)
{ }

  /* 3-Argument Constructor */
Color::Color(float r, float g, float b)
  : r(r), g(g), b(b)
{ }

/* Element mutators */
void Color::set_red(float red) { r = red; }
void Color::set_blue(float blue) { b = blue; }
void Color::set_green(float green) { g = green; }

/* Arithmetic & Compound Assignment Operators */
Color & Color::operator+=(const Color &rhs)
{
  r += rhs.r;
  b += rhs.b;
  g += rhs.g;
  
  return *this;
}

Color & Color::operator-=(const Color &rhs)
{
  r -= rhs.r;
  b -= rhs.b;
  g -= rhs.g;
  
  return *this;
}

Color & Color::operator*=(const Color &rhs)
{
  r *= rhs.r;
  b *= rhs.b;
  g *= rhs.g;
  
  return *this;
}

const Color Color::operator+(const Color &other) const
{
  Color result = *this;
  return result += other;
}

const Color Color::operator-(const Color &other) const
{
  Color result = *this;
  return result += other;
}

const Color Color::operator*(const Color &other) const
{
  Color result = *this;
  return result += other;
}

/* Scalar Mult/Div */
Color & Color::operator*=(const float &s)
{
  r *= s;
  b *= s;
  g *= s;
  
  return *this;
}

Color & Color::operator/=(const float &s)
{
  r /= s;
  b /= s;
  g /= s;
  
  return *this;
}

const Color operator*(const Color &v, const float &s)
{
  Color result = v;
  return result *= s;
}

const Color operator*(const float &s, const Color &v)
{
  Color result = v;
  return result *= s;
}

const Color operator/(const Color &v, const float &s)
{
  Color result = v;
  return result /= s;
}

/* Print operator */
std::ostream & operator<<(std::ostream &os, const Color &v)
{
  os << "( " << v.get_red() << ' ';
  os << v.get_green() << ' ' << v.get_blue() << " )";

  return os;
}


