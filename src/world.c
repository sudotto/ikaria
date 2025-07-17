#include "stdlib.h"

#include "world.h"

// TILE DATA TABLE

Tile_data tile_data_table[TILE_TYPE_COUNT] = {
	{"Water", "assets/tiles/water.png"},
	{"Sand",  "assets/tiles/sand.png"},
	{"Grass", "assets/tiles/grass.png"},
	{"Snow",  "assets/tiles/snow.png"}
};

// TILE STRUCTURE

Tile new_tile(Game* game, Tile_type type){
	Tile tile;
	tile.type = type;
	tile.data = tile_data_table[type];
	tile.sprite = new_img(game->rend, tile.data.spritename, true);
	return tile;
}

// WORLD STRUCTURE

World new_world(Game* game, char* name, int size){
	World world;
	world.name = name;
	world.size = size;
	world.tiles = malloc(sizeof(Tile) * (size * size));
	for(int y = 0; y < size; y++){
		for(int x = 0; x < size; x++){
			world.tiles[y + world.size + x] = new_tile(game, TILE_WATER);
		}
	}
	return world;
}

void render_world(Game* game, World* world){
	for(int y = 0; y < world->size; y++){
		for(int x = 0; x < world->size; x++){
			render_img(game->rend, &world->tiles[y + world->size + x].sprite, x * 40, y * 40, 40, 40);
		}
	}
}
