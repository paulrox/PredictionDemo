/*
 * graphics.c
 *
 *  Created on: 11/dic/2015
 *      Author: paolo
 */

#include "graphics.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>

#include "globals.h"

int32_t rp_color, np_color, pp_color, txt_color, line_color;
BITMAP *info_buffer, *box_buffer;

void initGraphics()
{

	/* initialize allegro related stuff */
	allegro_init();
	install_keyboard();
	install_mouse();
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	clear_to_color(screen, 0);

	/* initialize used colors*/
	txt_color = makecol(255, 255, 0);		/* yellow color for text */
	line_color = makecol(255, 0, 0);		/* red color for lines */
	np_color = makecol(255, 0, 0);			/* red color for real points */
	rp_color = makecol(0, 255, 0);			/* green color for noise points */
	pp_color = makecol(255, 255, 0);		/* yellow color for predicted points */

	/* initialize screen buffers */
	info_buffer = create_bitmap(INFO_WIDTH, INFO_HEIGHT);
	box_buffer = create_bitmap(BOX_WIDTH, BOX_HEIGHT);

	/* clear screen buffer to black */
	clear_to_color(info_buffer, 0);
	clear_to_color(box_buffer, 0);
}

void endGraphics()
{
	destroy_bitmap(info_buffer);

	allegro_exit();
}

void drawGUI()
{

	line(screen, 0, INFO_POS_Y + INFO_HEIGHT + 1, SCREEN_WIDTH,
			INFO_POS_Y + INFO_HEIGHT + 1, line_color);
	line(screen, INFO_WIDTH + 1, 0, INFO_WIDTH + 1, INFO_HEIGHT + 1, line_color);

	textout_centre_ex(screen, font, "Keyboard Commands", 525, 2, txt_color, 0);
	textout_ex(screen, font, "C : Clear the screen", 350, 20, txt_color, 0);
	textout_ex(screen, font, "S : Hide/Show points", 350, 40, txt_color, 0);
	textout_ex(screen, font, "T: Show the trail", 350, 60, txt_color, 0);
	textout_ex(screen, font, "1, 2: Pos Filter - / +", 550, 20, txt_color, 0);
	textout_ex(screen, font, "3, 4: Speed Filter - / +", 550, 40, txt_color, 0);
	textout_ex(screen, font, "5, 6: Acc Filter - / +", 550, 60, txt_color, 0);
}

void drawPointTrail(int32_t x, int32_t y, uint8_t type)
{
int32_t color;

	if (type == REAL_POINT) color = rp_color;
	if (type == NOISE_POINT) color = np_color;
	if (type == PRED_POINT) color = pp_color;

	scare_mouse();
	circlefill(screen, x, y, 2, color);
	unscare_mouse();
}

void drawPoint(int32_t x, int32_t y, uint8_t type)
{
int32_t color;

	if (type == REAL_POINT) color = rp_color;
	if (type == NOISE_POINT) color = np_color;
	if (type == PRED_POINT) color = pp_color;

	scare_mouse();
	circlefill(box_buffer, x, y - BOX_POS_Y, 2, color);
	unscare_mouse();
}

void drawStats(pred_stat s, float32_t pf, float32_t vf, float32_t af)
{
char str[20];

	sprintf(str, "vx: %.2f", s.vxf);
	textout_centre_ex(info_buffer, font, str, 52, 2, txt_color, 0);
	sprintf(str, "vy: %.2f", s.vyf);
	textout_centre_ex(info_buffer, font, str, 52, 22, txt_color, 0);
	sprintf(str, "ax: %.2f", s.axf);
	textout_centre_ex(info_buffer, font, str, 52, 42, txt_color, 0);
	sprintf(str, "ay: %.2f", s.ayf);
	textout_centre_ex(info_buffer, font, str, 52, 62, txt_color, 0);
	sprintf(str, "pos_filter: %.2f", pf);
	textout_centre_ex(info_buffer, font, str, 180, 2, txt_color, 0);
	sprintf(str, "v_filter: %.2f", vf);
	textout_centre_ex(info_buffer, font, str, 180, 22, txt_color, 0);
	sprintf(str, "a_filter: %.2f", af);
	textout_centre_ex(info_buffer, font, str, 180, 42, txt_color, 0);
}

void updateBox()
{
	blit(box_buffer, screen, 0, 0, BOX_POS_X, BOX_POS_Y, BOX_WIDTH, BOX_HEIGHT);
	clear_to_color(box_buffer, 0);
}

void updateInfo()
{
	blit(info_buffer, screen, 0, 0, INFO_POS_X, INFO_POS_Y, INFO_WIDTH, INFO_HEIGHT);
	clear_to_color(info_buffer, 0);
}

void clearScreen()
{
	clear_to_color(screen, 0);
	drawGUI();
}
