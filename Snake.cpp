#include "Snake.h"

Snake::Snake(unsigned int _color){
	this->color_node = _color;
	this->color_head = WHITE;
	this->direction = Direction::right;
	this->death = false;
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

void Snake::setDeath(bool _death){
	this->death = _death;
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

unsigned int Snake::getDeah() const{
	return this->death;
}

Vector2 Snake::getHeadPos() const{
	if (!this->list.size()) {
		return Vector2(0, 0);
	}
	return (*this->list.cbegin()).getPosition();
}

Vector2 Snake::getRandPos() const{
	Vector2 location = this->controllMap->getRandPos();
	
	//判断从GameMap类里面的取出的随机Chunk坐标是否为蛇身体的节点，
	//因为这个方法会来被用作食物之类的，所以要保证百分之百不能为蛇的身体
	while (this->checkPosIsNode(location)) {
		location = this->controllMap->getRandPos();
	}

	return location;
}


code_t Snake::checkPosIsNode(Vector2 _position) const{
	for (auto iter_chunk = this->list.begin(); iter_chunk != this->list.end(); iter_chunk++) {
		if ((*iter_chunk).getPosition() == _position) {
			return true;
		}
	}
	return false;
}


code_t Snake::checkNextMoveErro(Vector2 &outNextLocation){

	Vector2 headLocation = this->getHeadPos();
	Vector2 targetLocation;

	switch (this->getDirection())
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

	if (this->controllMap->checkOutSide(targetLocation))
		return MoveCode::error;

	if (this->checkPosIsNode(targetLocation))
		return MoveCode::owning;

	return MoveCode::normal;
}

code_t Snake::checkMapErro(){
	return !this->controllMap;
}

code_t Snake::checkHeadBump(){

	if (this->list.size() < 1) {
		return false;
	}

	for (unsigned int i = 1; i < this->list.size(); i++) {
		if (this->getHeadPos() == this->list[i].getPosition()) {
			return true;
		}
	}

	return false;
}

void Snake::updata(Vector2 nextPos) {

	size_t local_size = this->list.size();

	if (local_size <= 1) {
		this->setHeadPos(nextPos);
		return;
	}

	for (unsigned int next = local_size - 1; next > 0; next--) {

		auto pre = next - 1;
		this->list[next] = this->list[pre];

	}
	this->setHeadPos(nextPos);
}

void Snake::controllerMove(unsigned short _direction) {

	auto curDirection = this->getDirection();//在修改朝向之前先记录当前的朝向，用于处理反方向异常

	this->setDirection(_direction);

	Vector2 moveLocation;//下次移动的坐标会从输出到这个Vec2变量里面

	auto checkCode = this->checkNextMoveErro(moveLocation);

	if (checkCode == MoveCode::normal) {
		bool isFoodChunk = (this->controllMap->getFoodPos() == this->getHeadPos());
		if (isFoodChunk) {

			Chunk chunk(moveLocation, this->controllMap->getChunkSize(), RED);
			this->addChunk(chunk, false);
			this->controllMap->setFoodRenew(true);

			//如果食物在边界的那种，那么获取下次的坐标一定出界了，那么我要把下次坐标设置为头部坐标
			//不然的话无解死亡
			if (this->checkNextMoveErro(moveLocation) == MoveCode::error) {
				moveLocation = this->getHeadPos();
			}
		}

	}else if (checkCode == MoveCode::owning) {
		this->setDirection(curDirection);
		this->checkNextMoveErro(moveLocation);
	}
	//若蛇出界
	else if (checkCode == MoveCode::error) {
		this->setDeath(true);//设置死亡
		MessageBoxA(GetHWnd(), "OutSide!", "GameOver", MB_OK);
	}
	
	//更新节点数据
	this->updata(moveLocation);

	//若头部与身体有碰撞
	if (this->checkHeadBump()) {
		this->setDeath(true);//设置死亡
		MessageBoxA(GetHWnd(), "Bump!", "GameOver", MB_OK);
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
