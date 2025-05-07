#ifndef WORLD
#define WORLD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "otto-game.h"

#define TILE_TYPE_COUNT 5

// TILE TYPES

typedef enum {
	TILE_WATER,
	TILE_SAND,
	TILE_GRASS,
	TILE_STONE,
	TILE_SNOW
} Tile_type;

typedef struct {
	char* name;
	char* filename;
	bool animated;
} Tile_data;

extern Tile_data tile_data_table[TILE_TYPE_COUNT];

// TILES

typedef struct {
	Tile_data data;
	Img sprite;
	Anim anim;
} Tile;

Tile new_tile(SDL_Renderer* rend, Tile_type type);
void render_tile(SDL_Renderer* rend, Tile* tile, int x, int y);

// WORLD

typedef struct {
	char* name;
	Tile tiles[64][64];
} World;

World new_world(SDL_Renderer* rend, char* name);
void render_world(SDL_Renderer* rend, World* world);

#endif
