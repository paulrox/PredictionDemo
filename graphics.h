/*
 * graphics.h
 *
 *  Created on: 11/dic/2015
 *      Author: paolo
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <allegro.h>

#include "globals.h"

void initGraphics();
void endGraphics();
void drawGUI();
void drawPointTrail(int32_t x, int32_t y, uint8_t type);
void drawPoint(int32_t x, int32_t y, uint8_t type);
void drawStats(pred_stat s, float32_t pf, float32_t vf, float32_t af);
void clearScreen();
void updateBox();
void updateInfo();
#endif /* GRAPHICS_H_ */
