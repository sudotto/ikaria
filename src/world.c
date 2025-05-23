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
	tile.type = type;
	tile.data = tile_data_table[type];
	if(tile.data.animated){
		tile.anim = new_anim(game->rend, tile.data.filename, 4, 0, 160, 160, true);
	} else {
		tile.sprite = new_img(game->rend, tile.data.filename, true);
	}
	return tile;
}

void render_tile(Game* game, Tile* tile, int x, int y){
	x *= 16*4;
	y *= 16*4;
	int size = 16*4;
	if(tile->data.animated){
		render_anim(game->rend, &tile->anim, x, y, size, size, 0.1);
	} else {
		render_img(game->rend, &tile->sprite, x, y, size, size);
	}
}

// WORLD
void generate_blob(Game* game, World* world, Tile_type type, int size, int start_x, int start_y){
	Tile tile = new_tile(game, type);
	int scatter = 1;
	int x = start_x;
	int y = start_y;
	for(int i = 0; i < size; i++){
		set_world_tile(world, x, y, tile);
		set_world_tile(world, x-scatter, y, tile);
		set_world_tile(world, x+scatter, y, tile);
		set_world_tile(world, x, y-scatter, tile);
		set_world_tile(world, x, y+scatter, tile);
		int direction = gen_rand(0,4);
		switch(direction){
			case 0:
				y -= scatter;
				break;
			case 1:
				x += scatter;
				break;
			case 2:
				y += scatter;
				break;
			case 3:
				x -= scatter;
				break;
		}
		if(x < 0 || y < 0 || x > WORLD_SIZE - 1 || y > WORLD_SIZE - 1){
			x = start_x;
			y = start_y;
		}
	}
}

World new_world(Game* game, char* name){
	World world;
	world.name = name;
	Tile default_tile = new_tile(game, TILE_WATER); 
	for(int y = 0; y < WORLD_SIZE; y++){
		for(int x = 0; x < WORLD_SIZE; x++){
			world.tiles[y][x] = default_tile;
		}
	}
	int land_count = 1 * WORLD_SIZE;
	int land_size = 1 * WORLD_SIZE;
	for(int i = 0; i < land_count; i++){
		generate_blob(game, &world, TILE_GRASS, land_size, gen_rand(0, WORLD_SIZE), gen_rand(0, WORLD_SIZE));
	}
	Tile sand = new_tile(game, TILE_SAND);
	for(int y = 0; y < WORLD_SIZE; y++){
		for(int x = 0; x < WORLD_SIZE; x++){
			if(world.tiles[y][x].type == TILE_WATER){
				if( world.tiles[y - 1][x].type == TILE_GRASS ||
					world.tiles[y][x + 1].type == TILE_GRASS ||
					world.tiles[y + 1][x].type == TILE_GRASS ||
					world.tiles[y][x - 1].type == TILE_GRASS){
					world.tiles[y][x] = sand;
				}
			}
		}
	}
	return world;
}

void set_world_tile(World* world, int x, int y, Tile tile){
	if(x > 0 && y > 0 && x < WORLD_SIZE && y < WORLD_SIZE){
		world->tiles[y][x] = tile;
	}
}

void render_world(Game* game, World* world){
	for(int y = 0; y < WORLD_SIZE; y++){
		for(int x = 0; x < WORLD_SIZE; x++){
			render_tile(game, &world->tiles[y][x], x, y);
		}
	}
}
