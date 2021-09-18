#include "Snake.h"

Snake::Snake(unsigned int _color){
	this->color_node = _color;
	this->color_head = WHITE;
	this->direction = Direction::right;
}

void Snake::setControlMap(GameMap* gameMap){
	this->controllMap = gameMap;
}

void Snake::setBeginPos(){
	if (this->checkMapErro()) {
		return;
	}

	Vector2 randlocation = this->controllMap->getRandPos();
	Chunk headChunk(randlocation, this->controllMap->getChunkSize(), RED, GREEN);
	this->addChunk(headChunk);

}

void Snake::set(unsigned int _color, unsigned int _direction){
	this->color_node = _color;
	this->direction = _direction;
}

void Snake::setColor(unsigned int _color) {
	this->color_node = _color;
}

void Snake::setDirection(unsigned int _direction){
	this->direction = _direction;
}

void Snake::setHeadPos(Vector2 _position){
	this->getHeadChunk().setPosition(_position);
}

void Snake::setHeadColor(unsigned int _color) {
	this->color_head = _color;
}

Chunk &Snake::getHeadChunk(){
	return (*this->list.begin());
}

unsigned int Snake::getColor() const{
	return this->color_node;
}

unsigned int Snake::getDirection() const {
	return this->direction;
}

Vector2 Snake::getHeadPos() const{
	if (!this->list .size()) {
		return Vector2(0, 0);
	}
	return (*this->list.cbegin()).getPosition();
}


bool Snake::checkPosIsNode(Vector2 _position){
	for (auto iter_chunk = this->list.begin(); iter_chunk != this->list.end(); iter_chunk++) {
		if ((*iter_chunk).getPosition() == _position) {
			return true;
		}
	}
	return false;
}


bool Snake::checkNextMoveErro(Vector2 &outNextLocation){

	Vector2 headLocation = this->getHeadPos();
	Vector2 targetLocation;
	switch (this->direction)
	{
	case Direction::up:
		targetLocation.set(headLocation.x, headLocation.y - 1);
		break;

	case Direction::down:
		targetLocation.set(headLocation.x, headLocation.y + 1);
		break;

	case Direction::left:
		targetLocation.set(headLocation.x - 1, headLocation.y);
		break;

	case Direction::right:
		targetLocation.set(headLocation.x + 1, headLocation.y);
		break;

	default:
		break;
	}
	outNextLocation = targetLocation;
	return
		this->controllMap->checkOutSide(targetLocation) &&
		this->checkPosIsNode(targetLocation);
}

bool Snake::checkMapErro(){
	return !this->controllMap;
}

void Snake::updata() {

	size_t local_size = this->list.size();

	if (local_size <= 1) {
		return;
	}

	//这个方法执行之后，后一个节点数据就等于了前面的节点数据
	//那么在头部节点的后面一个节点也会==当前头部节点的数据
	//所以这个方法是要和move方法配套使用的
	//move方法会将头部节点更新到玩家控制的按钮方向节点
	//然后通过draw再将蛇渲染出来
	//0=头部 1=头部,2=1,3=2,4=3,5=4,6=5
	for (unsigned int i = 1; i < local_size; i++) {
		this->list[i].setPosition(
			this->list[i - 1].getPosition()
		);
	}
}

void Snake::controllerMove() {

	if (_kbhit()) {

		char input_key = _getch();
		switch (input_key)
		{
		case 'W':
		case 'w':
			this->setDirection(Direction::up);
			break;

		case 'S':
		case 's':
			this->setDirection(Direction::down);
			break;


		case 'A':
		case 'a':
			this->setDirection(Direction::left);
			break;

		case 'D':
		case 'd':
			this->setDirection(Direction::right);
			break;

		default:
			break;
		}
	}

	Vector2 moveLocation;
	if (this->checkNextMoveErro(moveLocation) == false) {
		this->updata();
		this->getHeadChunk().setPosition(moveLocation);
	}


}

void Snake::addChunk(Chunk _chunk, bool isLast){
	//在后面插入
	if (isLast) {
		this->list.push_back(_chunk);
	}
	//在头部插入
	else {
		this->list.insert(list.begin(), _chunk);
	}
}

void Snake::render(){

	if (this->checkMapErro()) {
		return;
	}

	for (auto iter_chunk = this->list.cbegin(); iter_chunk != this->list.cend(); iter_chunk++) {
		
		auto &chunk = (*iter_chunk);
		this->controllMap->setChunkColor(chunk.getPosition(), chunk.getSideColor(), chunk.getFillColor());

	}

}
