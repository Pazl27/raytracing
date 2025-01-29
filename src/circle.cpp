#include <circle.hpp>
#include <constants.hpp>

#include <SDL2/SDL.h>

Circle::Circle(double x, double y, double radius) : x(x), y(y), radius(radius), speed(1) {}

void Circle::fill(SDL_Surface *screen, Uint32 color) {
  double radius_squared = pow(this->get_radius(), 2);
  for (double x = this->get_x() - this->get_radius(); x <= this->get_x() + this->get_radius();
       x++) {
    for (double y = this->get_y() - this->get_radius(); y <= this->get_y() + this->get_radius();
         y++) {
      double distance_squared = pow(x - this->get_x(), 2) + pow(y - this->get_y(), 2);
      if (distance_squared < radius_squared) {
        SDL_Rect pixel =
            (SDL_Rect){static_cast<int>(x), static_cast<int>(y), RAY_THICKNESS, 1};
        SDL_FillRect(screen, &pixel, color);
      }
    }
  }
}
