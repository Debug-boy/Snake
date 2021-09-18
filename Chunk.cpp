#include "Chunk.h"

Chunk::Chunk(Vector2 _position, unsigned int _size, unsigned int _color_full,unsigned int _color_side) {
	this->size = _size;
	this->color_side = _color_side;
	this->color_fill = _color_full;
	this->position = _position;
}

void Chunk::set(unsigned int _size, unsigned int _color_fill, unsigned int _color_side, Vector2 _position) {
	this->size = _size;
	this->color_fill = _color_fill;
	this->color_side = _color_side;
	this->position = _position;
}

void Chunk::setSize(unsigned int _size) {
	this->size = _size;
}

void Chunk::setFillColor(unsigned int _color_fill) {
	this->color_fill = _color_fill;
}

void Chunk::setSideColor(unsigned int _color_side) {
	this->color_side = _color_side;
}

void Chunk::setPosition(Vector2 _position) {
	this->position = _position;
}

unsigned int Chunk::getSize() const {
	return this->size;
}

unsigned int Chunk::getSideColor() const {
	return this->color_side;
}

unsigned int Chunk::getFillColor() const {
	return this->color_fill;
}

Vector2 Chunk::getPosition() const {
	return this->position;
}

void Chunk::draw() const{
	int width = this->position.x + this->size;
	int height = this->position.y + this->size;
	Hook::linecolor_begin(this->color_side);
	Hook::fillcolor_begin(this->color_fill);
	fillrectangle(this->position.x, this->position.y, width, height);
	Hook::fillcolor_end();
	Hook::linecolor_end();
}
