#ifndef _MONSTER_DEFS_H_
#define _MONSTER_DEFS_H_

#include <Arduino.h>

enum MonsterName {
Empty,
Agu2006_Digitama,
Botamon,
Koromon
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
	"walk",
	2,
	"None",
	{Agu2006_Digitama}
},
{
	"sprites/digitama/Agu2006_Digitama.bmp",
	Agu2006_Digitama,
	digitama,
	"walk",
	2,
	"None",
	{Botamon}
},
{
	"sprites/baby/Botamon.bmp",
	Botamon,
	baby,
	"walk",
	2,
	"None",
	{Koromon}
},
{
	"sprites/baby_ii/Koromon.bmp",
	Koromon,
	baby_ii,
	"walk",
	2,
	"None",
	{Agu2006_Digitama}
}
};
#endif //_MONSTER_DEFS_H_