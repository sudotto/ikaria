#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

Tile new_tile(SDL_Renderer* rend, Tile_type type){
	Tile tile;
	tile.data = tile_data_table[type];
	if(tile.data.animated){
		tile.anim = new_anim(rend, tile.data.filename, 4, 0, 180, 180);
	} else {
		tile.sprite = new_img(rend, tile.data.filename);
	}
	return tile;
}

void render_tile(SDL_Renderer* rend, Tile* tile, int x, int y){
	x *= 15*4;
	y *= 15*4;
	int size = 18 * 4;
	if(tile->data.animated){
		render_anim(rend, &tile->anim, x, y, size, size, 0.1);
	} else {
		render_img(rend, &tile->sprite, x, y, size, size);
	}
}

// WORLD

World new_world(SDL_Renderer* rend, char* name){
	World world;
	world.name = name;
	for(int y = 0; y < 16; y++){
		for(int x = 0; x < 16; x++){
			world.tiles[y][x] = new_tile(rend, gen_rand(0, 4));
		}
	}
	return world;
}

void render_world(SDL_Renderer* rend, World* world){
	for(int y = 0; y < 16; y++){
		for(int x = 0; x < 16; x++){
			if(x + 64 > 0 &&
				y + 64 > 0 &&
				x < 900 / 64 &&
				y < 600 / 64
			){
				render_tile(rend, &world->tiles[y][x], x, y);
			}
		}
	}
}
