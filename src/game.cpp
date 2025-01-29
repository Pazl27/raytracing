#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <circle.hpp>
#include <constants.hpp>
#include <game.hpp>
#include <ray.hpp>
#include <raytracer.hpp>
#include <vector>

void Game::run() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window =
      SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  if (!window) {
    SDL_Quit();
    return;
  }

  SDL_Surface *screen = SDL_GetWindowSurface(window);
  SDL_Rect eraser = {0, 0, WIDTH, HEIGHT};

  Raytracer raytracer;
  Circle circle = {200, 200, 80};
  Circle shadow_circle = {550, 300, 120};

  std::vector<Ray> rays;
  raytracer.generate_rays(circle);

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_q) {
          running = false;
        }
      }
      if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
        circle.set_x(event.motion.x);
        circle.set_y(event.motion.y);
        raytracer.generate_rays(circle);
      }
    }

    shadow_circle.move();

    SDL_FillRect(screen, &eraser, COLOR_BLACK);
    raytracer.fill_rays(screen, COLOR_RAY, shadow_circle);
    circle.fill(screen, COLOR_WHITE);
    shadow_circle.fill(screen, COLOR_WHITE);

    SDL_UpdateWindowSurface(window);

    SDL_Delay(10);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
