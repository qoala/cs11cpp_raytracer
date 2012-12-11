/*! \file
 * \brief A templated N-Dim vector implementation.
 */

#ifndef _VECTOR_HH__
#define _VECTOR_HH__

#include <cassert>
#include <cmath>
#include <iostream>
#include <initializer_list>

//! A N-Dim vector implementation, templated on content type & # of dimensions.
/*!
 * \tparam E    Type of contained Elements.
 *              E should implement:
 *               - Construction around 0 and -1
 *               - arithmetic operations with itself
 *               - E sqrt(E) for magnitude
 * \tparam DIM  Number of elements in the vector.
 */
template <typename E, unsigned int DIM>
class Vector
{
  //! Fixed-size array of contents
  E data[DIM];

  public:

  // === Constructors

  //! Default constructor (Initializes with zeros)
  Vector();

  //! Initializer list constructor
  Vector(std::initializer_list<E> init);


  //! Subscript Operator (const)
  E operator[](unsigned int i) const;
  //! Subscript Operator (LHS compatible)
  E & operator[](unsigned int i);

  /* Arithmetic & Compound Assignment Operators */

  //! Compound assignment with addition
  Vector<E, DIM> & operator+=(const Vector<E, DIM> &rhs);
  //! Compound assignment with subtraction
  Vector<E, DIM> & operator-=(const Vector<E, DIM> &rhs);
  //! Binary addition operator
  const Vector<E, DIM> operator+(const Vector<E, DIM> &other) const;
  //! Binary subtraction operator
  const Vector<E, DIM> operator-(const Vector<E, DIM> &other) const;

  //! Compound assignment with scalar multiplication
  Vector<E, DIM> & operator*=(const E &s);
  //! Compound assignment with scalar division
  Vector<E, DIM> & operator/=(const E &s);

  //! Unary minus operator
  const Vector<E, DIM> operator-();

  /* Norm & Norm^2 */

  //! Norm (magnitude) of a vector
  const E norm() const;
  //! Norm (magnitude) squared of a vector
  const E norm_sq() const;

  //! Normalize this vector.
  Vector<E, DIM> & normalize();

  //! Produce a normalized copy of this Vector.
  Vector<E, DIM> get_normalized() const;

};


// === Non-member functions

/*! \relates Vector
 * \brief Stream-output operator
 */
template <typename E, unsigned int DIM>
std::ostream & operator<<(std::ostream &os, const Vector<E, DIM> &v);

/*! \relates Vector
 * \brief Stream-input operator
 */
template <typename E, unsigned int DIM>
std::istream & operator>>(std::istream &is, Vector<E, DIM> &v);

/* Scalar Mult/Div */

/*! \relates Vector
 * \brief Scalar multiplication binary operator
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM> operator*(const Vector<E, DIM> &v, const E &s);

/*! \relates Vector
 * \brief Scalar multiplication binary operator
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM> operator*(const E &s, const Vector<E, DIM> &v);

/*! \relates Vector
 * \brief Scalar division binary operator
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM> operator/(const Vector<E, DIM> &v, const E &s);


/*! \relates Vector
 *\brief Dot Product
 */
template <typename E, unsigned int DIM>
const E dot(const Vector<E, DIM> &v1, const Vector<E, DIM> &v2);

/*! \relates Vector
 * \brief Cross Product (DIM==3 only)
 */
template <typename E>
const Vector<E, 3> cross(const Vector<E, 3> &v1, const Vector<E, 3> &v2);


// === Function Definitions

// Default Constructor
/*!
 * Initializes all values by constructing E around 0.
 */
template <typename E, unsigned int DIM>
Vector<E, DIM>::Vector()
{
  for (unsigned int i = 0; i < DIM; ++i)
    data[i] = E(0);
}

// Initializer List Constructor
/*!
 * Uses C++11 initializer list syntax to specify elements on construction.
 * (Used as N-argument constructor wouldn't otherwise work)
 *
 * Allows such lines as: Vector3D v = {1, 1, 1};
 *
 * Asserts that provided initializer list is of size DIM.
 *
 * \param init  A curly braced list of DIM elements of type E.
 */
template <typename E, unsigned int DIM>
Vector<E, DIM>::Vector(std::initializer_list<E> init)
{
  assert(init.size() == DIM);

  // Iterator over initializer_list
  typename std::initializer_list<E>::iterator it = init.begin();

  for (unsigned int i = 0; i < DIM; ++i, ++it)
    data[i] = *it;
}

// Subscript Operator (const)
/*!
 * Bounds are checked via assertions!
 *
 * \param i Index into the vector.
 */
template <typename E, unsigned int DIM>
inline E Vector<E, DIM>::operator[](unsigned int i) const
{
  assert(i < DIM);
  return data[i];
}
// Subscript Operator (LHS compatible)
/*!
 * Bounds are checked via assertions!
 *
 * \param i Index into the vector.
 */
template <typename E, unsigned int DIM>
inline E& Vector<E, DIM>::operator[](unsigned int i)
{
  assert(i < DIM);
  return data[i];
}

// Stream-output Operator
/*! \relates Vector
 * Writes contents of vector to stream,
 * bracketed by parentheses and with elements separated by spaces.
 *
 * For example, the default Vector will (depending on E) be written as
 * `"( 0 0 0 )"`
 *
 * \param os  ostream to which to write output.
 * \param v   Vector to write to stream output.
 */
template <typename E, unsigned int DIM>
std::ostream & operator<<(std::ostream &os, const Vector<E, DIM> &v)
{
  os << "( ";
  for (unsigned int i = 0; i < DIM; ++i)
    os << v[i] << ' ';

  os << ')';

  return os;
}

