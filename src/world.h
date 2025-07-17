#ifndef WORLD
#define WORLD

#include "otto-game.h"

#define TILE_TYPE_COUNT 4

// TILE TYPE ENUM

typedef enum {
	TILE_WATER,
	TILE_SAND,
	TILE_GRASS,
	TILE_SNOW
} Tile_type;

// TILE DATA STRUCTURE

typedef struct {
	char* name;
	char* spritename;
} Tile_data;

// TILE DATA TABLE

extern Tile_data tile_data_table[TILE_TYPE_COUNT];

// TILE STRUCTURE

typedef struct {
	Tile_type type;
	Tile_data data;
	Img sprite;
} Tile;

Tile new_tile(Game* game, Tile_type type);

// WORLD STRUCTURE

typedef struct {
	char* name;
	Tile *tiles;
	int size;
} World;

World new_world(Game* game, char* name, int size);
void render_world(Game* game, World* world);

#endif
