#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <TFT_eSPI.h>
#include <EventQueue.h>

//Monster Spritesheet Coordinates
#define SPR_HATCH_X 32*2
#define SPR_HATCH_Y 0*2
#define SPR_STAND1_X 0*2
#define SPR_STAND1_Y 0*2
#define SPR_STAND2_X 16*2
#define SPR_STAND2_Y 0*2
#define SPR_SHOUT_X 32*2
#define SPR_SHOUT_Y 0*2
#define SPR_HAPPY_X 16*2
#define SPR_HAPPY_Y 32*2
#define SPR_ANGRY_X 32*2
#define SPR_ANGRY_Y 48*2
#define SPR_ATTACK_X 32*2
#define SPR_ATTACK_Y 32*2

extern TFT_eSPI tft;

extern EventQueue queue;

#endif // _GLOBAL_H_