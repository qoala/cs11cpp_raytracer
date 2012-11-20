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
Color & Color::set_red(float red) { r = red; return *this; }
Color & Color::set_green(float green) { g = green; return *this; }
Color & Color::set_blue(float blue) { b = blue; return *this; }

/* Arithmetic & Compound Assignment Operators */
Color & Color::operator+=(const Color &rhs)
{
  r += rhs.r;
  g += rhs.g;
  b += rhs.b;
  
  return *this;
}

Color & Color::operator-=(const Color &rhs)
{
  r -= rhs.r;
  g -= rhs.g;
  b -= rhs.b;
  
  return *this;
}

Color & Color::operator*=(const Color &rhs)
{
  r *= rhs.r;
  g *= rhs.g;
  b *= rhs.b;
  
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
  return result -= other;
}

const Color Color::operator*(const Color &other) const
{
  Color result = *this;
  return result *= other;
}

/* Scalar Mult/Div */
Color & Color::operator*=(const float &s)
{
  r *= s;
  g *= s;
  b *= s;
  
  return *this;
}

Color & Color::operator/=(const float &s)
{
  r /= s;
  g /= s;
  b /= s;
  
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

Color & Color::clamp()
{
  r = (r < 0) ? 0 : ((r > 1) ? 1 : r);
  g = (g < 0) ? 0 : ((g > 1) ? 1 : g);
  b = (b < 0) ? 0 : ((b > 1) ? 1 : b);

  return *this;
}

/* Print operator */
std::ostream & operator<<(std::ostream &os, const Color &v)
{
  os << "( " << v.get_red() << ' ';
  os << v.get_green() << ' ' << v.get_blue() << " )";

  return os;
}


