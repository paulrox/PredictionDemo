/*
 * tasks.h
 *
 *  Created on: 11/dic/2015
 *      Author: paolo
 */

#ifndef TASKS_H_
#define TASKS_H_

#include "graphics.h"
#include "globals.h"

extern float32_t pos_f, v_f, a_f;
extern uint8_t end;

extern void init();
extern void endProgram();
extern void *display_task(void *arg);
extern void *mouse_task(void *arg);
extern void *keyboard_task(void *arg);

#endif /* TASKS_H_ */
