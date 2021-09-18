#include "Hook.h"

COLORREF g_fillcolor;
COLORREF g_linecolor;
COLORREF g_textcolor;

void Hook::fillcolor_begin(COLORREF setColor){
	g_fillcolor = getfillcolor();
	setfillcolor(setColor);
}

void Hook::fillcolor_end() {
	setfillcolor(g_fillcolor);
}

void Hook::linecolor_begin(COLORREF setColor) {
	g_linecolor = getlinecolor();
	setlinecolor(setColor);
}

void Hook::linecolor_end() {
	setlinecolor(g_fillcolor);
}

void Hook::textcolor_begin(COLORREF setColor){
	g_textcolor = gettextcolor();
	settextcolor(setColor);
}

void Hook::textcolor_end(){
	settextcolor(g_textcolor);
}
