#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "GameMap.h"

enum Direction { left = 1, right, up, down };

class Snake {
private:
	unsigned int color_node;
	unsigned int color_head;
	unsigned int direction;
	std::vector<Chunk>list;
	GameMap* controllMap = nullptr;

public:
	Snake(unsigned int _color = RED);
	
	void setControlMap(GameMap *gameMap);
	void setBeginPos();
	void set(unsigned int _color, unsigned int _direction);
	void setColor(unsigned int _color);
	void setDirection(unsigned int _direction);
	void setHeadPos(Vector2 _position);
	void setHeadColor(unsigned int _color);

	Chunk &getHeadChunk();
	unsigned int getColor() const;
	unsigned int getDirection() const;
	Vector2 getHeadPos() const;
	Vector2 getRandPos();

	bool checkPosIsNode(Vector2 _position);
	bool checkNextMoveErro(Vector2& outNextLocation);
	bool checkMapErro();
	
	void updata(Vector2 nextPos);

	void controllerMove(unsigned short _direction);
	void autoMove();
	void addChunk(Chunk _chunk, bool isLast = true);
	void swap(Chunk& a, Chunk& b);

public:
	void draw();


};