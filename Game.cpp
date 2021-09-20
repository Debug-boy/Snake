#include "Game.h"

#define GAME_SIZE 800
#define CHUNK_SIZE 20

std::mutex mu;

void minorkeyboard(void*);
GameMap gameMap(WHITE, DARKGRAY, GAME_SIZE, CHUNK_SIZE);
Snake snake(RED);

unsigned char gameSatet = State::unknow;

void Game::init() {
	initgraph(GAME_SIZE, GAME_SIZE);
	snake.setControlMap(&gameMap);
	snake.setBeginPos();
}

void Game::begin(){

	gameSatet = State::begin;

	Game::minorKeyboard();
	BeginBatchDraw();

	while (true) {

		if (gameMap.getFoodRenew()) {
			gameMap.setFoodPos(snake.getRandPos());
			gameMap.setFoodColor(gameMap.getRandColor());
		}
		gameMap.draw();
		snake.draw();

		FlushBatchDraw();

		if (gameSatet == State::end) {
			break;
		}

	}
}

void Game::end(){
	gameSatet = State::end;
	MessageBoxA(GetHWnd(), "exit!", "Game Happy!", MB_OK);
	closegraph();
}

void Game::minorKeyboard(){
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)minorkeyboard, nullptr, 0, nullptr);
}

void minorkeyboard(void*){

	while (true) {

		if (GetAsyncKeyState(VK_UP)) {
			snake.controllerMove(Direction::up);

		}else if (GetAsyncKeyState(VK_DOWN)) {
			snake.controllerMove(Direction::down);

		}else if (GetAsyncKeyState(VK_LEFT)) {
			snake.controllerMove(Direction::left);

		}else if (GetAsyncKeyState(VK_RIGHT)) {
			snake.controllerMove(Direction::right);

		}
		else {
			snake.autoMove();
		}

		if (snake.getDeath()){
			break;
		}

		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}

		SleepEx(100, false);
	}

	gameSatet = State::end;
	return;
}
