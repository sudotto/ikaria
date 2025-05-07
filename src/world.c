#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "otto-game.h"
#include "world.h"

// TILE TYPES

Tile_data tile_data_table[TILE_TYPE_COUNT] = {
	{"Water", "assets/tiles/water.png", true},
	{"Sand",  "assets/tiles/sand.png",  false},
	{"Grass", "assets/tiles/grass.png", false},
	{"Stone", "assets/tiles/stone.png", false},
	{"Snow",  "assets/tiles/snow.png",  false},
};

// TILES

Tile new_tile(Game* game, Tile_type type){
	Tile tile;
	tile.data = tile_data_table[type];
	if(tile.data.animated){
		tile.anim = new_anim(game->rend, tile.data.filename, 4, 0, 180, 180);
	} else {
		tile.sprite = new_img(game->rend, tile.data.filename);
	}
	return tile;
}

void render_tile(Game* game, Tile* tile, int x, int y){
	x *= 15*4;
	y *= 15*4;
	int size = 18 * 4;
	if(tile->data.animated){
		render_anim(game->rend, &tile->anim, x, y, size, size, 0.1, true);
	} else {
		render_img(game->rend, &tile->sprite, x, y, size, size, true);
	}
}

// WORLD

World new_world(Game* game, char* name){
	World world;
	world.name = name;
	float frequency1 = 1.0;
	float frequency2 = 2.0;
	float frequency3 = 4.0;
	float amplitude1 = 1.0;
	float amplitude2 = 0.5;
	float amplitude3 = 0.25;
	for(int y = 0; y < WORLD_SIZE; y++){
		for(int x = 0; x < WORLD_SIZE; x++){
			float value =
				sin(x * frequency1 * M_PI / 10 + y * frequency1 * M_PI / 10) * amplitude1 +
				sin(x * frequency2 * M_PI / 10 + y * frequency2 * M_PI / 10) * amplitude2 +
				sin(x * frequency3 * M_PI / 10 + y * frequency3 * M_PI / 10) * amplitude3;
			value = (value + 1.75f) * (4.0f / 3.5f);
			world.tiles[y][x] = new_tile(game, value);//gen_rand(0, 4));
		}
	}
	return world;
}

void render_world(Game* game, World* world){
	for(int y = 0; y < WORLD_SIZE; y++){
		for(int x = 0; x < WORLD_SIZE; x++){
			if( x + 16 > camera.x / 64 &&
				y + 16 > camera.y / 64 &&
				x - 16 < (900 + camera.x) / 64 &&
				y - 16 < (600 + camera.y) / 64
			){
				render_tile(game, &world->tiles[y][x], x, y);
			}
		}
	}
}
