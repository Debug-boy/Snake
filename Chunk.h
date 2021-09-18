#pragma once
#include "Hook.h"

class Vector2 {
public:
	int x;
	int y;

public:
	Vector2(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}

	Vector2 operator +(Vector2 vec) const {
		Vector2 location;
		location.x = this->x + vec.x;
		location.y = this->y + vec.y;
		return location;
	}

	Vector2 operator -(Vector2 vec) const {
		Vector2 location;
		location.x = this->x - vec.x;
		location.y = this->y - vec.y;
		return location;
	}

	int operator *(Vector2 vec) const {
		Vector2 location;
		location.x = this->x * vec.x;
		location.y = this->y * vec.y;
		return location.x + location.y;
	}

	bool operator ==(Vector2 vec) const {
		return (this->x == vec.x && this->y == this->y);
	}

	void set(int _x, int _y) {
		this->x = _x;
		this->y = _y;
	}

};


class Chunk{

protected:
	unsigned int size;
	unsigned int color_fill;
	unsigned int color_side;
	Vector2 position;

public:
	Chunk(Vector2 _position, unsigned int _size = 0, unsigned int _color_fill = BLACK,unsigned int _color_side = GREEN);

	void set(unsigned int _size, unsigned int _color_fill, unsigned int _color_side, Vector2 _position);
	void setSize(unsigned int _size);
	void setFillColor(unsigned int _color);
	void setSideColor(unsigned int _color);
	void setPosition(Vector2 _position);

	unsigned int getSize() const;
	unsigned int getFillColor() const;
	unsigned int getSideColor() const;
	Vector2 getPosition() const;

	void draw() const;

};