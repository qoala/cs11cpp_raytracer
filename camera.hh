/* camera.hh
 *
 * A Camera implementation that renders a Scene by ray tracing
 */

#include "ray.hh"

class Camera
{
  // Position of camera
  Vector3F position;
  // Direction of facing (normalized)
  Vector3F direction;
  // Horizontal field of view (in degrees)
  float fov;
  // Up vector of render (normalized)
  Vector3F up;
  // Right vector of render (normalized)
  Vector3F right;
  // Distance of view box (computed internally)
  float distance;

  public:
  // === Constructors & methods

  // Constructor takes position, "look-at" target position, "up" vector,
  // and (optionally) horizontal field of view in degrees (default 60).
  Camera(const Vector3F &position, const Vector3F &target, const Vector3F &up,
         float fov = 60);

  // Generate a ray for a given pixel 0 <= (x,y) < img_size
  Ray get_ray_for_pixel(int x, int y, int img_size) const;
};