/*
 * tasks.c
 *
 *  Created on: 11/dic/2015
 *      Author: paolo
 */

#include "tasks.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <allegro.h>

#include "taskslib.h"
#include "globals.h"

float32_t	pos_f, v_f, a_f;
coords	real_c, noise_c, pred_c;
pred_stat ps;
uint8_t	end, show, trail;
pthread_mutex_t	coords_mutex, stat_mutex;

static void clearStats();

void init()
{
	initGraphics();							/* initializes the graphic module */

	pthread_mutex_init(&coords_mutex, NULL);
	pthread_mutex_init(&stat_mutex, NULL);

	clearStats();

	pos_f = POS_F0;
	v_f = V_F0;
	a_f = A_F0;

	show = 1;
	trail = 1;
	end = 0;
}

/*----------------------------------------------------------------------------------+
 *	endProgram()																	|
 *																					|
 *	Terminates the allegro stuff and destroys the mutexes						 	|
 *----------------------------------------------------------------------------------+
 */

void endProgram()
{
	endGraphics();

	pthread_mutex_destroy(&stat_mutex);
	pthread_mutex_destroy(&coords_mutex);

}

void filter(int32_t x, int32_t y, float32_t period, pred_stat *ps, coords *predicted)
{
	float32_t xf, yf, vx, vy, ax, ay, vxf, vyf, axf, ayf;

		if (ps->xf == 0 && ps->yf == 0) {
			predicted->x = x;
			predicted->y = y;
		}

		xf = pos_f * predicted->x + (1 - pos_f) * x;
		yf = pos_f * predicted->y + (1 - pos_f) * y;

		vx = (xf - predicted->x) / period;
		vy = (yf - predicted->y) / period;

		vxf = v_f * ps->vxf + (1 - v_f) * vx;
		vyf = v_f * ps->vyf + (1 - v_f) * vy;

		ax = (vxf - ps->vxf) / period;
		ay = (vyf - ps->vyf) / period;

		axf = a_f * ps->axf + (1 - a_f) * ax;
		ayf = a_f * ps->ayf + (1 - a_f) * ay;

		ps->xf = xf;
		ps->yf = yf;
		ps->vxf = vxf;
		ps->vyf = vyf;
		ps->axf = axf;
		ps->ayf = ayf;
#ifdef PREDICTION
		predicted->x = ps->xf + ps->vxf * period * 10 + ps->axf * period *period / 2 * 10 * 10;
		predicted->y = ps->yf + ps->vyf * period * 10 + ps->ayf * period *period / 2 * 10 * 10;
#else
		predicted->x = xf;
		predicted->y = yf;
#endif
}

void clearStats() {

	pthread_mutex_lock(&stat_mutex);

	ps.xf = 0;
	ps.yf = 0;
	ps.vxf = 0;
	ps.vyf = 0;
	ps.axf = 0;
	ps.ayf = 0;

	pthread_mutex_unlock(&stat_mutex);

}

void *display_task(void *arg)
{
task_des *td;
pred_stat s;

	td = (task_des *)arg;

	set_period(td);

	while (!end) {

		if (show) {
			pthread_mutex_lock(&coords_mutex);
			if (trail) {
				drawPointTrail(real_c.x, real_c.y, REAL_POINT);
				drawPointTrail(noise_c.x, noise_c.y, NOISE_POINT);
				drawPointTrail(pred_c.x, pred_c.y, PRED_POINT);
			} else {
				drawPoint(real_c.x, real_c.y, REAL_POINT);
				drawPoint(noise_c.x, noise_c.y, NOISE_POINT);
				drawPoint(pred_c.x, pred_c.y, PRED_POINT);
				updateBox();
			}
			pthread_mutex_unlock(&coords_mutex);
		}

		pthread_mutex_lock(&stat_mutex);
		s = ps;
		pthread_mutex_unlock(&stat_mutex);
		drawStats(s, pos_f, v_f, a_f);

		updateInfo();

		check_deadline(td);
		wfp(td);
	}
	pthread_exit(NULL);
}

void *mouse_task(void *arg)
{
task_des *td;

	ps.xf = ps.yf = ps.vxf = ps.vyf = ps.axf = ps.ayf = 0;
	td = (task_des *)arg;

	set_period(td);

	while (!end) {

		pthread_mutex_lock(&coords_mutex);
		real_c.x = mouse_x;
		real_c.y = mouse_y;
		noise_c.x = real_c.x + frand(-MAX_X_NOISE, MAX_X_NOISE);
		noise_c.y = real_c.y + frand(-MAX_Y_NOISE, MAX_Y_NOISE);
		filter(noise_c.x, noise_c.y, (float32_t)(td->period) / 1000, &ps, &pred_c);
		pthread_mutex_unlock(&coords_mutex);

		check_deadline(td);
		wfp(td);
	}
	pthread_exit(NULL);
}

void *keyboard_task(void *arg)
{
task_des *td;

	td = (task_des *)arg;

	set_period(td);

	while (!end) {

		/* key 'ESC' quits the program */
		if (key[KEY_ESC]) end = 1;
		if (key[KEY_C]) clearScreen();
		if (key[KEY_S]) show = (show + 1) % 2;
		if (key[KEY_T]) {
			trail = (trail + 1) % 2;
			clearScreen();
		}
		if (key[KEY_2]) {
			if (pos_f < FILTER_MAX) pos_f += FILTER_STEP;
		}
		if (key[KEY_1]) {
			if (pos_f > FILTER_MIN) pos_f -= FILTER_STEP;
		}
		if (key[KEY_4]) {
			if (v_f < FILTER_MAX) v_f += FILTER_STEP;
		}
		if (key[KEY_3]) {
			if (v_f > FILTER_MIN) v_f -= FILTER_STEP;
		}
		if (key[KEY_6]) {
			if (a_f < FILTER_MAX) a_f += FILTER_STEP;
		}
		if (key[KEY_5]) {
			if (a_f > FILTER_MIN) a_f -= FILTER_STEP;
		}

		check_deadline(td);
		wfp(td);
	}
	pthread_exit(NULL);
}
