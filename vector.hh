/* vector.hh
 *
 * A N-Dim vector implementation, templated on content type and # of dimensions
 * Element type E should implement:
 * - Construction around 0 and -1
 * - arithmetic operations with itself
 * - sqrt(E) for magnitude
 *
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <initializer_list>

template <typename E, unsigned int DIM>
class Vector
{
  /* Fixed-size array of contents */
  E data[3];

  public:

  /* Constructors */

  /* Default constructor initializes with zeros */
  Vector();

  /* Initializer List Constructor
   * (Used as N-argument constructor wouldn't otherwise work)
   *
   * Allows such lines as: Vector3D v = {1, 1, 1};
   */
  Vector(std::initializer_list<E> init);


  /* Subscript Operators (const & non-const)
   *
   * Bounds are checked via assertions!
   */
  E operator[](unsigned int i) const { assert(i < DIM); return data[i]; }
  E & operator[](unsigned int i) { assert(i < DIM); return data[i]; }

  /* Arithmetic & Compound Assignment Operators */
  Vector<E, DIM> & operator+=(const Vector<E, DIM> &rhs);
  Vector<E, DIM> & operator-=(const Vector<E, DIM> &rhs);
  const Vector<E, DIM> operator+(const Vector<E, DIM> &other) const;
  const Vector<E, DIM> operator-(const Vector<E, DIM> &other) const;

  /* Scalar Mult/Div */
  Vector<E, DIM> & operator*=(const E &s);
  Vector<E, DIM> & operator/=(const E &s);

  /* Unary Minus */
  const Vector<E, DIM> operator-();

  /* Norm & Norm^2 */
  const E norm() const;
  const E norm_sq() const;

  /* Normalize Vector */
  const Vector<E, DIM> normalize() const;

};


/* Non-member functions */

/* Print operator */
template <typename E, unsigned int DIM>
std::ostream & operator<<(std::ostream &os, const Vector<E, DIM> &v);

/* Scalar Mult/Div */
template <typename E, unsigned int DIM>
const Vector<E, DIM> operator*(const Vector<E, DIM> &v, const E &s);

template <typename E, unsigned int DIM>
const Vector<E, DIM> operator*(const E &s, const Vector<E, DIM> &v);

template <typename E, unsigned int DIM>
const Vector<E, DIM> operator/(const Vector<E, DIM> &v, const E &s);


/* Dot Product */
template <typename E, unsigned int DIM>
const E dot(const Vector<E, DIM> &v1, const Vector<E, DIM> &v2);

/* Cross Product
 *
 * Only defined for DIM=3
 */
template <typename E>
const Vector<E, 3> cross(const Vector<E, 3> &v1, const Vector<E, 3> &v2);


//// Function Definitions ////

/* Default Constructor */
template <typename E, unsigned int DIM>
Vector<E, DIM>::Vector()
{
  for (unsigned int i = 0; i < DIM; ++i)
    data[i] = E(0);
}

/* Initializer List Constructor */
template <typename E, unsigned int DIM>
Vector<E, DIM>::Vector(std::initializer_list<E> init)
{
  assert(init.size() == DIM);

  // Iterator over initializer_list
  typename std::initializer_list<E>::iterator it = init.begin();

  for (unsigned int i = 0; i < DIM; ++i, ++it)
    data[i] = *it;
}

template <typename E, unsigned int DIM>
std::ostream & operator<<(std::ostream &os, const Vector<E, DIM> &v)
{
  os << "( ";
  for (unsigned int i = 0; i < DIM; ++i)
    os << v[i] << ' ';

  os << ')';

  return os;
}

/* Arithmetic & Compound Assignment Operators */
template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::operator+=(const Vector<E, DIM> &rhs)
{
  for (unsigned int i = 0; i < DIM; ++i)
    this->data[i] += rhs.data[i];

  return *this;
}

template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::operator-=(const Vector<E, DIM> &rhs)
{
  for (unsigned int i = 0; i < DIM; ++i)
    this->data[i] -= rhs.data[i];

  return *this;
}

template <typename E, unsigned int DIM>
const Vector<E, DIM>
    Vector<E, DIM>::operator+(const Vector<E, DIM> &other) const
{
  Vector<E, DIM> result = *this;
  return result += other;
}

template <typename E, unsigned int DIM>
const Vector<E, DIM>
    Vector<E, DIM>::operator-(const Vector<E, DIM> &other) const
{
  Vector<E, DIM> result = *this;
  return result -= other;
}

/* Scalar Mult/Div */
template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::operator*=(const E &s)
{
  for (unsigned int i = 0; i < DIM; ++i)
    this->data[i] *= s;

  return *this;
}

template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::operator/=(const E &s)
{
  assert(s != 0);

  for (unsigned int i = 0; i < DIM; ++i)
    this->data[i] /= s;

  return *this;
}

template <typename E, unsigned int DIM>
const Vector<E, DIM> operator*(const Vector<E, DIM> &v, const E &s)
{
  Vector<E, DIM> result = v;
  return result *= s;
}

template <typename E, unsigned int DIM>
const Vector<E, DIM> operator*(const E &s, const Vector<E, DIM> &v)
{
  Vector<E, DIM> result = v;
  return result *= s;
}

template <typename E, unsigned int DIM>
const Vector<E, DIM> operator/(const Vector<E, DIM> &v, const E &s)
{
  Vector<E, DIM> result = v;
  return result /= s;
}

/* Unary Minus */
template <typename E, unsigned int DIM>
const Vector<E, DIM> Vector<E, DIM>::operator-()
{
  return *this * E(-1);
}
/* Norm & Norm^2 */
template <typename E, unsigned int DIM>
const E Vector<E, DIM>::norm() const
{
  return std::sqrt(dot(*this, *this));
}

template <typename E, unsigned int DIM>
const E Vector<E, DIM>::norm_sq() const
{
  return dot(*this, *this);
}

/* Normalize Vector */
template <typename E, unsigned int DIM>
const Vector<E, DIM> Vector<E, DIM>::normalize() const
{
  return *this / this->norm();
}

/* Dot Product */
template <typename E, unsigned int DIM>
const E dot(const Vector<E, DIM> &v1, const Vector<E, DIM> &v2)
{
  E result = E(0);

  for(unsigned int i = 0; i < DIM; ++i)
    result += (v1[i] * v2[i]);
  return result;
}

/* Cross Product */
template <typename E>
const Vector<E, 3> cross(const Vector<E, 3> &v1, const Vector<E, 3> &v2)
{
    Vector<E, 3> result;

    result[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    result[1] = (v1[0] * v2[2]) - (v1[2] * v2[0]);
    result[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    return result;
}


//// Typedefs of common vector types ////

/* Vector3D: A 3D vector of doubles */
typedef Vector<double, 3> Vector3D;

/* Vector3F: A 3D vector of floats */
typedef Vector<float, 3> Vector3F;
