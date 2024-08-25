#include "raycaster.h"
/**
 * main - main function 
 * @argc: number of command line arguments
 * @argv: array vector of commmand line arguments
 *
 * Return: 0 successful
 */
int main(int argc, char *args[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Ray Casting");
	SDL_Event e;
	bool quit = false;

	Raycaster raycaster;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W]) raycaster.movePlayer(0.1, 0);
		if (state[SDL_SCANCODE_S]) raycaster.movePlayer(-0.1, 0);
		if (state[SDL_SCANCODE_A]) raycaster.rotatePlayer(-0.1);
		if (state[SDL_SCANCODE_D]) raycaster.rotatePlayer(0.1);

		raycaster.draw(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
