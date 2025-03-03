#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <SDL.h>

typedef struct {
  SDL_Window* win;
  SDL_Surface* win_surface;
} App;

App app;

void cleanup()
{
  if (app.win_surface) {
    SDL_DestroyWindowSurface(app.win);
    app.win_surface = NULL;
  }

  if (app.win) {
    SDL_DestroyWindow(app.win);
    app.win = NULL;
  }

  SDL_Quit();
}

void init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void prepare()
{
  /* Create our window */
  app.win = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );

  /* Make sure creating the window succeeded */
  if (!app.win) {
    fprintf(stderr, "Error creating window: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /* Get the surface from the window */
  app.win_surface = SDL_GetWindowSurface( app.win );

  /* Make sure getting the surface succeeded */
  if ( !app.win_surface ) {
    fprintf(stderr, "Error getting surface: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void redraw()
{
  /* Fill the window with a white rectangle */
  SDL_FillRect( app.win_surface, NULL, SDL_MapRGB( app.win_surface->format, 255, 255, 255 ) );

  /* Update the window display */
  SDL_UpdateWindowSurface( app.win );
}

int main(int argc, char *argv[])
{
  memset(&app, 0, sizeof(app));

  init();
  atexit(cleanup);

  prepare();

  while(1) {
    redraw();
    SDL_Delay(10);
  }

  exit(EXIT_SUCCESS);
}
