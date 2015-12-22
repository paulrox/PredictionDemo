/*
 * main.c
 *
 *  Created on: 10/dic/2015
 *      Author: paolo
 */

#include "taskslib.h"
#include "graphics.h"
#include "tasks.h"

#include "globals.h"

int main()
{
	init();

	drawGUI();

	create_task(display_task, DISPLAY_PER, DISPLAY_DL, DISPLAY_PRIO,
			DISPLAY_INDEX);
	create_task(mouse_task, MOUSE_PER, MOUSE_DL, MOUSE_PRIO, MOUSE_INDEX);
	create_task(keyboard_task, KEYBOARD_PER, KEYBOARD_DL, KEYBOARD_PRIO,
			KEYBOARD_INDEX);

	while(!end);

	endProgram();

	return 0;
}

