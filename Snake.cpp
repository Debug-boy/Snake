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

	//每次蛇初始化在游戏的屏幕中间
	auto center = this->controllMap->getGameSize() / 2;
	Vector2 centerLocation(center, center);
	Chunk headChunk(centerLocation, this->controllMap->getChunkSize(), RED, GREEN);
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

Vector2 Snake::getRandPos(){
	Vector2 location = this->controllMap->getRandPos();
	
	//判断从GameMap类里面的取出的随机Chunk坐标是否为蛇身体的节点，
	//因为这个方法会来被用作食物之类的，所以要保证百分之百不能为蛇的身体
	while (this->checkPosIsNode(location)) {
		location = this->controllMap->getRandPos();
	}

	return location;
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

void Snake::updata(Vector2 nextPos) {

	size_t local_size = this->list.size();

	if (local_size <= 1) {
		this->setHeadPos(nextPos);
		return;
	}

	//这个方法执行之后，后一个节点数据就等于了前面的节点数据
	//那么在头部节点的后面一个节点也会==当前头部节点的数据
	//所以这个方法是要和move方法配套使用的
	//move方法会将头部节点更新到玩家控制的按钮方向节点
	//然后通过draw再将蛇渲染出来
	//0=头部 1=0,2=1,3=2,4=3,5=4,6=5
	for (unsigned int next = local_size - 1; next > 0; next--) {

		auto pre = next - 1;
		this->list[next] = this->list[pre];

	}
	this->setHeadPos(nextPos);
}

void Snake::controllerMove(unsigned short _direction) {

	this->setDirection(_direction);

	Vector2 moveLocation;//下次移动的坐标会从输出到这个Vec2变量里面

	if (this->checkNextMoveErro(moveLocation) == false) {

		bool isFoodChunk = (this->controllMap->getFoodPos() == this->getHeadPos());
		if (isFoodChunk) {

			Chunk chunk(moveLocation, this->controllMap->getChunkSize(), RED);
			this->addChunk(chunk, false);
			this->controllMap->setFoodRenew(true);

			//如果食物在边界的那种，那么获取下次的坐标一定出界了，那么我要把下次坐标设置为头部坐标
			if (this->checkNextMoveErro(moveLocation)) {
				moveLocation = this->getHeadPos();
			}
		}
		this->updata(moveLocation);
	}

}

void Snake::autoMove(){
	this->controllerMove(this->direction);
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

void Snake::swap(Chunk& a, Chunk& b){
	Chunk temp = a;
	a = b;
	b = temp;
}

void Snake::draw(){

	if (this->checkMapErro()) {
		return;
	}

	for (auto iter_chunk = this->list.cbegin(); iter_chunk != this->list.cend(); iter_chunk++) {
		
		auto &chunk = (*iter_chunk);
		this->controllMap->setChunkColor(chunk.getPosition(), chunk.getSideColor(), chunk.getFillColor());

	}

}
