#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <Arduino.h>
#include <Entity.h>
#include <global.h>
#include <MonsterDefs.h>

#include "../lib/MrBitmap/MrBitmap.h"
#include "../lib/TFT_eSprite_X/TFT_eSprite_X.h"

class Monster : public Entity{

    public:
        Monster();
        Monster(MonsterName name);

        MonsterName _name;
        int _age, _lifespan;

        void setCharacter(MonsterName name);
        void update();

};

#endif //_MONSTER_H_