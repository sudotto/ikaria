#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "otto-game.h"

Tile new_tile(Tile_type type, SDL_Renderer* rend){
	Tile tile;
	switch(type){
		case TILE_GRASS:
			tile.name = "Grass";
			tile.type = TILE_GRASS;
			tile.sprite = new_img(rend, "assets/tiles/grass.png");
			break;
		case TILE_STONE:
			tile.name = "Grass";
			tile.type = TILE_GRASS;
			tile.sprite = new_img(rend, "assets/tiles/grass.png");
			break;
		case TILE_SAND:
			tile.name = "Grass";
			tile.type = TILE_GRASS;
			tile.sprite = new_img(rend, "assets/tiles/grass.png");
			break;
		case TILE_WATER:
			tile.name = "Grass";
			tile.type = TILE_GRASS;
			tile.sprite = new_img(rend, "assets/tiles/grass.png");
			break;
	}
}
