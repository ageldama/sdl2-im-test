#include <stdio.h>
#include <SDL.h>

typedef struct {
  SDL_Window* window;
} App;


int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  // Create our window
  SDL_Window* window;
  window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );

  // Make sure creating the window succeeded
  if ( !window ) {
    /* TODO cout << "Error creating window: " << SDL_GetError()  << endl; */
    return 1;
  }

  // Get the surface from the window
  SDL_Surface* win_surface;
  win_surface = SDL_GetWindowSurface( window );

  // Make sure getting the surface succeeded
  if ( !win_surface ) {
    /* TODO cout << "Error getting surface: " << SDL_GetError() << endl; */
    // End the program
    return 1;
  }

  // Fill the window with a white rectangle
  SDL_FillRect( win_surface, NULL, SDL_MapRGB( win_surface->format, 255, 255, 255 ) );

  // Update the window display
  SDL_UpdateWindowSurface( window );

  // Destroy the window. This will also destroy the surface
  SDL_DestroyWindow( window );
	
  SDL_Quit();

  return 0;
}
