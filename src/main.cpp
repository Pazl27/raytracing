#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <math.h>
#include <vector>

#define WIDTH 1200
#define HEIGHT 600
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x00000000
#define COLOR_RAY 0xf5c31d
#define RAY_THICKNESS 2
#define RAY_COUNT 500

struct Circle {
  double x, y, radius;
  double speed;
};

struct Ray {
  double x_start, y_start;
  double angle;
};

void fill_circle(SDL_Surface *screen, struct Circle circle, Uint32 color) {
  double radius_squared = pow(circle.radius, 2);
  for (double x = circle.x - circle.radius; x <= circle.x + circle.radius;
       x++) {
    for (double y = circle.y - circle.radius; y <= circle.y + circle.radius;
         y++) {
      double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
      if (distance_squared < radius_squared) {
        SDL_Rect pixel =
            (SDL_Rect){static_cast<int>(x), static_cast<int>(y), RAY_THICKNESS, RAY_THICKNESS};
        SDL_FillRect(screen, &pixel, color);
      }
    }
  }
}

void generate_rays(struct Circle circle, std::vector<Ray> &rays) {
  rays.clear();

  for (int i = 0; i < RAY_COUNT; i++) {
    double angle = (static_cast<double>(i) / RAY_COUNT) * 2 * M_PI;
    struct Ray ray = {circle.x, circle.y, angle};
    rays.push_back(ray);
  }
}

void fill_rays(SDL_Surface *screen, std::vector<Ray> &rays, Uint32 color,
               struct Circle object) {

  double radius_squared = pow(object.radius, 2);
  for (int i = 0; i < rays.size(); i++) {
    struct Ray ray = rays[i];
    bool end_of_screen = false;
    bool object_hit = false;

    double step = 1;
    double x_draw = ray.x_start;
    double y_draw = ray.y_start;
    while (!end_of_screen && !object_hit) {
      x_draw += step * cos(ray.angle);
      y_draw += step * sin(ray.angle);

      SDL_Rect pixel = {static_cast<int>(x_draw), static_cast<int>(y_draw), 2,
                        2};
      SDL_FillRect(screen, &pixel, color);

      if (x_draw < 0 || x_draw > WIDTH || y_draw < 0 || y_draw > HEIGHT) {
        end_of_screen = true;
      }
      double distance_squared =
          pow(x_draw - object.x, 2) + pow(y_draw - object.y, 2);
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
        circle.x = event.motion.x;
        circle.y = event.motion.y;
        generate_rays(circle, rays);
      }
    }

    SDL_FillRect(screen, &eraser, COLOR_BLACK);
    fill_rays(screen, rays, COLOR_RAY, shadow_circle);
    fill_circle(screen, circle, COLOR_WHITE);
    fill_circle(screen, shadow_circle, COLOR_WHITE);

    shadow_circle.y += speed;
    if (shadow_circle.y + shadow_circle.radius > HEIGHT ||
        shadow_circle.y - shadow_circle.radius < 0) {
      speed *= -1;
    }

    SDL_UpdateWindowSurface(window);

    SDL_Delay(10);
  }
}
