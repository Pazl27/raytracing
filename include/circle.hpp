#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SDL2/SDL.h>

class Circle {
public:
  Circle(double x, double y, double radius);

  void fill(SDL_Surface *screen, Uint32 color);
  void move();

  double get_x() const { return x; }
  double get_y() const { return y; }
  double get_radius() const { return radius; }
  double get_speed() const { return speed; }
  void set_x(double x) { this->x = x;}
  void set_y(double y) { this->y = y;}
  void set_speed(double speed) { this->speed = speed;}


  private:
  double x;
  double y;
  double radius;
  double speed;
};

#endif
