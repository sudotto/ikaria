#ifndef WORLD
#define WORLD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "otto-game.h"

typedef enum {
	TILE_GRASS;
	TILE_STONE;
	TILE_SAND;
	TILE_WATER;
} Tile_type;

typedef struct {
	char* name;
	bool animated;
	Img sprite;
	Anim anim;
} Tile_data;

Tile_data new_tile_data(char* name, char* filename, bool animated SDL_Renderer* rend);

typedef struct {
	Tile_data data;
	int x;
	int y;
} Tile;

Tile new_tile(Tile_type, int x, int y, SDL_Renderer* rend);

typedef struct {
	char* name;
	Tile tiles[64][64];
} World;

#endif
