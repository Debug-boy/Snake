#include "GameMap.h"
#include "Hook.h"

GameMap::GameMap(unsigned int _color,unsigned int _sideColor, unsigned int _size,unsigned int _chunk_size) {
	this->backgroundColor = _color;
	this->sideColor = _sideColor;
	this->size = _size;
	this->chunk_size = _chunk_size;
	this->food = nullptr;
	this->renewfood = false;
	this->setFoodPos(this->getRandPos());
}

GameMap::~GameMap() {
	delete this->food;
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
			Chunk chunk(Vector2(x, y), this->chunk_size, this->backgroundColor, this->sideColor);
			chunk.draw();
		}
	}

}

void GameMap::draw_food(){
	if (this->checkFoodErro() == false) {
		this->setChunkColor(this->food->getPosition(), this->food->getSideColor(), CYAN);
	}
}

unsigned int GameMap::getSize(){
	return this->size;
}

unsigned int GameMap::getGameSize(){
	return this->size / this->chunk_size;
}

Vector2 GameMap::getRandPos(){
	srand((unsigned int)time(NULL));
	auto c_max = this->getGameSize();
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

void GameMap::setFoodPos(Vector2 _position){
	if (!this->food) {
		this->food = new Chunk(_position, this->chunk_size,CYAN,this->sideColor);
	}
	if (this->renewfood) {
		this->food->setPosition(_position);
		this->setFoodRenew(false);//当食物的坐标刷新后，就立即把刷新状态改为假=不刷新
	}
}

void GameMap::setFoodRenew(bool is){
	this->renewfood = is;
}


Vector2 GameMap::getFoodPos() {
	if (this->food) {
		return this->food->getPosition();
	}
	return Vector2(-1, -1);
}

bool GameMap::getFoodRenew(){
	return this->renewfood;
}

bool GameMap::checkFoodErro(){
	return !this->food;
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
	return (this->food->getPosition() == location);
}

unsigned int GameMap::getChunkSize(){
	return this->chunk_size;
}

