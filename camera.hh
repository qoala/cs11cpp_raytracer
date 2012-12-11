/* camera.hh
 *
 * A Camera implementation that renders a Scene by ray tracing
 */

#include "ray.hh"

//! Camera for generating Rays to trace a Scene
class Camera
{
  //! Position of camera
  Vector3F position;
  //! Direction of facing (normalized)
  Vector3F direction;
  //! Horizontal field of view (in degrees)
  float fov;
  //! Up vector of render (normalized)
  Vector3F up;
  //! Right vector of render (normalized)
  Vector3F right;
  //! Distance of view box (computed internally)
  float distance;

  public:
  // === Constructors & methods

  //! Default Constructor creates an invalid Camera
  Camera();

  //! Constructor takes position, "look-at" target position, & "up" vector
  Camera(const Vector3F &position, const Vector3F &target, const Vector3F &up,
         float fov = 60);

  //! Check if Camera is valid
  bool valid();

  //! Generate a ray for a given pixel
  Ray get_ray_for_pixel(int x, int y, int img_size) const;
};

/*! \relates Camera
 * \brief Function to read a Camera from an input stream
 */
Camera read_Camera(std::istream &is);
