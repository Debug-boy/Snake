#pragma once
#include "Snake.h"
using namespace std;

enum State {
	unknow = 0,
	begin,
	end
};

namespace Game {

	void init();
	void begin();
	void end();
	void minorKeyboard();

}