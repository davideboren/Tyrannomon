#ifndef _MONSTER_DEFS_H_
#define _MONSTER_DEFS_H_

#include <Arduino.h>

enum MonsterName {
Empty,
Tyrannomon
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
String filename;
MonsterName evos[8];
int speed;
};

static const MonsterRef MonsterDB[] = {
{
	"null", 
	{Tyrannomon},
	2
},{
	"sprites/adult/Tyrannomon.bmp",
	{Tyrannomon},
	2
}
};
#endif //_MONSTER_DEFS_H_