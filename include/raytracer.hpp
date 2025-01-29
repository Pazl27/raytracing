#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <vector>
#include <SDL2/SDL.h>

#include <ray.hpp>
#include <circle.hpp>

class Raytracer {
public:
  Raytracer() = default;
  
  void generate_rays(Circle circle);
  void fill_rays(SDL_Surface *screen, Uint32 color, Circle object);


private:
  std::vector<Ray> rays;
};

#endif
