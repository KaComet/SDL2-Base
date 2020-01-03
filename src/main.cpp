// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "resource.h"
#include "LTexture.h"
#include "ltimer.h"
#include <SDL.h>
#include <vector>
#include <fstream>
#include <SDL_image.h>

// Screen constants
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// The window we'll be rendering to
SDL_Window *gWindow = nullptr;

// The window renderer
SDL_Renderer *gRenderer = nullptr;

bool init();

void close();

int main(int argc, char *args[]) {
    printf("--SDL2 Base--\n");

    // Start SDL and create window
    if (!init()) {
        printf("!Failed to initialize SDL! Closing...\n");
    } else {
        bool allResourcesLoaded = true;

        // If all resources were not loaded, exit the application.
        if (!allResourcesLoaded) {
            printf("!Failed to load required resources! Closing...\n");
        } else {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event eventH;

            SDL_Rect screenRect;
            screenRect.h = SCREEN_HEIGHT;
            screenRect.w = SCREEN_WIDTH;
            screenRect.x = 0;
            screenRect.y = 0;

            // Setup the viewport for the map's renderer.
            SDL_Rect mapViewRect;
            mapViewRect.x = 0;
            mapViewRect.y = 0;
            mapViewRect.w = SCREEN_WIDTH;
            mapViewRect.h = SCREEN_HEIGHT;
            SDL_RenderSetViewport(gRenderer, &mapViewRect);

            // Create a timer to regulate the FPS. Without this, the application
            //   will render as fast as possible. This would waste system resources.
            LTimer fpsReg;

            //While application is running
            while (!quit) {
                fpsReg.start();

                // If there are events in the que, try to process them,
                while (SDL_PollEvent(&eventH) != 0) {
                    // If the user wants to quit the app, signal to exit.
                    if (eventH.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                // Update screen with the contents of the renderer.
                SDL_RenderPresent(gRenderer);

                // Wait out the rest of the frame.
                int elapsedTicks = fpsReg.getTicks();
                if (elapsedTicks < SCREEN_TICKS_PER_FRAME)
                    SDL_Delay((Uint32) (SCREEN_TICKS_PER_FRAME - elapsedTicks));
            }
        }
    }

    // If the user has chosen to exit, free resources and close SDL.
    close();

    return 0;
}

// Initializes SDL2, creates a window, and creates a renderer.
// Call before using any SDL2 resources.
bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("!SDL could not initialize! SDL Error: %s\n !", SDL_GetError());
        success = false;
    } else {
        //Try to set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
            printf("!Linear texture filtering could not be enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("SDL2 Base", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            printf("!Window could not be created. SDL Error: %s\n !", SDL_GetError());
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr) {
                printf("!Renderer could not be created. SDL Error: %s\n !", SDL_GetError());
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("!SDL_image could not initialize. SDL_image Error: %s\n !", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

// Closes any SDL2/SDL2_Image resources. Call before exiting the application.
void close() {
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
