#ifndef WORLD
#define WORLD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "otto-game.h"

#define WORLD_SIZE 32
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
	Tile_type type;
	Img sprite;
	Anim anim;
} Tile;

Tile new_tile(Game* game, Tile_type type);
void render_tile(Game* game, Tile* tile, int x, int y);

// WORLD

typedef struct {
	char* name;
	Tile tiles[WORLD_SIZE][WORLD_SIZE];
} World;

World new_world(Game* game, char* name);
void set_world_tile(World* world, int x, int y, Tile tile);
void render_world(Game* game, World* world);

#endif
