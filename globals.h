/*
 * globals.h
 *
 *  Created on: 11/dic/2015
 *      Author: paolo
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

/* TASKS GLOBALS */

#define TASK_NUM 		3
#define DISPLAY_INDEX	0
#define DISPLAY_PER		35
#define DISPLAY_DL		DISPLAY_PER
#define DISPLAY_PRIO	30
#define MOUSE_INDEX		1
#define MOUSE_PER		80
#define MOUSE_DL		MOUSE_PER
#define MOUSE_PRIO		29
#define KEYBOARD_INDEX	2
#define KEYBOARD_PER	100
#define KEYBOARD_DL		KEYBOARD_PER
#define KEYBOARD_PRIO	28
#define REAL_POINT		0
#define NOISE_POINT		1
#define PRED_POINT		2

/* DISPLAY GLOBALS */

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define BOX_HEIGHT		498
#define BOX_WIDTH		800
#define BOX_POS_X		0
#define BOX_POS_Y		102
#define INFO_WIDTH		300
#define INFO_HEIGHT		100
#define INFO_POS_X		0
#define INFO_POS_Y		0

/* OTHER GLOBALS */

#define MAX_X_NOISE		20
#define MAX_Y_NOISE		20
#define POS_F0			0.8
#define V_F0			0.8
#define A_F0			0.8
#define FILTER_MAX		0.99
#define FILTER_MIN		0.00
#define FILTER_STEP		0.01

#define PREDICTION

typedef				char	char_t;
typedef signed		char	int8_t;
typedef signed		short	int16_t;
typedef signed 		int		int32_t;
typedef signed 		long	int64_t;
typedef unsigned 	char	uint8_t;
typedef unsigned 	short	uint16_t;
typedef unsigned 	int		uint32_t;
typedef unsigned 	long	uint64_t;
typedef 			float	float32_t;
typedef 			double 	float64_t;
typedef long		double 	float128_t;

typedef struct _coords {
	int32_t x;
	int32_t y;
} coords;

typedef struct _pred_stat {
	float32_t xf;
	float32_t yf;
	float32_t vxf;
	float32_t vyf;
	float32_t axf;
	float32_t ayf;
} pred_stat;

#endif /* GLOBALS_H_ */
