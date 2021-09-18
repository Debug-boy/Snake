#include "GameMap.h"
#include "Hook.h"

GameMap::GameMap(unsigned int _color,unsigned int _sideColor, unsigned int _size,unsigned int _chunk_size) {
	this->backgroundColor = _color;
	this->sideColor = _sideColor;
	this->size = _size;
	this->chunk_size = _chunk_size;
}

void GameMap::draw_side(){
	int width = this->position.x + this->size;
	int height = this->position.y + this->size;
	Hook::linecolor_begin(this->sideColor);
	rectangle(position.x, position.y, width, height);
	Hook::linecolor_end();
}

void GameMap::draw_background(){

	for (auto x = 0U; x < this->size; x += this->chunk_size) {
		for (auto y = 0U; y < this->size; y += this->chunk_size) {
			Chunk chunk(Vector2(x, y), this->chunk_size, BLACK, GREEN);
			chunk.draw();
		}
	}

}

unsigned int GameMap::getSize(){
	return this->size;
}

Vector2 GameMap::getRandPos(){
	srand((unsigned int)time(NULL));
	auto c_max = this->size / this->chunk_size;
	auto x = rand() % c_max;
	auto y = rand() % c_max;
	return Vector2(x, y);
}

void GameMap::setChunkColor(Vector2 target_pos, COLORREF color_side, COLORREF color_fill) {
	auto x = target_pos.x * this->chunk_size;
	auto y = target_pos.y * this->chunk_size;

	if (x >= 0 && x < this->size) {

		if (y >= 0 && y < this->size) {

			Chunk chunk(Vector2(x, y), this->chunk_size, color_fill, color_side);
			chunk.draw();
		}
	}

}

void GameMap::setFoodChunk(COLORREF foodColor){
	this->food.setFillColor(foodColor);
}

bool GameMap::checkOutSide(Vector2 checkLocation){
	auto check_x = checkLocation.x * this->chunk_size;
	auto check_y = checkLocation.y * this->chunk_size;
	if (check_x >= 0 && check_x < this->size) {
		if (check_y >= 0 && check_y < this->size) {
			return false;
		}
	}
	MessageBoxA(GetHWnd(), "OutSide!", "GameOver", MB_OK);
	exit(1);
	return true;
}

bool GameMap::isFoodChunk(Vector2 location){
	return (this->food.getPosition() == location);
}

unsigned int GameMap::getChunkSize(){
	return this->chunk_size;
}

