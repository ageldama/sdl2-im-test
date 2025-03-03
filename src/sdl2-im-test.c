#include <stdio.h>
#include <SDL.h>


int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Quit();

  return 0;
}