// Stream-input operator
/*! \relates Vector
 * Reads contents of vector from a stream,
 * bracketed by parentheses and with elements separated by spaces.
 *
 * For example, the default Vector can (depending on E) be read as
 * `"( 0 0 0 )"`
 *
 * \param      is  istream from which to read output.
 * \param[out] v   Vector to read from stream.
 */
template <typename E, unsigned int DIM>
std::istream & operator>>(std::istream &is, Vector<E, DIM> &v)
{
  // Holding area for read values
  E d[DIM];
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
  for (unsigned i = 0; i < DIM; i++)
    is >> d[i];
  
  // Read trailing ')'
  is >> ch;
  if (ch != ')') is.clear(std::ios_base::failbit);

  if (is)
  {
    // Copy read data into Vector
    for (unsigned i = 0; i < DIM; i++)
      v[i] = d[i];
  }

  return is;
}

/* Arithmetic & Compound Assignment Operators */

/*!
 * \param rhs Other vector to add
 * \returns   This vector, after adding rhs
 */
template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::operator+=(const Vector<E, DIM> &rhs)
{
  for (unsigned int i = 0; i < DIM; ++i)
    this->data[i] += rhs.data[i];

  return *this;
}

/*!
 * \param rhs Other vector to subtract
 * \returns   This vector, after subtracting rhs
 */
template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::operator-=(const Vector<E, DIM> &rhs)
{
  for (unsigned int i = 0; i < DIM; ++i)
    this->data[i] -= rhs.data[i];

  return *this;
}

/*!
 * \param other Other vector to add
 * \returns     New vector, after adding rhs
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM>
    Vector<E, DIM>::operator+(const Vector<E, DIM> &other) const
{
  Vector<E, DIM> result = *this;
  return result += other;
}

/*!
 * \param other Other vector to subtract
 * \returns     New vector, after subtracting rhs
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM>
    Vector<E, DIM>::operator-(const Vector<E, DIM> &other) const
{
  Vector<E, DIM> result = *this;
  return result -= other;
}

/* Scalar Mult/Div */

/*!
 * \param s Scalar to multiply by
 * \returns This vector after multiplying by s
 */
template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::operator*=(const E &s)
{
  for (unsigned int i = 0; i < DIM; ++i)
    this->data[i] *= s;

  return *this;
}

/*!
 * \param s Scalar to divide by
 * \returns This vector after dividing by s
 */
template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::operator/=(const E &s)
{
  assert(s != 0);

  for (unsigned int i = 0; i < DIM; ++i)
    this->data[i] /= s;

  return *this;
}

/*! \relates Vector
 * \param v Vector to multiply
 * \param s Scalar to multiply by
 * \returns New vector, v * s
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM> operator*(const Vector<E, DIM> &v, const E &s)
{
  Vector<E, DIM> result = v;
  return result *= s;
}

/*! \relates Vector
 * \param v Vector to multiply
 * \param s Scalar to multiply by
 * \returns New vector, v * s
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM> operator*(const E &s, const Vector<E, DIM> &v)
{
  Vector<E, DIM> result = v;
  return result *= s;
}

/*! \relates Vector
 * \param v Vector to divide
 * \param s Scalar to divide by
 * \returns New vector, v / s
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM> operator/(const Vector<E, DIM> &v, const E &s)
{
  Vector<E, DIM> result = v;
  return result /= s;
}

// Unary Minus
/*!
 * \returns This vector, after multiplying by -1.
 */
template <typename E, unsigned int DIM>
const Vector<E, DIM> Vector<E, DIM>::operator-()
{
  return *this * E(-1);
}

/* Norm & Norm^2 */

/*!
 * \returns the Euclidean norm of the vector
 */
template <typename E, unsigned int DIM>
const E Vector<E, DIM>::norm() const
{
  return std::sqrt(dot(*this, *this));
}

/*!
 * Saves an operation over the norm by skipping the square root.
 *
 * \returns the square of the Euclidean norm of the vector.
 */
template <typename E, unsigned int DIM>
const E Vector<E, DIM>::norm_sq() const
{
  return dot(*this, *this);
}

// Normalize Vector
/*!
 * Modifies this vector to have a norm of 1.
 * \returns This vector (for chaining)
 */
template <typename E, unsigned int DIM>
Vector<E, DIM> & Vector<E, DIM>::normalize()
{
  // Calculate norm
  E n = this->norm();

  // Check for 0-length
  if (n > 0)
  {
    return *this /=this->norm();
  }
  else
  {
    // Leave vector as-is
    return *this;
  }
}

// Return a normalized copy of this Vector
/*!
 * \returns A copy of this vector which has been normalized
 *          to have a norm of 1.
 */
template <typename E, unsigned int DIM>
Vector<E, DIM> Vector<E, DIM>::get_normalized() const
{
  Vector<E, DIM> result = *this;
  return result.normalize();
}

// Dot Product
/*! \relates Vector
 * \param v1  A vector
 * \param v2  Another vector
 * \returns   The dot product of the two vectors
 */
template <typename E, unsigned int DIM>
const E dot(const Vector<E, DIM> &v1, const Vector<E, DIM> &v2)
{
  E result = E(0);

  for(unsigned int i = 0; i < DIM; ++i)
    result += (v1[i] * v2[i]);
  return result;
}

// Cross Product
/*! \relates Vector
 * \param v1  A vector
 * \param v2  Another vector
 * \returns   The cross product of the two vectors
 */
template <typename E>
const Vector<E, 3> cross(const Vector<E, 3> &v1, const Vector<E, 3> &v2)
{
    Vector<E, 3> result;

    result[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    result[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    result[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    return result;
}


//// Typedefs of common vector types ////

//! A 3D vector of doubles
typedef Vector<double, 3> Vector3D;

//! A 3D vector of floats
typedef Vector<float, 3> Vector3F;

#endif
