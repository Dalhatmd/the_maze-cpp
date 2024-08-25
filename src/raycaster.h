#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <vector>
#include <SDL2/SDL.h>
#include <cmath>

class Raycaster {
	public:
		Raycaster();
		void draw(SDL_Renderer *renderer);
		void movePlayer(double dx, double dy);
		void rotatePlayer(double angle);
	private:
		static const int SCREEN_WIDTH = 640;
		static const int SCREEN_HEIGHT = 480;
		static const int MAP_WIDTH = 10;
		static const int MAP_HEIGHT = 10;

		static constexpr double FOV = M_PI / 3;
		static constexpr double DEPTH = 16;

		int world_map[MAP_WIDTH][MAP_HEIGHT];
		/**
		 * struct Player - struct that holds fuctionality of a player
		 *
		 * @x: x coordinate of player
		 * @y: y coordinate of player
		 * @angle: angle player is facing
		 */
		struct Player
		{
			double x;
			double y;
			double angle;
		} player;

		void drawline(SDL_Renderer *renderer, int x, int h, int color);
};

#endif
