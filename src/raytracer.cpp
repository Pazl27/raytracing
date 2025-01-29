#include <vector>
#include <SDL2/SDL.h>

#include <circle.hpp>
#include <raytracer.hpp>
#include <constants.hpp>

void Raytracer::generate_rays(Circle circle) {
  rays.clear();

  for (int i = 0; i < RAY_COUNT; i++) {
    double angle = (static_cast<double>(i) / RAY_COUNT) * 2 * M_PI;
    struct Ray ray = {circle.get_x(), circle.get_y(), angle};
    rays.push_back(ray);
  }
}

void Raytracer::fill_rays(SDL_Surface *screen, Uint32 color, Circle object) {

  double radius_squared = pow(object.get_radius(), 2);
  for (int i = 0; i < rays.size(); i++) {
    struct Ray ray = rays[i];
    bool end_of_screen = false;
    bool object_hit = false;

    double step = 1;
    double x_draw = ray.get_x_start();
    double y_draw = ray.get_y_start();
    while (!end_of_screen && !object_hit) {
      x_draw += step * cos(ray.get_angle());
      y_draw += step * sin(ray.get_angle());

      SDL_Rect pixel = {static_cast<int>(x_draw), static_cast<int>(y_draw), 2,
                        2};
      SDL_FillRect(screen, &pixel, color);

      if (x_draw < 0 || x_draw > WIDTH || y_draw < 0 || y_draw > HEIGHT) {
        end_of_screen = true;
      }
      double distance_squared =
          pow(x_draw - object.get_x(), 2) + pow(y_draw - object.get_y(), 2);
      if (distance_squared < radius_squared) {
        break;
        object_hit = true;
      }
    }
  }
}
