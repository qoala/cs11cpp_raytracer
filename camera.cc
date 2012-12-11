/* camera.cc
 *
 * A Camera implementation that renders a Scene by ray tracing
 */

#include "camera.hh"

// define math constants such as M_PI
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159)
#endif

// Default Constructor creates an invalid Camera
/*!
 * Initializes everything to zero vectors or zeros.
 * (Allows returning an invalid Camera)
 */
Camera::Camera()
  : position()
  , direction()
  , fov(0)
  , up()
  , right()
  , distance(0)
{ }

// Constructor takes position, "look-at" target position, "up" vector,
// and (optionally) horizontal field of view in degrees (default 60).
/*!
 * \param position  Position of the camera's origin
 * \param target    Position at which the camera is pointed
 * \param in_up     Up vector for vies
 * \param fov       Horizontal field of view in degrees (optional, default: 60)
 */
Camera::Camera(const Vector3F &position, const Vector3F &target,
               const Vector3F &in_up, float fov)
  : position(position)
  , direction(target - position)
  , fov(fov)
{
  // Normalize direction vector
  direction.normalize();

  // Compute right vector
  right = cross(direction, in_up);
  right.normalize();

  // Compute up vector
  up = cross(right, direction);
  up.normalize();

  // Compute distance
  distance = 0.5 / tanf((fov * float(M_PI) / 180) / 2);
}

// Check if Camera is valid
/*!
 * Checks 
 * \returns true if Camera is properly set up for rendering
 */
bool Camera::valid()
{
  // Due to the vector math, if any input (using direction instead of lookat)
  // was zero, then "up" will be zero
  return ((up.norm() != 0)
          // Additionally check that the render distance is non-zero
          && (distance != 0));
}

// Generate a ray for a given pixel 0 <= (x,y) < img_size
/*!
 * \param x, y      Pixel coordinates, 0 <= (x,y) < img_size
 * \param img_size  Pixel dimensions of image (only square images supported)
 */
Ray Camera::get_ray_for_pixel(int x, int y, int img_size) const
{
  Vector3F pixel_dir = distance * direction
                       + (0.5f - float(y) / (img_size - 1)) * up
                       + (float(x) / (img_size - 1) - 0.5f) * right;

  return Ray(position, pixel_dir);
}

/*! \relates Camera
 * Reads a Camera from the provided input stream in the format:
 * "position lookat up"
 *
 * With the read formats for Vectors, this looks like:
 * "(px py pz) (lx ly lz) (ux uy uz)"
 *
 * \param is  Input stream from which to read a new Plane
 * \returns   a Camera, (invalid if reading failed)
 */
Camera read_Camera(std::istream &is)
{
  // Check if stream is already bad
  if (!is) return Camera();

  Vector3F p;
  Vector3F l;
  Vector3F u;

  // Read components
  is >> p;
  is >> l;
  is >> u;

  if (is)
    return Camera(p, l, u);
  else
    return Camera();
}
