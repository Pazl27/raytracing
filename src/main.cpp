#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <math.h>
#include <vector>

#include <constants.hpp>
#include <circle.hpp>
#include <ray.hpp>

void fill_circle(SDL_Surface *screen, Circle circle, Uint32 color) {
  double radius_squared = pow(circle.get_radius(), 2);
  for (double x = circle.get_x() - circle.get_radius(); x <= circle.get_x() + circle.get_radius();
       x++) {
    for (double y = circle.get_y() - circle.get_radius(); y <= circle.get_y() + circle.get_radius();
         y++) {
      double distance_squared = pow(x - circle.get_x(), 2) + pow(y - circle.get_y(), 2);
      if (distance_squared < radius_squared) {
        SDL_Rect pixel =
            (SDL_Rect){static_cast<int>(x), static_cast<int>(y), RAY_THICKNESS, 1};
        SDL_FillRect(screen, &pixel, color);
      }
    }
  }
}

void generate_rays(Circle circle, std::vector<Ray> &rays) {
  rays.clear();

  for (int i = 0; i < RAY_COUNT; i++) {
    double angle = (static_cast<double>(i) / RAY_COUNT) * 2 * M_PI;
    struct Ray ray = {circle.get_x(), circle.get_y(), angle};
    rays.push_back(ray);
  }
}

void fill_rays(SDL_Surface *screen, std::vector<Ray> &rays, Uint32 color, Circle object) {

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

int main() {

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window =
      SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Surface *screen = SDL_GetWindowSurface(window);

  SDL_Rect eraser = {0, 0, WIDTH, HEIGHT};

  struct Circle circle = {200, 200, 80};
  struct Circle shadow_circle = {550, 300, 120};

  std::vector<Ray> rays;
  generate_rays(circle, rays);

  bool running = true;
  SDL_Event event;
  double speed = 1;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_q:
          running = false;
          break;
        }
      }
      if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
        circle.set_x(event.motion.x);
        circle.set_y(event.motion.y);
        generate_rays(circle, rays);
      }
    }

    SDL_FillRect(screen, &eraser, COLOR_BLACK);
    fill_rays(screen, rays, COLOR_RAY, shadow_circle);
    fill_circle(screen, circle, COLOR_WHITE);
    fill_circle(screen, shadow_circle, COLOR_WHITE);

    shadow_circle.set_speed(shadow_circle.get_y() + speed);
    if (shadow_circle.get_y() + shadow_circle.get_radius() > HEIGHT ||
        shadow_circle.get_y() - shadow_circle.get_radius() < 0) {
      speed *= -1;
    }

    SDL_UpdateWindowSurface(window);

    SDL_Delay(10);
  }
}
