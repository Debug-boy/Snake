#include "Snake.h"
using namespace std;

int main(int argc, char* argv[]) {

	initgraph(800, 800);
	GameMap gameMap(WHITE, GREEN, 800, 40);
	Snake snake(RED);
	snake.setControlMap(&gameMap);
	snake.setBeginPos();

	while (true) {
		gameMap.draw();
		gameMap.setFoodPos(snake.getRandPos());
		snake.controllerMove();
		snake.render();
		SleepEx(500, false);
	}

	

	int ret = getchar();
	return 0;
}