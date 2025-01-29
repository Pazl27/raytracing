#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <SDL2/SDL.h>
#include <vector>

#include <circle.hpp>
#include <ray.hpp>

class Raytracer {
public:
  static void generate_rays(Circle circle);
  static void fill_rays(SDL_Surface *screen, Uint32 color, Circle object);

private:
  static std::vector<Ray> rays;
};

#endif
