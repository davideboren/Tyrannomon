//This file is auto-generated by Digitizer

#ifndef _MONSTER_DEFS_H_
#define _MONSTER_DEFS_H_

#include <Arduino.h>

enum MonsterName {
Empty,
PicoDevi_Digitama,
Mokumon,
PetiMeramon,
Candmon,
Ghostmon,
PicoDevimon,
RandomEgg
};

enum MonsterStage {
	digitama,
    baby,
    baby_ii,
    child,
    adult,
    perfect,
    ultimate,
    armor
};

struct MonsterRef {
        String filepath;
        MonsterName name;
        MonsterStage stage;
        int lifespan;
        String move_style;
        int speed;
        String bg;
        MonsterName evos[8];
};

static const MonsterRef MonsterDB[] = {
{
	"sprites/digitama/Agu2006_Digitama.bmp",
	Empty,
	digitama,
	0,
	"walk",
	2,
	"None",
	{Empty}
},
{
	"sprites/digitama/PicoDevi_Digitama.bmp",
	PicoDevi_Digitama,
	digitama,
	60,
	"walk",
	0,
	"bg/bg_spooky.bmp",
	{Mokumon}
},
{
	"sprites/baby/Mokumon.bmp",
	Mokumon,
	baby,
	120,
	"walk",
	2,
	"bg/bg_spooky.bmp",
	{PetiMeramon}
},
{
	"sprites/baby_ii/PetiMeramon.bmp",
	PetiMeramon,
	baby_ii,
	180,
	"walk",
	2,
	"bg/bg_spooky.bmp",
	{PicoDevimon, Candmon, Ghostmon}
},
{
	"sprites/child/Candmon.bmp",
	Candmon,
	child,
	240,
	"walk",
	2,
	"bg/bg_spooky.bmp",
	{RandomEgg}
},
{
	"sprites/child/Ghostmon.bmp",
	Ghostmon,
	child,
	240,
	"walk",
	2,
	"bg/bg_spooky.bmp",
	{RandomEgg}
},
{
	"sprites/child/PicoDevimon.bmp",
	PicoDevimon,
	child,
	240,
	"walk",
	2,
	"bg/bg_spooky.bmp",
	{RandomEgg}
},
{
	"sprites/adult/Tyrannomon.bmp",
	RandomEgg,
	adult,
	0,
	"walk",
	2,
	"bg/bg_0.bmp",
	{PicoDevi_Digitama}
}
};
#endif //_MONSTER_DEFS_H_