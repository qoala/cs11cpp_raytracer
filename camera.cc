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

// Constructor takes position, "look-at" target position, "up" vector,
// and (optionally) horizontal field of view in degrees (default 60).
Camera::Camera(const Vector3F &position, const Vector3F &target,
               const Vector3F &in_up, float fov)
  : position(position)
  , direction(target - direction)
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


// Generate a ray for a given pixel 0 <= (x,y) < img_size
Ray Camera::get_ray_for_pixel(int x, int y, int img_size) const
{
  Vector3F pixel_dir = distance * direction
                       + (0.5f - float(y) / (img_size - 1)) * up
                       + (float(x) / (img_size - 1) - 0.5f) * right;

  return Ray(position, pixel_dir);
}

