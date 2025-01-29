#ifndef RAY_HPP
#define RAY_HPP

class Ray {
public:
  Ray(double x, double y, double angle);

  double get_x_start() const { return x_start; }
  double get_y_start() const { return y_start; }
  double get_angle() const { return angle; }

private:
  double x_start;
  double y_start;
  double angle;
};

#endif
