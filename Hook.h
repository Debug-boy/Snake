#pragma once
#include <easyx.h>

namespace Hook {
	void fillcolor_begin(COLORREF setColor);
	void fillcolor_end();

	void linecolor_begin(COLORREF setColor);
	void linecolor_end();

	void textcolor_begin(COLORREF setColor);
	void textcolor_end();
}