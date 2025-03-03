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
    app.win = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 200, SDL_WINDOW_SHOWN );

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

    SDL_StartTextInput();
}

void redraw()
{
    /* Fill the window with a white rectangle */
    SDL_FillRect( app.win_surface, NULL, SDL_MapRGB( app.win_surface->format, 0x90, 0x00, 0x00 ) );

    /* Update the window display */
    SDL_UpdateWindowSurface( app.win );
}

int main(int argc, char *argv[])
{
    memset(&app, 0, sizeof(app));

    init();
    atexit(cleanup);

    prepare();

    SDL_bool done = SDL_FALSE;

    SDL_Event event;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = SDL_TRUE;
                break;

            case SDL_TEXTINPUT:
              /* Add new text onto the end of our text */
              /* strcat(text, event.text.text); */
              fprintf(stdout, "TEXTINPUT: [%s]\n", event.text.text);
              break;

            case SDL_TEXTEDITING:
              /*
                Update the composition text.
                Update the cursor position.
                Update the selection length (if any).
              */
              /* composition = event.edit.text; */
              /* cursor = event.edit.start; */
              /* selection_len = event.edit.length; */
              fprintf(stdout, "\tTEXTEDITING: [%s] start:%d sel:%d\n", event.edit.text, event.edit.start, event.edit.length);
              break;

            case SDL_KEYDOWN:
              switch (event.key.keysym.scancode) {
              case SDL_SCANCODE_ESCAPE:
                done = SDL_TRUE;
                break;

              default:
                break;
              }
              
              break;
            }

            redraw();
        }
    }

    exit(EXIT_SUCCESS);
}
