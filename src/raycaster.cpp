#include "raycaster.h"
#include <iostream>

Raycaster::Raycaster() : player{1.5, 1.5, 0} {
	int initial_map[MAP_WIDTH][MAP_HEIGHT] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	std::copy(&initial_map[0][0], &initial_map[0][0] + MAP_WIDTH * MAP_HEIGHT, &world_map[0][0]);
	std::cout << "Raycaster initialized. Player position: (" << player.x << ", " << player.y << ")" << std::endl;
}
void Raycaster::drawline(SDL_Renderer *renderer, int x, int h, int color)
{
	int start = SCREEN_HEIGHT / 2 - h / 2;
	int end = start + h;
	SDL_SetRenderDrawColor(renderer, color, 0, 0, 255);
	SDL_RenderDrawLine(renderer, x, start, x, end);
}

void Raycaster::draw(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (int x = 0; x < SCREEN_WIDTH; x++) {
		double angle = player.angle - FOV / 2 + FOV * x / SCREEN_WIDTH;
		double distance = 0;
		double step = 0.1;
		double dx = cos(angle) * step;
		double dy = sin(angle) * step;
		double rayX = player.x;
		double rayY = player.y;

		while (distance < DEPTH)
		{
			rayX += dx;
			rayY += dy;
			distance += step;

			int mapX = static_cast<int>(rayX);
			int mapY = static_cast<int>(rayY);

			if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
			{
				distance = DEPTH;
				break;
			}
			if (world_map[mapY][mapX] == 1)
			{
				break;
			}
		}
		double correctedDistance = distance * cos(angle - player.angle);
		int h = static_cast<int>(SCREEN_HEIGHT / correctedDistance);
		int color = static_cast<int>(255 / (1 + distance * distance * 0.0001));
		drawline(renderer, x, h, color);
	}
	SDL_RenderPresent(renderer);
}

void Raycaster::movePlayer(double dx, double dy)
{
	double newX = player.x + dx * cos(player.angle) - dy * sin(player.angle);
	double newY = player.y + dx * sin(player.angle) + dy * cos(player.angle);

	if (newX > 0 && newX < MAP_WIDTH && newY > 0 && newY < MAP_HEIGHT)
	{
		if (world_map[static_cast<int>(newY)][static_cast<int>(newX)] == 0)
		{
			player.x = newX;
			player.y = newY;
			std::cout << "Player moved to (" << player.x << ", " << player.y << ")" << std::endl;
		}
	}
}

void Raycaster::rotatePlayer(double angle)
{
	player.angle += angle;
	std::cout << "Player rotated. New angle: " << player.angle << std::endl;
}
