#pragma once
#include <iostream>
#include <vector>
#include <easyx.h>
#include "Chunk.h"

class GameMap {
private:
	unsigned int backgroundColor;
	unsigned int sideColor;
	unsigned int size;//size * size
	unsigned int chunk_size;
	Vector2 position;
	Chunk* food;
	bool renewfood;

public:
	GameMap(unsigned int _backgroundColor = BLACK,unsigned int _sideColor = 0, unsigned int _size = 0,unsigned int _chunk_size = 20);
	~GameMap();


public:
	void draw_side();
	void draw_background();
	void draw_food();

	unsigned int getSize();
	unsigned int getChunkSize();
	Vector2 getRandPos();

	void setChunkColor(Vector2 target_pos, COLORREF _color_side, COLORREF _color_fill);

	void setFoodPos(Vector2 _position);
	void setFoodRenew(bool is);

	Vector2 getFoodPos();

	bool checkFoodErro();
	bool checkOutSide(Vector2 checkLocation);
	bool isFoodChunk(Vector2 location);

	void draw() {
		this->draw_side();
		this->draw_background();
		this->draw_food();
	}

};